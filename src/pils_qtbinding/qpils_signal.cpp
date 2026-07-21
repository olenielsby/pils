#include "rule.h"
#include "qpils_signal.h"
#include "qpils_thread.h"
#include "qpils_plumming.h"
#include "qpils_qobject_wrapper.h"
#include "qpils_event.h"
namespace PILS{

    bool QtSignalEventClicheExtractor::convert(const Closure &closure)
    {
        const Ruleset &ruleset = static_cast<const Ruleset &>(*closure.element[1]);
        const ListExpress &rules = static_cast<const ListExpress &>(*ruleset.element[0]);
        size_t count = rules.count->value;
        for (size_t i = 0; i < count; i++)
        {
            const Rule &rule = static_cast<const Rule &>(*rules.element[i]);
            ExtractFromPattern extract;
            rule.element[0]->convert(extract);
            if (extract.signalCliche)
                signalCliches.emplace(extract.signalCliche);
            if (extract.eventCliche)
                eventMask |= extract.eventCliche->mask;
        }
        return !signalCliches.empty();
    }

    bool QtSignalEventClicheExtractor::ExtractFromPattern::convert(const Cliche &cliche, const Any *const *value)
    {
        // TODO: allow aliases in pattern
        return cliche.platformConvert(*this);
    }

    bool QtSignalCliche::platformConvert(PlatformSpecificConverter &converter) const
    {
        return converter.converting(*this);
    }

    bool QtSignalEventClicheExtractor::ExtractFromPattern::converting(const QtSignalCliche &cliche)
    {
        signalCliche = &cliche;
        return true;
    }

    const ClicheTiny *QtSignalName::newCliche() const
    {
        return new const QtSignalCliche(this);
    }

    const QtSignalName *QtSignalName::get(const char *name)
    {
        const PilsString *string = PilsString::get(name);
        Namespace_QtSignal::singleton.uri->retain();
        const ClicheShort *signalName = Namespace_QtSignal::singleton.uri->clichefy(string);
        assert(dynamic_cast<const QtSignalName *>(signalName));
        return static_cast<const QtSignalName *>(signalName);
    }

    const QtSignalCliche *QtSignalCliche::get(const char *name)
    {
        const ClicheShort *signalName = QtSignalName::get(name);
        const ClicheTiny *signalCliche = signalName->clichefy();
        assert(dynamic_cast<const QtSignalCliche *>(signalCliche));
        return static_cast<const QtSignalCliche *>(signalCliche);
    }

    void QtObjectWrapper::pilsSignalCallback(const QtSignalCliche *cliche, const Constant **args, size_t argc) const
    {
        const Constant *arg = (argc == 1 ? args[0] : ListConstant::get(args, argc));
        const NodeConstantShort *call = cliche->nodeConstant(arg);
        // call->writeToDebugOutput(10);
        if (!when) return;
        PilsThread *thread = MainThread::singleton;
        assert(thread);
        assert(QThread::currentThread() == thread->qThread);
        PilsThread::RunLevel running(thread);
        Runner &run = running.run();
        when->retain();
        run.calling.who = this;
        retain();
        run.calling.what = (const Express *)this;
        new (run.allocate(sizeof(SinkQtSignalCallback))) SinkQtSignalCallback(run.where_);
        run.where_ = when;
        run.run(call->caller(*thread, *when));
        run.release(call);
        run.release(this);
    }

    Sink *SinkQtSignalCallback::kick(Runner &run)
    {
        run.release(run.where_);
        run.where_ = whence;
        return this + 1;
    }

    const Step *SinkQtSignalCallback::pass(Runner &run, const Any *value)
    {
        run.release(value);
        run.sink = kick(run);
        return nullptr;
    }

    const Step *SinkQtSignalCallback::miss(Runner &run)
    {
        while (run.sink != this) run.sink = run.sink->kick(run);
        run.sink = kick(run);
        return nullptr;
    }
}
