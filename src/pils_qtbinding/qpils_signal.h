#pragma once
#include <QApplication>
#include <QDockWidget>
#include "qpils_plumming.h"
#include "qpils_converter.h"
#include "qpils_qobject_wrapper.h"
namespace PILS{

class QtSignalCliche;
class QtEventCliche;

class QtSignalEventClicheExtractor : public Converter
{
public:
    bool convert(const Closure &closure) override;
    std::set<const QtSignalCliche*> signalCliches;
    int64_t eventMask = 0;
private:
    class ExtractFromPattern : public PlatformSpecificConverter
    {
    public:
        const QtSignalCliche *signalCliche = nullptr;
        const QtEventCliche *eventCliche = nullptr;
        bool convert(const Cliche &cliche, const Any *const *value) override;
        bool converting(const QtSignalCliche &argument) override;
        bool converting(const QtEventCliche &argument) override;
    };
};

struct QtSignalImplementation
{
    const QMetaObject* meta;
    const QtSignalImplementation* next;

    QtSignalImplementation(const QMetaObject* m,
                           const QtSignalImplementation* n)
        : meta(m), next(n) {}

    virtual bool connectIfCompatible(QObject* obj,
                                     QtObjectWrapper* wrapper,
                                     const QtSignalCliche* cliche) const = 0;
};

class QtSignalCliche
    : public ClicheTiny
{
public:
    QtSignalCliche(const QtSignalName *head)
        : ClicheTiny(head)
    {}
    bool platformConvert(PlatformSpecificConverter &converter) const override;
    mutable const QtSignalImplementation* implementations = nullptr;
    const QtSignalCliche* add(QtSignalImplementation* impl) const
    {
        impl->next = implementations;
        implementations = impl;
        return this;
    }
    static const QtSignalCliche *get(const char *name);
};

template<typename Obj, typename Signal, Signal signal>
struct QtSignalImpl : QtSignalImplementation
{
    QtSignalImpl(const QtSignalImplementation* next)
        : QtSignalImplementation(&Obj::staticMetaObject, next) {}

    bool connectIfCompatible(QObject* obj,
                             QtObjectWrapper* wrapper,
                             const QtSignalCliche* cliche) const override
    {
        if (!obj->metaObject()->inherits(meta))
            return false;
        auto* casted = static_cast<Obj*>(obj);
        QObject::connect(casted, signal,
                         qApp,
                         [wrapper, cliche](auto&&... args)
                         {
                             wrapper->retain();
                             auto args_copy = std::make_tuple(args...);
                             QMetaObject::invokeMethod(qApp,
                                                       [wrapper, cliche, args_copy]() mutable
                                                       {
                                                           std::apply([&](auto&&... unpacked)
                                                                      {
                                                                          const Constant* argv[] = {
                                                                              QtWrap::wrap(unpacked)...
                                                                          };
                                                                          wrapper->pilsSignalCallback(cliche, argv, sizeof...(unpacked));
                                                                      }, args_copy);
                                                           wrapper->release();
                                                       },
                                                       Qt::QueuedConnection);
                         });
        return true;
    }
};

// class SignalListener
// {
// public:
//     const QtObjectWrapper *wrapper;
//     const Closure *closure;
//     QByteArray signalName;

//     SignalListener(const QtObjectWrapper *w,
//                    const Closure *c,
//                    const QByteArray &name)
//         : wrapper(w), closure(c), signalName(name)
//     {}

//     template<typename... Args>
//     void handle(Args&&... args)
//     {
//         std::vector<const Any*> pilsArgs;

//         // (pilsArgs.push_back(
//         //      wrapper->convertFromQt(
//         //          &args,
//         //          QMetaType::fromType<std::decay_t<Args>>()
//         //          )
//         //      ), ...);

//         // const Any *node =
//         //     wrapper->buildSignalNode(signalName, pilsArgs);

//         // wrapper->invokeClosure(closure, node);
//     }
// };

class SinkQtSignalCallback
    : Sink
{
public:
    SinkQtSignalCallback(const Any *whence)
        : whence(whence)
    {}
    Sink *kick(Runner &run) override;
    const Step *pass(Runner &run, const Any *thing) override;
    const Step *miss(Runner &run) override;
private:
    const Any *whence;
};
}
