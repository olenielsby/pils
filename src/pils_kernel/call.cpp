/* This file is public domain */
#include "call.h"
namespace PILS
{
	void Sink::refer(Runner &run, const Express &what)
	{
		run.calling.what = &what;
	}

	const Step *Sink::call(Runner &run, const Express &what, const Any *call)
	{
		run.calling.what = &what;
		new (run.allocate(sizeof(SinkHoldCalling))) SinkHoldCalling(call);
		return call->caller(run, *(run.calling.who = run.where_));
	}

	const Step *Sink::call(Runner &run, const Express &what, const Any *call, const Any *who)
	{
		new (run.allocate(sizeof(SinkHoldCalling))) SinkHoldCalling(call);
		new (run.allocate(sizeof(SinkHoldWho))) SinkHoldWho(who);
		run.calling.what = &what;
		return call->caller(run, *(run.calling.who = who));
	}

	const Step *Sink::call(Runner &run, const Express &what, const Any &call)
	{
		run.calling.what = &what;
		return call.caller(run, *(run.calling.who = run.where_));
	}

	const Step *Sink::call(Runner &run, const Express &what, const Any &call, const Any *who)
	{
		new (run.allocate(sizeof(SinkHoldWho))) SinkHoldWho(who);
		run.calling.what = &what;
		return call.caller(run, *(run.calling.who = who));
	}

	const Step *Sink::assignCall(Runner &run, const Express &what, const Any *call, const Any *assignValue)
	{
		run.calling.what = &what;
		new (run.allocate(sizeof(SinkHoldCalling))) SinkHoldCalling(call);
		return (run.calling.who = run.where_)->calling(run, *call, assignValue);
	}

	const Step *Sink::assignCall(Runner &run, const Express &what, const Any *call, const Any *who, const Any *assignValue)
	{
		new (run.allocate(sizeof(SinkHoldCalling))) SinkHoldCalling(call);
		new (run.allocate(sizeof(SinkHoldWho))) SinkHoldWho(who);
		run.calling.what = &what;
		return (run.calling.who = who)->calling(run, *call, assignValue);
	}

    const Step *Constant::caller(Runner &run, const Any &where_) const
	{
		return where_.calling(run, *this);
	}

	const Step *NodeConstant::caller(Runner &run, const Any &where_) const
	{
		return where_.calling(run, *this);
	}

	const Step *ListConstant::caller(Runner &run, const Any &where_) const
	{
		return where_.calling(run, *this);
	}

	const Step *Empty::caller(Runner &run, const Any &where_) const
	{
		return where_.calling(run, *this);
	}

	const Step *NodeExpress::caller(Runner &run, const Any &where_) const
	{
		return where_.calling(run, *this);
	}

    const Step *ListExpress::caller(Runner &run, const Any &where_) const
	{
		return where_.calling(run, *this);
	}

	const Step *Any::calling(Runner &run, const Constant &call) const
	{
		return run.sink->called(run, call);
	}

	const Step *Any::calling(Runner &run, const Integer &call) const
	{
		return run.sink->called(run, call);
	}

	const Step *Any::calling(Runner &run, const Empty &call) const
	{
		return run.sink->called(run, call);
	}

	const Step *Any::calling(Runner &run, const ListConstant &call) const
	{
		return run.sink->called(run, call);
	}

	const Step *Any::calling(Runner &run, const NodeConstant &call) const
	{
		return run.sink->called(run, call);
	}

/**/
	const Step *Any::calling(Runner &run, const ListExpress &call) const
	{
		return run.sink->called(run, call);
	}

	const Step *Any::calling(Runner &run, const NodeExpress &call) const
	{
		return run.sink->called(run, call);
	}

    const Step *Any::calling(Runner &run, const Any &call, const Any *assignValue) const
	{
		return run.sink->called(run, call, assignValue);
	}

	const Step *NodeConstantShort::calling(Runner &run, const Constant &call) const
	{
		if (&call == cliche->attributes[0])
			return element[0]->passUncounted(run);
		return run.sink->called(run, call);
	}

	const Step *NodeConstantShort::calling(Runner &run, const Integer &call) const
	{
		if (&call == cliche->attributes[0])
			return element[0]->passUncounted(run);
		return run.sink->called(run, call);
	}

	const Step *NodeConstantShort::calling(Runner &run, const NodeConstant &call) const
	{
		if (&call == cliche->attributes[0])
			return element[0]->passUncounted(run);
		return run.sink->called(run, call);
	}

	const Step *NodeConstantShort::calling(Runner &run, const ListConstant &call) const
	{
		if (&call == cliche->attributes[0])
			return element[0]->passUncounted(run);
		return run.sink->called(run, call);
	}

	const Step *NodeConstantTiny::calling(Runner &run, const Empty &call) const
	{
		return element[0]->passUncounted(run);
	}

	const Step *NodeConstantTiny::calling(Runner &run, const Constant &call) const
	{
		return run.sink->called(run, call);
	}

	const Step *NodeConstantTiny::calling(Runner &run, const Integer &call) const
	{
		return run.sink->called(run, call);
	}

	const Step *NodeConstantTiny::calling(Runner &run, const NodeConstant &call) const
	{
		return run.sink->called(run, call);
	}

	const Step *NodeConstantTiny::calling(Runner &run, const ListConstant &call) const
	{
		return run.sink->called(run, call);
	}

	const Step *NodeConstantLong::calling(Runner &run, const Constant &call) const
	{
		if (const Constant *result = cliche->lookupNonempty(this, 0, &call))
			return result->passUncounted(run);
		else return run.sink->called(run, call);
	}

	const Step *NodeConstantLong::calling(Runner &run, const Integer &call) const
	{
		if (const Constant *result = cliche->lookupNonempty(this, 0, &call))
			return result->passUncounted(run);
		else return run.sink->called(run, call);
	}

	const Step *NodeConstantLong::calling(Runner &run, const NodeConstant &call) const
	{
		if (const Constant *result = cliche->lookupNonempty(this, 0, &call))
			return result->passUncounted(run);
		else return run.sink->called(run, call);
	}

	const Step *NodeConstantLong::calling(Runner &run, const ListConstant &call) const
	{
		if (const Constant *result = cliche->lookupNonempty(this, 0, &call))
			return result->passUncounted(run);
		else return run.sink->called(run, call);
	}

	const Step *NodeConstantTrailer::calling(Runner &run, const Constant &call) const
	{
		if (const Constant *result = cliche->lookupNonempty(this, 1, &call))
			return result->passUncounted(run);
		else return run.sink->called(run, call);
	}

	const Step *NodeConstantTrailer::calling(Runner &run, const Integer &call) const
	{
		if (const Constant *result = cliche->lookupNonempty(this, 1, &call))
			return result->passUncounted(run);
		else return run.sink->called(run, call);
	}

	const Step *NodeConstantTrailer::calling(Runner &run, const NodeConstant &call) const
	{
		if (const Constant *result = cliche->lookupNonempty(this, 1, &call))
			return result->passUncounted(run);
		else return run.sink->called(run, call);
	}

	const Step *NodeConstantTrailer::calling(Runner &run, const ListConstant &call) const
	{
		if (const Constant *result = cliche->lookupNonempty(this, 1, &call))
			return result->passUncounted(run);
		else return run.sink->called(run, call);
	}

	const Step *NodeConstantTrailer::calling(Runner &run, const Empty &call) const
	{
		return element[0]->passUncounted(run);
	}

	const Step *NodeExpressShort::calling(Runner &run, const Constant &call) const
	{
		if (&call == cliche->attributes[0])
			return element[0]->passUncounted(run);
		return run.sink->called(run, call);
	}

	const Step *NodeExpressShort::calling(Runner &run, const Integer &call) const
	{
		if (&call == cliche->attributes[0])
			return element[0]->passUncounted(run);
		return run.sink->called(run, call);
	}

	const Step *NodeExpressShort::calling(Runner &run, const NodeConstant &call) const
	{
		if (&call == cliche->attributes[0])
			return element[0]->passUncounted(run);
		return run.sink->called(run, call);
	}

	const Step *NodeExpressShort::calling(Runner &run, const ListConstant &call) const
	{
		if (&call == cliche->attributes[0])
			return element[0]->passUncounted(run);
		return run.sink->called(run, call);
	}

	const Step *NodeExpressTiny::calling(Runner &run, const Empty &call) const
	{
		return element[0]->passUncounted(run);
	}

	const Step *NodeExpressTiny::calling(Runner &run, const Constant &call) const
	{
		return run.sink->called(run, call);
	}

	const Step *NodeExpressTiny::calling(Runner &run, const Integer &call) const
	{
		return run.sink->called(run, call);
	}

	const Step *NodeExpressTiny::calling(Runner &run, const NodeConstant &call) const
	{
		return run.sink->called(run, call);
	}

	const Step *NodeExpressTiny::calling(Runner &run, const ListConstant &call) const
	{
		return run.sink->called(run, call);
	}

	const Step *NodeExpressLong::calling(Runner &run, const Constant &call) const
	{
		if (const Any *result = cliche->lookupNonempty(this, 0, &call))
			return result->passUncounted(run);
		else return run.sink->called(run, call);
	}

	const Step *NodeExpressLong::calling(Runner &run, const Integer &call) const
	{
		if (const Any *result = cliche->lookupNonempty(this, 0, &call))
			return result->passUncounted(run);
		else return run.sink->called(run, call);
	}

	const Step *NodeExpressLong::calling(Runner &run, const NodeConstant &call) const
	{
		if (const Any *result = cliche->lookupNonempty(this, 0, &call))
			return result->passUncounted(run);
		else return run.sink->called(run, call);
	}

	const Step *NodeExpressLong::calling(Runner &run, const ListConstant &call) const
	{
		if (const Any *result = cliche->lookupNonempty(this, 0, &call))
			return result->passUncounted(run);
		else return run.sink->called(run, call);
	}

	const Step *NodeExpressTrailer::calling(Runner &run, const Constant &call) const
	{
		if (const Any *result = cliche->lookupNonempty(this, 1, &call))
			return result->passUncounted(run);
		else return run.sink->called(run, call);
	}

	const Step *NodeExpressTrailer::calling(Runner &run, const Integer &call) const
	{
		if (const Any *result = cliche->lookupNonempty(this, 1, &call))
			return result->passUncounted(run);
		else return run.sink->called(run, call);
	}

	const Step *NodeExpressTrailer::calling(Runner &run, const NodeConstant &call) const
	{
		if (const Any *result = cliche->lookupNonempty(this, 1, &call))
			return result->passUncounted(run);
		else return run.sink->called(run, call);
	}

	const Step *NodeExpressTrailer::calling(Runner &run, const ListConstant &call) const
	{
		if (const Any *result = cliche->lookupNonempty(this, 1, &call))
			return result->passUncounted(run);
		else return run.sink->called(run, call);
	}

	const Step *NodeExpressTrailer::calling(Runner &run, const Empty &call) const
	{
		return element[0]->passUncounted(run);
	}

	const Step *Bind::calling(Runner &run, const Constant &call) const
	{
		if (const Any *result = cliche->lookupNonempty(this, 1, &call))
			return result->passUncounted(run);
		else return element[0]->calling(run, call);
	}

	const Step *Bind::calling(Runner &run, const Integer &call) const
	{
		if (const Any *result = cliche->lookupNonempty(this, 1, &call))
			return result->passUncounted(run);
		else return element[0]->calling(run, call);
	}

	const Step *Bind::calling(Runner &run, const ListConstant &call) const
	{
		if (const Any *result = cliche->lookupNonempty(this, 1, &call))
			return result->passUncounted(run);
		else return element[0]->calling(run, call);
	}

	const Step *Bind::calling(Runner &run, const NodeConstant &call) const
	{
		if (const Any *result = cliche->lookupNonempty(this, 1, &call))
			return result->passUncounted(run);
		else return element[0]->calling(run, call);
	}

	const Step *Bind::calling(Runner &run, const ListExpress &call) const
	{
		return element[0]->calling(run, call);
	}

	const Step *Bind::calling(Runner &run, const NodeExpress &call) const
	{
		return element[0]->calling(run, call);
	}

	const Step *Bind::calling(Runner &run, const Empty &call) const
	{
		return element[0]->calling(run, call);
	}

	const Step *Bind::calling(Runner &run, const Any &call, const Any *assignValue) const
	{
		return element[0]->calling(run, call, assignValue);
	}

	const Step *Bind1::calling(Runner &run, const Constant &call) const
	{
		if (cliche->attributes[1] == &call)
			return element[1]->passUncounted(run);
		else return element[0]->calling(run, call);
	}

	const Step *Bind1::calling(Runner &run, const Integer &call) const
	{
		if (cliche->attributes[1] == &call)
			return element[1]->passUncounted(run);
		else return element[0]->calling(run, call);
	}

	const Step *Bind1::calling(Runner &run, const ListConstant &call) const
	{
		if (cliche->attributes[1] == &call)
			return element[1]->passUncounted(run);
		else return element[0]->calling(run, call);
	}

	const Step *Bind1::calling(Runner &run, const NodeConstant &call) const
	{
		if (cliche->attributes[1] == &call)
			return element[1]->passUncounted(run);
		else return element[0]->calling(run, call);
	}

	const Step *Bind2::calling(Runner &run, const Constant &call) const
	{
		for (size_t i = 1; i < 3; i++)
			if (cliche->attributes[i] == &call)
				return element[i]->passUncounted(run);
		return element[0]->calling(run, call);
	}

	const Step *Bind2::calling(Runner &run, const Integer &call) const
	{
		for (size_t i = 1; i < 3; i++)
			if (cliche->attributes[i] == &call)
				return element[i]->passUncounted(run);
		return element[0]->calling(run, call);
	}

	const Step *Bind2::calling(Runner &run, const ListConstant &call) const
	{
		for (size_t i = 1; i < 3; i++)
			if (cliche->attributes[i] == &call)
				return element[i]->passUncounted(run);
		return element[0]->calling(run, call);
	}

	const Step *Bind2::calling(Runner &run, const NodeConstant &call) const
	{
		for (size_t i = 1; i < 3; i++)
			if (cliche->attributes[i] == &call)
				return element[i]->passUncounted(run);
		return element[0]->calling(run, call);
	}

	const Step *Bind3::calling(Runner &run, const Constant &call) const
	{
		for (size_t i = 1; i < 4; i++)
			if (cliche->attributes[i] == &call)
                return element[i]->passUncounted(run);
		return element[0]->calling(run, call);
	}

	const Step *Bind3::calling(Runner &run, const Integer &call) const
	{
		for (size_t i = 1; i < 4; i++)
			if (cliche->attributes[i] == &call)
				return element[i]->passUncounted(run);
		return element[0]->calling(run, call);
	}

	const Step *Bind3::calling(Runner &run, const ListConstant &call) const
	{
		for (size_t i = 1; i < 4; i++)
			if (cliche->attributes[i] == &call)
				return element[i]->passUncounted(run);
		return element[0]->calling(run, call);
	}

	const Step *Bind3::calling(Runner &run, const NodeConstant &call) const
	{
		for (size_t i = 1; i < 4; i++)
			if (cliche->attributes[i] == &call)
				return element[i]->passUncounted(run);
		return element[0]->calling(run, call);
	}

	const Step *Jumper::calling(Runner &run, const Empty &call) const
	{
		for (SinkTagged *tagged = run.sinkTagChain; tagged; tagged = tagged->chain)
			if (&tagged->tag == this)
				return tagged->skip(run);
		call.retain();
		run.calling.what->retain();
		run.calling.who->retain();
		return run.sink->error(run, &call, run.calling.what, run.calling.who);
	}

	const Step *Jumper0::calling(Runner &run, const Empty &call) const
	{
		for (SinkTagged *tagged = run.sinkTagChain; tagged; tagged = tagged->chain)
			if (&tagged->tag == this)
				return tagged->skip(run);
		call.retain();
		run.calling.who->retain();
		return run.sink->error(run, &call, run.calling.what, run.calling.who);
	}

	const Step *Jumper0::calling(Runner &run, const Constant &call) const
	{
		return element[0]->calling(run, call);
	}

	const Step *Jumper0::calling(Runner &run, const Integer &call) const
	{
		return element[0]->calling(run, call);
	}

	const Step *Jumper0::calling(Runner &run, const NodeConstant &call) const
	{
		return element[0]->calling(run, call);
	}

	const Step *Jumper0::calling(Runner &run, const ListConstant &call) const
	{
		return element[0]->calling(run, call);
	}

	const Step *Jumper0::calling(Runner &run, const NodeExpress &call) const
	{
		return element[0]->calling(run, call);
	}

	const Step *Jumper0::calling(Runner &run, const ListExpress &call) const
	{
		return element[0]->calling(run, call);
	}

	const Step *Jumper0::calling(Runner &run, const Any &call, const Any *assignValue) const
	{
		return element[0]->calling(run, call, assignValue);
	}

	const Step *Jumper1::calling(Runner &run, const Empty &call) const
	{
		for (SinkTagged *tagged = run.sinkTagChain; tagged; tagged = tagged->chain)
			if (&tagged->tag == this)
				return tagged->skip(run);
		call.retain();
		run.calling.what->retain();
		run.calling.who->retain();
		return run.sink->error(run, &call, run.calling.what, run.calling.who);
	}

	const Step *Jumper2::calling(Runner &run, const Empty &call) const
	{
		for (SinkTagged *tagged = run.sinkTagChain; tagged; tagged = tagged->chain)
			if (&tagged->tag == this)
				return tagged->skip(run);
		call.retain();
		run.calling.what->retain();
		run.calling.who->retain();
		return run.sink->error(run, &call, run.calling.what, run.calling.who);
	}

	const Step *Jumper3::calling(Runner &run, const Empty &call) const
	{
		for (SinkTagged *tagged = run.sinkTagChain; tagged; tagged = tagged->chain)
			if (&tagged->tag == this)
				return tagged->skip(run);
		call.retain();
		run.calling.what->retain();
		run.calling.who->retain();
		return run.sink->error(run, &call, run.calling.what, run.calling.who);
	}

	const Step *Sink::called(Runner &run, const Constant &call)
	{
		new (run.allocate(sizeof(MissCall))) MissCall(call);
		return miss(run);
	}

	const Step *MissCall::missing(Runner &run, Sink *sink)
	{
		const Any *call = &this->call;
		call->retain();
		const Any *who = run.calling.who;
		who->retain();
		const Express *what = run.calling.what;
		what->retain();
		for (Sink *s = this + 1; s != sink; s = s->kick(run));
		return (run.sink = sink)->error(run, call, what, who);
	}

	Sink *MissCall::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *Sink::called(Runner &run, const Integer &call)
	{
		new (run.allocate(sizeof(MissCall))) MissCall(call);
		return miss(run);
	}

	const Step *Sink::called(Runner &run, const Empty &call)
	{
		new (run.allocate(sizeof(MissCall))) MissCall(call);
		return miss(run);
	}

	const Step *Sink::called(Runner &run, const ListConstant &call)
	{
		new (run.allocate(sizeof(MissCall))) MissCall(call);
		return miss(run);
	}

	const Step *Sink::called(Runner &run, const NodeConstant &call)
	{
		new (run.allocate(sizeof(MissCall))) MissCall(call);
		return miss(run);
	}

	const Step *Sink::called(Runner &run, const ListExpress &call)
	{
		new (run.allocate(sizeof(MissCall))) MissCall(call);
		return miss(run);
	}

	const Step *Sink::called(Runner &run, const NodeExpress &call)
	{
		new (run.allocate(sizeof(MissCall))) MissCall(call);
		return miss(run);
	}

    const Step *Sink::called(Runner &run, const Any &call, const Any *assignValue)
	{
		new (run.allocate(sizeof(MissAssignCall))) MissAssignCall(call, assignValue);
		return miss(run);
	}

	const Step *MissAssignCall::missing(Runner &run, Sink *sink)
	{
		const Any *error;
		if (assignValue->as_Constant())
			error = BuiltinClicheAssign::singleton.node((const Constant*)assignValue);
		else
			error = BuiltinClicheAssign::singleton.node((const Express*)assignValue);
		call.retain();
		error = error->callWho(&call);
		const Any *who = run.calling.who;
		who->retain();
		const Express *what = run.calling.what;
		what->retain();
		for (Sink *s = this + 1; s != sink; s = s->kick(run));
		return (run.sink = sink)->error(run, error, what, who);
	}

	Sink *MissAssignCall::kick(Runner &run)
	{
        run.release(assignValue);
		return this + 1;
	}

	const Step *Sink::miss(Runner &run)
	{
		Miss *miss = (Miss *)run.sink;
		return miss->missing(run, this);
	}

	const Step *SinkHoldWho::called(Runner &run, const Constant &call)
	{

// sloppy code
		call.retain();
		const CallWho *callWho = call.callWho(thing);
		new ((void*)this) SinkHoldCalling(callWho);
// should be replaced by this, but this creates memory leak
//		SinkHoldCalling &sink = (SinkHoldCalling &)this[1];
//		const CallWho *callWho = sink.thing->callWho(thing);
//		sink.thing = callWho;
//		run.sink = &sink;
		return (run.calling.who = run.where_)->calling(run, *callWho);
	}

	const Step *SinkHoldWho::called(Runner &run, const Integer &call)
	{
		call.retain();
		const CallWho *callWho = call.callWho(thing);
		new ((void*)this) SinkHoldCalling(callWho);
		return (run.calling.who = run.where_)->calling(run, *callWho);
	}

	const Step *SinkHoldWho::called(Runner &run, const Empty &call)
	{
		call.retain();
		const CallWho *callWho = call.callWho(thing);
		new ((void*)this) SinkHoldCalling(callWho);
		return (run.calling.who = run.where_)->calling(run, *callWho);
	}

	const Step *SinkHoldWho::called(Runner &run, const ListConstant &call)
	{
		call.retain();
		const CallWho *callWho = call.callWho(thing);
		new ((void*)this) SinkHoldCalling(callWho);
		return (run.calling.who = run.where_)->calling(run, *callWho);
	}

	const Step *SinkHoldWho::called(Runner &run, const NodeConstant &call)
	{
		call.retain();
		const CallWho *callWho = call.callWho(thing);
		new ((void*)this) SinkHoldCalling(callWho);
		return (run.calling.who = run.where_)->calling(run, *callWho);
	}

	const Step *SinkHoldWho::called(Runner &run, const ListExpress &call)
	{
		call.retain();
		const CallWho *callWho = call.callWho(thing);
		new ((void*)this) SinkHoldCalling(callWho);
		return (run.calling.who = run.where_)->calling(run, *callWho);
	}

	const Step *SinkHoldWho::called(Runner &run, const NodeExpress &call)
	{
		call.retain();
		const CallWho *callWho = call.callWho(thing);
		new ((void*)this) SinkHoldCalling(callWho);
		return (run.calling.who = run.where_)->calling(run, *callWho);
	}

	const Step *SinkHoldWho::called(Runner &run, const Any &call, const Any *assignValue)
	{
		call.retain();
		const CallWho *callWho = call.callWho(thing);
		new ((void*)this) SinkHoldCalling(callWho);
		return (run.calling.who = run.where_)->calling(run, *callWho, assignValue);
	}
	Sink *SinkCallStackedBase::kick(Runner &run)
	{
		return this + 1;
	}
	const Step *SinkCallStacked::pass(Runner &run, long value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, double value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const Integer &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const Float &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const PilsString &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const PilsColor &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const Cliche &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const ListConstant &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const NodeConstantLong &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const NodeConstantShort &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const ListExpress &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const NodeExpressLong &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const NodeExpressShort &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const Special &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const Integer *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const Float *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const Timestamp *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const Duration *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const PilsColor *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const PilsDate *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const PilsString *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const Cliche *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const ListConstant *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const NodeConstantLong *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const NodeConstantShort *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const ListExpress *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const NodeExpressLong *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const NodeExpressShort *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const Special *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkCallStacked::pass(Runner &run, const Any *value) //dummy
	{
		throw L"Bad pass";
	}
	const Step *SinkCallStacked::called(Runner &run, const Constant &call)
	{
		const Any &stacked = this->stacked;
		run.sink = this + 1;
		return stacked.calling(run, call);
	}
	const Step *SinkCallStacked::called(Runner &run, const Integer &call)
	{
		const Any &stacked = this->stacked;
		run.sink = this + 1;
		return stacked.calling(run, call);
	}
	const Step *SinkCallStacked::called(Runner &run, const ListConstant &call)
	{
		const Any &stacked = this->stacked;
		run.sink = this + 1;
		return stacked.calling(run, call);
	}
	const Step *SinkCallStacked::called(Runner &run, const NodeConstant &call)
	{
		const Any &stacked = this->stacked;
		run.sink = this + 1;
		return stacked.calling(run, call);
	}
	const Step *SinkCallStacked::called(Runner &run, const Empty &call)
	{
		const Any &stacked = this->stacked;
		run.sink = this + 1;
		return stacked.calling(run, call);
	}
	const Step *SinkCallStacked::called(Runner &run, const ListExpress &call)
	{
		const Any &stacked = this->stacked;
		run.sink = this + 1;
		return stacked.calling(run, call);
	}

	const Step *SinkCallStacked::called(Runner &run, const NodeExpress &call)
	{
		const Any &stacked = this->stacked;
		run.sink = this + 1;
		return stacked.calling(run, call);
	}

	const Step *SinkCallStacked::called(Runner &run, const Any &call, const Any *assignValue)
	{
		const Any &stacked = this->stacked;
		run.sink = this + 1;
		return stacked.calling(run, call, assignValue);
	}

	const Step *SinkCallStacked::tailStep(Runner &run, const Any *thing, const Any *where_)
	{
		return (run.sink = this + 1)->tailStep(run, thing, where_);
	}

	const Step *SinkCallStacked::tailStep(Runner &run, const Any *thing)
	{
		return (run.sink = this + 1)->tailStep(run, thing);
	}

	Pipe *SinkCallStacked::connectPipe(Runner &run)
	{
		return (run.sink = this + 1)->connectPipe(run);
	}

	const Step *SinkCallStackedBase::error(Runner &run, const Any *error, const Express *what, const Any *who)
	{
		return (run.sink = kick(run))->error(run, error, what, who);
	}

	const Step *Call::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkCall))) SinkCall(*this);
		return element[0];
	}

	const Step *Slot::step_(Runner &run) const
	{
		return run.sink->call(run, *this, *element[0]);
	}

	const Step *EmptySlot::step_(Runner &run) const
	{
		return run.sink->call(run, *this, Empty::singleton);
	}

	Sink *SinkCall::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkCall::pass(Runner &run, const Any *thing)
	{
		return (run.sink = this + 1)->call(run, what, thing);
	}

	const Step *Special::calling(Runner &run, const Constant &call) const
	{
		const Any *thing = call.specialCall(run, *(const ReallySpecial*)this);
        if (thing)
			return thing->passCounted(run);
        if (thing = getWhen())
		{
			new (run.allocate(sizeof(SinkHoldCalling))) SinkHoldCalling(thing);
			new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
			run.calling.who = this;
			return thing->calling(run, call);
		}
		return run.sink->called(run, call);
	}

	const Step *Special::calling(Runner &run, const Integer &call) const
	{
		const Any *thing = call.specialCall(run, *(const ReallySpecial*)this);
		if (thing)
			return thing->passCounted(run);
        if (thing = getWhen())
		{
			new (run.allocate(sizeof(SinkHoldCalling))) SinkHoldCalling(thing);
			new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
			run.calling.who = this;
			return thing->calling(run, call);
		}
		return run.sink->called(run, call);
	}

	const Step *Special::calling(Runner &run, const ListConstant &call) const
	{
		const Any *thing = call.specialCall(run, *(const ReallySpecial*)this);
		if (thing)
			return thing->passCounted(run);
        if (thing = getWhen())
		{
			new (run.allocate(sizeof(SinkHoldCalling))) SinkHoldCalling(thing);
			new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
			run.calling.who = this;
			return thing->calling(run, call);
		}
		return run.sink->called(run, call);
	}

	const Step *Special::calling(Runner &run, const NodeConstant &call) const
	{
		const Any *thing = call.specialCall(run, *(const ReallySpecial*)this);
		if (thing)
			return thing->passCounted(run);
        if (thing = getWhen())
		{
			new (run.allocate(sizeof(SinkHoldCalling))) SinkHoldCalling(thing);
			new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
			run.calling.who = this;
			return thing->calling(run, call);
		}
		return run.sink->called(run, call);
	}

	const Step *Special::calling(Runner &run, const ListExpress &call) const
	{
		const Any *thing = call.specialCall(run, *(const ReallySpecial*)this);
		if (thing)
			return thing->passCounted(run);
        if (thing = getWhen())
		{
			new (run.allocate(sizeof(SinkHoldCalling))) SinkHoldCalling(thing);
			new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
			run.calling.who = this;
			return thing->calling(run, call);
		}
		return run.sink->called(run, call);
	}

	const Step *Special::calling(Runner &run, const NodeExpress &call) const
	{
		const Any *thing = call.specialCall(run, *(const ReallySpecial*)this);
		if (thing)
			return thing->passCounted(run);
        if (thing = getWhen())
		{
			new (run.allocate(sizeof(SinkHoldCalling))) SinkHoldCalling(thing);
			new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
			run.calling.who = this;
			return thing->calling(run, call);
		}
		return run.sink->called(run, call);
	}

	const Step *Special::calling(Runner &run, const Any &call, const Any *assignValue) const
	{
		const Any *thing = call.specialCall(run, *(const ReallySpecial*)this, *assignValue);
		if (thing)
		{
            run.release(assignValue);
			return thing->passCounted(run);
		}
        if (thing = getWhen())
		{
			new (run.allocate(sizeof(SinkHoldCalling))) SinkHoldCalling(thing);
			new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
			run.calling.who = this;
			return thing->calling(run, call, assignValue);
		}
		return run.sink->called(run, call, assignValue);
	}

	const Any *Any::specialCall(Runner &run, const ReallySpecial &special) const
	{
        return nullptr;
	}

	const Any *Any::specialCall(Runner &run, const ReallySpecial &special, const Any &assignValue) const
	{
        return nullptr;
	}

	const Any *Integer::specialCall(Runner &run, const ReallySpecial &special) const
	{
		return ((const Special&)special).specialCalling(run, *this);
	}

	const Any *Integer::specialCall(Runner &run, const ReallySpecial &special, const Any &assignValue) const
	{
		return ((const Special&)special).specialCalling(run, *this, assignValue);
	}

	const Any *PilsString::specialCall(Runner &run, const ReallySpecial &special) const
	{
		return ((const Special&)special).specialCalling(run, *this);
	}

	const Any *PilsString::specialCall(Runner &run, const ReallySpecial &special, const Any &assignValue) const
	{
		return ((const Special&)special).specialCalling(run, *this, assignValue);
	}

	const Any *Special::specialCalling(Runner &run, const Integer &call) const
	{
        return nullptr;
	}

	const Any *Special::specialCalling(Runner &run, const Integer &call, const Any &AssignValue) const
	{
        return nullptr;
	}

	const Any *Special::specialCalling(Runner &run, const PilsString &call) const
	{
        return nullptr;
	}

	const Any *Special::specialCalling(Runner &run, const PilsString &call, const Any &AssignValue) const
	{
        return nullptr;
	}

	const Any *Special::specialCalling(Runner &run, const Constant &call) const
	{
        return nullptr;
	}

	const Step *Using::calling(Runner &run, const Constant &call) const
	{
		new (run.allocate(sizeof(SinkCallStacked))) SinkCallStacked(*element[0]);
		return element[1]->calling(run, call);
	}

	const Step *Using::calling(Runner &run, const Integer &call) const
	{
		new (run.allocate(sizeof(SinkCallStacked))) SinkCallStacked(*element[0]);
		return element[1]->calling(run, call);
	}

	const Step *Using::calling(Runner &run, const Empty &call) const
	{
		new (run.allocate(sizeof(SinkCallStacked))) SinkCallStacked(*element[0]);
		return element[1]->calling(run, call);
	}

	const Step *Using::calling(Runner &run, const NodeConstant &call) const
	{
		new (run.allocate(sizeof(SinkCallStacked))) SinkCallStacked(*element[0]);
		return element[1]->calling(run, call);
	}

	const Step *Using::calling(Runner &run, const ListConstant &call) const
	{
		new (run.allocate(sizeof(SinkCallStacked))) SinkCallStacked(*element[0]);
		return element[1]->calling(run, call);
	}

	const Step *Using::calling(Runner &run, const NodeExpress &call) const
	{
		new (run.allocate(sizeof(SinkCallStacked))) SinkCallStacked(*element[0]);
		return element[1]->calling(run, call);
	}

	const Step *Using::calling(Runner &run, const ListExpress &call) const
	{
		new (run.allocate(sizeof(SinkCallStacked))) SinkCallStacked(*element[0]);
		return element[1]->calling(run, call);
	}

	const Step *Using::calling(Runner &run, const Any &call, const Any *assignValue) const
	{
		new (run.allocate(sizeof(SinkCallStacked))) SinkCallStacked(*element[0]);
		return element[1]->calling(run, call, assignValue);
	}

	const Express *Using::findCatchTag() const
	{
		return element[0]->findCatchTag();
	}

	bool Using::convert(Converter &converter) const
	{
		return element[0]->convert(converter);
	}

	const Step *Through::calling(Runner &run, const Constant &call) const
	{
		new (run.allocate(sizeof(SinkThroughStacked))) SinkThroughStacked(run, *element[0]);
		return element[1]->calling(run, call);
	}

	const Step *Through::calling(Runner &run, const Integer &call) const
	{
		new (run.allocate(sizeof(SinkThroughStacked))) SinkThroughStacked(run, *element[0]);
		return element[1]->calling(run, call);
	}

	const Step *Through::calling(Runner &run, const Empty &call) const
	{
		new (run.allocate(sizeof(SinkThroughStacked))) SinkThroughStacked(run, *element[0]);
		return element[1]->calling(run, call);
	}

	const Step *Through::calling(Runner &run, const NodeConstant &call) const
	{
		new (run.allocate(sizeof(SinkThroughStacked))) SinkThroughStacked(run, *element[0]);
		return element[1]->calling(run, call);
	}

	const Step *Through::calling(Runner &run, const ListConstant &call) const
	{
		new (run.allocate(sizeof(SinkThroughStacked))) SinkThroughStacked(run, *element[0]);
		return element[1]->calling(run, call);
	}

	const Step *Through::calling(Runner &run, const NodeExpress &call) const
	{
		new (run.allocate(sizeof(SinkThroughStacked))) SinkThroughStacked(run, *element[0]);
		return element[1]->calling(run, call);
	}

	const Step *Through::calling(Runner &run, const ListExpress &call) const
	{
		new (run.allocate(sizeof(SinkThroughStacked))) SinkThroughStacked(run, *element[0]);
		return element[1]->calling(run, call);
	}

	const Step *Through::calling(Runner &run, const Any &call, const Any *assignValue) const
	{
		new (run.allocate(sizeof(SinkThroughStacked))) SinkThroughStacked(run, *element[0]);
		return element[1]->calling(run, call, assignValue);
	}

	const Step *SinkThroughStacked::called(Runner &run, const Constant &call)
	{
		const Any &who = *run.calling.who;
		run.calling.who = &stacked;
		run.sink = this + 1;
		return who.calling(run, call);
	}

	const Step *SinkThroughStacked::called(Runner &run, const Integer &call)
	{
		const Any &who = *run.calling.who;
		run.calling.who = &stacked;
		run.sink = this + 1;
		return who.calling(run, call);
	}

	const Step *SinkThroughStacked::called(Runner &run, const Empty &call)
	{
		const Any &who = *run.calling.who;
		run.calling.who = &stacked;
		run.sink = this + 1;
		return who.calling(run, call);
	}

	const Step *SinkThroughStacked::called(Runner &run, const NodeConstant &call)
	{
		const Any &who = *run.calling.who;
		run.calling.who = &stacked;
		run.sink = this + 1;
		return who.calling(run, call);
	}

	const Step *SinkThroughStacked::called(Runner &run, const ListConstant &call)
	{
		const Any &who = *run.calling.who;
		run.calling.who = &stacked;
		run.sink = this + 1;
		return who.calling(run, call);
	}

	const Step *SinkThroughStacked::called(Runner &run, const NodeExpress &call)
	{
		const Any &who = *run.calling.who;
		run.calling.who = &stacked;
		run.sink = this + 1;
		return who.calling(run, call);
	}

	const Step *SinkThroughStacked::called(Runner &run, const ListExpress &call)
	{
		const Any &who = *run.calling.who;
		run.calling.who = &stacked;
		run.sink = this + 1;
		return who.calling(run, call);
	}

	const Step *SinkThroughStacked::called(Runner &run, const Any &call, const Any *assignValue)
	{
		const Any &who = *run.calling.who;
		run.calling.who = &stacked;
		run.sink = this + 1;
		return who.calling(run, call, assignValue);
	}

	const Step *Around::calling(Runner &run, const Constant &call) const
	{
		new (run.allocate(sizeof(SinkAroundStacked))) SinkAroundStacked(run, *element[0]);
		return element[1]->calling(run, call);
	}

	const Step *Around::calling(Runner &run, const Integer &call) const
	{
		new (run.allocate(sizeof(SinkAroundStacked))) SinkAroundStacked(run, *element[0]);
		return element[1]->calling(run, call);
	}

	const Step *Around::calling(Runner &run, const Empty &call) const
	{
		new (run.allocate(sizeof(SinkAroundStacked))) SinkAroundStacked(run, *element[0]);
		return element[1]->calling(run, call);
	}

	const Step *Around::calling(Runner &run, const NodeConstant &call) const
	{
		new (run.allocate(sizeof(SinkAroundStacked))) SinkAroundStacked(run, *element[0]);
		return element[1]->calling(run, call);
	}

	const Step *Around::calling(Runner &run, const ListConstant &call) const
	{
		new (run.allocate(sizeof(SinkAroundStacked))) SinkAroundStacked(run, *element[0]);
		return element[1]->calling(run, call);
	}

	const Step *Around::calling(Runner &run, const NodeExpress &call) const
	{
		new (run.allocate(sizeof(SinkAroundStacked))) SinkAroundStacked(run, *element[0]);
		return element[1]->calling(run, call);
	}

	const Step *Around::calling(Runner &run, const ListExpress &call) const
	{
		new (run.allocate(sizeof(SinkAroundStacked))) SinkAroundStacked(run, *element[0]);
		return element[1]->calling(run, call);
	}

	const Step *Around::calling(Runner &run, const Any &call, const Any *assignValue) const
	{
		new (run.allocate(sizeof(SinkAroundStacked))) SinkAroundStacked(run, *element[0]);
		return element[1]->calling(run, call, assignValue);
	}

	const Step *SinkAroundStacked::called(Runner &run, const Constant &call)
	{
		run.calling.who = &stacked;
		return (run.sink = this + 1)->called(run, call);
	}

	const Step *SinkAroundStacked::called(Runner &run, const Integer &call)
	{
		run.calling.who = &stacked;
		return (run.sink = this + 1)->called(run, call);
	}

	const Step *SinkAroundStacked::called(Runner &run, const Empty &call)
	{
		run.calling.who = &stacked;
		return (run.sink = this + 1)->called(run, call);
	}

	const Step *SinkAroundStacked::called(Runner &run, const NodeConstant &call)
	{
		run.calling.who = &stacked;
		return (run.sink = this + 1)->called(run, call);
	}

	const Step *SinkAroundStacked::called(Runner &run, const ListConstant &call)
	{
		run.calling.who = &stacked;
		return (run.sink = this + 1)->called(run, call);
	}

	const Step *SinkAroundStacked::called(Runner &run, const NodeExpress &call)
	{
		run.calling.who = &stacked;
		return (run.sink = this + 1)->called(run, call);
	}

	const Step *SinkAroundStacked::called(Runner &run, const ListExpress &call)
	{
		run.calling.who = &stacked;
		return (run.sink = this + 1)->called(run, call);
	}

	const Step *SinkAroundStacked::called(Runner &run, const Any &call, const Any *assignValue)
	{
		run.calling.who = &stacked;
		return (run.sink = this + 1)->called(run, call, assignValue);
	}

	const Step *PokerShort::step_(Runner &run) const
	{
		return run.sink->call(run, *this, *this);
	}

	const Step *PokerLong::step_(Runner &run) const
	{
		return run.sink->call(run, *this, *this);
	}

	const Step *PokerTrailer::step_(Runner &run) const
	{
		return run.sink->call(run, *this, *this);
	}

	const NodeConstantShort *BuiltinClicheCalling::newNode(const Constant *&link, const Integer *value) const
	{
        return new CallingConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheCalling::newNode(const Constant *&link, const Float *value) const
	{
        return new CallingConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheCalling::newNode(const Constant *&link, const PilsColor *value) const
	{
        return new CallingConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheCalling::newNode(const Constant *&link, const Timestamp *value) const
	{
        return new CallingConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheCalling::newNode(const Constant *&link, const Duration *value) const
	{
        return new CallingConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheCalling::newNode(const Constant *&link, const PilsDate *value) const
	{
        return new CallingConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheCalling::newNode(const Constant *&link, const PilsString *value) const
	{
        return new CallingConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheCalling::newNode(const Constant *&link, const Cliche *value) const
	{
        return new CallingConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheCalling::newNode(const Constant *&link, const ListConstant *value) const
	{
        return new CallingConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheCalling::newNode(const Constant *&link, const NodeConstant *value) const
	{
        return new CallingConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheCalling::newNode(const Constant *&link, const Special *value) const
	{
        return new CallingConstant(link, *this, value);
	}

	const NodeExpressShort *BuiltinClicheCalling::node(const Express *element) const
	{
        return new CallingExpress(*this, element);
	}

	const NodeConstantShort *BuiltinClicheCallingOk::newNode(const Constant *&link, const Integer *value) const
	{
        return new CallingOkConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheCallingOk::newNode(const Constant *&link, const Float *value) const
	{
        return new CallingOkConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheCallingOk::newNode(const Constant *&link, const PilsColor *value) const
	{
        return new CallingOkConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheCallingOk::newNode(const Constant *&link, const Timestamp *value) const
	{
        return new CallingOkConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheCallingOk::newNode(const Constant *&link, const Duration *value) const
	{
        return new CallingOkConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheCallingOk::newNode(const Constant *&link, const PilsDate *value) const
	{
        return new CallingOkConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheCallingOk::newNode(const Constant *&link, const PilsString *value) const
	{
        return new CallingOkConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheCallingOk::newNode(const Constant *&link, const Cliche *value) const
	{
        return new CallingOkConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheCallingOk::newNode(const Constant *&link, const ListConstant *value) const
	{
        return new CallingOkConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheCallingOk::newNode(const Constant *&link, const NodeConstant *value) const
	{
        return new CallingOkConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheCallingOk::newNode(const Constant *&link, const Special *value) const
	{
        return new CallingOkConstant(link, *this, value);
	}

	const NodeExpressShort *BuiltinClicheCallingOk::node(const Express *element) const
	{
        return new CallingOkExpress(*this, element);
	}

	const Step *CallingOkConstant::calling(Runner &run, const Constant &call) const
	{
		return element[0]->passUncounted(run);
	}

	const Step *CallingOkConstant::calling(Runner &run, const Integer &call) const
	{
		return element[0]->passUncounted(run);
	}

	const Step *CallingOkConstant::calling(Runner &run, const Empty &call) const
	{
		return element[0]->passUncounted(run);
	}

	const Step *CallingOkConstant::calling(Runner &run, const ListConstant &call) const
	{
		return element[0]->passUncounted(run);
	}

	const Step *CallingOkConstant::calling(Runner &run, const NodeConstant &call) const
	{
		return element[0]->passUncounted(run);
	}

	const Step *CallingOkConstant::calling(Runner &run, const ListExpress &call) const
	{
		return element[0]->passUncounted(run);
	}

	const Step *CallingOkConstant::calling(Runner &run, const NodeExpress &call) const
	{
		return element[0]->passUncounted(run);
	}

	const Step *CallingOkExpress::calling(Runner &run, const Constant &call) const
	{
		return element[0]->passUncounted(run);
	}

	const Step *CallingOkExpress::calling(Runner &run, const Integer &call) const
	{
		return element[0]->passUncounted(run);
	}

	const Step *CallingOkExpress::calling(Runner &run, const Empty &call) const
	{
		return element[0]->passUncounted(run);
	}

	const Step *CallingOkExpress::calling(Runner &run, const ListConstant &call) const
	{
		return element[0]->passUncounted(run);
	}

	const Step *CallingOkExpress::calling(Runner &run, const NodeConstant &call) const
	{
		return element[0]->passUncounted(run);
	}

	const Step *CallingOkExpress::calling(Runner &run, const ListExpress &call) const
	{
		return element[0]->passUncounted(run);
	}

	const Step *CallingOkExpress::calling(Runner &run, const NodeExpress &call) const
	{
		return element[0]->passUncounted(run);
	}

	const Step *CallingConstant::calling(Runner &run, const Constant &call) const
	{
		new (run.allocate(sizeof(SinkCallaround))) SinkCallaround(*run.calling.who);
		run.calling.who = &call;
		return element[0]->caller(run, call);
	}

	const Step *CallingConstant::calling(Runner &run, const Integer &call) const
	{
		new (run.allocate(sizeof(SinkCallaround))) SinkCallaround(*run.calling.who);
		run.calling.who = &call;
		return element[0]->caller(run, call);
	}

	const Step *CallingConstant::calling(Runner &run, const Empty &call) const
	{
		new (run.allocate(sizeof(SinkCallaround))) SinkCallaround(*run.calling.who);
		run.calling.who = &call;
		return element[0]->caller(run, call);
	}

	const Step *CallingConstant::calling(Runner &run, const ListConstant &call) const
	{
		new (run.allocate(sizeof(SinkCallaround))) SinkCallaround(*run.calling.who);
		run.calling.who = &call;
		return element[0]->caller(run, call);
	}

	const Step *CallingConstant::calling(Runner &run, const NodeConstant &call) const
	{
		new (run.allocate(sizeof(SinkCallaround))) SinkCallaround(*run.calling.who);
		run.calling.who = &call;
		return element[0]->caller(run, call);
	}

	const Step *CallingConstant::calling(Runner &run, const ListExpress &call) const
	{
		new (run.allocate(sizeof(SinkCallaround))) SinkCallaround(*run.calling.who);
		run.calling.who = &call;
		return element[0]->caller(run, call);
	}

	const Step *CallingConstant::calling(Runner &run, const NodeExpress &call) const
	{
		new (run.allocate(sizeof(SinkCallaround))) SinkCallaround(*run.calling.who);
		run.calling.who = &call;
		return element[0]->caller(run, call);
	}

	const Step *CallingConstant::calling(Runner &run, const Any &call, const Any *assignValue) const
	{
		new (run.allocate(sizeof(SinkCallaround))) SinkCallaround(*run.calling.who);
		run.calling.who = &call;
		return call.calling(run, *element[0], assignValue);
	}

	const Step *CallingExpress::calling(Runner &run, const Constant &call) const
	{
		new (run.allocate(sizeof(SinkCallaround))) SinkCallaround(*run.calling.who);
		run.calling.who = &call;
		return element[0]->caller(run, call);
	}

	const Step *CallingExpress::calling(Runner &run, const Integer &call) const
	{
		new (run.allocate(sizeof(SinkCallaround))) SinkCallaround(*run.calling.who);
		run.calling.who = &call;
		return element[0]->caller(run, call);
	}

	const Step *CallingExpress::calling(Runner &run, const Empty &call) const
	{
		new (run.allocate(sizeof(SinkCallaround))) SinkCallaround(*run.calling.who);
		run.calling.who = &call;
		return element[0]->caller(run, call);
	}

	const Step *CallingExpress::calling(Runner &run, const ListConstant &call) const
	{
		new (run.allocate(sizeof(SinkCallaround))) SinkCallaround(*run.calling.who);
		run.calling.who = &call;
		return element[0]->caller(run, call);
	}

	const Step *CallingExpress::calling(Runner &run, const NodeConstant &call) const
	{
		new (run.allocate(sizeof(SinkCallaround))) SinkCallaround(*run.calling.who);
		run.calling.who = &call;
		return element[0]->caller(run, call);
	}

	const Step *CallingExpress::calling(Runner &run, const ListExpress &call) const
	{
		new (run.allocate(sizeof(SinkCallaround))) SinkCallaround(*run.calling.who);
		run.calling.who = &call;
		return element[0]->caller(run, call);
	}

	const Step *CallingExpress::calling(Runner &run, const NodeExpress &call) const
	{
		new (run.allocate(sizeof(SinkCallaround))) SinkCallaround(*run.calling.who);
		run.calling.who = &call;
		return element[0]->caller(run, call);
	}

	const Step *CallingExpress::calling(Runner &run, const Any &call, const Any *assignValue) const
	{
		new (run.allocate(sizeof(SinkCallaround))) SinkCallaround(*run.calling.who);
		run.calling.who = &call;
		return call.calling(run, *element[0], assignValue);
	}

	Sink *SinkCallaround::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkCallaround::pass(Runner &run, const Any *value)
	{
		run.sink = this + 1;
		return value->passCounted(run);
	}

	const Step *SinkCallaround::tailStep(Runner &run, const Any *thing)
	{
		return (run.sink = this + 1)->tailStep(run, thing);
	}

	const Step *SinkCallaround::tailStep(Runner &run, const Any *thing, const Any *where_)
	{
		return (run.sink = this + 1)->tailStep(run, thing, where_);
	}

	Pipe *SinkCallaround::connectPipe(Runner &run)
	{
		return (run.sink = this + 1)->connectPipe(run);
	}

	const Step *SinkCallaround::error(Runner &run, const Any *error, const Express *what, const Any *who)
	{
		return (run.sink = this + 1)->error(run, error, what, who);
	}

	const Step *SinkCallaround::called(Runner &run, const Constant &failed)
	{
		const Any &call = *run.calling.who;
		run.calling.who = &who;
		run.sink = this + 1;
		//delegate to called(..., T &call) through dummy call
		return call.caller(run, Empty::singleton);
	}

	const Step *SinkCallaround::called(Runner &run, const Integer &failed)
	{
		const Any &call = *run.calling.who;
		run.calling.who = &who;
		run.sink = this + 1;
		//delegate to called(..., T &call) through dummy call
		return call.caller(run, Empty::singleton);
	}

	const Step *SinkCallaround::called(Runner &run, const Empty &failed)
	{
		const Any &call = *run.calling.who;
		run.calling.who = &who;
		run.sink = this + 1;
		//delegate to called(..., T &call) through dummy call
		return call.caller(run, Empty::singleton);
	}

	const Step *SinkCallaround::called(Runner &run, const ListConstant &failed)
	{
		const Any &call = *run.calling.who;
		run.calling.who = &who;
		run.sink = this + 1;
		//delegate to called(..., T &call) through dummy call
		return call.caller(run, Empty::singleton);
	}

	const Step *SinkCallaround::called(Runner &run, const NodeConstant &failed)
	{
		const Any &call = *run.calling.who;
		run.calling.who = &who;
		run.sink = this + 1;
		//delegate to called(..., T &call) through dummy call
		return call.caller(run, Empty::singleton);
	}

	const Step *SinkCallaround::called(Runner &run, const ListExpress &failed)
	{
		const Any &call = *run.calling.who;
		run.calling.who = &who;
		run.sink = this + 1;
		//delegate to called(..., T &call) through dummy call
		return call.caller(run, Empty::singleton);
	}

	const Step *SinkCallaround::called(Runner &run, const NodeExpress &failed)
	{
		const Any &call = *run.calling.who;
		run.calling.who = &who;
		run.sink = this + 1;
		//delegate to called(..., T &call) through dummy call
		return call.caller(run, Empty::singleton);
	}

	const Step *SinkCallaround::called(Runner &run, const Any &failed, const Any *assignValue)
	{
		const Any &call = *run.calling.who;
		run.calling.who = &who;
		return (run.sink = this + 1)->called(run, call, assignValue);
	}

	const Step *BuiltinClicheCalling::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		new (run.allocate(sizeof(SinkWhoCalling))) SinkWhoCalling(what, value);
		return what.whoAttribute();
	}

	Sink *SinkWhoCalling::kick(Runner &run)
	{
        run.release(who);
		return this + 1;
	}

	const Step *SinkWhoCalling::pass(Runner &run, const Any* call)
	{
		const Any *who = this->who;
		const WhoUntypedOperation &what = this->what;
		return (run.sink = this + 1)->callaround(run, what, call, who);
	}

	const Step *Sink::callaround(Runner &run, const Express &what, const Any *call, const Any *who)
	{
		new (run.allocate(sizeof(SinkCalling))) SinkCalling(call, who);
		run.calling.what = &what;
		run.calling.who = who;
		return call->caller(run, *who);
	}

	const Step *Sink::assignCallaround(Runner &run, const Express &what, const Any *call, const Any *who, const Any *assignValue)
	{
		new (run.allocate(sizeof(SinkCalling))) SinkCalling(call, who);
		run.calling.what = &what;
		run.calling.who = who;
		return who->calling(run, *call, assignValue);
	}

	Sink *SinkCalling::kick(Runner &run)
	{
        run.release(call);
        run.release(who);
		return this + 1;
	}

	const Step *SinkCalling::pass(Runner &run, const Any *value)
	{
        run.release(call);
        run.release(who);
        run.sink = this + 1;
		return value->passCounted(run);
	}

	const Step *SinkCalling::error(Runner &run, const Any *error, const Express *what, const Any *who)
	{
        run.release(call);
        run.release(who);
        return (run.sink = this + 1)->error(run, error, what, who);
	}

	const Step *SinkCalling::tailStep(Runner &run, const Any *thing)
	{
        run.release(call);
        run.release(who);
        return (run.sink = this + 1)->tailStep(run, thing);
	}

	const Step *SinkCalling::tailStep(Runner &run, const Any *thing, const Any *who)
	{
        run.release(call);
        run.release(this->who);
        return (run.sink = this + 1)->tailStep(run, thing, who);
	}

	Pipe *SinkCalling::connectPipe(Runner &run)
	{
        run.release(call);
        run.release(this->who);
        return (run.sink = this + 1)->connectPipe(run);
	}

	const Step *BuiltinClicheCalling::gotOperand(Runner &run, const WhoAssign &what, const Any *value, const Any *assignValue) const
	{
		const CallWho &whoOperation = (const CallWho&)*what.whoAttribute();
		new (run.allocate(sizeof(SinkWhoCallingAssign))) SinkWhoCallingAssign(what, value, assignValue);
		return whoOperation.whoAttribute();
	}

	Sink *SinkWhoCallingAssign::kick(Runner &run)
	{
        run.release(who);
        run.release(assignValue);
		return this + 1;
	}

	const Step *SinkWhoCallingAssign::pass(Runner &run, const Any *call)
	{
		const Any *assignValue = this->assignValue;
		const Any *who = this->who;
		const Express &what = this->what;
		return (run.sink = this + 1)->assignCallaround(run, what, call, who, assignValue);
	}

	const Step *PredefinedNameOk::calling(Runner &run, const Constant &call) const
	{
		call.retain();
		return call.passCounted(run);
	}

	const Step *PredefinedNameOk::calling(Runner &run, const Integer &call) const
	{
		call.retain();
		return run.sink->pass(run, &call);
	}
	const Step *PredefinedNameOk::calling(Runner &run, const ListConstant &call) const
	{
		call.retain();
		return run.sink->pass(run, &call);
	}
	const Step *PredefinedNameOk::calling(Runner &run, const NodeConstant &call) const
	{
		call.retain();
		return call.passCounted(run);
	}
	const Step *PredefinedNameOk::calling(Runner &run, const Empty &call) const
	{
		call.retain();
		return run.sink->pass(run, &call);
	}
	const Step *PredefinedNameOk::calling(Runner &run, const ListExpress &call) const
	{
		call.retain();
		return run.sink->pass(run, &call);
	}
	const Step *PredefinedNameOk::calling(Runner &run, const NodeExpress &call) const
	{
		call.retain();
		return call.passCounted(run);
	}
	const NodeConstantShort *BuiltinClicheWhoTag::newNode(const Constant *&link, const Integer *value) const
	{
        return new WhoTagConstant(link, *this, value);
	}
	const NodeConstantShort *BuiltinClicheWhoTag::newNode(const Constant *&link, const Float *value) const
	{
        return new WhoTagConstant(link, *this, value);
	}
	const NodeConstantShort *BuiltinClicheWhoTag::newNode(const Constant *&link, const PilsColor *value) const
	{
        return new WhoTagConstant(link, *this, value);
	}
	const NodeConstantShort *BuiltinClicheWhoTag::newNode(const Constant *&link, const Timestamp *value) const
	{
        return new WhoTagConstant(link, *this, value);
	}
	const NodeConstantShort *BuiltinClicheWhoTag::newNode(const Constant *&link, const Duration *value) const
	{
        return new WhoTagConstant(link, *this, value);
	}
	const NodeConstantShort *BuiltinClicheWhoTag::newNode(const Constant *&link, const PilsDate *value) const
	{
        return new WhoTagConstant(link, *this, value);
	}
	const NodeConstantShort *BuiltinClicheWhoTag::newNode(const Constant *&link, const PilsString *value) const
	{
        return new WhoTagConstant(link, *this, value);
	}
	const NodeConstantShort *BuiltinClicheWhoTag::newNode(const Constant *&link, const Cliche *value) const
	{
        return new WhoTagConstant(link, *this, value);
	}
	const NodeConstantShort *BuiltinClicheWhoTag::newNode(const Constant *&link, const Special *value) const
	{
        return new WhoTagConstant(link, *this, value);
	}
	const NodeConstantShort *BuiltinClicheWhoTag::newNode(const Constant *&link, const NodeConstant *value) const
	{
        return new WhoTagConstant(link, *this, value);
	}
	const NodeConstantShort *BuiltinClicheWhoTag::newNode(const Constant *&link, const ListConstant *value) const
	{
        return new WhoTagConstant(link, *this, value);
	}
	const NodeExpressShort *BuiltinClicheWhoTag::node(const Express *value) const
	{
        return new WhoTagExpress(*this, value);
	}

	const Step *WhoTagConstant::calling(Runner &run, const Constant &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		return (run.calling.who = element[0])->calling(run, call);
	}

	const Step *WhoTagConstant::calling(Runner &run, const Integer &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		return (run.calling.who = element[0])->calling(run, call);
	}

	const Step *WhoTagConstant::calling(Runner &run, const NodeConstant &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		return (run.calling.who = element[0])->calling(run, call);
	}

	const Step *WhoTagConstant::calling(Runner &run, const ListConstant &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		return (run.calling.who = element[0])->calling(run, call);
	}

	const Step *WhoTagConstant::calling(Runner &run, const Empty &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		return (run.calling.who = element[0])->calling(run, call);
	}

	const Step *WhoTagConstant::calling(Runner &run, const ListExpress &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		return (run.calling.who = element[0])->calling(run, call);
	}

	const Step *WhoTagConstant::calling(Runner &run, const NodeExpress &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		return (run.calling.who = element[0])->calling(run, call);
	}

	const Step *WhoTagConstant::calling(Runner &run, const Any &call, const Any *assignValue) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		return (run.calling.who = element[0])->calling(run, call, assignValue);
	}

	const Step *WhoTagExpress::calling(Runner &run, const Constant &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		return (run.calling.who = element[0])->calling(run, call);
	}

	const Step *WhoTagExpress::calling(Runner &run, const Integer &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		return (run.calling.who = element[0])->calling(run, call);
	}

	const Step *WhoTagExpress::calling(Runner &run, const NodeConstant &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		return (run.calling.who = element[0])->calling(run, call);
	}

	const Step *WhoTagExpress::calling(Runner &run, const ListConstant &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		return (run.calling.who = element[0])->calling(run, call);
	}

	const Step *WhoTagExpress::calling(Runner &run, const Empty &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		return (run.calling.who = element[0])->calling(run, call);
	}

	const Step *WhoTagExpress::calling(Runner &run, const ListExpress &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		return (run.calling.who = element[0])->calling(run, call);
	}

	const Step *WhoTagExpress::calling(Runner &run, const NodeExpress &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		return (run.calling.who = element[0])->calling(run, call);
	}

	const Step *WhoTagExpress::calling(Runner &run, const Any &call, const Any *assignValue) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		return (run.calling.who = element[0])->calling(run, call, assignValue);
	}

	const Any *BuiltinClicheWhoTagTrailer::node(const Any *const *element) const
	{
		for(size_t i = 0; i < count; i++)
		{
			if(element[i]->as_Constant() == nullptr)
			{
                return new const WhoTagExpressTrailer(*this, element);
			}
		}
		return ((const ClicheLong*)this)->node((const Constant *const *)(void*const *)element);
	}

	const NodeConstantLong *BuiltinClicheWhoTagTrailer::newNodeConstant(const Constant *&link, const Constant *const *value) const
	{
        return new WhoTagConstantTrailer(link, *this, value);
	}

	const Step *WhoTagConstantTrailer::calling(Runner &run, const Constant &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		run.calling.who = element[1];
		return element[0]->calling(run, call);
	}

	const Step *WhoTagConstantTrailer::calling(Runner &run, const Integer &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		run.calling.who = element[1];
		return element[0]->calling(run, call);
	}

	const Step *WhoTagConstantTrailer::calling(Runner &run, const NodeConstant &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		run.calling.who = element[1];
		return element[0]->calling(run, call);
	}

	const Step *WhoTagConstantTrailer::calling(Runner &run, const ListConstant &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		run.calling.who = element[1];
		return element[0]->calling(run, call);
	}

	const Step *WhoTagConstantTrailer::calling(Runner &run, const Empty &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		run.calling.who = element[1];
		return element[0]->calling(run, call);
	}

	const Step *WhoTagConstantTrailer::calling(Runner &run, const ListExpress &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		run.calling.who = element[1];
		return element[0]->calling(run, call);
	}

	const Step *WhoTagConstantTrailer::calling(Runner &run, const NodeExpress &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		run.calling.who = element[1];
		return element[0]->calling(run, call);
	}

	const Step *WhoTagConstantTrailer::calling(Runner &run, const Any &call, const Any *assignValue) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		run.calling.who = element[1];
		return element[0]->calling(run, call, assignValue);
	}

	const Step *WhoTagExpressTrailer::calling(Runner &run, const Constant &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		run.calling.who = element[1];
		return element[0]->calling(run, call);
	}

	const Step *WhoTagExpressTrailer::calling(Runner &run, const Integer &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		run.calling.who = element[1];
		return element[0]->calling(run, call);
	}

	const Step *WhoTagExpressTrailer::calling(Runner &run, const NodeConstant &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		run.calling.who = element[1];
		return element[0]->calling(run, call);
	}

	const Step *WhoTagExpressTrailer::calling(Runner &run, const ListConstant &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		run.calling.who = element[1];
		return element[0]->calling(run, call);
	}

	const Step *WhoTagExpressTrailer::calling(Runner &run, const Empty &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		run.calling.who = element[1];
		return element[0]->calling(run, call);
	}

	const Step *WhoTagExpressTrailer::calling(Runner &run, const ListExpress &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		run.calling.who = element[1];
		return element[0]->calling(run, call);
	}

	const Step *WhoTagExpressTrailer::calling(Runner &run, const NodeExpress &call) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		run.calling.who = element[1];
		return element[0]->calling(run, call);
	}

	const Step *WhoTagExpressTrailer::calling(Runner &run, const Any &call, const Any *assignValue) const
	{
		new (run.allocate(sizeof(SinkCallingWhoTag))) SinkCallingWhoTag(*run.calling.who);
		run.calling.who = element[1];
		return element[0]->calling(run, call, assignValue);
	}

	const Step *SinkCallingWhoTag::called(Runner &run, const Constant &call)
	{
		run.calling.who = &stacked;
		return (run.sink = kick(run))->called(run, call);
	}

	const Step *SinkCallingWhoTag::called(Runner &run, const Integer &call)
	{
		run.calling.who = &stacked;
		return (run.sink = kick(run))->called(run, call);
	}

	const Step *SinkCallingWhoTag::called(Runner &run, const Empty &call)
	{
		run.calling.who = &stacked;
		return (run.sink = kick(run))->called(run, call);
	}

	const Step *SinkCallingWhoTag::called(Runner &run, const ListConstant &call)
	{
		run.calling.who = &stacked;
		return (run.sink = kick(run))->called(run, call);
	}

	const Step *SinkCallingWhoTag::called(Runner &run, const NodeConstant &call)
	{
		run.calling.who = &stacked;
		return (run.sink = kick(run))->called(run, call);
	}

	const Step *SinkCallingWhoTag::called(Runner &run, const ListExpress &call)
	{
		run.calling.who = &stacked;
		return (run.sink = kick(run))->called(run, call);
	}

	const Step *SinkCallingWhoTag::called(Runner &run, const NodeExpress &call)
	{
		run.calling.who = &stacked;
		return (run.sink = kick(run))->called(run, call);
	}

	const Step *SinkCallingWhoTag::called(Runner &run, const Any &call, const Any *assignValue)
	{
		run.calling.who = &stacked;
		return (run.sink = kick(run))->called(run, call, assignValue);
	}

	const NodeExpressShort *BuiltinClicheRecalling::node(const Express *element) const
	{
        return new Recalling(*this, element);
	}

	const Any *BuiltinClicheRecalling::node(const Constant *element) const
	{
        return new Recalling(*this, element);
	}

	const Step *BuiltinClicheRecall::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		new (run.allocate(sizeof(SinkWhoRecall))) SinkWhoRecall(what, value);
		return what.whoAttribute();
	}

	const Step *SinkWhoRecall::pass(Runner &run, const Any* call)
	{
        const Recalling *who = new Recalling(BuiltinClicheRecalling::singleton, this->who);
		const WhoUntypedOperation &what = this->what;
		run.sink = this + 1;
		run.sinkTagChain = new (run.allocate(sizeof(SinkRecall))) SinkRecall(call, who, run.sinkTagChain);
		run.calling.what = &what;
		run.calling.who = who;
		return call->caller(run, *who);
	}

	const Step *SinkRecall::skip(Runner &run)
	{
		throw L"Internal PILS error: Bad tagged sink";
	}

	Sink *SinkRecall::kick(Runner &run)
	{
        run.release(&tag);
        run.release(call);
		for (std::map<const Constant*, const Any*>::iterator i=map.begin(); i != map.end(); i++)
		{
            run.release(i->first);
            if(i->second) run.release(i->second);
		}
		map.~map();
		return run.sinkTagChain = this + 1;
	}

	const Step *SinkRecall::pass(Runner &run, double value){return Sink::pass(run, value);}
	const Step *SinkRecall::pass(Runner &run, const Integer &value){return Sink::pass(run, value);}
	const Step *SinkRecall::pass(Runner &run, const Float &value){return Sink::pass(run, value);}
	const Step *SinkRecall::pass(Runner &run, const PilsString &value){return Sink::pass(run, value);}
	const Step *SinkRecall::pass(Runner &run, const Cliche &value){return Sink::pass(run, value);}
	const Step *SinkRecall::pass(Runner &run, const ListConstant &value){return Sink::pass(run, value);}
	const Step *SinkRecall::pass(Runner &run, const NodeConstantLong &value){return Sink::pass(run, value);}
	const Step *SinkRecall::pass(Runner &run, const NodeConstantShort &value){return Sink::pass(run, value);}
	const Step *SinkRecall::pass(Runner &run, const ListExpress &value){return Sink::pass(run, value);}
	const Step *SinkRecall::pass(Runner &run, const NodeExpressLong &value){return Sink::pass(run, value);}
	const Step *SinkRecall::pass(Runner &run, const NodeExpressShort &value){return Sink::pass(run, value);}
	const Step *SinkRecall::pass(Runner &run, const Any *value)
	{
		run.sink = kick(run);
		return value->passCounted(run);
	}
	bool SinkRecall::needsResult(){return true;}

	const Step *Recalling::calling(Runner &run, const Constant &call) const
	{
		SinkTagged *tagged;
		for (tagged = run.sinkTagChain; tagged && &tagged->tag != this; tagged = tagged->chain) {;}
		if (tagged)
		{
			SinkRecall &sinkRecall = *static_cast<SinkRecall *>(tagged);
			std::pair<std::map<const Constant*, const Any*>::iterator, bool> insert = sinkRecall.map.insert(std::pair<const Constant *, const Any *>(&call, static_cast<const Any *>(nullptr)));
			if (insert.second)
			{
				call.retain();
				new (run.allocate(sizeof(SinkRecalling))) SinkRecalling(sinkRecall, call);
				return call.caller(run, *element[0]);
			}
			else if (insert.first->second)
				return insert.first->second->passUncounted(run);
		}
		return call.caller(run, Empty::singleton);
	}
	const Step *Recalling::calling(Runner &run, const Integer &call) const {return calling(run, (const Constant &)call);}
	const Step *Recalling::calling(Runner &run, const ListConstant &call) const {return calling(run, (const Constant &)call);}
	const Step *Recalling::calling(Runner &run, const NodeConstant &call) const {return calling(run, (const Constant &)call);}
	const Step *Recalling::calling(Runner &run, const Empty &call) const {return calling(run, (const Constant &)call);}

	Sink *SinkRecalling::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkRecalling::pass(Runner &run, const Any *value)
	{
		sinkRecall.map[&call] = value;
		run.sink = this + 1;
		return value->passUncounted(run);
	}

	const Step *SinkRecalling::called(Runner &run, const Constant &call)
	{
		return (run.sink = this + 1)->called(run, call);
	}

	const Step *SinkRecalling::called(Runner &run, const Integer &call)
	{
		return (run.sink = this + 1)->called(run, call);
	}

	const Step *SinkRecalling::called(Runner &run, const NodeConstant &call)
	{
		return (run.sink = this + 1)->called(run, call);
	}

	const Step *SinkRecalling::called(Runner &run, const ListConstant &call)
	{
		return (run.sink = this + 1)->called(run, call);
	}

	const Step *SinkRecalling::called(Runner &run, const Empty &call)
	{
		return (run.sink = this + 1)->called(run, call);
	}

	const NodeConstantShort *BuiltinClicheNot::newNode(const Constant *&link, const Integer *value) const
	{
        return new NotConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheNot::newNode(const Constant *&link, const Float *value) const
	{
        return new NotConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheNot::newNode(const Constant *&link, const PilsColor *value) const
	{
        return new NotConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheNot::newNode(const Constant *&link, const Timestamp *value) const
	{
        return new NotConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheNot::newNode(const Constant *&link, const Duration *value) const
	{
        return new NotConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheNot::newNode(const Constant *&link, const PilsDate *value) const
	{
        return new NotConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheNot::newNode(const Constant *&link, const PilsString *value) const
	{
        return new NotConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheNot::newNode(const Constant *&link, const Cliche *value) const
	{
        return new NotConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheNot::newNode(const Constant *&link, const Special *value) const
	{
        return new NotConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheNot::newNode(const Constant *&link, const ListConstant *value) const
	{
        return new NotConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheNot::newNode(const Constant *&link, const NodeConstant *value) const
	{
        return new NotConstant(link, *this, value);
	}

	const NodeExpressShort *BuiltinClicheNot::node(const Express *value) const
	{
        return new NotExpress(*this, value);
	}

	const Step *NotConstant::calling(Runner &run, const Constant &call) const
	{
		new (run.allocate(sizeof(SinkCallingNot))) SinkCallingNot(call);
		return element[0]->calling(run, call);
	}

	const Step *NotConstant::calling(Runner &run, const Integer &call) const
	{
		new (run.allocate(sizeof(SinkCallingNot))) SinkCallingNot(call);
		return element[0]->calling(run, call);
	}

	const Step *NotConstant::calling(Runner &run, const Empty &call) const
	{
		new (run.allocate(sizeof(SinkCallingNot))) SinkCallingNot(call);
		return element[0]->calling(run, call);
	}

	const Step *NotConstant::calling(Runner &run, const ListConstant &call) const
	{
		new (run.allocate(sizeof(SinkCallingNot))) SinkCallingNot(call);
		return element[0]->calling(run, call);
	}

	const Step *NotConstant::calling(Runner &run, const ListExpress &call) const
	{
		new (run.allocate(sizeof(SinkCallingNot))) SinkCallingNot(call);
		return element[0]->calling(run, call);
	}

	const Step *NotConstant::calling(Runner &run, const NodeConstant &call) const
	{
		new (run.allocate(sizeof(SinkCallingNot))) SinkCallingNot(call);
		return element[0]->calling(run, call);
	}

	const Step *NotConstant::calling(Runner &run, const NodeExpress &call) const
	{
		new (run.allocate(sizeof(SinkCallingNot))) SinkCallingNot(call);
		return element[0]->calling(run, call);
	}

	const Step *NotExpress::calling(Runner &run, const Constant &call) const
	{
		new (run.allocate(sizeof(SinkCallingNot))) SinkCallingNot(call);
		return element[0]->calling(run, call);
	}

	const Step *NotExpress::calling(Runner &run, const Integer &call) const
	{
		new (run.allocate(sizeof(SinkCallingNot))) SinkCallingNot(call);
		return element[0]->calling(run, call);
	}

	const Step *NotExpress::calling(Runner &run, const Empty &call) const
	{
		new (run.allocate(sizeof(SinkCallingNot))) SinkCallingNot(call);
		return element[0]->calling(run, call);
	}

	const Step *NotExpress::calling(Runner &run, const ListConstant &call) const
	{
		new (run.allocate(sizeof(SinkCallingNot))) SinkCallingNot(call);
		return element[0]->calling(run, call);
	}

	const Step *NotExpress::calling(Runner &run, const ListExpress &call) const
	{
		new (run.allocate(sizeof(SinkCallingNot))) SinkCallingNot(call);
		return element[0]->calling(run, call);
	}

	const Step *NotExpress::calling(Runner &run, const NodeConstant &call) const
	{
		new (run.allocate(sizeof(SinkCallingNot))) SinkCallingNot(call);
		return element[0]->calling(run, call);
	}

	const Step *NotExpress::calling(Runner &run, const NodeExpress &call) const
	{
		new (run.allocate(sizeof(SinkCallingNot))) SinkCallingNot(call);
		return element[0]->calling(run, call);
	}

	Sink *SinkCallingNot::kick(PILS::Runner &run)
	{
		return this + 1;
	}

	const Step *SinkCallingNot::called(Runner &run, const ListConstant &)
	{
		const Any &call = this->call;
		run.sink = this + 1;
		return call.passUncounted(run);
	}

	const Step *SinkCallingNot::called(Runner &run, const ListExpress &)
	{
		const Any &call = this->call;
		run.sink = this + 1;
		return call.passUncounted(run);
	}

	const Step *SinkCallingNot::called(Runner &run, const NodeConstant &)
	{
		const Any &call = this->call;
		run.sink = this + 1;
		return call.passUncounted(run);
	}

	const Step *SinkCallingNot::called(Runner &run, const NodeExpress &)
	{
		const Any &call = this->call;
		run.sink = this + 1;
		return call.passUncounted(run);
	}

	const Step *SinkCallingNot::called(Runner &run, const Integer &)
	{
		const Any &call = this->call;
		run.sink = this + 1;
		return call.passUncounted(run);
	}

	const Step *SinkCallingNot::called(Runner &run, const Empty &)
	{
		const Any &call = this->call;
		run.sink = this + 1;
		return call.passUncounted(run);
	}

	const Step *SinkCallingNot::called(Runner &run, const Constant &)
	{
		const Any &call = this->call;
		run.sink = this + 1;
		return call.passUncounted(run);
	}

	const Step *SinkCallingNot::called(PILS::Runner &run, const PILS::Any &, const PILS::Any *assignValue)
	{
        run.release(assignValue);
		const Any &call = this->call;
		run.sink = this + 1;
		return call.passUncounted(run);
	}

	const Step *SinkCallingNot::pass(Runner &run, long value)
	{
		const Any &call = this->call;
		run.sink = this + 1;
		return call.caller(run, Empty::singleton);
	}

	const Step *SinkCallingNot::error(Runner &run, const Any *error, const Express *what, const Any *who)
	{
		return (run.sink = kick(run))->error(run, error, what, who);
	}
}
