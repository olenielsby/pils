/* This file is public domain */
#ifndef DEFINE_PILS_PILSMUTEX_H
#define DEFINE_PILS_PILSMUTEX_H

#include <map>
#include <set>
#include <vector>
#include <new>
#include <algorithm>
#include <list>
#include <locale>

namespace PILS
{
	/* Locking mechanism is platform-dependent */
	class Mutex_implementation;

	class Mutex
	{
	public:
		Mutex();
		~Mutex();
	private:
		class Implement
		{
		public:
			static void lock(Mutex_implementation &mutex_implementation);
			static void unlock(Mutex_implementation &mutex_implementation);
		};
		/* Lock when working with memory and hashing */
	private:
		class Hold
		{
		protected:
			Hold(Mutex &mutex)
				: hold(mutex.implementation)
			{}
			void lock()
			{
				Implement::lock(hold);
			}
			void unlock()
			{
				Implement::unlock(hold);
			}
		private:
			Mutex_implementation &hold;
		};
	public:
		class Lock
			: Hold
		{
		public:
			Lock(Mutex &mutex)
				: Hold(mutex)
			{
				Hold::lock();
			}
			~Lock()
			{
				Hold::unlock();
			}
		};
		/* Temporary unlock when freeing external resources etc. */
		class Unlock
			: Hold
		{
		public:
			Unlock(Mutex &mutex)
				: Hold(mutex)
			{
				Hold::unlock();
			}
			~Unlock()
			{
				Hold::lock();
			}
		};
	private:
		Mutex_implementation &implementation;
	};
}
#endif
