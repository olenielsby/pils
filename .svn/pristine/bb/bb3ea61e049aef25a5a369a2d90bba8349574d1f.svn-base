/* This file is public domain */
#ifndef _PLUMMING_JPILS_THREAD_H_
#define _PLUMMING_JPILS_THREAD_H_
#include "jpils-binding-base.h"
#include "pils-kernel/pilsthread.h"

namespace PILS
{
	/* threads */

	class Pending;
	class Bridge {public: static Bridge singleton;};
	class PilsThread
		: public ReallySpecial, public Runner
	{
	public:
		const juce::Thread::ThreadID threadID;
		bool specialCompare(const ReallySpecial *special) const;
		bool specialComparing(const ThreadLookup &lookup) const;
		const Constant *as_Thread() const;
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
		PilsThread(const HashedConstant *&link, juce::Thread::ThreadID threadID)
			:  ReallySpecial(link), Runner(Bridge::singleton, 0x10000), threadID(threadID), runLevels(0)
		{}
		static void postThreadDestructionMessage(juce::Thread *deadThread);
		int runLevels;
	private:
		void write(Writing &writing) const;
	};

	class PendableThread
		: public PilsThread
	{
	public:
		void doPending();
		virtual void runLevelTouchDown();
	protected:
		PendableThread(const HashedConstant *&link, juce::Thread::ThreadID threadID)
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
		size_t unlinkAndGetSize();
		static MainThread *singleton;
		virtual void runLevelTouchDown();
	private:
		const Step *thread(const Any &what);
		friend class ThreadLookup;
		MainThread(const HashedConstant *&link, juce::Thread::ThreadID threadID)
			: PendableThread(link, threadID)
		{}
	};

	class WorkerThread
		: public PilsThread
	{
	public:
		WorkerThread(const HashedConstant *&link, juce::Thread::ThreadID threadID)
			: PilsThread(link, threadID)
		{}
		size_t unlinkAndGetSize();
		const Step *callingKnot(const Any &who, const Any &call);
		const Step *callingKnot(const Any &who, const Any &call, const Any *assignValue);
		static void* knotCallback(void*);
	};

	class ThreadLookup
		: public SpecialLookup
	{
	public:
		ThreadLookup(juce::Thread::ThreadID const threadID)
			: threadID(threadID)
		{}
		const juce::Thread::ThreadID threadID;
		virtual ~ThreadLookup() {}
		bool compare(const ReallySpecial &special) const;
		const ReallySpecial *newSpecial(const HashedConstant *&link);
		size_t hash() const;
		void unduplicate();
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
#endif
