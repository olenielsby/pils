#include "rule.h"
#include "qpils_event.h"
#include "qpils_thread.h"
#include "qpils_plumming.h"
#include "qpils_signal.h"
namespace PILS{

    const QtEventCliche* QtEventCliche::eventTable[QEvent::MaxUser + 1] = {};

    bool QtEventCliche::platformConvert(PlatformSpecificConverter &converter) const
    {
        return converter.converting(*this);
    }

    bool QtSignalEventClicheExtractor::ExtractFromPattern::converting(const QtEventCliche &cliche)
    {
        eventCliche = &cliche;
        return true;
    }

    bool QtObjectWrapper::pilsEventCallback(const QtEventCliche *cliche, const Constant *arg) const
    {
        PilsThread *thread = MainThread::singleton;
        assert(thread);
        if (when == nullptr || QThread::currentThread() != thread->qThread)
        {
            run.release(arg);
            return false;
        }
        bool eventWasHandled = false;
        const NodeConstantShort *call = cliche->nodeConstant(arg);
        PilsThread::RunLevel running(thread);
        Runner &run = running.run();
        when->retain();
        run.calling.who = this;
        retain();
        run.calling.what = (const Express *)this;
        new (run.allocate(sizeof(SinkQtEventCallback))) SinkQtEventCallback(run.where_, eventWasHandled);
        run.where_ = when;
        run.run(call->caller(*thread, *when));
        run.release(call);
        run.release(this);
        return eventWasHandled;
    }

    Sink *SinkQtEventCallback::kick(Runner &run)
    {
        run.release(run.where_);
        run.where_ = whence;
        return this + 1;
    }

    const Step *SinkQtEventCallback::pass(Runner &run, const Any *value)
    {
        run.release(value);
        run.sink = kick(run);
        wasHandled = true;
        return nullptr;
    }

    const Step *SinkQtEventCallback::miss(Runner &run)
    {
        while (run.sink != this) run.sink = run.sink->kick(run);
        run.sink = kick(run);
        return nullptr;
    }

    QtEventFilterProxy::QtEventFilterProxy(const QtObjectWrapper *wrapper, QObject *parent)
        : QObject(parent), wrapper(wrapper)
    {
    }

    QtEventFilterProxy::~QtEventFilterProxy()
    {
        if (wrapper)
        {
            wrapper->eventFilterProxy = nullptr;
            wrapper = nullptr;
        }
    }

    bool QtEventFilterProxy::eventFilter(QObject *watched, QEvent *event)
    {
        if (!wrapper)
            return false;

        const QtEventCliche *c = QtEventCliche::eventTable[event->type()];
        if (!c)
            return false;

        if (!(wrapper->eventMask & c->mask))
            return false;

        // dispatch til PILS
        c->impl(event, wrapper, c);

        return false; // true hvis event skal stoppes
    }
}
