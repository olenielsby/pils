/* This file is public domain */
#ifndef DEFINE_PILS_PILSERROR_H
#define DEFINE_PILS_PILSERROR_H
#include "catchy.h"
namespace PILS
{
	class SinkErrorCall
		: public Sink
	{
	public:
		SinkErrorCall(Error *error, const Express *what, const Any *who)
			: error(error), what(what), who(who)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
		const Step *tailStep(Runner &run, const Any *thing, const Any *where_);
		const Step *called(Runner &run, const NodeExpress &call);
	private:
		Error *error;
		const Express *what;
		const Any *who;
	};

	class SinkComputeError
		: public Sink
	{
	public:
		SinkComputeError(Catch &catching)
			: catching(catching)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
	private:
		Catch &catching;
	};

	class SinkError
		: public Sink
	{
	public:
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
	};

}
#endif
