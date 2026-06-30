#pragma once
#include <QApplication>
#include "qpils_plumming.h"
#include "qpils_converter.h"
#include "qpils_qobject_wrapper.h"
namespace PILS{

class QtEventCliche;

class QtEventClicheExtractor : public Converter
{
public:
    bool convert(const Closure &closure) override;
    uint64_t eventFilter = 0;
private:
    class ExtractFromPattern : public Converter
    {
    public:
        const QtEventCliche *found = nullptr;
        bool convert(const Cliche &cliche, const Any *const *value) override;
    };
};

struct QtEventImplementation
{
    const QMetaObject* meta;
    const QtEventImplementation* next;

    QtEventImplementation(const QMetaObject* m,
                           const QtEventImplementation* n)
        : meta(m), next(n) {}

    virtual bool connectIfCompatible(QObject* obj,
                                     QtObjectWrapper* wrapper,
                                     const QtEventCliche* cliche) const = 0;
};

using QtEventImplement = void(*)(QEvent*, const QtObjectWrapper*, const QtEventCliche*);

class QtEventCliche
    : public ClicheTiny
{
public:
    static const PilsString *namespace_;
    static const QtEventCliche* eventTable[QEvent::MaxUser + 1];
    static void initialize();
    static void initializeNamespace();
    uint64_t mask;
    QtEventImplement impl;
    bool platformConvert(PlatformSpecificConverter &converter) const override;
private:
    inline static uint64_t maskShifter = 1;
    QtEventCliche(QEvent::Type type, const char *name, QtEventImplement impl)
        : ClicheTiny(getEventName(name)), mask(maskShifter), impl(std::move(impl))
    {
        assert(type >= 0 && type <= QEvent::MaxUser);
        assert(maskShifter != 0);
        eventTable[type] = this;
        maskShifter <<= 1;
    }

    inline static const ClicheShort *getEventName(const char *name)
    {
        std::string s(name);

        if (!s.empty())
            s[0] = std::tolower(static_cast<unsigned char>(s[0]));

        return namespace_->clichefy(PilsString::get(s.c_str()));
    }
};

class EventListener
{
public:
    QtObjectWrapper *wrapper;
    const Closure *closure;
    QByteArray EventName;

    EventListener(QtObjectWrapper *w,
                   const Closure *c,
                   const QByteArray &name)
        : wrapper(w), closure(c), EventName(name)
    {}
};

class SinkQtEventCallback
    : Sink
{
public:
    SinkQtEventCallback(const Any *whence, bool &wasHandled)
        : whence(whence), wasHandled(wasHandled)
    {}
    Sink *kick(Runner &run) override;
    const Step *pass(Runner &run, const Any *thing) override;
    const Step *miss(Runner &run) override;
private:
    const Any *whence;
    bool &wasHandled;
};

class QtEventFilterProxy : public QObject
{
public:
    QtEventFilterProxy(const QtObjectWrapper *wrapper, QObject *parent);
    ~QtEventFilterProxy();
    bool eventFilter(QObject *watched, QEvent *event) override;
    const QtObjectWrapper *wrapper;
};

}
