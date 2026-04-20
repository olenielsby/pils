/* This file is public domain */
#include "pilserror.h"
namespace PILS
{
	const Step *Sink::error(Runner &run, const Any *thing, const Express *what, const Any *who)
	{
        const Error *error = new const Error(thing);
        // const int debugOutputLevels = 5;
        // error->writeToDebugOutput(debugOutputLevels);
		new (run.allocate(sizeof(SinkErrorCall))) SinkErrorCall(error, what, who);
		run.calling.who = who;
		run.calling.what = what;
		return run.where_->calling(run, *error);
	}

	const Any *BuiltinClicheError::node(const Constant *element) const
	{
        return new const Error(element);
	}

	const NodeExpressShort *BuiltinClicheError::node(const Express *element) const
	{
        return new const Error(element);
	}

	Sink *SinkErrorCall::kick(Runner &run)
	{
		error->release();
		what->release();
		who->release();
		return this + 1;
	}

	const Step *SinkErrorCall::pass(Runner &run, const Any *value)
	{
		run.sink = kick(run);
		return value->passCounted(run);
	}

	const Step *SinkErrorCall::tailStep(Runner &run, const Any *thing, const Any *where_)
	{
		return (run.sink = kick(run))->tailStep(run, thing, where_);
	}
	
	const Step *SinkErrorCall::called(Runner &run, const NodeExpress &call)
	{
		const Any *error = &call; // call.element[0];
		error->retain();
		return pass(run, error);
	}

	const Step *Error::catching(Runner &run, Catch &catching) const
	{
		const Any *error = element[0];
		if (error->as_Constant())
		{
			error->retain();
			for (Sink *sink = run.sink; sink != &catching; sink = sink->kick(run));
			const Express *what = &catching.what;
			what->retain();
			const Any *who = &catching.who;
			who->retain();
			return (run.sink = catching.kick(run))->error(run, error, what, who);
		}
		else
		{
			new (run.allocate(sizeof(SinkComputeError))) SinkComputeError(catching);
			return error;
		}
	}

	const Step *ErrorTrailer::catching(Runner &run, Catch &catching) const
	{
		const Any *error = element[0];
		if (error->as_Constant())
		{
			error->retain();
			for (Sink *sink = run.sink; sink != &catching; sink = sink->kick(run));
			const Express *what = &catching.what;
			what->retain();
			const Any *who = &catching.who;
			who->retain();
			return (run.sink = catching.kick(run))->error(run, error, what, who);
		}
		else
		{
			new (run.allocate(sizeof(SinkComputeError))) SinkComputeError(catching);
			return error;
		}
	}

	Sink *SinkComputeError::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkComputeError::pass(Runner &run, const Any *error)
	{
		for (Sink *sink = this + 1; sink != &catching; sink = sink->kick(run));
		const Express *what = &catching.what;
		what->retain();
		const Any *who = &catching.who;
		who->retain();
		return (run.sink = catching.kick(run))->error(run, error, what, who);
	}

	Sink *SinkError::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkError::pass(Runner &run, const Any *error)
	{
		const Express *what = run.calling.what;
		what->retain();
		const Any *who = run.calling.who;
		who->retain();
		return (run.sink = kick(run))->error(run, error, what, who);
	}
}
