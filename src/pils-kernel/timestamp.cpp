/* This file is public domain */
#include "timestamp.h"
#include "writing.h"

namespace PILS
{
	bool Timestamp::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (writing.overflow()) return false;
		if (dot == &Empty::singleton)
		{
			writing.spaceDot();
			writing.write(". ");
		}
		else writing.spaceElement();

		Split split;
		split.put(value);

		writing.write(split.year, 4);
		writing.write((PILS_CHAR)'-');
		writing.write(split.month, 2);
		writing.write((PILS_CHAR)'-');
		writing.write(split.day, 2);
		writing.write((PILS_CHAR)'T');
		writing.write(split.hour, 2);
		writing.write((PILS_CHAR)':');
		writing.write(split.minute, 2);
		writing.write((PILS_CHAR)':');
		writing.write(split.second, 2);
		writing.write((PILS_CHAR)'.');
		writing.write(split.millisecond, 3);
		int zoneMinute = split.zoneSecond / 60;
		if (zoneMinute < 0)
		{
			writing.write((PILS_CHAR)'+');
			zoneMinute = -zoneMinute;
		}
		else writing.write((PILS_CHAR)'-');
		writing.write(zoneMinute / 60, 2);
		if (zoneMinute %= 60)
		{
			writing.write((PILS_CHAR)':');
			writing.write(zoneMinute, 2);
		}
		writing.spacing = Writing::space;
		return false;
	}

	const Timestamp *Timestamp::get(long long value)
	{
		const HashedConstant *&chain = hashChain((size_t)value ^ (size_t)(value >> 32));
		Mutex::Lock lock (Heap::mutex);
		return chain->hashLookupTimestamp(value);
	}

	bool Duration::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (writing.overflow()) return false;
		if (dot == &Empty::singleton)
		{
			writing.spaceDot();
			writing.write(". ");
		}
		else writing.spaceElement();

		Split split;
		if (value < 0)
		{
			writing.write('-');
			split.put(-value);
		}
		else
		{
			split.put(value);
		}
		int first = split.days?0:split.hour?1:split.minute?2:3;
		int last = first==3?3:split.millisecond?3:split.second?3:split.minute?2:split.hour?1:0;
		if (first == 0)
		{
			writing.write((long long)split.days);
			writing.write('d');
		}
		if (first <= 1 && last >= 1)
		{
			if (first == 2) writing.write((size_t)split.hour);
			else writing.write(split.hour, 2);
			writing.write('h');
		}
		if (first <= 2 && last >= 2)
		{
			if (first == 2) writing.write((size_t)split.minute);
			else writing.write(split.minute, 2);
			writing.write('m');
		}
		if (last == 3)
		{
			if (first == 3)	writing.write((size_t)split.second);
			else writing.write(split.second, 2);
			if (split.millisecond)
			{
				writing.write('.');
				writing.write(split.millisecond, 3);
			}
			writing.write('s');
		}
		
		writing.spacing = Writing::space;
		return false;
	}

	const Duration *Duration::get(long long value)
	{
		const HashedConstant *&chain = hashChain((size_t)value ^ (size_t)(value >> 32));
		Mutex::Lock lock (Heap::mutex);
		return chain->hashLookupDuration(value);
	}

	const PilsDate *PilsDate::get(long long value)
	{
		const HashedConstant *&chain = hashChain((size_t)value ^ (size_t)(value >> 32));
		Mutex::Lock lock (Heap::mutex);
		return chain->hashLookupPilsDate(value);
	}

	const PilsColor *ShortInteger::hashLookupPilsColor(unsigned int value) const
	{
		/* End of hash chain - construct Timestamp */
		return new (Heap::allocate(sizeof(PilsColor))) PilsColor(((ShortInteger*)this)->hashLink, value);
	}

	const Timestamp *ShortInteger::hashLookupTimestamp(long long value) const
	{
		/* End of hash chain - construct Timestamp */
		return new (Heap::allocate(sizeof(Timestamp))) Timestamp(((ShortInteger*)this)->hashLink, value);
	}

	const Duration *ShortInteger::hashLookupDuration(long long value) const
	{
		/* End of hash chain - construct Duration */
		return new (Heap::allocate(sizeof(Duration))) Duration(((ShortInteger*)this)->hashLink, value);
	}

	const PilsDate *ShortInteger::hashLookupPilsDate(long long value) const
	{
		/* End of hash chain - construct PilsDate */
		return new (Heap::allocate(sizeof(PilsDate))) PilsDate(((ShortInteger*)this)->hashLink, value);
	}

	const Timestamp *Timestamp::hashLookupTimestamp(long long value) const
	{
		if (value == this->value &&  duplicateReference()) return this;
		else return hashLink->hashLookupTimestamp(value);
	}

	const Timestamp *HashedConstant::hashLookupTimestamp(long long value) const
	{
		return hashLink->hashLookupTimestamp(value);
	}

	const Duration *Duration::hashLookupDuration(long long value) const
	{
		if (value == this->value &&  duplicateReference()) return this;
		else return hashLink->hashLookupDuration(value);
	}

	const Duration *HashedConstant::hashLookupDuration(long long value) const
	{
		return hashLink->hashLookupDuration(value);
	}

	bool PilsDate::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (writing.overflow()) return false;
		if (dot == &Empty::singleton)
		{
			writing.spaceDot();
			writing.write(". ");
		}
		else writing.spaceElement();
		Split split;
		split.put(value);

		writing.write(split.year, 4);
		writing.write((PILS_CHAR)'-');
		writing.write(split.month, 2);
		writing.write((PILS_CHAR)'-');
		writing.write(split.day, 2);
		if (split.hour||split.minute||split.second||split.millisecond)
		{
			writing.write((PILS_CHAR)'T');
			writing.write(split.hour, 2);
			writing.write((PILS_CHAR)':');
			writing.write(split.minute, 2);
			if (split.second||split.millisecond)
			{
				writing.write((PILS_CHAR)':');
				writing.write(split.second, 2);
				if (split.millisecond)
				{
					writing.write((PILS_CHAR)'.');
					writing.write(split.millisecond, 3);
				}
			}
		}
		writing.spacing = Writing::space;
		return false;
	}

	const PilsDate *PilsDate::hashLookupPilsDate(long long value) const
	{
		if (value == this->value &&  duplicateReference()) return this;
		else return hashLink->hashLookupPilsDate(value);
	}

	const PilsDate *HashedConstant::hashLookupPilsDate(long long value) const
	{
		return hashLink->hashLookupPilsDate(value);
	}

	const Step *Timevalue::step_(Runner &run) const
	{
		addReference();
		return passCounted(run);
	}

	const Step *Timevalue::passUncounted(Runner &run) const
	{
		addReference();
		return passCounted(run);
	}

	const Step *Timestamp::passCounted(Runner &run) const
	{
		return run.sink->pass(run, this);
	}

	const Step *Duration::passCounted(Runner &run) const
	{
		return run.sink->pass(run, this);
	}

	const Step *PilsDate::passCounted(Runner &run) const
	{
		return run.sink->pass(run, this);
	}

	bool Converter::convert(const PilsColor &)
	{
		return false;
	}

	bool Converter::convert(const Timestamp &)
	{
		return false;
	}

	bool Converter::convert(const Duration &)
	{
		return false;
	}

	bool Converter::convert(const PilsDate &)
	{
		return false;
	}

	const Timestamp *Any::as_Timestamp() const
	{
		return NULL;
	}

	const Timestamp *Timestamp::as_Timestamp() const
	{
		return this;
	}

	const Duration *Any::as_Duration() const
	{
		return NULL;
	}

	const Duration *Duration::as_Duration() const
	{
		return this;
	}

	const PilsDate *Any::as_PilsDate() const
	{
		return NULL;
	}

	const PilsDate *PilsDate::as_PilsDate() const
	{
		return this;
	}

	int Timestamp::order(const Constant *other) const
	{
		if (const Timestamp *that = other->as_Timestamp())
		{
			if (this->value < that->value) return -1;
			else if (this->value > that->value) return 1;
		}
		return 0;
	}

	int Duration::order(const Constant *other) const
	{
		if (const Duration *that = other->as_Duration())
		{
			if (this->value < that->value) return -1;
			else if (this->value > that->value) return 1;
		}
		return 0;
	}

	int PilsDate::order(const Constant *other) const
	{
		if (const PilsDate *that = other->as_PilsDate())
		{
			if (this->value < that->value) return -1;
			else if (this->value > that->value) return 1;
		}
		return 0;
	}
}
