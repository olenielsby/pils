/* This file is public domain */
#ifndef DEFINE_PILSTIME_H
#define DEFINE_PILSTIME_H
#include "datamodel.h"

namespace PILS
{
	class Timesplit : Converter
	{
	public:
		unsigned short year;
		unsigned short month;
		unsigned short day;
		unsigned short hour;
		unsigned short minute;
		unsigned short second;
		unsigned long nanosecond;
		bool zoneValid;
		long zoneSecond;
		const Constant *timestamp();
		bool convert(const Timestamp &timestamp);
	};
}

#endif
