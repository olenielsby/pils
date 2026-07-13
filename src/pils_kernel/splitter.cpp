/* This file is public domain */
#include "splitter.h"
namespace PILS
{
	const ClicheLong *PredefinedNameSplit::newCliche(const Constant *&link, const Constant *const *a, size_t c) const
	{
		if (a[0] == &Empty::singleton)
            return	new ((c - 1) * sizeof(Constant*)) const ClicheSplitter(link, this, a, c);
        else return PredefinedName::newCliche(link, a, c);
	}

	const NodeConstantLong *ClicheSplitter::newNodeConstant(const Constant *&link, const Constant *const *value) const
	{
        return new ((count - 1) * sizeof(Constant*)) const Splitter(link, *this, value);
	}

	const CallWho *Splitter::callWho(const Any *who) const
	{
        return new const WhoSplitter(this, who);
	}

	const Step *WhoSplitter::step_(Runner &run) const
	{
		callAttribute()->retain();
		new (run.allocate(sizeof(SinkWhoSplitter))) SinkWhoSplitter(*this, callAttribute());
		return whoAttribute();
	}

	const Step *SinkWhoSplitter::pass(Runner &run, const PilsString *value)
	{
		return pass(run, value, value->value, value->count->value);
	}

	const Step *SinkWhoSplitter::pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count)
	{
		const Splitter *splitter = (const Splitter *)argument;
		Pipe &pipe = *(run.sink = this + 1)->connectPipe(run);
		new (run.allocate(sizeof(PipesourceSplitter))) PipesourceSplitter(splitter, anchor, range, range + count);
		return pipe.pipeBegin(run);
	}

	Sink *PipesourceSplitter::kick(Runner &run)
	{
        run.release(anchor);;
        run.release(splitter);;
		return this + 1;
	}

	const Step *PipesourceSplitter::step_(Runner &run) const
	{
		if (at < end)
			return (new (run.allocate(sizeof(SplitsinkRoot))) SplitsinkRoot(*(PipesourceSplitter *)this))->back(run);
		else return ((Pipe *)(run.sink = ((PipesourceSplitter *)this)->kick(run)))->pipeEnd(run);
	}

	Sink *Splitsink::kick(Runner &run)
	{
		return &splitting;
	}

	const Step *Splitsink::pass(Runner &run, const Any *thing)
	{
        run.release(thing);
		return back(run);
	}

	const Step *Splitsink::pass(Runner &run, const Integer &count)
	{
		const PILS_CHAR *to = at + count.value;
		if (to >= at && to <= splitting.end)
			return done(run, to);
		else return back(run);
	}

	const Step *Splitsink::pass(Runner &run, const Cliche &name)
	{
		const Splitter &splitter = *splitting.splitter;
		if (const Constant *options = splitter.cliche->lookupNonempty(&splitter, 1, &name))
			return (new (run.allocate(sizeof(SplitsinkOptions))) SplitsinkOptions(splitting, at, options))->back(run);
		else
			return back(run);
	}

	const Step *Splitsink::pass(Runner &run, const PilsString &value)
	{
		size_t count = value.count->value;
		if (count == 3 && value.value[1] == '-')
		{
			if (at < splitting.end && (unsigned int)*at >= (unsigned int)value.value[0] && (unsigned int)*at <= (unsigned int)value.value[2])
				return done(run, at + 1);
			else return back(run);
		}
		else
		{
			if (at + count > splitting.end) return back(run);
			for (size_t i = 0; i < count; i++)
				if (at[i] != value.value[i]) return back(run);
			return done(run, at + count);
		}
	}

	const Step *Splitsink::pass(Runner &run, const NodeConstantShort &value)
	{
		if (value.cliche == &BuiltinClicheOperationTimes::singleton)
		{
			return (new (run.allocate(sizeof(SplitsinkRepeat))) SplitsinkRepeat(splitting, at, value.element[0], true))->back(run);
		}
		else if (value.cliche == &BuiltinClicheOperationPlus::singleton)
		{
			return (new (run.allocate(sizeof(SplitsinkRepeat))) SplitsinkRepeat(splitting, at, value.element[0], false))->back(run);
		}
		else if (value.cliche == &BuiltinClicheOperationMinus::singleton)
		{
			return (new (run.allocate(sizeof(SplitsinkNot))) SplitsinkNot(splitting, at, value.element[0]))->back(run);
		}
		else if (value.cliche == &BuiltinClicheOperationDivide::singleton)
		{
			return (new (run.allocate(sizeof(SplitsinkLast))) SplitsinkLast(splitting, at, value.element[0]))->back(run);
		}
		else if (value.cliche == &BuiltinClicheSearchContains::plain)
		{
			return (new (run.allocate(sizeof(SplitsinkFind))) SplitsinkFind(splitting, at, value.element[0], false))->back(run);
		}
		else if (value.cliche == &BuiltinClicheSearchTill::plain)
		{
			return (new (run.allocate(sizeof(SplitsinkFind))) SplitsinkFind(splitting, at, value.element[0], true))->back(run);
		}
		else return back(run);
	}

	const Step *Splitsink::pass(Runner &run, const ListConstant &value)
	{
		return (new (run.allocate(sizeof(SplitsinkCompound))) SplitsinkCompound(splitting, at, value))->done(run, at);
	}

	const Step *SplitsinkRoot::back(Runner &run)
	{
		if (optionAt < optionEnd)
			return *optionAt++;
		else
		{
			const Constant *e[2];
			(splitting.last = e[0] = &Empty::singleton)->retain();
			e[1] = PilsString::get(splitting.at++, 1);
			const ListConstant *item = ListConstant::get(e, 2);
			run.sink = &splitting;			
			return splitting.pipe().pipeItem(run, item);
		}
	}

	const Step *SplitsinkRoot::done(Runner &run, const PILS_CHAR *at)
	{
		if (at == splitting.at)	return back(run); // prevent infinite loops
		const Constant *e[2];
		(splitting.last = e[0] = optionAt[-1])->retain();
		e[1] = PilsString::get(splitting.at, at - splitting.at);
		splitting.at = at;
		const ListConstant *item = ListConstant::get(e, 2);
		run.sink = &splitting;
		return splitting.pipe().pipeItem(run, item);
	}

	const Step *SplitsinkOptions::back(Runner &run)
	{
		if (optionAt < optionEnd)
			return *optionAt++;
		else
		{
			Splitsink &next = this[1];
			run.sink = &next;
			return next.back(run);
		}
	}

	const Step *SplitsinkOptions::done(Runner &run, const PILS_CHAR *at)
	{
		Splitsink &next = this[1];
		run.sink = &next;
		return next.done(run, at);
	}

	const Step *SplitsinkRepeat::back(Runner &run)
	{
		if (optionAt < optionEnd)
			return *optionAt++;
		else
		{
			Splitsink &next = this[1];
			run.sink = &next;
			if (ok) return next.done(run, at);
			else return next.back(run);
		}
	}

	const Step *SplitsinkRepeat::done(Runner &run, const PILS_CHAR *at)
	{
		if (this->at == at) return back(run); // prevent infinite loops
		this->at = at;
		optionAt = optionBegin;
		ok = true;
		return *optionAt++;
	}

	const Step *SplitsinkFind::back(Runner &run)
	{
		if (optionAt < optionEnd)
			return *optionAt++;
		else if (at < splitting.end)
		{
			at++;
			optionAt = optionBegin;
			return *optionAt++;
		}
		else
		{
			Splitsink &next = this[1];
			run.sink = &next;
			if (ok) return next.done(run, at);
			else return next.back(run);
		}
	}

	const Step *SplitsinkFind::done(Runner &run, const PILS_CHAR *at)
	{
		if (ok) at = this->at;
		Splitsink &next = this[1];
		run.sink = &next;
		return next.done(run, at);
	}

	const Step *SplitsinkCompound::back(Runner &run)
	{
		Splitsink &next = this[1];
		run.sink = &next;
		return next.back(run);
	}

	const Step *SplitsinkCompound::done(Runner &run, const PILS_CHAR *at)
	{
		if (optionAt < optionEnd)
		{
			this->at = at;
			return *optionAt++;
		}
		else
		{
			Splitsink &next = this[1];
			run.sink = &next;
			return next.done(run, at);
		}
	}

	const Step *SplitsinkCompound::pass(Runner &run, const ListConstant &value)
	{
		return (new (run.allocate(sizeof(SplitsinkOptions))) SplitsinkOptions(splitting, at, value))->back(run);
	}

	const Step *SplitsinkNot::back(Runner &run)
	{
		if (optionAt < optionEnd)
		{
			this->at = at;
			return *optionAt++;
		}
		else
		{
			Splitsink &next = this[1];
			run.sink = &next;
			return next.done(run, at);
		}
	}

	const Step *SplitsinkNot::done(Runner &run, const PILS_CHAR *at)
	{
		Splitsink &next = this[1];
		run.sink = &next;
		return next.back(run);
	}

	const Step *SplitsinkLast::pass(Runner &run, const Cliche &name)
	{
		if (splitting.last == &name) return done(run, at);
		else return back(run);
	}

	const Step *SplitsinkLast::pass(Runner &run, const ListConstant &value)
	{
		for (long i = 0; i < value.count->value; i++)
			if (splitting.last == value.element[i])
				return done(run, at);
		return back(run);
	}

	const Step *SplitsinkLast::pass(Runner &run, const NodeConstantShort &value)
	{
		return back(run);
	}

	const Step *SplitsinkLast::pass(Runner &run, const PilsString &value)
	{
		return back(run);
	}
}
