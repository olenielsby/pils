/* This file is public domain */
#pragma once
#include <thread>
// #include "qpils-binding-base.h"
#include "qpils-plumming.h"
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
        const std::thread::id threadID;
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
			RunLevel(PilsThread *candidate = NULL)
				: thread(*getCurrent(candidate))
			{
				thread.runLevels++;
			}
			~RunLevel()
			{
				if (thread.runLevels == 1)
					thread.runLevelTouchDown();
				--thread.runLevels;
				thread.releaseReference();
			}
			Runner &run() {return thread;}
			static PilsThread *getCurrent(PilsThread *candidate = NULL);
		private:
			PilsThread &thread;
		};
	protected:
        PilsThread(const HashedConstant *&link, std::thread::id threadID)
            :  ReallySpecial(link), Runner(0x10000), threadID(threadID), runLevels(0)
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
        PendableThread(const HashedConstant *&link, std::thread::id threadID)
			:  PilsThread(link, threadID), pending(NULL)
		{}
	private:
		friend class Pending;
		Pending *pending;
	};

	class MainThread
		: public PendableThread
	{
	public:
        size_t unlinkAndGetSize() override;
		static MainThread *singleton;
        // void runLevelTouchDown() override;
	private:
        const Step *thread(const Any &what) override;
		friend class ThreadLookup;
        MainThread(const HashedConstant *&link, std::thread::id threadID)
			: PendableThread(link, threadID)
		{}
	};

    // class WorkerThread
    // 	: public PilsThread
    // {
    // public:
 //        WorkerThread(const HashedConstant *&link, std::thread::id threadID)
    // 		: PilsThread(link, threadID)
    // 	{}
 //        size_t unlinkAndGetSize() override;
 //        const Step *callingKnot(const Any &who, const Any &call) override;
 //        const Step *callingKnot(const Any &who, const Any &call, const Any *assignValue) override;
    // 	static void* knotCallback(void*);
    // };

	class ThreadLookup
		: public SpecialLookup
	{
	public:
        ThreadLookup(std::thread::id const threadID)
			: threadID(threadID)
		{}
        const std::thread::id threadID;
		virtual ~ThreadLookup() {}
        bool compare(const ReallySpecial &special) const override;
        const ReallySpecial *newSpecial(const HashedConstant *&link) override;
        size_t hash() const override;
        void unduplicate() override;
	};

	class Pending
	{
	public:
		Pending(PendableThread &thread)
			: thread(thread), link(&thread.pending)
		{
			Mutex::Lock lock(Heap::mutex);
			next = *link;
			*link = this;
		}
		virtual ~Pending(){}
		Pending *unlink()
		{
			Mutex::Lock lock(Heap::mutex);
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
