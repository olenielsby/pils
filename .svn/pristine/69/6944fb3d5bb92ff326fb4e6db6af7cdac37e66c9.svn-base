/* This file is public domain */
#include "pils-kernel/compile.h"
#include "jpils-standard-specials.h"
namespace PILS
{
	long long longlongtime(::juce::Time time) {return time.toMilliseconds();}
	const Constant *pils(const juce::Time &time) {return Timestamp::get(time.toMilliseconds());}
	const Any *SystemPropertyNow::get(Runner &run) const
	{
		return pils(juce::Time::getCurrentTime());
	}

	const Any *SystemPropertyTimestamp::get(Runner &run) const
	{
		long long time = longlongtime(juce::Time::getCurrentTime());
		run.oldTimer = false;
		{
			Mutex::Lock lock(Heap::mutex);
			time = Timestamp::stamp = Timestamp::stamp < time?time:Timestamp::stamp + 1;
		}
		return Timestamp::get(time);
	}

	bool TypecheckingConverterIdentifier::convert(const ReallySpecial &special)
	{
		return special.isIdentifier();
	}

	void Timestamp::Split::put(long long source)
	{
		juce::Time time(source);
		year = time.getYear();
		month = time.getMonth() + 1;
		day = time.getDayOfMonth();
		hour = time.getHours();
		minute = time.getMinutes();
		second = time.getSeconds();
		millisecond = time.getMilliseconds();
		juce::RelativeTime zoneshift = time - Time(year, month - 1, day, hour, minute, second, millisecond, false);
		zoneSecond = (long)zoneshift.inSeconds();
	}

	void PilsDate::Split::put(long long source)
	{
		source += 210866803200000LL;
		millisecond = source % 1000;
		source /= 1000;
		second = source % 60;
		source /= 60;
		minute = source % 60;
		source /= 60;
		hour = source % 24;
		source /= 24;
        const int days = (int) (source);
        const int a = 32044 + days;
        const int b = (4 * a + 3) / 146097;
        const int c = a - (b * 146097) / 4;
        const int d = (4 * c + 3) / 1461;
        const int e = c - (d * 1461) / 4;
        const int m = (5 * e + 2) / 153;
        day = e - (153 * m + 2) / 5 + 1;
        month = m + 3 - 12 * (m / 10);
        year  = b * 100 + d - 4800 + (m / 10);
	}

	long long Timestamp::Split::get()
	{
		return juce::Time(year, month - 1, day, hour, minute, second, millisecond, false).toMilliseconds() - zoneSecond * 1000;
	}

	void Duration::Split::put(long long source)
	{
		millisecond = source % 1000;
		source /= 1000;
		second = source % 60;
		source /= 60;
		minute = source % 60;
		source /= 60;
		hour = source % 24;
		source /= 24;
		days = (long)source;
	}

	long long Duration::Split::get()
	{
		return ((((long long)days * 24 + hour) * 60 + minute) * 60 + second) * 1000 + millisecond;
	}

	long long PilsDate::Split::getTimestampFromLocalTime()
	{
		return juce::Time(year, month - 1, day, hour, minute, second, millisecond).toMilliseconds();
	}

	/*
	bool Identifier::isIdentifier() const
	{
		return true;
	}

	const Identifier *Identifier::get(GUID value)
	{
		return (const Identifier*) IdentifierLookup(value).lookup();
	}

	int Identifier::order(const Constant *value) const
	{
		return 0;
	}

	const ReallySpecial *IdentifierLookup::newSpecial(const HashedConstant *&link)
	{
		return new (Heap::allocate(sizeof(Identifier))) Identifier(link, value);
	}

	bool IdentifierLookup::compare(const PILS::ReallySpecial &other) const
	{
		return other.specialComparing(*this);
	}

	void IdentifierLookup::unduplicate()
	{}

	size_t IdentifierLookup::hash() const
	{
		const unsigned long *ptr = &value.Data1;
		return ptr[0] + ptr[1] + ptr[2] + ptr[3];
	}

	size_t Identifier::unlinkAndGetSize()
	{
		unhash();
		return sizeof(Identifier);
	}

	const Special *SpecialReader::Format<SpecialReader::Identifier>::tryRead(const PILS_CHAR *cc, const PILS_CHAR *end, const Reading &reading) const
	{
		GUID g;
		unsigned char *cp = g.Data4;
		unsigned long accumulator (0);
		if (end - cc != 36) return NULL;
		for (long i = 0; i < 36; i++)
		{
			const PILS_CHAR c = *(cc++);
			switch (i)
			{
			case 8:
				if (c != '-') return NULL;
				g.Data1 = accumulator;
				break;
			case 13:
				if (c != '-') return NULL;
				g.Data2 = (unsigned short)accumulator;
				break;
			case 18:
				if (c != '-') return NULL;
				g.Data3 = (unsigned short)accumulator;
				break;
			case 23:
				if (c != '-') return NULL;
				*cp++ = (char)accumulator;
				break;
			case 21:
			case 26:
			case 28:
			case 30:
			case 32:
			case 34:
				*cp++ = (char)accumulator;
			default:
				accumulator <<= 4;
				switch (c)
				{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					accumulator += c - '0';
					break;
				case 'A':
				case 'B':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
					accumulator += c - 'A' + 10;
					break;
				case 'a':
				case 'b':
				case 'c':
				case 'd':
				case 'e':
				case 'f':
					accumulator += c - 'a' + 10;
					break;
				default:
					return NULL;
				}
			}
		}
		*cp++ = (char)accumulator;
		return PILS::Identifier::get(g);
	}

	void Identifier::write(Writing &writing) const
	{
		for (long i = 7; i >= 0; i--)
			writing.write(_PS("0123456789ABCDEF")[0xf & (value.Data1 >> (i * 4))]);
		writing.write((PILS_CHAR)'-');
		for (long i = 3; i >= 0; i--)
			writing.write(_PS("0123456789ABCDEF")[0xf & (value.Data2 >> (i * 4))]);
		writing.write((PILS_CHAR)'-');
		for (long i = 3; i >= 0; i--)
			writing.write(_PS("0123456789ABCDEF")[0xf & (value.Data3 >> (i * 4))]);
		writing.write((PILS_CHAR)'-');
		for (long i = 0; i < 8; i++)
		{
			if (i == 2) writing.write((PILS_CHAR)'-');
			writing.write(_PS("0123456789ABCDEF")[value.Data4[i] >> 4]);
			writing.write(_PS("0123456789ABCDEF")[0xf & value.Data4[i]]);
		}
	}
	*/
}
