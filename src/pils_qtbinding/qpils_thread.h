/* This file is public domain */
#pragma once
#include <QThread>
// #include "qpils_binding_base.h"
#include "qpils_plumming.h"
#include "pilsthread.h"

namespace PILS
{
	/* threads */

	class Pending;
	class Bridge {public: static Bridge singleton;};
	class PilsThread
		: public ReallySpecial, public Runner
	{
	public:
        QThread *qThread;
        static size_t hash(QThread *qThread);
        bool specialCompare(const ReallySpecial *special) const;
        bool specialComparing(const ThreadLookup &lookup) const override;
        const Constant *as_Thread() const override;
		virtual void runLevelTouchDown()
		{
			threadStrapSticker.clear();
		}
		class RunLevel
		{
		public:
			RunLevel(PilsThread *candidate = nullptr)
				: thread(*getCurrent(candidate))
			{
				thread.runLevels++;
			}
			~RunLevel()
			{
				if (thread.runLevels == 1)
					thread.runLevelTouchDown();
				--thread.runLevels;
				thread.release();
			}
			Runner &run() {return thread;}
			static PilsThread *getCurrent(PilsThread *candidate = nullptr);
		private:
			PilsThread &thread;
		};
	protected:
        PilsThread(const Constant *&link, QThread *qThread)
            :  ReallySpecial(link), Runner(0x10000), qThread(qThread), runLevels(0)
		{}
        static void postThreadDestructionMessage(std::thread *deadThread);
		int runLevels;
	private:
        void write(Writing &writing) const override;
	};

	class PendableThread
		: public PilsThread
	{
	public:
		void doPending();
        void runLevelTouchDown() override;
	protected:
        PendableThread(const Constant *&link, QThread *qThread)
            :  PilsThread(link, qThread), pending(nullptr)
		{}
	private:
		friend class Pending;
		Pending *pending;
	};

	class MainThread
		: public PendableThread
	{
	public:
        void unlink() override;
		static MainThread *singleton;
        // void runLevelTouchDown() override;
	private:
        const Step *thread(const Any &what) override;
        friend class PilsCommander;
        MainThread(QThread *qThread)
            : PendableThread(hashChain(PilsThread::hash(qThread)), qThread)
        {}
	};

    // class WorkerThread
    // 	: public PilsThread
    // {
    // public:
 //        WorkerThread(const Constant *&link, std::thread::id threadID)
    // 		: PilsThread(link, threadID)
    // 	{}
 //        void unlink() override;
 //        const Step *callingKnot(const Any &who, const Any &call) override;
 //        const Step *callingKnot(const Any &who, const Any &call, const Any *assignValue) override;
    // 	static void* knotCallback(void*);
    // };

	class ThreadLookup
		: public SpecialLookup
	{
	public:
        ThreadLookup(QThread *qThread)
            : qThread(qThread)
		{}
        QThread *const qThread;
		virtual ~ThreadLookup() {}
        bool compare(const ReallySpecial &special) const override;
        const ReallySpecial *newSpecial(const Constant *&link) override;
        size_t hash() const override;
        void unduplicate() override;
	};

	class Pending
	{
	public:
		Pending(PendableThread &thread)
			: thread(thread), link(&thread.pending)
		{
            Mutex::Lock lock(Mutex::singleMutex);
			next = *link;
			*link = this;
		}
		virtual ~Pending(){}
        Pending *unlinkPending()
		{
            Mutex::Lock lock(Mutex::singleMutex);
			*link = next;
			if (next) next->link = link;
			return this;
		}
	protected:
		PendableThread &thread;
	private:
		Pending **link;
		Pending *next;
	};
}
