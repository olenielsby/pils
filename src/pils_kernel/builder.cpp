/* This file is public domain */
#include "builder.h"
namespace PILS
{
	const Any *BuiltinClicheBuilding::node(const Any *const *element) const
	{
		if (element[1]->as_Constant())
            return new Building(*this, element);
		else return BuiltinPokerClicheTrailer::node(element);
	}

	const Step *Building::calling(Runner &run, const Constant &call) const
	{
		if (&call == element[1])
		{
			for (SinkTagged *sink = run.sinkTagChain; sink; sink = sink->chain)
			{
				if (&sink->tag == this)
					return ((SinkTaggedBuilding*)sink)->calling(run, *this);
			}
		}
		return element[0]->calling(run, call);
	}

	const Step *Building::calling(Runner &run, const Integer &call) const
	{
		return element[0]->calling(run, call);
	}

	const Step *Building::calling(Runner &run, const ListConstant &call) const
	{
		return element[0]->calling(run, call);
	}

	const Step *Building::calling(Runner &run, const Empty &call) const
	{
		return element[0]->calling(run, call);
	}

	const Step *Building::calling(Runner &run, const NodeExpress &call) const
	{
		return element[0]->calling(run, call);
	}

	const Step *Building::calling(Runner &run, const ListExpress &call) const
	{
		return element[0]->calling(run, call);
	}

	const Step *Building::calling(Runner &run, const NodeConstant &call) const
	{
		if (&call == element[1])
		{
			for (SinkTagged *sink = run.sinkTagChain; sink; sink = sink->chain)
			{
				if (&sink->tag == this)
					return ((SinkTaggedBuilding*)sink)->calling(run, *this);
			}
		}
		return element[0]->calling(run, call);
	}

	const Step *Building::calling(Runner &run, const Any &call, const Any *assignValue) const
	{
		if (&call == element[1])
		{
			for (SinkTagged *sink = run.sinkTagChain; sink; sink = sink->chain)
			{
				if (&sink->tag == this)
					return ((SinkTaggedBuilding*)sink)->calling(run, *this, assignValue);
			}
		}
		return element[0]->calling(run, call, assignValue);
	}

	const Express *Building::findCatchTag() const
	{
		return element[0]->findCatchTag();
	}

	Sink *PipesourceListBuilderBegin::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *PipesourceListBuilderBegin::step_(Runner &run) const
	{
		run.sink = (PipesourceListBuilderBegin *)this + 1;
		return &thing;
	}

	Sink *SinkTaggedListBuilding::kick(Runner &run)
	{
		run.sinkTagChain = chain;
		run.where_ = ((const NodeExpress&)tag).element[0];
		tag.release();
		return this + 1;
	}

	const Step *SinkTaggedListBuilding::calling(Runner &run, const Building &tag)
	{
		return tag.element[0]->calling(run, *(const NodeConstant*)tag.element[1]);
	}

	const Step *SinkTaggedListBuilding::calling(Runner &run, const Building &tag, const Any *assignValue)
	{
		assignValue->retain();
		new (run.allocate(sizeof(PipesourceHold))) PipesourceHold(assignValue);
		return ((Pipe*)(this + 1))->pipeItem(run, assignValue);
	}

	Sink *PipesourceHold::kick(Runner &run)
	{
		hold->release();
		return this + 1;
	}

	const Step *PipesourceHold::step_(Runner &run) const
	{
		const Any *hold = this->hold;
		run.sink = (PipesourceHold*)this + 1;
		return hold->passCounted(run);
	}

	const Step *SinkTaggedListBuilding::pass(Runner &run, long value)
	{
		run.sinkTagChain = chain;
		run.where_ = ((const NodeExpress&)tag).element[0];
		tag.release();
		return ((Pipe*)(run.sink = this + 1))->pipeEnd(run);
	}

	const Step *Sink::pass(Runner &run, SinkTaggedNodeBuilding &nodeBuilding)
	{
		const Express *what = run.calling.what;
		const NodeExpress *tag = &(const NodeExpress&)nodeBuilding.tag;
		const Constant *name = (const Constant*)tag->element[1];
		what->retain();
		name->retain();
		tag->retain();
		return error(run, name, what, tag);
	}

	const Step *SinkWho::pass(Runner &run, SinkTaggedNodeBuilding &nodeBuilding)
	{
		const Constant *name = argument->as_Constant();
		if (name)
		{
			const Any *value = nullptr;
			if (name == &Empty::singleton) value = nodeBuilding.joker;
			else
			{
				std::map<const Constant*, const Any*>::iterator found = nodeBuilding.building.find(name);
				if (found != nodeBuilding.building.end())
					value = found->second;
			}
			if (value)
			{
				name->unduplicateReference();
                run.sink = this + 1;
				return value->passUncounted(run);
			}
			else
			{
				name->release();
				return (run.sink = this + 1)->called(run, Empty::singleton);
			}
		}
		else return Sink::pass(run, nodeBuilding);
	}

	const Step *SinkWho::pass(Runner &run, PassingMind *mind, const Express *what)
	{
		const Constant *key = argument->as_Constant();
		const Any *value;
        if (key && (value = mind->get(*key)))
		{
			what->release();
			run.sink = kick(run);
			return value->passCounted(run);
		}
		else
		{
			value = argument;
			Sink *sink = this + 1;
			run.sink = sink;
			new (run.allocate(sizeof(MissPassingMindCall))) MissPassingMindCall(mind, value, what);
			return sink->miss(run);
		}
	}

	Sink *SinkTaggedExit::kick(Runner &run)
	{
		run.sinkTagChain = chain;
		run.where_ = ((const NodeExpress&)tag).element[0];
		tag.release();
		return this + 1;
	}

	const Step *SinkTaggedExit::calling(Runner &run, const Building &tag)
	{
		return tag.element[0]->calling(run, *(const NodeConstant*)tag.element[1]);
	}

	const Step *SinkTaggedExit::calling(Runner &run, const Building &tag, const Any *assignValue)
	{
		for (Sink *sink = run.sink; sink != this; sink = sink->kick(run));
		run.sink = kick(run);
		return assignValue->passCounted(run);
	}

	Sink *SinkExit::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkExit::pass(Runner &run, const Any *value)
	{
		SinkTaggedExit *sink = (SinkTaggedExit*)(this + 1);
		run.sink = sink->kick(run);
		return value->passCounted(run);
	}

	const Step *Sink::pass(Runner &run, PassingMind *mind, const Express *what)
	{
        Builtin::name.mind.retain();
        Builtin::name.mind.retain();
        mind->owner.retain();
        const Any *error = Builtin::name.mind.callWho(&mind->owner);
		return this->error(run, error, what, &Builtin::name.mind);
	}

	const Step *MissPassingMindCall::missing(Runner &run, Sink *sink)
	{
        Builtin::name.mind.retain();
        Builtin::name.mind.retain();
        mind->owner.retain();
        const Any *call = this->call->callWho(Builtin::name.mind.callWho(&mind->owner));
		const Express *what = this->what;
		for (Sink *s = this + 1; s != sink; s = s->kick(run));
		return (run.sink = sink)->error(run, call, what, &Builtin::name.mind);
	}

	Sink *MissPassingMindCall::kick(Runner &run)
	{
		call->release();
		what->release();
		return this + 1;
	}

	const Step *SinkTaggedBuilding::skip(Runner &run)
	{
		throw L"Internal PILS error: Bad tagged sink";
	}

	const NodeExpressShort *BuiltinClicheBuilderShort::node(const Express *element) const
	{
        return new BuilderShort(*this, element);
	}

	const Any *BuiltinClicheBuilderShort::node(const Constant *element) const
	{
        return new BuilderShort(*this, element);
	}

	const Any *BuiltinClicheBuilderTrailer::node(const Constant *const *element) const
	{
        return new BuilderTrailer(*this, element[0], element[1]);
	}

	const Any *BuiltinClicheBuilderTrailer::node(const Any *const *element) const
	{
		const Constant *name = element[1]->as_Constant();
		if (name)
            return new BuilderTrailer(*this, element[0], name);
		else
			return BuiltinPokerClicheTrailer::node(element);
	}

    void BuilderTrailer::unlink()
	{
		cliche->releaseFrom(*this);
		element[0]->releaseFrom(*this);
		element[1]->releaseFrom(*this);
		name->releaseFrom(*this);
	}

	const Step *BuilderShort::step_(Runner &run) const
	{
		const BuilderName *kind = (const BuilderName *)cliche->attributes[0];
		kind->retain();
		run.where_->retain();
        const Building *building = new Building(run.where_, kind);
		run.where_ = building;
		return kind->building(run, *element[0], *kind);
	}

	const Step *BuilderTrailer::step_(Runner &run) const
	{
		const BuilderName *kind = (const BuilderName *)cliche->attributes[1];
		name->retain();
		run.where_->retain();
        const Building *building = new Building(run.where_, name);
		run.where_ = building;
		return kind->building(run, *element[0], *(const Constant *)element[1]);
	}

	const Step *BuilderNameList::building(Runner &run, const Any &step_, const Constant &head) const
	{
		Pipe &pipe = *run.sink->connectPipe(run);
		run.sinkTagChain = new (run.allocate(sizeof(SinkTaggedListBuilding))) SinkTaggedListBuilding(*(Building*)run.where_, run.sinkTagChain);
		new (run.allocate(sizeof(PipesourceListBuilderBegin))) PipesourceListBuilderBegin(step_);
		return pipe.pipeBegin(run);
	}

	const Step *BuilderNameExit::building(Runner &run, const Any &step_, const Constant &head) const
	{
		run.sinkTagChain = new (run.allocate(sizeof(SinkTaggedExit))) SinkTaggedExit(*(Building*)run.where_, run.sinkTagChain);
		new (run.allocate(sizeof(SinkExit))) SinkExit();
		return &step_;
	}
}
