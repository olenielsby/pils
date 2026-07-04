
/* This file is public domain */
#include "compile.h"
#include "qpils_standard_specials.h"
#include <QDateTime>
#include <QTimeZone>
namespace PILS
{
    const Constant *pils(const QDateTime &time)
    {
        return Timestamp::get(time.toMSecsSinceEpoch());
    }
	const Any *SystemPropertyNow::get(Runner &run) const
	{
        return Timestamp::get(QDateTime::currentMSecsSinceEpoch());
	}

	const Any *SystemPropertyTimestamp::get(Runner &run) const
	{
        long long time = QDateTime::currentMSecsSinceEpoch();
		{
            Mutex::Lock lock(Mutex::singleMutex);
            run.oldTimer = false;
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
        QDateTime time = QDateTime::fromMSecsSinceEpoch(source, QTimeZone::systemTimeZone());

        year = time.date().year();
        month = time.date().month();
        day = time.date().day();

        hour = time.time().hour();
        minute = time.time().minute();
        second = time.time().second();
        millisecond = time.time().msec();

        zoneSecond = -time.offsetFromUtc();
    }

    void PilsDate::Split::put(long long source)
    {
        QDateTime dt = QDateTime::fromMSecsSinceEpoch(source, QTimeZone::UTC);

        year  = dt.date().year();
        month = dt.date().month();
        day   = dt.date().day();

        hour        = dt.time().hour();
        minute      = dt.time().minute();
        second      = dt.time().second();
        millisecond = dt.time().msec();
    }

    long long Timestamp::Split::get()
    {
        QDateTime dt(QDate(year, month, day),
                     QTime(hour, minute, second, millisecond),
                     QTimeZone::fromSecondsAheadOfUtc(zoneSecond));
        return dt.toMSecsSinceEpoch();
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
        QDateTime dt(QDate(year, month, day),
                     QTime(hour, minute, second, millisecond),
                     QTimeZone::systemTimeZone());

        return dt.toMSecsSinceEpoch();
    }

    bool Identifier::isIdentifier() const
	{
		return true;
	}

    const Identifier *Identifier::get(QUuid value)
	{
        return (const Identifier*) IdentifierLookup(value).lookup();
	}

	int Identifier::order(const Constant *value) const
	{
		return 0;
	}

	const ReallySpecial *IdentifierLookup::newSpecial(const Constant *&link)
	{
        return new const Identifier(link, value);
	}

	bool IdentifierLookup::compare(const PILS::ReallySpecial &other) const
	{
		return other.specialComparing(*this);
	}

	void IdentifierLookup::unduplicate()
	{}

	size_t IdentifierLookup::hash() const
	{
        return qHash(value);
	}

    // const Special *SpecialReader::Format<SpecialReader::Identifier>::tryRead(const PILS_CHAR *cc, const PILS_CHAR *end, const Reading &reading) const
    // {
 //        QUuid g;
 //        unsigned char *cp = g.data4;
    // 	unsigned long accumulator (0);
    // 	if (end - cc != 36) return nullptr;
    // 	for (long i = 0; i < 36; i++)
    // 	{
    // 		const PILS_CHAR c = *(cc++);
    // 		switch (i)
    // 		{
    // 		case 8:
    // 			if (c != '-') return nullptr;
 //                g.data1 = accumulator;
    // 			break;
    // 		case 13:
    // 			if (c != '-') return nullptr;
 //                g.data2 = (unsigned short)accumulator;
    // 			break;
    // 		case 18:
    // 			if (c != '-') return nullptr;
 //                g.data3 = (unsigned short)accumulator;
    // 			break;
    // 		case 23:
    // 			if (c != '-') return nullptr;
    // 			*cp++ = (char)accumulator;
    // 			break;
    // 		case 21:
    // 		case 26:
    // 		case 28:
    // 		case 30:
    // 		case 32:
    // 		case 34:
    // 			*cp++ = (char)accumulator;
    // 		default:
    // 			accumulator <<= 4;
    // 			switch (c)
    // 			{
    // 			case '0':
    // 			case '1':
    // 			case '2':
    // 			case '3':
    // 			case '4':
    // 			case '5':
    // 			case '6':
    // 			case '7':
    // 			case '8':
    // 			case '9':
    // 				accumulator += c - '0';
    // 				break;
    // 			case 'A':
    // 			case 'B':
    // 			case 'C':
    // 			case 'D':
    // 			case 'E':
    // 			case 'F':
    // 				accumulator += c - 'A' + 10;
    // 				break;
    // 			case 'a':
    // 			case 'b':
    // 			case 'c':
    // 			case 'd':
    // 			case 'e':
    // 			case 'f':
    // 				accumulator += c - 'a' + 10;
    // 				break;
    // 			default:
    // 				return nullptr;
    // 			}
    // 		}
    // 	}
    // 	*cp++ = (char)accumulator;
    // 	return PILS::Identifier::get(g);
    // }

	void Identifier::write(Writing &writing) const
	{
		for (long i = 7; i >= 0; i--)
            writing.write(_PS("0123456789ABCDEF")[0xf & (value.data1 >> (i * 4))]);
		writing.write((PILS_CHAR)'-');
		for (long i = 3; i >= 0; i--)
            writing.write(_PS("0123456789ABCDEF")[0xf & (value.data2 >> (i * 4))]);
		writing.write((PILS_CHAR)'-');
		for (long i = 3; i >= 0; i--)
            writing.write(_PS("0123456789ABCDEF")[0xf & (value.data3 >> (i * 4))]);
		writing.write((PILS_CHAR)'-');
		for (long i = 0; i < 8; i++)
		{
			if (i == 2) writing.write((PILS_CHAR)'-');
            writing.write(_PS("0123456789ABCDEF")[value.data4[i] >> 4]);
            writing.write(_PS("0123456789ABCDEF")[0xf & value.data4[i]]);
		}
	}
}
