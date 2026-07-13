#pragma once
#include "qpils_qobject_wrapper.h"
#include "qpils_converter.h"
#include "qpils_signal.h"
#include <tuple>
#include <type_traits>
#include <QDialog>
#include <QWidget>
#include <QMainWindow>
#include <QDialog>
#include <QApplication>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QScrollBar>
#include <QPushButton>
#include <QToolButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QTimer>
#include <QScrollArea>
#include <QGroupBox>
#include <QLabel>
#include <QProgressBar>
#include <QLayout>

#include <QTabWidget>
#include <QStackedWidget>
#include <QSplitter>

#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QShortcut>

#include <QListView>
#include <QTreeView>
#include <QTableView>

#include <QFileDialog>
#include <QMessageBox>

#include <QNetworkAccessManager>
#include <QNetworkReply>
namespace PILS
{

// ===== MethodTraits =====

template<typename>
struct MethodTraits;

// non-const
template<typename C, typename R, typename... Args>
struct MethodTraits<R(C::*)(Args...)>
{
    using Class = C;
    using Return = R;
    using ArgsTuple = std::tuple<Args...>;
    static constexpr size_t Arity = sizeof...(Args);
};

// const
template<typename C, typename R, typename... Args>
struct MethodTraits<R(C::*)(Args...) const>
{
    using Class = C;
    using Return = R;
    using ArgsTuple = std::tuple<Args...>;
    static constexpr size_t Arity = sizeof...(Args);
};

template<typename Method, size_t... I>
bool qtInvokeHelper(
    QObject* obj,
    Method method,
    const Any* const* args,
    size_t argc,
    const Any*& result,
    std::index_sequence<I...>)
{
    using Traits = MethodTraits<Method>;
    using Class = typename Traits::Class;

    auto* casted = static_cast<Class*>(obj);

    std::tuple<std::decay_t<std::tuple_element_t<I, typename Traits::ArgsTuple>>...> unpacked;

    bool ok = (QtFill::fill(args[I], std::get<I>(unpacked)) && ...);
    if (!ok)
        return false;

    if constexpr (std::is_void_v<typename Traits::Return>)
    {
        std::apply([&](auto&&... a) {
            (casted->*method)(a...);
        }, unpacked);

        result = nullptr;
        return true;
    }
    else
    {
        auto ret = std::apply([&](auto&&... a) {
            return (casted->*method)(a...);
        }, unpacked);

        result = QtWrap::wrap(ret);
        return true;
    }
}

template<typename Method>
QtMethodName::Invoker makeQtInvoker(Method method)
{
    using Traits = MethodTraits<Method>;

    return [method](QObject* obj,
                    const Any* const* args,
                    size_t argc,
                    const Any*& result) -> bool
    {
        if (!obj)
            return false;

        if (argc != Traits::Arity)
            return false;

        return qtInvokeHelper(
            obj,
            method,
            args,
            argc,
            result,
            std::make_index_sequence<Traits::Arity>{});
    };
}

template<typename Method>
struct QtMethodRegistrar
{
    QtMethodRegistrar(const char* name, Method method, const char *className = nullptr)
    {
        using Traits = MethodTraits<Method>;
        using Class = typename Traits::Class;

        QtMethodName::get(name)->implement(
            &Class::staticMetaObject,
            makeQtInvoker(method),
            className);
    }
};

#define METHOD_(CLASS, METHOD) \
QtMethodRegistrar(#METHOD, &CLASS::METHOD);

#define METHOD_OVERLOAD(CLASS, METHOD, SIGNATURE) \
QtMethodRegistrar(#METHOD, static_cast<SIGNATURE>(&CLASS::METHOD));

#define EXACT_METHOD(CLASS, METHOD) \
QtMethodRegistrar(#METHOD, &CLASS::METHOD, #CLASS);

#define EXACT_METHOD_OVERLOAD(CLASS, METHOD, SIGNATURE) \
QtMethodRegistrar(#METHOD, static_cast<SIGNATURE>(&CLASS::METHOD), #CLASS);

const QtObjectClassName *QtObjectClassName::registerQtClass(char const *qName, const QMetaObject &meta)
{
    const PilsString *name = PilsString::get(qName+1);
    const Namespace_QtClass *ns = Namespace_QtClass::singleton;
    ns->retain();
    return new QtObjectClassName(ClicheShort::hashChain(ns, name), ns, name, &meta);
}

// --- Class registration + constructor DSL ---

#define BEGIN_CLASS(CLASS) \
{ \
        auto classEntry = registerQtClass(#CLASS, CLASS::staticMetaObject);

#define END_CLASS() }

#define CONSTRUCTOR_NOARGS(CLASS) \
    classEntry->constructors = \
        new QtConstructorImpl0<CLASS>(classEntry->constructors);

#define CONSTRUCTOR_ARGS(CLASS, ...) \
    classEntry->constructors = \
        new QtConstructorImpl<CLASS, __VA_ARGS__>(classEntry->constructors);

#define SIGNAL_(CLASS, SIGNAL_NAME) \
QtSignalCliche::get(#SIGNAL_NAME)->add( \
    new QtSignalImpl<CLASS, \
                     decltype(&CLASS::SIGNAL_NAME), \
                                                        &CLASS::SIGNAL_NAME>( \
                                                                               QtSignalCliche::get(#SIGNAL_NAME)->implementations));

#define BLIND_SIGNAL(CLASS, SIGNAL_NAME) \
QtSignalCliche::get(#SIGNAL_NAME)->add( \
    new QtSignalImpl<CLASS, \
                     decltype(&CLASS::SIGNAL_NAME), \
                                                        &CLASS::SIGNAL_NAME, true>( \
                                                                               QtSignalCliche::get(#SIGNAL_NAME)->implementations));


#define SIGNAL_OVERLOAD(CLASS, SIGNAL_NAME, SIGNATURE) \
QtSignalCliche::get(#SIGNAL_NAME)->add( \
    new QtSignalImpl<CLASS, SIGNATURE, \
                     static_cast<SIGNATURE>(&CLASS::SIGNAL_NAME)>( \
                                                          QtSignalCliche::get(#SIGNAL_NAME)->implementations));



}