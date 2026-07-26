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
                                     QtNewObjectWrapper* wrapper,
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

template<typename Obj, typename Signal, Signal signal, bool Blind = false>
struct QtSignalImpl : QtSignalImplementation
{
    QtSignalImpl(const QtSignalImplementation* next)
        : QtSignalImplementation(&Obj::staticMetaObject, next) {}
    bool connectIfCompatible(QObject* obj,
                             QtNewObjectWrapper* wrapper,
                             const QtSignalCliche* cliche) const override
    {
        if (!obj->metaObject()->inherits(meta))
            return false;

        auto* casted = static_cast<Obj*>(obj);

        QPointer<QtNewObjectWrapper> safeWrapper(wrapper);

        QObject::connect(
            casted,
            signal,
            qApp,
            [safeWrapper, cliche](auto&&... args)
            {
                if (!safeWrapper)
                    return;

                if constexpr (Blind)
                {
                    safeWrapper->pilsSignalCallback(cliche, nullptr, 0);
                }
                else
                {
                    const Constant* argv[] = {
                        QtWrap::wrap(args)...
                    };

                    safeWrapper->pilsSignalCallback(
                        cliche,
                        argv,
                        sizeof...(args));
                }
            },
            Qt::QueuedConnection);

        return true;
    }
};

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
