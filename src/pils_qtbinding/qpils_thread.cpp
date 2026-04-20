/* This file is public domain */
#include "qpils_thread.h"
namespace PILS
{
    MainThread *MainThread::singleton = nullptr;
	Bridge Bridge::singleton;

	const Constant *PilsThread::as_Thread() const
	{
		retain();
		return this;
	}

	bool ReallySpecial::specialComparing(const ThreadLookup &lookup) const
	{
		return false;
	}

    void MainThread::unlink()
	{
		unhash();
		this->Runner::~Runner();
	}

	PilsThread *PilsThread::RunLevel::getCurrent(PilsThread *candidate)
	{
        QThread *qThread = QThread::currentThread();
        if (candidate && candidate->qThread == qThread)
		{
			candidate->retain();
			return candidate;
		}
        else return (PilsThread*)ThreadLookup(qThread).lookup();
	}

	size_t ThreadLookup::hash() const
	{
        return PilsThread::hash(qThread);
    }

    size_t PilsThread::hash(QThread *qThread)
    {
        return std::hash<QThread *>{}(qThread);
    }

    bool ThreadLookup::compare(const ReallySpecial &special) const
	{
		return special.specialComparing(*this);
	}

	void ThreadLookup::unduplicate()
	{}

	const ReallySpecial *ThreadLookup::newSpecial(const Constant *&link)
    {
        throw L"ThreadLookup::newSpecial: WorkerThread not implemented";
	}

	bool PilsThread::specialComparing(const ThreadLookup &lookup) const
	{
        return qThread == lookup.qThread;
	}

	void PilsThread::write(Writing &writing) const
	{
        writing.write("{thread}");
        // writing.write(threadID);
	}

    const Step *MainThread::thread(const Any &what)
    {
    // 	class QtWorkerThread : public QThread
    // 	{
    // 	public:
    // 		QtWorkerThread(const Any *what, const Any *where_)
    // 			: QThread("WorkerThread"), what(what), where_(where_)
    // 		{}
    // 	private:
    // 		const Any *what;
    // 		const Any *where_;
    //      void run() override
    // 		{
    // 			PilsThread *thread = (PilsThread*)ThreadLookup(juce::Thread::getCurrentThreadId()).lookup();
    // 			thread->where_ = where_;
    // 			thread->run(what);
    // 			what->release();
    // 			thread->release();
    // 			postThreadDestructionMessage(this);
    // 		}
    // 	};
    // 	where_->retain();
    // 	what.retain();
    // 	(new JuceWorkerThread(&what, where_))->startThread();
        return &Empty::singleton;
    }

    // class SinkKnotCall
    // 	: protected Sink
    // {
    // public:
    // 	SinkKnotCall(WorkerThread &thread, const Any *whence)
    // 		: thread(thread), whence(whence)
    // 	{}
 //        Sink *kick(Runner &run) override
    // 	{
    // 		run.where_ = whence;
    // 		return this + 1;
    // 	}
    // protected:
    // 	const Step *backToWork(Runner &run)
    // 	{
    // 		run.sink = kick(run);
    // 		return nullptr;
    // 	}
    // 	WorkerThread &thread;
    // 	const Any *whence;
    // private:
 //        const Step *pass(Runner &run, const Any *result) override
    // 	{
    // 		new (thread.allocate(sizeof(KnotStepResult))) KnotStepResult(result);
    // 		return backToWork(run);
    // 	}

 //        const Step *called(Runner &run, const Constant &call) override
    // 	{
    // 		new (thread.allocate(sizeof(KnotStepCalled))) KnotStepCalled(call);
    // 		return backToWork(run);
    // 	}
 //        const Step *called(Runner &run, const Integer &call) override
    // 	{
    // 		new (thread.allocate(sizeof(KnotStepCalled))) KnotStepCalled(call);
    // 		return backToWork(run);
    // 	}
 //        const Step *called(Runner &run, const ListConstant &call) override
    // 	{
    // 		new (thread.allocate(sizeof(KnotStepCalled))) KnotStepCalled(call);
    // 		return backToWork(run);
    // 	}
 //        const Step *called(Runner &run, const NodeConstant &call) override
    // 	{
    // 		new (thread.allocate(sizeof(KnotStepCalled))) KnotStepCalled(call);
    // 		return backToWork(run);
    // 	}
 //        const Step *called(Runner &run, const Empty &call) override
    // 	{
    // 		new (thread.allocate(sizeof(KnotStepCalled))) KnotStepCalled(call);
    // 		return backToWork(run);
    // 	}
 //        const Step *called(Runner &run, const ListExpress &call) override
    // 	{
    // 		new (thread.allocate(sizeof(KnotStepCalled))) KnotStepCalled(call);
    // 		return backToWork(run);
    // 	}
 //        const Step *called(Runner &run, const NodeExpress &call) override
    // 	{
    // 		new (thread.allocate(sizeof(KnotStepCalled))) KnotStepCalled(call);
    // 		return backToWork(run);
    // 	}
 //        const Step *called(Runner &run, const Any &call, const Any *assignValue) override
    // 	{
    // 		new (thread.allocate(sizeof(KnotStepAssignCalled))) KnotStepAssignCalled(call, assignValue);
    // 		return backToWork(run);
    // 	}
    // };

	const Step *LaterPoker::step_(Runner &run) const
	{
		return element[0]; //dummy
	}

	void PendableThread::doPending()
	{
		while (pending)
		{
            delete pending->unlinkPending();
		}
	}

    void PendableThread::runLevelTouchDown()
    {
        doPending();
        PilsThread::runLevelTouchDown();
    }

    // size_t WorkerThread::unlink()
    // {
    // 	unhash();
    // 	if (when) when->releaseFrom(*this);
    // 	this->Runner::~Runner();
    // 	return sizeof(WorkerThread);
    // }

    // const Step *WorkerThread::callingKnot(const Any &who, const Any &call)
    // {
    // 	class KnotCall : Step
    // 	{
    // 	public:
    // 		KnotCall(WorkerThread &thread, const Any &who, const Any &call)
    // 			: thread(thread), who(who), call(call)
    // 		{}
    // 		WorkerThread &thread;
    // 		const Any &who;
    // 		const Any &call;
 //            const Step *step_(Runner &run) const override
    // 		{
    // 			new (run.allocate(sizeof(SinkKnotCall))) SinkKnotCall(thread, run.where_);
    // 			run.where_ = thread.where_;
    // 			run.calling.who = thread.Runner::calling.who;
    // 			run.calling.what = thread.Runner::calling.what;
    // 			return call.caller(run, who);
    // 		}
    // 	} knotCall(*this, who, call);
    // 	juce::MessageManager::getInstance()->callFunctionOnMessageThread(knotCallback, (void*)&knotCall);
    // 	return sink;
    // }

    // const Step *WorkerThread::callingKnot(const Any &who, const Any &call, const Any *assignValue)
    // {
    // 	class KnotCall : Step
    // 	{
    // 	public:
    // 		KnotCall(WorkerThread &thread, const Any &who, const Any &call, const Any *assignValue)
    // 			: who(who), call(call), thread(thread), assignValue(assignValue)
    // 		{}
    // 		WorkerThread &thread;
    // 		const Any &who;
    // 		const Any &call;
    // 		const Any *assignValue;
 //            const Step *step_(Runner &run) const override
    // 		{
    // 			new (run.allocate(sizeof(SinkKnotCall))) SinkKnotCall(thread, run.where_);
    // 			run.where_ = thread.where_;
    // 			run.calling.who = thread.Runner::calling.who;
    // 			run.calling.what = thread.Runner::calling.what;
    // 			return run.calling.who->calling(run, call, assignValue);
    // 		}
    // 	} knotCall(*this, who, call, assignValue);
    // 	juce::MessageManager::getInstance()->callFunctionOnMessageThread(knotCallback, (void*)&knotCall);
    // 	return sink;
    // }

    // void *WorkerThread::knotCallback(void *step_)
    // {
    // 	MainThread::singleton->run((const Step *)step_);
    // 	return nullptr;
    // }
}
