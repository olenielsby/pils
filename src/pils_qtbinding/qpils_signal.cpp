#include "rule.h"
#include "qpils_signal.h"
#include "qpils_thread.h"
#include "qpils_plumming.h"
#include "qpils_qobject_wrapper.h"
namespace PILS{

    bool QtSignalClicheExtractor::convert(const Closure &closure)
    {
        const Ruleset &ruleset = static_cast<const Ruleset &>(*closure.element[1]);
        const ListExpress &rules = static_cast<const ListExpress &>(*ruleset.element[0]);
        size_t count = rules.count->value;
        for (size_t i = 0; i < count; i++)
        {
            const Rule &rule = static_cast<const Rule &>(*rules.element[i]);
            ExtractFromPattern extract;
            if (rule.element[0]->convert(extract))
                cliches.emplace(extract.found);
        }
        return !cliches.empty();
    }

    bool QtSignalClicheExtractor::ExtractFromPattern::convert(const Cliche &cliche, const Any *const *value)
    {
        // TODO: allow aliases in pattern
        if (cliche.as_ClicheTiny() == nullptr)
            return false;
        if (auto name = cliche.head->as_ClicheShort())
        {
            const Any *ns = Namespace_QtSignal::singleton;
            const Any *nh = name->head;
            if (name->head != Namespace_QtSignal::singleton || name->attributes[0]->as_String() == nullptr)
                return false;
            found = static_cast<const QtSignalCliche *>(&cliche);
            return true;
        }
        return false;
    }

    const ClicheTiny *QtSignalName::newCliche() const
    {
        return new const QtSignalCliche(this);
    }

    const QtSignalName *QtSignalName::get(const char *name)
    {
        const PilsString *string = PilsString::get(name);
        Namespace_QtSignal::singleton->retain();
        const ClicheShort *signalName = Namespace_QtSignal::singleton->clichefy(string);
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

    // const Any *CallbackHelperBase::pilsCall(const Any *call) const
    // {
    //     if (!who->when) return nullptr;
    //     PilsThread *thread = PilsThread::RunLevel::getCurrent(this->thread);
    //     PilsThread::RunLevel running(thread);
    //     Runner &run = running.run();
    //     const Any *result = nullptr;
    //     who->when->addReference();
    //     JuceObject *who = this->who;
    //     run.calling.who = who;
    //     who->addReference();
    //     run.calling.what = (const Express *)who;
    //     new (run.allocate(sizeof(SinkJuceCallback))) SinkJuceCallback(result, run.where_);
    //     run.where_ = who->when;
    //     run.run(call->caller(*thread, *who->when));
    //     call->releaseReference();
    //     if (result)
    //         who->alert();
    //     who->releaseReference();
    //     thread->releaseReference();
    //     return result;
    // }


    void QtObjectWrapper::pilsCallback(const QtSignalCliche *cliche, const Constant **args, size_t argc)
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
        call->release();
        release();
    }

    Sink *SinkQtSignalCallback::kick(Runner &run)
    {
        run.where_->release();
        run.where_ = whence;
        return this + 1;
    }

    const Step *SinkQtSignalCallback::pass(Runner &run, const Any *value)
    {
        value->release();
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
