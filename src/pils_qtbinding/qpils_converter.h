#pragma once
#include "qpils_plumming.h"
#include "qobject.h"
#include <QMouseEvent>
#include <type_traits>
#include <QTextCursor>

namespace PILS {

class NeQPoint;
class NeQSize;
class NeQRect;
class NeQImage;
class NeQByteArray;
class NeQTransform;
class QtObjectWrapper;

class PlatformSpecificConverter : public Converter
{
public:
    bool convert(const ReallySpecial &argument) override;
    bool convert(const PlatformSpecializedNodeConstantTiny &argument) override;
    virtual bool converting(const Cliche &argument) {return false;}
    virtual bool converting(const QtObjectWrapper &argument) {return false;}
    virtual bool converting(const NeQPoint &argument) {return false;}
    virtual bool converting(const NeQSize &argument) {return false;}
    virtual bool converting(const NeQRect &argument) {return false;}
    virtual bool converting(const NeQImage &argument) {return false;}
    virtual bool converting(const NeQByteArray &argument) {return false;}
    virtual bool converting(const NeQTransform &argument) {return false;}
    virtual bool converting(const QtSignalCliche &argument) {return false;}
    virtual bool converting(const QtEventCliche &argument) {return false;}
    static QObject* getObject(const QtObjectWrapper &wrap);
};

class QtImageConverter
    : public PlatformSpecificConverter
{
public:
    explicit QtImageConverter(QImage &out) : out(out) {}
    bool converting(const NeQImage &argument) override;
private:
    QImage &out;
};

template<typename T>
class QObjectConverter : public PlatformSpecificConverter
{
public:
    QObjectConverter(T*& t) : target(t) {}
    bool converting(const QtObjectWrapper &argument) override
    {
        QObject *object = getObject(argument);
        if (object == nullptr)
            return false;
        if (!object->metaObject()->inherits(&T::staticMetaObject))
            return false;
        target = static_cast<T*>(object);
        return true;
    }
private:
    T*& target;
};

class QtFill
{
public:
    static bool fill(const Any *a, int &out);
    static bool fill(const Any *a, double &out);
    static bool fill(const Any *a, bool &out);
    static bool fill(const Any *a, QString &out);
    static bool fill(const Any *a, QByteArray &out);
    static bool fill(const Any *a, QColor &out);
    static bool fill(const Any *a, QImage &out);
    static bool fill(const Any *a, QIcon &out);
    static bool fill(const Any *a, QPixmap &out);
    static bool fill(const Any *a, QVariant &out);
    static bool fill(const Any *a, QKeySequence &out);
    static bool fill(const Any* a, QList<int>& out);
    static bool fill(const Any* a, QTextCursor& out);
    template<typename T>
    static bool fill(const Any* a, T*& out)
    {
        QObjectConverter<T> conv(out);
        return a->convert(conv);
    }
    template<typename T>
    static std::enable_if_t<std::is_enum_v<T>, bool>
    fill(const Any* a, T& out)
    {
        int v;
        if (!fill(a, v))
            return false;

        out = static_cast<T>(v);
        return true;
    }
    template<typename Enum>
    static bool fill(const Any* a, QFlags<Enum>& out)
    {
        int v;
        if (!fill(a, v)) return false;

        out = QFlags<Enum>(static_cast<Enum>(v));
        return true;
    }
};

class QtWrap
{
public:
    static const Constant *wrap(const QString &s);
    static const Constant *wrap(QObject *obj);
    static const Constant *wrap(int v);
    static const Constant *wrap(double v);
    static const Constant *wrap(bool v);
    static const Constant *wrap(const char* s);
    static const Constant *wrap(const QMouseEvent &e);
    static const Constant *wrap(const QKeyEvent &e);
    static const Constant *wrap(const QResizeEvent &e);
    static const Constant *wrap(const QWheelEvent &e);
    static const Constant *wrap(const QFocusEvent &e);
    static const Constant *wrap(const Qt::MouseButton &e);
    static const Constant *wrap(const Qt::KeyboardModifier &e);
    static const Constant *wrap(const QTextCursor &e);
    template<typename Enum>
    static const Constant *wrap(QFlags<Enum> flags)
    {
        return wrap(static_cast<int>(flags));
    }
    template<typename T>
    static const Constant *wrap(const T &)
    {
        return PilsString::get(typeid(T).name());
    }

    template<typename T>
    static std::enable_if_t<std::is_base_of_v<QObject, T>, const Constant*>
    wrap(T* obj)
    {
        return wrap(static_cast<QObject*>(obj));
    }
};

    struct QtConstructorImplementation
    {
        const QtConstructorImplementation* next;
        QtConstructorImplementation(const QtConstructorImplementation* next)
            : next(next) {}
        virtual QObject* construct(const Any* const argv[], size_t argc) const = 0;
    };

    template<typename Obj, typename... Args>
    struct QtConstructorImpl : QtConstructorImplementation
    {
        QtConstructorImpl(const QtConstructorImplementation* next)
            : QtConstructorImplementation(next) {}

        QObject* construct(const Any* const argv[], size_t argc) const override
        {
            if (argc != sizeof...(Args))
                return nullptr;

            std::tuple<std::decay_t<Args>...> values;

            if (!fillAll(argv, values, std::index_sequence_for<Args...>{}))
                return nullptr;

            return std::apply([](auto&&... v) {
                return new Obj(std::forward<decltype(v)>(v)...);
            }, values);
        }
    private:
        template<size_t... I>
        bool fillAll(const Any* const argv[],
                     std::tuple<std::decay_t<Args>...>& values,
                     std::index_sequence<I...>) const
        {
            return (QtFill::fill(argv[I], std::get<I>(values)) && ...);
        }
    };

    template<typename Obj>
    struct QtConstructorImpl0 : QtConstructorImplementation
    {
        QtConstructorImpl0(const QtConstructorImplementation* next)
            : QtConstructorImplementation(next) {}
        QObject* construct(const Any* const* args, size_t argc) const override
        {
            if (argc != 0)
                return nullptr;
            return new Obj();
        }
    };
}