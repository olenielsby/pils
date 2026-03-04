/* This file is public domain */
#include "jpils-thread.h"
namespace PILS
{
	MainThread *MainThread::singleton = NULL;
	volatile long JuceComponent::desktopComponentCount = 0;
	Bridge Bridge::singleton;

	const Constant *PilsThread::as_Thread() const
	{
		addReference();
		return this;
	}

	bool ReallySpecial::specialComparing(const ThreadLookup &lookup) const
	{
		return false;
	}

	size_t MainThread::unlinkAndGetSize()
	{
		unhash();
		if (when) when->releaseFrom(*this);
		this->Runner::~Runner();
		return sizeof(MainThread);
	}

	PilsThread *PilsThread::RunLevel::getCurrent(PilsThread *candidate)
	{
		juce::Thread::ThreadID threadID = juce::Thread::getCurrentThreadId();
		if (candidate && candidate->threadID == threadID)
		{
			candidate->addReference();
			return candidate;
		}
		else return (PilsThread*)ThreadLookup(threadID).lookup();
	}

	size_t ThreadLookup::hash() const
	{
		return (size_t)threadID;
	}

	bool ThreadLookup::compare(const ReallySpecial &special) const
	{
		return special.specialComparing(*this);
	}

	void ThreadLookup::unduplicate()
	{}

	const ReallySpecial *ThreadLookup::newSpecial(const HashedConstant *&link)
	{
		if (!MainThread::singleton)
			return new (Heap::allocate(sizeof(MainThread))) MainThread(link, threadID);
		else
			return new (Heap::allocate(sizeof(WorkerThread))) WorkerThread(link, threadID);
	}

	bool PilsThread::specialComparing(const ThreadLookup &lookup) const
	{
		return threadID == lookup.threadID;
	}

	void PilsThread::write(Writing &writing) const
	{
		writing.write((PILS_CHAR)'~');
		writing.write((long long)threadID);
	}

	const Step *MainThread::thread(const Any &what)
	{
		class JuceWorkerThread : public juce::Thread
		{
		public:
			JuceWorkerThread(const Any *what, const Any *where_)
				: juce::Thread("WorkerThread"), what(what), where_(where_)
			{}
		private:
			const Any *what;
			const Any *where_;
            void run() override
			{
				PilsThread *thread = (PilsThread*)ThreadLookup(juce::Thread::getCurrentThreadId()).lookup();
				thread->where_ = where_;
				thread->run(what);
				what->releaseReference();
				thread->releaseReference();
				postThreadDestructionMessage(this);
			}
		};
		where_->addReference();
		what.addReference();
		(new JuceWorkerThread(&what, where_))->startThread();
		return &Empty::singleton;
	}

	class SinkKnotCall
		: protected Sink
	{
	public:
		SinkKnotCall(WorkerThread &thread, const Any *whence)
			: thread(thread), whence(whence)
		{}
        Sink *kick(Runner &run) override
		{
			run.where_ = whence;
			return this + 1;
		}
	protected:
		const Step *backToWork(Runner &run)
		{
			run.sink = kick(run);
			return NULL;
		}
		WorkerThread &thread;
		const Any *whence;
	private:
        const Step *pass(Runner &run, const Any *result) override
		{
			new (thread.allocate(sizeof(KnotStepResult))) KnotStepResult(result);
			return backToWork(run);
		}

        const Step *called(Runner &run, const Constant &call) override
		{
			new (thread.allocate(sizeof(KnotStepCalled))) KnotStepCalled(call);
			return backToWork(run);
		}
        const Step *called(Runner &run, const Integer &call) override
		{
			new (thread.allocate(sizeof(KnotStepCalled))) KnotStepCalled(call);
			return backToWork(run);
		}
        const Step *called(Runner &run, const ListConstant &call) override
		{
			new (thread.allocate(sizeof(KnotStepCalled))) KnotStepCalled(call);
			return backToWork(run);
		}
        const Step *called(Runner &run, const NodeConstant &call) override
		{
			new (thread.allocate(sizeof(KnotStepCalled))) KnotStepCalled(call);
			return backToWork(run);
		}
        const Step *called(Runner &run, const Empty &call) override
		{
			new (thread.allocate(sizeof(KnotStepCalled))) KnotStepCalled(call);
			return backToWork(run);
		}
        const Step *called(Runner &run, const ListExpress &call) override
		{
			new (thread.allocate(sizeof(KnotStepCalled))) KnotStepCalled(call);
			return backToWork(run);
		}
        const Step *called(Runner &run, const NodeExpress &call) override
		{
			new (thread.allocate(sizeof(KnotStepCalled))) KnotStepCalled(call);
			return backToWork(run);
		}
        const Step *called(Runner &run, const Any &call, const Any *assignValue) override
		{
			new (thread.allocate(sizeof(KnotStepAssignCalled))) KnotStepAssignCalled(call, assignValue);
			return backToWork(run);
		}
	};

	const Step *LaterPoker::step_(Runner &run) const
	{
		return element[0]; //dummy
	}

	void PendableThread::doPending()
	{
		while (pending)
		{
			delete pending->unlink();
		}
	}

	void PendableThread::runLevelTouchDown()
	{
		doPending();
		PilsThread::runLevelTouchDown();
	}

	size_t WorkerThread::unlinkAndGetSize()
	{
		unhash();
		if (when) when->releaseFrom(*this);
		this->Runner::~Runner();
		return sizeof(WorkerThread);
	}

	const Step *WorkerThread::callingKnot(const Any &who, const Any &call)
	{
		class KnotCall : Step
		{
		public:
			KnotCall(WorkerThread &thread, const Any &who, const Any &call)
				: thread(thread), who(who), call(call)
			{}
			WorkerThread &thread;
			const Any &who;
			const Any &call;
            const Step *step_(Runner &run) const override
			{
				new (run.allocate(sizeof(SinkKnotCall))) SinkKnotCall(thread, run.where_);
				run.where_ = thread.where_;
				run.calling.who = thread.Runner::calling.who;
				run.calling.what = thread.Runner::calling.what;
				return call.caller(run, who);
			}
		} knotCall(*this, who, call);
		juce::MessageManager::getInstance()->callFunctionOnMessageThread(knotCallback, (void*)&knotCall);
		return sink;
	}

	const Step *WorkerThread::callingKnot(const Any &who, const Any &call, const Any *assignValue)
	{
		class KnotCall : Step
		{
		public:
			KnotCall(WorkerThread &thread, const Any &who, const Any &call, const Any *assignValue)
				: who(who), call(call), thread(thread), assignValue(assignValue)
			{}
			WorkerThread &thread;
			const Any &who;
			const Any &call;
			const Any *assignValue;
            const Step *step_(Runner &run) const override
			{
				new (run.allocate(sizeof(SinkKnotCall))) SinkKnotCall(thread, run.where_);
				run.where_ = thread.where_;
				run.calling.who = thread.Runner::calling.who;
				run.calling.what = thread.Runner::calling.what;
				return run.calling.who->calling(run, call, assignValue);
			}
		} knotCall(*this, who, call, assignValue);
		juce::MessageManager::getInstance()->callFunctionOnMessageThread(knotCallback, (void*)&knotCall);
		return sink;
	}

	void *WorkerThread::knotCallback(void *step_)
	{
		MainThread::singleton->run((const Step *)step_);
		return NULL;
	}
}
