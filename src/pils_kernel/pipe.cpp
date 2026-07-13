/* This file is public domain */
#include "pipe.h"
namespace PILS
{
	Pipe *Sink::connectPipe(Runner &run)
	{
		if (needsResult())
			return new (run.allocate(sizeof(PipeToList))) PipeToList();
		else
			return new (run.allocate(sizeof(PipeToNowhere))) PipeToNowhere();
	}

	Pipe *Pipe::connectPipe(Runner &run)
	{
		return this;
	}

	const Step *ListExpress::step_(Runner &run) const
	{
		Pipe *pipe = run.sink->connectPipe(run);
		new (run.allocate(sizeof(PipesourceListRangeEval)))	PipesourceListRangeEval(&element[0], count->value);
		return pipe->pipeBegin(run);
	}

	Sink *PipeToNowhere::kick(Runner &run)
	{
		return this + 1;
	}

	Sink *PipeToNowhere::shortcut(Runner &run)
	{
		return run.sink = kick(run);
	}

	const Step *PipeToNowhere::pass(Runner &run, const Any *thing)
	{
		run.sink = kick(run);
		return thing->passCounted(run);
	}

	const Step *PipeToNowhere::called(Runner &run, const Empty &call)
	{
		return (run.sink = kick(run))->called(run, call);
	}

	Sink *PipeToList::kick(Runner &run)
	{
		for (std::vector<const Any*>::iterator i = elements.begin(); i != elements.end(); i++)
            run.release(*i);
		elements.~vector();
		return this + 1;
	}

	const Step *PipeToNowhere::error(Runner &run, const Any *error, const Express *what, const Any *who)
	{
		return (run.sink = kick(run))->error(run, error, what, who);
	}

	const Step *PipeToNowhere::miss(Runner &run)
	{
		Sink &next = this[1];
		return next.miss(run);
	}

	void PipeToNowhere::refer(Runner &run, const Express &what)
	{
//		Sink *next = this + 1;
		run.calling.what = &what;
//		next->refer(run, what);
	}

	const Step *PipeToNowhere::pipeBegin(Runner &run)
	{
		return (Pipesource*)run.sink;
	}

	const Step *PipeToNowhere::pipeItem(Runner &run, const Any *thing)
	{
        run.release(thing);
		return (Pipesource*)run.sink;
	}

	const Step *PipeToNowhere::pipeEnd(Runner &run)
	{
		return (run.sink = this + 1)->pass(run, (long)0);
	}

	const Step *PipeToList::pipeEnd(Runner &run)
	{
		size_t count = elements.size();
		const Any *list;
		if (count)
		{
			for (std::vector<const Any*>::iterator i = elements.begin();; i++)
			{
				if (i == elements.end())
				{
					list = ListConstant::get((const Constant *const *)(&elements[0]), count);
					break;
				}
				if ((*i)->as_Constant() == nullptr)
				{
                    list = new ((count - 1) * sizeof(Any*))	const ListExpress(&elements[0], count);
					break;
				}
			}
		}
		else
			(list = &Empty::singleton)->retain();
		elements.~vector();
		run.sink = this + 1;
		return list->passCounted(run);
	}

	const Step *PipeToList::pipeItem(Runner &run, const Any *thing)
	{
		elements.push_back(thing);
		return (Pipesource*)run.sink;
	}

	const Step *PipeToList::miss(Runner &run)
	{
		Sink &next = this[1];
		return next.miss(run);
	}

	void PipeToList::refer(Runner &run, const Express &what)
	{
		Sink &next = this[1];
		next.refer(run, what);
	}

	Pipe *SinkHoldTail::connectPipe(Runner &run)
	{
		const Any *thing = this->thing;
		const Any *whence = this->whence;
		(run.sink = this + 1)->connectPipe(run);
		return new (run.allocate(sizeof(PipeHoldTail))) PipeHoldTail(thing, whence);
	}

	Sink *PipeHoldTail::kick(Runner &run)
	{
        run.release(thing);
        run.release(run.where_);
		run.where_ = whence;
		return this + 1;
	}

	const Step *PipeHoldTail::pass(Runner &run, const Any *value)
	{
        run.release(thing);
        run.release(run.where_);
        run.where_ = whence;
		run.sink = this + 1;
		return value->passCounted(run);
	}

	const Step *PipeHoldTail::tailStep(Runner &run, const Any *thing, const Any *where_)
	{
		//reuse sink
        run.release(run.where_);
        run.where_ = where_;
        run.release(this->thing);
		return this->thing = thing;
	}

	const Step *PipeHoldTail::tailStep(Runner &run, const Any *thing)
	{
		//reuse sink
        run.release(this->thing);
		return this->thing = thing;
	}

	bool PipeHoldTail::needsResult()
	{
		Pipe &next = this[1];
		return next.needsResult();
	}

	const Step *PipeHoldTail::pipeItem(Runner &run, const Any *thing)
	{
		Pipe &next = this[1];
		return next.pipeItem(run, thing);
	}

	const Step *PipeHoldTail::pipeBegin(Runner &run)
	{
		Pipe &next = this[1];
		return next.pipeBegin(run);
	}

	const Step *PipeHoldTail::pipeEnd(Runner &run)
	{
		Pipe &next = this[1];
        run.release(thing);
        run.release(run.where_);
		run.where_ = whence;
		run.sink = &next;
		return next.pipeEnd(run);
	}

	Sink *PipeHoldTail::pushWhere(Runner &run, const Any *where_)
	{
        run.release(run.where_);
        run.where_ = where_;
		return run.sink;
	}

	Pipe *SinkWhereabout::connectPipe(Runner &run)
	{
		const Any *where_ = this->where_;
		(run.sink = this + 1)->connectPipe(run);
		return new (run.allocate(sizeof(PipeWhereabout))) PipeWhereabout(where_);
	}

	Sink *PipeWhereabout::kick(Runner &run)
	{
        run.release(run.where_);
        run.where_ = where_;
		return this + 1;
	}

	const Step *PipeWhereabout::pass(Runner &run, const Any *value)
	{
        run.release(run.where_);
        run.where_ = where_;
		run.sink = this + 1;
		return value->passCounted(run);
	}

	const Step *PipeWhereabout::tailStep(Runner &run, const Any *thing, const Any *where_)
	{
		return (run.sink = kick(run))->tailStep(run, thing, where_);
	}

	const Step *PipeWhereabout::tailStep(Runner &run, const Any *thing)
	{
		const Any *where_ = run.where_;
		run.where_ = this->where_;
		return (run.sink = this + 1)->tailStep(run, thing, where_);
	}

	bool PipeWhereabout::needsResult()
	{
		Sink &next = this[1];
		return next.needsResult();
	}

	Sink *PipeWhereabout::pushWhere(Runner &run, const Any *where_)
	{
        run.release(run.where_);
        run.where_ = where_;
		return this;
	}

	const Step *PipeWhereabout::pipeItem(Runner &run, const Any *thing)
	{
		Pipe &next = this[1];
		return next.pipeItem(run, thing);
	}

	const Step *PipeWhereabout::pipeBegin(Runner &run)
	{
		Pipe &next = this[1];
		return next.pipeBegin(run);
	}

	const Step *PipeWhereabout::pipeEnd(Runner &run)
	{
		Pipe &next = this[1];
        run.release(run.where_);
        run.where_ = where_;
		run.sink = &next;
		return next.pipeEnd(run);
	}

	const Step *Pipesource::pass(Runner &run, const Any *thing)
	{
		throw L"Bad piping";
	}

	Sink *PipesourceListRange::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *PipesourceListRange::step_(Runner &run) const
	{
		Pipe &pipe = *(Pipe*)(this + 1);
		if (source == end)
			return pipe.pipeEnd(run);
		const Any *item = *(((PipesourceListRange *)this)->source++);
		item->retain();
		return pipe.pipeItem(run, item);
	}

	const Step *PipesourceListRangeEval::step_(Runner &run) const
	{
		Pipe &pipe = *(Pipe*)(this + 1);
		if (source == end)
			return pipe.pipeEnd(run);
		new (run.allocate(sizeof(Piping))) Piping(pipe);
		return *(((PipesourceListRangeEval *)this)->source++);
	}

	const Step *Pipe::pass(Runner &run, const ListConstant &value)
	{
		new (run.allocate(sizeof(PipesourceListRange))) PipesourceListRange((const Any *const *)value.element, value.count->value);
		return pipeBegin(run);
	}

	const Step *Pipe::pass(Runner &run, const ListExpress &value)
	{
		new (run.allocate(sizeof(PipesourceListRange))) PipesourceListRange(value.element, value.count->value);
		return pipeBegin(run);
	}

	const Step *Pipe::pass(Runner &run, const ListConstant *value)
	{
		new (run.allocate(sizeof(PipeHold))) PipeHold(value);
		new (run.allocate(sizeof(PipesourceListRange))) PipesourceListRange((const Any *const *)value->element, value->count->value);
		return pipeBegin(run);
	}

	const Step *Pipe::pass(Runner &run, const ListExpress *value)
	{
		new (run.allocate(sizeof(PipeHold))) PipeHold(value);
		new (run.allocate(sizeof(PipesourceListRange))) PipesourceListRange(value->element, value->count->value);
		return pipeBegin(run);
	}

	const Step *Pipe::pass(Runner &run, const Any *anchor, const Any *const *range, size_t count)
	{
		new (run.allocate(sizeof(PipeHold))) PipeHold(anchor);
		new (run.allocate(sizeof(PipesourceListRange))) PipesourceListRange(range, count);
		return pipeBegin(run);
	}

	const Step *Pipe::pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count)
	{
		new (run.allocate(sizeof(PipeHold))) PipeHold(anchor);
		new (run.allocate(sizeof(PipesourceListRange))) PipesourceListRange((const Any* const*)range, count);
		return pipeBegin(run);
	}

	Sink *PipeHold::kick(Runner &run)
	{
        run.release(hold);
        return this + 1;
	}

	const Step *PipeHold::pass(Runner &run, const Any *thing)
	{
        run.release(hold);
        return thing->passCounted(run);
	}

	const Step *PipeHold::pipeItem(Runner &run, const Any *thing)
	{
		Pipe &next = this[1];
		return next.pipeItem(run, thing);
	}

	const Step *PipeHold::pipeBegin(Runner &run)
	{
		Pipe &next = this[1];
		return next.pipeBegin(run);
	}

	const Step *PipeHold::pipeEnd(Runner &run)
	{
		Pipe &next = this[1];
        run.release(hold);
        run.sink = &next;
		return next.pipeEnd(run);
	}

	Sink *Piping::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *Piping::pass(Runner &run, const Any *thing)
	{
		run.sink = this + 1;
		return pipe.pipeItem(run, thing);
	}

	const Step *BuiltinClicheEach::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		run.sink->connectPipe(run);
		new (run.allocate(sizeof(PipeEach))) PipeEach(what, value);
		return what.whoAttribute();
	}

	const Step *BuiltinClicheEvery::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		run.sink->connectPipe(run);
		new (run.allocate(sizeof(PipeEvery))) PipeEvery(what, value);
		return what.whoAttribute();
	}

	const Step *BuiltinClicheWhile::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		run.sink->connectPipe(run);
		new (run.allocate(sizeof(PipeWhile))) PipeWhile(what, value);
		return what.whoAttribute();
	}

	const Step *BuiltinClicheExcept::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		run.sink->connectPipe(run);
		new (run.allocate(sizeof(PipeExcept))) PipeExcept(what, value);
		return what.whoAttribute();
	}

	const Step *BuiltinClicheFind::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		new (run.allocate(sizeof(PipeFind))) PipeFind(what, value);
		return what.whoAttribute();
	}

	const Step *BuiltinClicheFold::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		new (run.allocate(sizeof(PipeFold))) PipeFold(what, value);
		return what.whoAttribute();
	}

	Sink *PipeEach::kick(Runner &run)
	{
        run.release(filter);
        return this + 1;
	}

	const Step *PipeEach::pass(Runner &run, const Any *thing)
	{
		/*Piping not applicable - perform standard method call*/
		const Any *const *dummy;
		const ClicheShort *c;
		what.callAttribute()->isNode(dummy, (const Cliche*&)c);
		const Any *call = c->node(filter);
		filter->retain();
		const Express &what = this->what;
		return (run.sink = kick(run))->call(run, what, call, thing);
	}

	const Step *PipeEach::pipeBegin(Runner &run)
	{
		Pipe &next = this[1];
		return next.pipeBegin(run);
	}

	const Step *PipeEach::pipeEnd(Runner &run)
	{
		return ((Pipe*)(run.sink = kick(run)))->pipeEnd(run);
	}

	const Step *PipeEach::pipeItem(Runner &run, const Any *thing)
	{
		new (run.allocate(sizeof(PipingEach))) PipingEach(this[1], thing);
		run.calling.who = filter;
		((Sink &)this[1]).refer(run, what);
		return thing->caller(run, *filter);
	}

	const Step *PipeEvery::pipeItem(Runner &run, const Any *thing)
	{
		new (run.allocate(sizeof(PipingEvery))) PipingEvery(this[1], thing);
		run.calling.who = filter;
		((Sink &)this[1]).refer(run, what);
		return thing->caller(run, *filter);
	}

	const Step *PipeWhile::pipeItem(Runner &run, const Any *thing)
	{
		new (run.allocate(sizeof(PipingWhile))) PipingWhile(this[1], thing);
		run.calling.who = filter;
		((Sink &)this[1]).refer(run, what);
		return thing->caller(run, *filter);
	}

	const Step *PipingEvery::error(Runner &run, const Any *error, const Express *what, const Any *who)
	{
		Pipe &pipe = this->pipe;
		for (Sink *sink = kick(run); sink != &pipe; sink = sink->kick(run));
		return (run.sink = &pipe)->error(run, error, what, who);
	}

	const Step *PipingEvery::miss(Runner &run)
	{
		return pipe.miss(run);
	}

	const Step *PipeExcept::pipeItem(Runner &run, const Any *thing)
	{
		new (run.allocate(sizeof(PipingExcept))) PipingExcept(this[1], thing);
		run.calling.who = filter;
		((Sink &)this[1]).refer(run, what);
		return thing->caller(run, *filter);
	}

	const Step *PipeFind::pipeItem(Runner &run, const Any *thing)
	{
		new (run.allocate(sizeof(PipingFind))) PipingFind(this[1], thing);
		run.calling.who = filter;
		((Sink &)this[1]).refer(run, what);
		return thing->caller(run, *filter);
	}

	Sink *PipeFold::kick(Runner &run)
	{
        run.release(fold);
        if (value) run.release(value);
		return this + 1;
	}

	const Step *PipeFold::pass(Runner &run, const Any *thing)
	{
		/*Piping not applicable - perform standard method call*/
        if (value) run.release(value); /* not supposed to happen */
		const Any *const *dummy;
		const ClicheShort *c;
		what.callAttribute()->isNode(dummy, (const Cliche*&)c);
		const Any *call = c->node(fold);
		fold->retain();
		(run.sink = kick(run))->refer(run, what);
		return run.sink->call(run, *run.calling.what, call, thing);
	}

	const Step *PipeFold::pipeBegin(Runner &run)
	{
		return (Pipesource *)run.sink;
	}

	const Step *PipeFold::pipeEnd(Runner &run)
	{
		if (value)
		{
            run.release(fold);
			const Any *value = this->value;
			run.sink = this + 1;
			return value->passCounted(run);
		}
		else
		{
			const Any *const *dummy;
			const ClicheShort *c;
			what.callAttribute()->isNode(dummy, (const Cliche*&)c);
			const Any *call = c->node(fold);
			const Express &what = this->what;
            return (run.sink = this + 1)->call(run, what, call, Empty::get());
		}
	}

	const Step *PipeFold::pipeItem(Runner &run, const Any *thing)
	{
		if (value)
		{
			new (run.allocate(sizeof(PipingFold))) PipingFold(*this);
			run.calling.who = fold;
			((Sink &)this[1]).refer(run, what);
			return fold->calling(run, *value, thing);
		}
		else
		{
			value = thing;
			return (Pipesource*)run.sink;
		}
	}

	Sink *PipingEvery::kick(Runner &run)
	{
        run.release(item);
		return this + 1;
	}

	const Step *PipingEvery::pass(Runner &run, const Any *thing)
	{
		run.sink = kick(run);
		return pipe.pipeItem(run, thing);
	}

	const Step *PipingEvery::tailStep(Runner &run, const Any *thing, const Any *where_)
	{
        run.release(item);
        Pipe &pipe = this->pipe;
		run.sink = this + 1;
		new (run.allocate(sizeof(PipingEveryTail))) PipingEveryTail(pipe, thing, run.where_);
		run.where_ = where_;
		return thing;
	}

	Sink *PipingEveryTail::kick(Runner &run)
	{
        run.release(run.where_);
		run.where_ = whence;
        run.release(thing);
		return this + 1;
	}

	const Step *PipingEveryTail::pass(Runner &run, const Any *value)
	{
        run.release(run.where_);
		run.where_ = whence;
        run.release(thing);
		Pipe &pipe = this->pipe;
		run.sink = this + 1;
		return pipe.pipeItem(run, value);
	}

	const Step *PipingEveryTail::tailStep(Runner &run, const Any *thing)
	{
        run.release(this->thing);
		return this->thing = thing;
	}

	const Step *PipingEveryTail::tailStep(Runner &run, const Any *thing, const Any *where_)
	{
        run.release(run.where_);
		run.where_ = where_;
        run.release(this->thing);
		return this->thing = thing;
	}

	Pipe *PipingEveryTail::connectPipe(Runner &run)
	{
		Pipe *splicing = pipe.splicing();
		if (splicing)
			return new (run.allocate(sizeof(PipeSplicingEvery))) PipeSplicingEvery(*splicing);
		else return Sink::connectPipe(run);
	}

	Sink *PipeSplicingEvery::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *PipeSplicingEvery::pipeBegin(Runner &run)
	{
		return (Pipesource *)run.sink;
	}

	const Step *PipeSplicingEvery::pipeItem(Runner &run, const Any *item)
	{
		return splicing.pipeItem(run, item);
	}

	const Step *PipeSplicingEvery::pipeEnd(Runner &run)
	{
		return (Pipesource*)(run.sink = ((PipingEveryTail*)(this + 1))->kick(run));
	}

	const Step *PipeSplicingEvery::pass(Runner &run, const Any *thing)
	{
		return (run.sink = this + 1)->pass(run, thing);
	}

	Sink *PipingExcept::kick(Runner &run)
	{
        run.release(item);
		return this + 1;
	}

	const Step *PipingExcept::pass(Runner &run, long dummy)
	{
		return (Pipesource*)(run.sink = kick(run));
	}

	const Step *PipingExcept::miss(Runner &run)
	{
		while (run.sink != this) run.sink = run.sink->kick(run);
		const Any *item = this->item;
		Pipe &pipe = this->pipe;
		run.sink = this + 1;
		return pipe.pipeItem(run, item);
	}

	const Step *PipingEach::called(Runner &run, const Constant &call)
	{
		return (Pipesource*)(run.sink = kick(run));
	}

	const Step *PipingEach::called(Runner &run, const Integer &call)
	{
		return (Pipesource*)(run.sink = kick(run));
	}

	const Step *PipingEach::called(Runner &run, const Empty &call)
	{
		return (Pipesource*)(run.sink = kick(run));
	}

	const Step *PipingEach::called(Runner &run, const NodeConstant &call)
	{
		return (Pipesource*)(run.sink = kick(run));
	}

	const Step *PipingEach::called(Runner &run, const ListConstant &call)
	{
		return (Pipesource*)(run.sink = kick(run));
	}

	const Step *PipingEach::called(Runner &run, const NodeExpress &call)
	{
		return (Pipesource*)(run.sink = kick(run));
	}

	const Step *PipingEach::called(Runner &run, const ListExpress &call)
	{
		return (Pipesource*)(run.sink = kick(run));
	}

	const Step *PipingEach::called(Runner &run, const Any &call, const Any *assignValue)
	{
        run.release(assignValue);
		return (Pipesource*)(run.sink = kick(run));
	}

	const Step *PipingEach::miss(Runner &run)
	{
		for (Sink *sink = run.sink->kick(run); sink != this; sink = sink->kick(run));
		return (Pipesource*)(run.sink = kick(run));
	}

	const Step *PipingWhile::called(Runner &run, const Constant &call)
	{
		Pipe *pipe = &this->pipe;
		while (run.sink != pipe) run.sink = run.sink->kick(run);
		return pipe->pipeEnd(run);
	}

	const Step *PipingWhile::called(Runner &run, const Integer &call)
	{
		Pipe *pipe = &this->pipe;
		while (run.sink != pipe) run.sink = run.sink->kick(run);
		return pipe->pipeEnd(run);
	}

	const Step *PipingWhile::called(Runner &run, const Empty &call)
	{
		Pipe *pipe = &this->pipe;
		while (run.sink != pipe) run.sink = run.sink->kick(run);
		return pipe->pipeEnd(run);
	}

	const Step *PipingWhile::called(Runner &run, const NodeConstant &call)
	{
		Pipe *pipe = &this->pipe;
		while (run.sink != pipe) run.sink = run.sink->kick(run);
		return pipe->pipeEnd(run);
	}

	const Step *PipingWhile::called(Runner &run, const ListConstant &call)
	{
		Pipe *pipe = &this->pipe;
		while (run.sink != pipe) run.sink = run.sink->kick(run);
		return pipe->pipeEnd(run);
	}

	const Step *PipingWhile::called(Runner &run, const NodeExpress &call)
	{
		Pipe *pipe = &this->pipe;
		while (run.sink != pipe) run.sink = run.sink->kick(run);
		return pipe->pipeEnd(run);
	}

	const Step *PipingWhile::called(Runner &run, const ListExpress &call)
	{
		Pipe *pipe = &this->pipe;
		while (run.sink != pipe) run.sink = run.sink->kick(run);
		return pipe->pipeEnd(run);
	}

	const Step *PipingWhile::called(Runner &run, const Any &call, const Any *assignValue)
	{
        run.release(assignValue);
		Pipe *pipe = &this->pipe;
		while (run.sink != pipe) run.sink = run.sink->kick(run);
		return pipe->pipeEnd(run);
	}

	const Step *PipingWhile::miss(Runner &run)
	{
		Pipe *pipe = &this->pipe;
		while (run.sink != pipe) run.sink = run.sink->kick(run);
		return pipe->pipeEnd(run);
	}

	const Step *PipeFind::pipeBegin(Runner &run)
	{
		return (Pipesource *)run.sink;
	}

	const Step *PipeFind::pipeEnd(Runner &run)
	{
		run.calling.what = &what;
		run.calling.who = &Empty::singleton;
		return (run.sink = kick(run))->called(run, Empty::singleton);
	}

	const Step *PipingFind::pass(Runner &run, const Any *thing)
	{
		Pipe &pipe = this->pipe;
		for(Sink *sink = kick(run); sink != &pipe; sink = sink->kick(run));
		run.sink = &pipe;
		return thing->passCounted(run);
	}

	const Step *PipingFind::tailStep(Runner &run, const Any *thing, const Any *where_)
	{
		Pipe &pipe = this->pipe;
		for(Sink *sink = kick(run); sink != &pipe; sink = sink->kick(run));
		return (run.sink = &pipe)->tailStep(run, thing, where_);
	}

	const Step *PipingFold::called(Runner &run, const Any &call, const Any *assignValue)
	{
		Pipe &pipe = this->pipe;
        run.release(assignValue);
        run.calling.who = &Empty::singleton; //must avoid dangling reference
		while (run.sink != &pipe) run.sink = run.sink->kick(run);
		return (run.sink = run.sink->kick(run))->called(run, Empty::singleton);
	}

	const Step *PipingFold::pass(Runner &run, const Any *thing)
	{
		const Any *&value = ((PipeFold&)pipe).value;
        run.release(value);
        value = thing;
		return (Pipesource*)(run.sink = this + 1);
	}

	const Step *PipingFold::error(Runner &run, const Any *error, const Express *what, const Any *who)
	{
		return kick(run)->error(run, error, what, who);
	}

	const Step *PipingFold::miss(Runner &run)
	{
		return ((Sink &)((PipeFold *)&pipe)[1]).miss(run);
	}

	Sink *PipeCount::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *PipeCount::pass(Runner &run, const PilsString &value)
	{
		return (run.sink = this + 1)->pass(run, *value.count);
	}

	const Step *PipeCount::pass(Runner &run, const ListConstant &value)
	{
		const Integer *count = value.count;
		count->retain();
		return (run.sink = this + 1)->pass(run, count);
	}

	const Step *PipeCount::pass(Runner &run, const ListExpress &value)
	{
		const Integer *count = value.count;
		count->retain();
		return (run.sink = this + 1)->pass(run, count);
	}

	const Step *PipeCount::pass(Runner &run, const PilsString *value)
	{
		const Integer *count = value->count;
		count->retain();
        run.release(value);
		return (run.sink = this + 1)->pass(run, count);
	}

	const Step *PipeCount::pass(Runner &run, const ListConstant *value)
	{
		const Integer *count = value->count;
		count->retain();
        run.release(value);
		return (run.sink = this + 1)->pass(run, count);
	}

	const Step *PipeCount::pass(Runner &run, const ListExpress *value)
	{
		const Integer *count = value->count;
		count->retain();
        run.release(value);
		return (run.sink = this + 1)->pass(run, count);
	}

	const Step *PipeCount::pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count)
	{
        run.release(anchor);
		return (run.sink = this + 1)->pass(run, (long)count);
	}

	const Step *PipeCount::pass(Runner &run, const Any *anchor, const Any *const *range, size_t count)
	{
        run.release(anchor);
        return (run.sink = this + 1)->pass(run, (long)count);
	}

	const Step *PipeCount::pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count)
	{
        run.release(anchor);
        return (run.sink = this + 1)->pass(run, (long)count);
	}

	const Step *PipeProperty::pass(Runner &run, SinkTaggedNodeBuilding &nodeBuilding)
	{
		const CallWho &what = this->what;
		run.sink = kick(run);
		Builtin::name.count_.retain();
		return (new (run.allocate(sizeof(SinkWho))) SinkWho(what, &Builtin::name.count_))->pass(run, nodeBuilding);
	}

	const Step *PipeProperty::pass(Runner &run, const Any *value)
	{
		const CallWho &what = this->what;
		return (run.sink = kick(run))->call(run, what, Builtin::name.count_, value);
	}

	const Step *PipeCount::pipeItem(Runner &run, const Any *item)
	{
        run.release(item);
        count++;
		return (Pipesource*)run.sink;
	}

	const Step *PipeProperty::pipeBegin(Runner &run)
	{
		return (Pipesource *)run.sink;
	}

	const Step *PipeCount::pipeEnd(Runner &run)
	{
		size_t count = this->count;
		return (run.sink = this + 1)->pass(run, (long)count);
	}

	const CallWho *PropertyIncrementRange::callWho(const Any *who) const
	{
        return new const WhoPropertyIncrementRange(this, who);
	}

	const CallWho *PropertyDecrementRange::callWho(const Any *who) const
	{
        return new const WhoPropertyDecrementRange(this, who);
	}

	const Step *WhoPropertyIncrementRange::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkPropertyIncrementRange))) SinkPropertyIncrementRange(*this);
		return whoAttribute();
	}

	const Step *WhoPropertyDecrementRange::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkPropertyDecrementRange))) SinkPropertyDecrementRange(*this);
		return whoAttribute();
	}

	Sink *SinkPropertyIncrementRange::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkPropertyIncrementRange::pass(Runner &run, const Any *who)
	{
		const WhoPropertyIncrementRange &what = this->what;
		return (run.sink = this + 1)->call(run, what, (const PropertyIncrementRange&)*what.callAttribute(), who);
	}

	const Step *SinkPropertyIncrementRange::pass(Runner &run, double value)
	{
		long shot = (long)value;
		if ((double)shot == value) return pass(run, shot);
		return pass(run, Float::get(value));
	}

	const Step *SinkPropertyIncrementRange::pass(Runner &run, const Integer &value)
	{
		long v = value.value;
		if (v < 0)
		{
			value.retain();
			return pass(run, (const Any*)&value);
		}
		return pass(run, v);
	}

	const Step *SinkPropertyIncrementRange::pass(Runner &run, const Integer *value)
	{
		long v = value->value;
		if (v < 0) return pass(run, (const Any*)value);
        run.release(value);
        return pass(run, v);
	}

	const Step *SinkPropertyIncrementRange::pass(Runner &run, long value)
	{
		if (value < 0) return pass(run, (const Any*)Integer::get(value));
		Pipe *pipe = (run.sink = this + 1)->connectPipe(run);
		new (run.allocate(sizeof(PipesourceIntegerStep))) PipesourceIntegerStep(1, value, 1);
		return pipe->pipeBegin(run);
	}

	const Step *SinkPropertyDecrementRange::pass(Runner &run, long value)
	{
		if (value < 0) return SinkPropertyIncrementRange::pass(run, (const Any*)Integer::get(value));
		Pipe *pipe = (run.sink = this + 1)->connectPipe(run);
		new (run.allocate(sizeof(PipesourceIntegerStep))) PipesourceIntegerStep(value, value, -1);
		return pipe->pipeBegin(run);
	}

	Sink *PipesourceIntegerStep::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *PipesourceIntegerStep::step_(Runner &run) const
	{
		Pipe &pipe = (Pipe&)this[1];
		if (((PipesourceIntegerStep *)this)->count--)
		{
			const Any *item = Integer::get(next);
			((PipesourceIntegerStep *)this)->next += delta;
			return pipe.pipeItem(run, item);
		}
		else
		{
			run.sink = &pipe;
			return pipe.pipeEnd(run);
		}
	}

	const NodeConstantShort *BuiltinClicheOperationUpDown::newNode(const Constant *&link, const Integer *value) const
	{
        return new UpDownInteger(link, *this, value);
	}

	const CallWho *BuiltinClicheOperationUpDown::whoOperation(const NodeExpressShort *operation, const Any *who) const
	{
		if (downwards)
            return new const WhoDownExpress(operation, who);
		else
            return new const WhoUpExpress(operation, who);
	}

	const CallWho *UpDownInteger::callWho(const Any *who) const
	{
		if (((BuiltinClicheOperationUpDown*)cliche)->downwards)
            return new const WhoDownInteger(this, who);
		else
            return new const WhoUpInteger(this, who);
	}

	const Step *WhoUpExpress::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkUpOperand))) SinkUpOperand(*this);
		return ((NodeExpressTiny*)callAttribute())->element[0];
	}

	const Step *WhoDownExpress::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkUpOperand))) SinkDownOperand(*this);
		return ((NodeExpressTiny*)callAttribute())->element[0];
	}

	const Step *WhoUpInteger::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkUp))) SinkUp(*this, ((const Integer*)((NodeConstantTiny*)callAttribute())->element[0])->value);
		return whoAttribute();
	}

	const Step *WhoDownInteger::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkDown))) SinkDown(*this, ((const Integer*)((NodeConstantTiny*)callAttribute())->element[0])->value);
		return whoAttribute();
	}

	Sink *SinkUpOperand::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkUpOperand::pass(Runner &run, const Any *operand)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		const Any *call = ((const ClicheShort*)((const NodeExpress*)what.callAttribute())->cliche)->node(operand);
		new (run.allocate(sizeof(SinkWho))) SinkWho(what, call);
		return what.whoAttribute();
	}

	const Step *SinkUpOperand::pass(Runner &run, long value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkUp))) SinkUp(what, value);
		return what.whoAttribute();
	}

	const Step *SinkUpOperand::pass(Runner &run, double value)
	{
		long v = (long)value;
		if ((double)v != value) return pass(run, (const Any*)Float::get(value));
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkUp))) SinkUp(what, v);
		return what.whoAttribute();
	}

	const Step *SinkUpOperand::pass(Runner &run, const Integer &value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkUp))) SinkUp(what, value.value);
		return what.whoAttribute();
	}

	const Step *SinkUpOperand::pass(Runner &run, const Integer *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		long v = value->value;
        run.release(value);
		new (run.allocate(sizeof(SinkUp))) SinkUp(what, v);
		return what.whoAttribute();
	}

	const Step *SinkDownOperand::pass(Runner &run, long value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkUp))) SinkDown(what, value);
		return what.whoAttribute();
	}

	const Step *SinkDownOperand::pass(Runner &run, double value)
	{
		long v = (long)value;
		if ((double)v != value) return SinkUpOperand::pass(run, (const Any*)Float::get(value));
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkUp))) SinkDown(what, v);
		return what.whoAttribute();
	}

	const Step *SinkDownOperand::pass(Runner &run, const Integer &value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkUp))) SinkDown(what, value.value);
		return what.whoAttribute();
	}

	const Step *SinkDownOperand::pass(Runner &run, const Integer *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		long v = value->value;
        run.release(value);
		new (run.allocate(sizeof(SinkUp))) SinkDown(what, v);
		return what.whoAttribute();
	}

	Sink *SinkUp::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkUp::pass(Runner &run, const Any *who)
	{
		const CallWho &what = this->what;
		const Integer *end = Integer::get(this->end);
		const Any *argument = what.callAttribute()->as_NodeConstant();
		if (argument)
			return (run.sink = this + 1)->call(run, what, *argument, who);
		else
		{
			argument = ((const ClicheShort*)((const NodeExpress*)what.callAttribute())->cliche)->nodeConstant(end);
			return (run.sink = this + 1)->call(run, what, argument, who);
		}
	}

	const Step *SinkUp::pass(Runner &run, double value)
	{
		long v = (long)value;
		if ((double)v != value)
			return pass(run, Float::get(value));
		else
			return pass(run, v);
	}

	const Step *SinkUp::pass(Runner &run, long begin)
	{
		long count = begin <= end ? end - begin + 1 : 0;
		Pipe &pipe = *(run.sink = this + 1)->connectPipe(run);
		new (run.allocate(sizeof(PipesourceIntegerStep))) PipesourceIntegerStep(begin, count, 1);
		return pipe.pipeBegin(run);
	}

	const Step *SinkUp::pass(Runner &run, const Integer &value)
	{
		long begin = value.value;
		long count = begin <= end ? end - begin + 1 : 0;
		Pipe &pipe = *(run.sink = this + 1)->connectPipe(run);
		new (run.allocate(sizeof(PipesourceIntegerStep))) PipesourceIntegerStep(begin, count, 1);
		return pipe.pipeBegin(run);
	}

	const Step *SinkUp::pass(Runner &run, const Integer *value)
	{
		long begin = value->value;
        run.release(value);
		long count = begin <= end ? end - begin + 1 : 0;
		Pipe &pipe = *(run.sink = this + 1)->connectPipe(run);
		new (run.allocate(sizeof(PipesourceIntegerStep))) PipesourceIntegerStep(begin, count, 1);
		return pipe.pipeBegin(run);
	}

	const Step *SinkDown::pass(Runner &run, double value)
	{
		long v = (long)value;
		if ((double)v != value)
			return SinkUp::pass(run, Float::get(value));
		else
			return pass(run, v);
	}

	const Step *SinkDown::pass(Runner &run, long begin)
	{
		long count = begin >= end ? begin - end + 1 : 0;
		Pipe &pipe = *(run.sink = this + 1)->connectPipe(run);
		new (run.allocate(sizeof(PipesourceIntegerStep))) PipesourceIntegerStep(begin, count, -1);
		return pipe.pipeBegin(run);
	}

	const Step *SinkDown::pass(Runner &run, const Integer &value)
	{
		long begin = value.value;
		long count = begin >= end ? begin - end + 1 : 0;
		Pipe &pipe = *(run.sink = this + 1)->connectPipe(run);
		new (run.allocate(sizeof(PipesourceIntegerStep))) PipesourceIntegerStep(begin, count, -1);
		return pipe.pipeBegin(run);
	}

	const Step *SinkDown::pass(Runner &run, const Integer *value)
	{
		long begin = value->value;
        run.release(value);
		long count = begin >= end ? begin - end + 1 : 0;
		Pipe &pipe = *(run.sink = this + 1)->connectPipe(run);
		new (run.allocate(sizeof(PipesourceIntegerStep))) PipesourceIntegerStep(begin, count, -1);
		return pipe.pipeBegin(run);
	}

	const CallWho *PropertyReverse::callWho(const Any *who) const
	{
        return new  const WhoReverse(this, who);
	}

	const Step *WhoReverse::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkReverse))) SinkReverse(*this);
		return whoAttribute();
	}

	Sink *SinkReverse::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkReverse::pass(Runner &run, const Any *who)
	{
		const CallWho &what = this->what;
		return (run.sink = this + 1)->call(run, what, *what.callAttribute(), who);
	}

	const Step *SinkReverse::pass(Runner &run, const PilsString *value)
	{
		return pass(run, value, value->value, value->count->value);
	}

	const Step *SinkReverse::pass(Runner &run, const ListConstant *value)
	{
		return pass(run, value, value->element, value->count->value);
	}

	const Step *SinkReverse::pass(Runner &run, const ListExpress *value)
	{
		return pass(run, value, value->element, value->count->value);
	}

	const Step *SinkReverse::pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count)
	{
		PILS_CHAR *buffer = new PILS_CHAR[count];
		for (size_t i = 0; i < count; i++) buffer[i] = range[count - i - 1];
		const PilsString *result = PilsString::get(buffer, count);
        delete[] buffer;
        run.release(anchor);
		return (run.sink = this + 1)->pass(run, result);
	}

	const Step *SinkReverse::pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count)
	{
		Pipe &pipe = *(run.sink = this + 1)->connectPipe(run);
		new (run.allocate(sizeof(PipeHold))) PipeHold(anchor);
		new (run.allocate(sizeof(PipesourceListRangeReverse))) PipesourceListRangeReverse((const Any *const *)range, count);
		return pipe.pipeBegin(run);
	}

	const Step *SinkReverse::pass(Runner &run, const Any *anchor,const Any *const *range, size_t count)
	{
		Pipe &pipe = *(run.sink = this + 1)->connectPipe(run);
		new (run.allocate(sizeof(PipeHold))) PipeHold(anchor);
		new (run.allocate(sizeof(PipesourceListRangeReverse))) PipesourceListRangeReverse(range, count);
		return pipe.pipeBegin(run);
	}

	const Step *PipesourceListRangeReverse::step_(Runner &run) const
	{
		if (source != end)
		{
			const Any *item = *--((PipesourceListRangeReverse *)this)->source;
			item->retain();
			return ((Pipe*)(this + 1))->pipeItem(run, item);
		}
		else return ((Pipe*)(run.sink = (PipesourceListRangeReverse *)this + 1))->pipeEnd(run);
	}

	const CallWho *PropertySplice::callWho(const Any *who) const
	{
        return new const WhoPropertySplice(this, who);
	}

	const Step *WhoPropertySplice::step_(Runner &run) const
	{
		run.sink->connectPipe(run);
		new (run.allocate(sizeof(PipeSplice))) PipeSplice(*this);
		return whoAttribute();
	}

	Sink *PipeSplice::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *PipeSplice::pass(Runner &run, const Any *who)
	{
		const CallWho &what = this->what;
		return (run.sink = this + 1)->call(run, what, Builtin::name.splice, who);
	}

	const Step *PipeSplice::pipeBegin(Runner &run)
	{
		return ((Pipe*)(this + 1))->pipeBegin(run);
	}

	const Step *PipeSplice::pipeEnd(Runner &run)
	{
		return ((Pipe*)(run.sink = this + 1))->pipeEnd(run);
	}

	const Step *PipeSplice::pipeItem(Runner &run, const Any *thing)
	{
		const Any *const *element;
		const Integer *count;
		if (thing->isList(element, count))
		{
			new (run.allocate(sizeof(PipingSplice))) PipingSplice(this[1], thing);
			return new (run.allocate(sizeof(PipesourceListRange))) PipesourceListRange(element, count->value);
		}
		else return ((Pipe*)(this + 1))->pipeItem(run, thing);
	}

	Sink *PipingSplice::kick(Runner &run)
	{
        run.release(anchor);
		return this + 1;
	}

	Pipe *Pipe::splicing()
	{
		return nullptr;
	}

	Sink *Pipe::shortcut(Runner &run)
	{
		return this;
	}

	const Step *PipingSplice::pass(Runner &run, const Any *thing)
	{
        run.release(anchor);
        Pipe &pipe = this->pipe;
		run.sink = this + 1;
		return pipe.pipeItem(run, thing);
	}

	const Step *PipingSplice::pipeBegin(Runner &run)
	{
		return (Pipesource*)run.sink;
	}

	const Step *PipingSplice::pipeEnd(Runner &run)
	{
        run.release(anchor);
        return (Pipesource*)(run.sink = this + 1);
	}

	const Step *PipingSplice::pipeItem(Runner &run, const Any *thing)
	{
		return pipe.pipeItem(run, thing);
	}

	Pipe *PipeSplice::splicing()
	{
		return this + 1;
	}

	Sink *PipeListSeparator::kick(Runner &run)
	{
        run.release(separator);
		return this + 1;
	}

	const Step *PipeListSeparator::pass(Runner &run, const Any *who)
	{
		const Any *argument = BuiltinClicheSplice::singleton.node(separator);
		run.sink = next().kick(run);
		return run.sink->call(run, what, argument, who);
	}

	const Step *PipeListSeparator::pipeBegin(Runner &run)
	{
		return next().pipeBegin(run);
	}

	const Step *PipeListSeparator::pipeEnd(Runner &run)
	{
		Pipe &next = this[1];
        run.release(separator);
        run.sink = &next;
		return next.pipeEnd(run);
	}

	const Step *PipeListSeparator::pipeItem(Runner &run, const Any *item)
	{
		if (insertSeparator)
		{
			new (run.allocate(sizeof(PipesourceInsert))) PipesourceInsert(next(), item);
			separator->retain();
			return next().pipeItem(run, separator);
		}
		else
		{
			insertSeparator = true;
			return next().pipeItem(run, item);
		}
	}

	Sink *PipesourceInsert::kick(Runner &run)
	{
        run.release(item);
        return this + 1;
	}

	const Step *PipesourceInsert::step_(Runner &run) const
	{
		Pipe &pipe = this->pipe;
		const Any *item = this->item;
		run.sink = (PipesourceInsert *)this + 1;
		return pipe.pipeItem(run, item);
	}

	const Step *PipeCounting::pipeItem(Runner &run, const Any *thing)
	{
		const Number *counting = Number::get(++count);
		new (run.allocate(sizeof(PipingEach))) PipingEach(this[1], counting);
		((Sink &)this[1]).refer(run, what);
		return (run.calling.who = filter)->calling(run, *counting, thing);
	}

	/*Copied from PipeEach - size is implied in: this + 1*/
	const Step *PipeCounting::pass(Runner &run, const Any *thing)
	{
		/*Piping not applicable - perform standard method call*/
		const Any *const *dummy;
		const ClicheShort *c;
		what.callAttribute()->isNode(dummy, (const Cliche*&)c);
		const Any *call = c->node(filter);
		const Express &what = this->what;
		return (run.sink = this + 1)->call(run, what, call, thing);
	}

	/*Copied from PipeEach - size is implied in: this + 1*/
	Sink *PipeCounting::kick(Runner &run)
	{
        run.release(filter);
		return this + 1;
	}

	/*Copied from PipeEach - size is implied in: this + 1*/
	const Step *PipeCounting::pipeBegin(Runner &run)
	{
		Pipe &next = this[1];
		return next.pipeBegin(run);
	}

	const Step *BuiltinClicheFirst::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		run.sink->connectPipe(run);
		new (run.allocate(sizeof(PipeFirst))) PipeFirst(what, value);
		return what.whoAttribute();
	}

	const Step *PipeFirst::pipeItem(Runner &run, const Any *item)
	{
		return ((Pipe*)(this + 1))->pipeItem(run, item);
	}

	const Step *PipeFirst::pipeBegin(Runner &run)
	{
		new (run.allocate(sizeof(PipesourceFirst))) PipesourceFirst(*this);
		return ((Pipe*)(this + 1))->pipeBegin(run);
	}

	const Step *PipeFirst::pipeMyItem(Runner &run)
	{
		const Any *item = filter;
		(filter = &Empty::singleton)->retain(); //dummy
		return ((Pipe*)(this + 1))->pipeItem(run, item);
	}

	Sink *PipesourceFirst::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *PipesourceFirst::step_(Runner &run) const
	{
		PipeFirst &pipeFirst = this->pipeFirst;
		run.sink = (PipesourceFirst *)this + 1;
		return pipeFirst.pipeMyItem(run);
	}

	const Step *BuiltinClicheMin::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *filter) const
	{
		new (run.allocate(sizeof(PipeMin))) PipeMin(what, filter);
		return what.whoAttribute();
	}

	const Step *BuiltinClicheMax::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *filter) const
	{
		new (run.allocate(sizeof(PipeMax))) PipeMax(what, filter);
		return what.whoAttribute();
	}

	Sink *PipeMinMax::kick(Runner &run)
	{
        run.release(filter);
		if(key)
		{
            run.release(key);
            run.release(value);
		}
		return this + 1;
	}

	const Step *PipeMinMax::pipeItem(Runner &run, const Any *thing)
	{
		new (run.allocate(sizeof(PipingMinMax))) PipingMinMax(*this, thing);
		run.calling.who = filter;
		((Sink &)this[1]).refer(run, what);
		return thing->caller(run, *filter);
	}

	const Step *PipeMinMax::pipeEnd(Runner &run)
	{
		const Any *value = this->value;
		if (value)
		{
            run.release(key);
            run.release(filter);
			run.sink = this + 1;
			return value->passCounted(run);
		}
		else return PipeFind::pipeEnd(run);
	}

	bool PipeMin::better(const Constant *key)
	{
		return key->order(this->key) < 0;
	}

	bool PipeMax::better(const Constant *key)
	{
		return key->order(this->key) > 0;
	}

	Sink *PipingMinMax::kick(Runner &run)
	{
        run.release(item);
		return this + 1;
	}

	const Step *PipingMinMax::miss(Runner &run)
	{
		while(run.sink != this + 1) run.sink = run.sink->kick(run);
		return (Pipesource *)(this + 1);
	}

	const Step *PipingMinMax::pass(Runner &run, const Constant *value)
	{
		if (!pipe.key || pipe.better(value))
		{
			if (pipe.value)
			{
                run.release(pipe.key);
                run.release(pipe.value);
			}
			pipe.key = value;
			pipe.value = item;
		}
		else
		{
            run.release(value);
            run.release(item);
		}
		return (Pipesource *)(run.sink = this + 1);
	}

	const Step *PipingMinMax::pass(Runner &run, const Any *value)
	{
        run.release(value);
        run.release(item);
		return (Pipesource *)(run.sink = this + 1);
	}

	const Step *BuiltinClicheSum::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *filter) const
	{
		new (run.allocate(sizeof(PipeSum))) PipeSum(what, filter);
		return what.whoAttribute();
	}

	Sink *PipeSum::kick(Runner &run)
	{
        run.release(filter);
		return this + 1;
	}

	const Step *PipeSum::pipeItem(Runner &run, const Any *thing)
	{
		new (run.allocate(sizeof(PipingSum))) PipingSum(*this, thing);
		run.calling.who = filter;
		((Sink &)this[1]).refer(run, what);
		return thing->caller(run, *filter);
	}

	const Step *PipeSum::pipeEnd(Runner &run)
	{
		const double sum = this->sum;
        run.release(filter);
		return (run.sink = this + 1)->pass(run, sum);
	}

	Sink *PipingSum::kick(Runner &run)
	{
        run.release(item);
		return this + 1;
	}

	const Step *PipingSum::miss(Runner &run)
	{
		while(run.sink != this + 1) run.sink = run.sink->kick(run);
		return (Pipesource *)(this + 1);
	}

	const Step *PipingSum::pass(Runner &run, long value)
	{
		pipe.sum += value;
		return (Pipesource *)(run.sink = this + 1);
	}

	const Step *PipingSum::pass(Runner &run, double value)
	{
		pipe.sum += value;
		return (Pipesource *)(run.sink = this + 1);
	}

	const Step *PipingSum::pass(Runner &run, const Integer &value)
	{
		pipe.sum += value.value;
		return (Pipesource *)(run.sink = this + 1);
	}

	const Step *PipingSum::pass(Runner &run, const Float &value)
	{
		pipe.sum += value.value;
		return (Pipesource *)(run.sink = this + 1);
	}

	const Step *PipingSum::pass(Runner &run, const Integer *value)
	{
		pipe.sum += value->value;
        run.release(value);
        run.release(item);
		return (Pipesource *)(run.sink = this + 1);
	}

	const Step *PipingSum::pass(Runner &run, const Float *value)
	{
		pipe.sum += value->value;
        run.release(value);
        run.release(item);
        return (Pipesource *)(run.sink = this + 1);
	}

	const Step *PipingSum::pass(Runner &run, const Any *value)
	{
        run.release(value);
        run.release(item);
        return (Pipesource *)(run.sink = this + 1);
	}

	bool Special::enumerate(Runner &run) const
	{
		return false;
	}

	const Step *Pipe::pass(Runner &run, const Special *value)
	{
		if (value->enumerate(run))
		{
            run.release(value);
			return pipeBegin(run);
		}
		else return ((Sink *)this)->pass(run, (const Any *)value);
	}

	const CallWho *PredefinedAggregateFunctionName::callWho(const Any *who) const
	{
        return new AggregateCallWho(this, who);
	}

	const Step *AggregateCallWho::step_(Runner &run) const
	{
		((PredefinedAggregateFunctionName *)callAttribute())->pushAggregatePipe(run, *this);
		return whoAttribute();
	}

	void PredefinedNameSum::pushAggregatePipe(Runner &run, const AggregateCallWho &what) const
	{
		new (run.allocate(sizeof(PipeAggregateSum))) PipeAggregateSum(what);
	}

	void PredefinedNameMin::pushAggregatePipe(Runner &run, const AggregateCallWho &what) const
	{
		new (run.allocate(sizeof(PipeAggregateMin))) PipeAggregateMin(what);
	}

	void PredefinedNameMax::pushAggregatePipe(Runner &run, const AggregateCallWho &what) const
	{
		new (run.allocate(sizeof(PipeAggregateMax))) PipeAggregateMax(what);
	}

	const Step *PipeAggregate::pass(Runner &run, const Any *who)
	{
		const AggregateCallWho &what = this->what;
		return (run.sink = this + 1)->call(run, what, *what.callAttribute(), who);
	}

	const Step *PipeAggregate::pipeBegin(Runner &run)
	{
		return run.sink;
	}

	Sink *PipeAggregateSum::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *PipeAggregateSum::pipeItem(Runner &run, const Any *item)
	{
		double value;
		if (item->isNumber(value))
		{
			sum += value;
            run.release(item);
			return run.sink;
		}
		Sink &next = this[1];
		new (run.allocate(sizeof(MissAssignCall))) MissAssignCall(*what.callAttribute(), item);
		return next.miss(run);
	}

	const Step *PipeAggregateSum::pipeEnd(Runner &run)
	{
		double value = sum;
		return (run.sink = this + 1)->pass(run, value);
	}

	Sink *PipeAggregateMinMax::kick(Runner &run)
	{
        if (item) run.release(item);
		return this + 1;
	}

	const Step *PipeAggregateMinMax::pipeEnd(Runner &run)
	{
		if (const Any *item = this->item)
		{
			run.sink = this + 1;
			return item->passCounted(run);
		}
		Sink &next = this[1];
		new (run.allocate(sizeof(MissCall))) MissCall(*what.callAttribute());
		return next.miss(run);
	}

	const Step *PipeAggregateMin::pipeItem(Runner &run, const Any *candidate)
	{
		if (const Constant *constantCandidate = candidate->as_Constant())
		{
			if (item == nullptr)
				item = constantCandidate;
			else if (constantCandidate->order(item) < 0)
			{
                run.release(item);
					item = constantCandidate;
			}
            else run.release(constantCandidate);
			return run.sink;
		}
		Sink &next = this[1];
		new (run.allocate(sizeof(MissAssignCall))) MissAssignCall(*what.callAttribute(), candidate);
		return next.miss(run);
	}

	const Step *PipeAggregateMax::pipeItem(Runner &run, const Any *candidate)
	{
		if (const Constant *constantCandidate = candidate->as_Constant())
		{
			if (item == nullptr)
				item = constantCandidate;
			else if (constantCandidate->order(item) > 0)
			{
                run.release(item);
					item = constantCandidate;
			}
            else run.release(constantCandidate);
			return run.sink;
		}
		Sink &next = this[1];
		new (run.allocate(sizeof(MissAssignCall))) MissAssignCall(*what.callAttribute(), candidate);
		return next.miss(run);
	}
}
