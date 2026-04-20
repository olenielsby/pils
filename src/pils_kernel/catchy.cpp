/* This file is public domain */
#include "catchy.h"
namespace PILS
{
	const Express *Any::findCatchTag() const
	{
        return nullptr;
	}

	const Express *Any::findCatchTag(const Constant &tag) const
	{
        return nullptr;
	}

	const Express *Bind::findCatchTag() const
	{
		return element[0]->findCatchTag();
	}

	const Express *Bind::findCatchTag(const Constant &tag) const
	{
		return element[0]->findCatchTag(tag);
	}

	const Express *Jumper::findCatchTag() const
	{
		return this;
	}

	const Express *Jumper0::findCatchTag() const
	{
		return this;
	}

	const Express *Jumper0::findCatchTag(const Constant &tag) const
	{
		return element[0]->findCatchTag(tag);
	}

	const Express *Jumper1::findCatchTag() const
	{
		return this;
	}

	const Express *Jumper2::findCatchTag() const
	{
		return this;
	}

	const Express *Jumper3::findCatchTag() const
	{
		return this;
	}

	const Any *BuiltinClicheOk::node(const Constant *element) const
	{
        return new const OkConstant(*this, element);
	}

	const NodeExpressShort *BuiltinClicheOk::node(const Express *element) const
	{
        return new const Ok(*this, element);
	}

	const Any *ImplicitParameter::ImplicitClicheShort::node(const Constant *element) const
	{
        return new ImplicitParameterShort(*this, element);
	}

	const NodeExpressShort *ImplicitParameter::ImplicitClicheShort::node(const Express *element) const
	{
        return new ImplicitParameterShort(*this, element);
	}

	const Any *ImplicitParameter::ImplicitClicheTrailer::node(const Constant *const *element) const
	{
        return new ImplicitParameterTrailer(*this, (const Any *const *)element);
	}

	const Any *ImplicitParameter::ImplicitClicheTrailer::node(const Any *const *element) const
	{
		if (element[1]->as_Constant())
		{
            return new ImplicitParameterTrailer(*this, element);
		}
		else
		{
			return PokerClicheTrailer::node(element);
		}
	}

	Catch::Catch(Runner &run, const QuickActionAny &action, const NodeExpress *where_)
		: SinkTagged(*where_, run.sinkTagChain),
		  action(action),
		  where_(*run.where_),
		  what(*run.calling.what),
		  who(*run.calling.who),
		  closure(*run.calling.closure)
	{
		run.where_ = where_;
		run.sinkTagChain = this;
		this->trial = this;
	}

	Sink *CatchConstant::kick(Runner &run)
	{
		run.sinkTagChain = chain;
		run.where_->release();
		run.where_ = &where_;
		run.calling.what = &what;
		return this + 1;
	}

	Sink *CatchNodeConstant::kick(Runner &run)
	{
		run.sinkTagChain = chain;
		run.where_->release();
		run.where_ = &where_;
		run.calling.what = &what;
		return this + 1;
	}

	Sink *CatchListConstant::kick(Runner &run)
	{
		run.sinkTagChain = chain;
		run.where_->release();
		run.where_ = &where_;
		run.calling.what = &what;
		return this + 1;
	}

	Sink *CatchEmpty::kick(Runner &run)
	{
		run.sinkTagChain = chain;
		run.where_->release();
		run.where_ = &where_;
		run.calling.what = &what;
		return this + 1;
	}

	Sink *CatchNodeExpress::kick(Runner &run)
	{
		run.sinkTagChain = chain;
		run.where_->release();
		run.where_ = &where_;
		run.calling.what = &what;
		return this + 1;
	}

	Sink *CatchListExpress::kick(Runner &run)
	{
		run.sinkTagChain = chain;
		run.where_->release();
		run.where_ = &where_;
		run.calling.what = &what;
		return this + 1;
	}

	Sink *CatchAssign::kick(Runner &run)
	{
		run.sinkTagChain = chain;
		run.where_->release();
		run.where_ = &where_;
		assignValue->release();
		run.calling.what = &what;
		return this + 1;
	}

	const Step *CatchyShort::step_(Runner &run) const
	{
		const Express *tag = run.where_->findCatchTag();
		if (tag)
		{
			for (SinkTagged *catcher = run.sinkTagChain; catcher; catcher = catcher->chain)
			if (&catcher->tag == tag)
				return catching(run, *(Catch*)catcher);
		}
		retain();
		retain();
		retain();
		return run.sink->error(run, this, this, this);
	}

	const Step *CatchyTrailer::step_(Runner &run) const
	{
		const Express *tag = run.where_->findCatchTag();
		if (tag)
		{
			for (SinkTagged *catcher = run.sinkTagChain; catcher; catcher = catcher->chain)
			if (&catcher->tag == tag)
				return catching(run, *(Catch*)catcher);
		}
		retain();
		retain();
		retain();
		return run.sink->error(run, this, this, this);
	}

	const Step *CatchyTagTrailer::step_(Runner &run) const
	{
		const Express *tag = run.where_->findCatchTag((const Constant &)*element[1]);
		if (tag)
		{
			for (SinkTagged *catcher = run.sinkTagChain; catcher; catcher = catcher->chain)
			if (&catcher->tag == tag)
				return catching(run, *(Catch*)catcher);
		}
		retain();
		retain();
		retain();
		return run.sink->error(run, this, this, this);
	}

	const Any &Catch::getImplicitParameter(ImplicitParameter::ImplicitCode code)
	{
		switch (code)
		{
		case ImplicitParameter::WHO: return who;
		case ImplicitParameter::WHERE: return where_;
		case ImplicitParameter::WHAT: return what;
		case ImplicitParameter::SELF: return closure;
		}
		throw L"Illegal implicit parameter code";
	}

	const Step *ImplicitParameterShort::catching(Runner &run, Catch &catching) const
	{
		/* Construct binding cliche.
		 *
		 * Don't bother with preconstructing though it would be faster
		 * - generally, the programmer will use compiled implicit
		 * parameters; these are merged into the jumpers by the compiler.
		 * The uncompiled version is mainly used for error processing.
		 */

		const Constant *name = cliche->attributes[0];
		name->retain();
        const Constant *bindingAttribute[2] = {Empty::get(), name};
        const Cliche *bindingCliche = Empty::get()->clichefy(bindingAttribute, 2);

		// Get value

		const ImplicitParameter::ImplicitCode code = ((const ImplicitParameter::ImplicitClicheShort*)cliche)->code;
		const Any *value[2] = {run.where_, &catching.getImplicitParameter(code)};

		// Bind value

		value[0]->retain();
		value[1]->retain();
		new (run.allocate(sizeof(SinkWhereabout))) SinkWhereabout(run.where_);
		run.where_ = bindingCliche->node(value);
		bindingCliche->unduplicateReference();

		// Go

		return element[0];
	}

	const Step *ImplicitParameterTrailer::catching(Runner &run, Catch &catching) const
	{
		/* Construct binding cliche.
		 *
		 * Don't bother with preconstructing though it would be faster
		 * - generally, the programmer will use compiled implicit
		 * parameters; these are merged into the jumpers by the compiler.
		 * The uncompiled version is mainly used for error processing.
		 */

		const NodeConstantShort *name = cliche->attributes[1]->clichefy()->nodeConstant((const Constant*)element[1]);
		cliche->attributes[1]->retain();
		name->cliche->unduplicateReference();
		name->retain();
        const Constant *bindingAttribute[2] = {Empty::get(), name};
        const Cliche *bindingCliche = Empty::get()->clichefy(bindingAttribute, 2);

		// Get value

		const ImplicitParameter::ImplicitCode code = ((const ImplicitParameter::ImplicitClicheShort*)cliche)->code;
		const Any *value[2] = {run.where_, &catching.getImplicitParameter(code)};

		// Bind value

		value[0]->retain();
		value[1]->retain();
		new (run.allocate(sizeof(SinkWhereabout))) SinkWhereabout(run.where_);
		run.where_ = bindingCliche->node(value);
		bindingCliche->unduplicateReference();

		// Go

		return element[0];
	}

	const Step *OkConstant::catching(Runner &run, Catch &catching) const
	{
		const Any *thing = element[0];
		thing->retain();
		for (Sink *sink = run.sink; sink != &catching; sink = sink->kick(run));
		run.sink = catching.kick(run);
		return thing->passCounted(run);
	}

	const Step *Ok::catching(Runner &run, Catch &catching) const
	{
		const Any *where_ = run.where_;
		where_->retain();
		const Any *thing = element[0];
		thing->retain();
		for (Sink *sink = run.sink; sink != &catching; sink = sink->kick(run));
		return (run.sink = catching.kick(run))->tailStep(run, thing, where_);
	}

	const Step *OkTrailer::catching(Runner &run, Catch &catching) const
	{
		const Any *where_ = run.where_;
		where_->retain();
		const Any *thing = element[0];
		thing->retain();
		for (Sink *sink = run.sink; sink != &catching; sink = sink->kick(run));
		return (run.sink = catching.kick(run))->tailStep(run, thing, where_);
	}

	const NodeExpressShort *BuiltinClichePossibly::node(const Express *element) const
	{
        return new Possibly(*this, element);
	}

	const Any *BuiltinClichePossibly::node(const Constant *element) const
	{
        return new Possibly(*this, element);
	}

	const NodeExpressShort *BuiltinClicheTry::node(const Express *element) const
	{
        return new Try(*this, element);
	}

	const Any *BuiltinClicheTry::node(const Constant *element) const
	{
        return new Try(*this, element);
	}

	const Any *BuiltinClicheOkTrailer::node(const Any *const *element) const
	{
        return new OkTrailer(*this, element);
	}

	const Any *BuiltinClicheOkTrailer::node(const Constant *const *element) const
	{
		return node((const Any *const *)element);
	}

	const Any *BuiltinClichePossiblyTrailer::node(const Any *const *element) const
	{
        return new PossiblyTrailer(*this, element);
	}

	const Any *BuiltinClichePossiblyTrailer::node(const Constant *const *element) const
	{
		return node((const Any *const *)element);
	}

	const Any *BuiltinClicheTryTrailer::node(const Any *const *element) const
	{
        return new TryTrailer(*this, element);
	}

	const Any *BuiltinClicheTryTrailer::node(const Constant *const *element) const
	{
		return node((const Any *const *)element);
	}

	const Any *BuiltinClicheNeedTrailer::node(const Any *const *element) const
	{
        return new NeedTrailer(*this, element);
	}

	const Any *BuiltinClicheNeedTrailer::node(const Constant *const *element) const
	{
		return node((const Any *const *)element);
	}

	const Any *BuiltinClicheErrorTrailer::node(const Any *const *element) const
	{
        return new ErrorTrailer(*this, element);
	}

	const Any *BuiltinClicheErrorTrailer::node(const Constant *const *element) const
	{
		return node((const Any *const *)element);
	}

	const Step *Possibly::catching(Runner &run, Catch &catching) const
	{
		Sink *sink = run.sink;
		new (run.allocate(sizeof(SinkPossiblying))) SinkPossiblying(catching, sink);
		return element[0];
	}

	const Step *PossiblyTrailer::catching(Runner &run, Catch &catching) const
	{
		Sink *sink = run.sink;
		new (run.allocate(sizeof(SinkPossiblying))) SinkPossiblying(catching, sink);
		return element[0];
	}

	const Step *Try::catching(Runner &run, Catch &catching) const
	{
		Sink *sink = run.sink;
		new (run.allocate(sizeof(SinkTrying))) SinkTrying(catching, sink);
		return element[0];
	}

	const Step *TryTrailer::catching(Runner &run, Catch &catching) const
	{
		Sink *sink = run.sink;
		new (run.allocate(sizeof(SinkTrying))) SinkTrying(catching, sink);
		return element[0];
	}

	Sink *SinkPossiblying::kick(Runner &run)
	{
		catching.trial = stackTrial;
		return this + 1;
	}

	const Step *SinkPossiblying::pass(Runner &run, const Any *value)
	{
		catching.kickOff(run);
		return value->passCounted(run);
	}

	const Step *SinkPossiblying::tailStep(Runner &run, const Any *thing, const Any *where_)
	{
		return catching.kickOff(run)->tailStep(run, thing, where_);
	}

	void SinkPossiblying::refer(Runner &run, const Express &what)
	{
		new (run.allocate(sizeof(SinkTryReferringUncounted))) SinkTryReferringUncounted(run.where_, catching);
		run.calling.what = &catching.what;
		run.where_ = &catching.where_;
	}

	const Step *SinkTrying::error(Runner &run, const Any *error, const Express *what, const Any *who)
	{
		what->release();
		who->release();
		what = &catching.what;
		who = &catching.who;
		what->retain();
		who->retain();
		return catching.kickOff(run)->error(run, error, what, who);
	}

	const Step *SinkTrying::call(Runner &run, const Express &what, const Any *call)
	{
		run.calling.what = &catching.what;
		new (run.allocate(sizeof(SinkTryCalling))) SinkTryCalling(run.calling.who = run.where_, call);
		run.where_ = &catching.where_;
		return call->caller(run, *run.calling.who);
	}

	const Step *SinkTrying::call(Runner &run, const Express &what, const Any *call, const Any *who)
	{
		run.calling.what = &catching.what;
		new (run.allocate(sizeof(SinkTryCallingWho))) SinkTryCallingWho(run.where_, call, who);
		run.where_ = &catching.where_;
		return call->caller(run, *(run.calling.who = who));
	}

	const Step *SinkTrying::call(Runner &run, const Express &what, const Any &call)
	{
		call.retain();
		return this->call(run, what, &call);
	}

	const Step *SinkTrying::call(Runner &run, const Express &what, const Any &call, const Any *who)
	{
		call.retain();
		return this->call(run, what, &call, who);
	}

	const Step *SinkTrying::miss(Runner &run)
	{
		for (Sink *sink = run.sink->kick(run); sink != this; sink = sink->kick(run));
		catching.trial = stackTrial;
		return (run.sink = this + 1)->pass(run, Empty::singleton);
	}

	const Step *SinkTrying::callaround(Runner &run, const Express &what, const Any *call, const Any *who)
	{
		run.calling.what = &catching.what;
		new (run.allocate(sizeof(SinkTryCallingAround))) SinkTryCallingAround(run.where_, call, who);
		run.where_ = &catching.where_;
		return call->caller(run, *(run.calling.who = who));
	}

	const Step *SinkTrying::assignCall(Runner &run, const Express &what, const Any *call, const Any *assignValue)
	{
		run.calling.what = &catching.what;
		new (run.allocate(sizeof(SinkTryCalling))) SinkTryCalling(run.calling.who = run.where_, call);
		run.where_ = &catching.where_;
		return run.calling.who->calling(run, *call, assignValue);
	}

	const Step *SinkTrying::assignCall(Runner &run, const Express &what, const Any *call, const Any *who, const Any *assignValue)
	{
		run.calling.what = &catching.what;
		new (run.allocate(sizeof(SinkTryCallingWho))) SinkTryCallingWho(run.where_, call, who);
		run.where_ = &catching.where_;
		return (run.calling.who = who)->calling(run, *call, assignValue);
	}

	const Step *SinkTrying::assignCallaround(Runner &run, const Express &what, const Any *call, const Any *who, const Any *assignValue)
	{
		run.calling.what = &catching.what;
		new (run.allocate(sizeof(SinkTryCallingAround))) SinkTryCallingAround(run.where_, call, who);
		run.where_ = &catching.where_;
		return (run.calling.who = who)->calling(run, *call, assignValue);
	}

	Sink *SinkTryReferringUncounted::kick(Runner &run)
	{
		run.where_ = where_;
		return this + 1;
	}

	bool SinkTryReferringUncounted::needsResult()
	{
		return ((Sink&)this[1]).needsResult();
	}

	const Step *SinkTryReferringUncounted::pass(Runner &run, const Any *thing)
	{
		run.sink = kick(run);
		return thing->passCounted(run);
	}

	Pipe *SinkTryReferringUncounted::connectPipe(Runner &run)
	{
		return kick(run)->connectPipe(run);
	}

	const Step *SinkTryReferringUncounted::tailStep(Runner &run, const Any *thing)
	{
		const Any *where_ = run.where_;
		where_->retain();
		run.where_ = this->where_;
		return (run.sink = this + 1)->tailStep(run, thing, where_);
	}

	const Step *SinkTryReferringUncounted::miss(Runner &run)
	{
		return ((Sink &)this[1]).miss(run);
	}

	const Step *SinkTryReferringUncounted::error(Runner &run, const Any *error, const Express *what, const Any *who)
	{
		return (run.sink = kick(run))->error(run, error, what, who);
	}

	Sink *SinkTryCalling::kick(Runner &run)
	{
		run.where_ = where_;
		call->release();
		return this + 1;
	}

	const Step *SinkTryCalling::miss(Runner &run)
	{
		return ((Sink &)this[1]).miss(run);
	}

	const Step *SinkTryCalling::pass(Runner &run, const Any *value)
	{
		return (run.sink = kick(run))->pass(run, value);
	}

	const Step *SinkTryCalling::tailStep(Runner &run, const Any *thing, const Any *where_)
	{
		return (run.sink = kick(run))->tailStep(run, thing, where_);
	}

	const Step *SinkTryCalling::error(Runner &run, const Any *error, const Express *what, const Any *who)
	{
		return (run.sink = kick(run))->error(run, error, what, who);
	}

	Sink *SinkTryCallingAround::kick(Runner &run)
	{
		run.where_ = where_;
		call->release();
		who->release();
		return this + 1;
	}

	const Step *SinkTryCallingAround::miss(Runner &run)
	{
		return ((Sink &)this[1]).miss(run);
	}

	const Step *SinkTryCallingWho::called(Runner &run, const Constant &call)
	{
		const Any *where_ = this->where_;
		const Any *callWho = this->call->callWho(who);
        void* mem = static_cast<void*>(reinterpret_cast<char*>(this + 1) - sizeof(SinkTryCalling));
        run.sink = new (mem) SinkTryCalling(where_, callWho);
		return callWho->caller(run, *where_);
	}

	const Step *SinkTryCallingWho::called(Runner &run, const Integer &call)
	{
		const Any *where_ = this->where_;
		const Any *callWho = this->call->callWho(who);
        void* mem = static_cast<void*>(reinterpret_cast<char*>(this + 1) - sizeof(SinkTryCalling));
        run.sink = new (mem) SinkTryCalling(where_, callWho);
        return callWho->caller(run, *where_);
	}

	const Step *SinkTryCallingWho::called(Runner &run, const ListConstant &call)
	{
		const Any *where_ = this->where_;
		const Any *callWho = this->call->callWho(who);
        void* mem = static_cast<void*>(reinterpret_cast<char*>(this + 1) - sizeof(SinkTryCalling));
        run.sink = new (mem) SinkTryCalling(where_, callWho);
        return callWho->caller(run, *where_);
	}

	const Step *SinkTryCallingWho::called(Runner &run, const NodeConstant &call)
	{
		const Any *where_ = this->where_;
		const Any *callWho = this->call->callWho(who);
        void* mem = static_cast<void*>(reinterpret_cast<char*>(this + 1) - sizeof(SinkTryCalling));
        run.sink = new (mem) SinkTryCalling(where_, callWho);
        return callWho->caller(run, *where_);
	}

	const Step *SinkTryCallingWho::called(Runner &run, const Empty &call)
	{
		const Any *where_ = this->where_;
		const Any *callWho = this->call->callWho(who);
        void* mem = static_cast<void*>(reinterpret_cast<char*>(this + 1) - sizeof(SinkTryCalling));
        run.sink = new (mem) SinkTryCalling(where_, callWho);
        return callWho->caller(run, *where_);
	}

	const Step *SinkTryCallingWho::called(Runner &run, const ListExpress &call)
	{
		const Any *where_ = this->where_;
		const Any *callWho = this->call->callWho(who);
        void* mem = static_cast<void*>(reinterpret_cast<char*>(this + 1) - sizeof(SinkTryCalling));
        run.sink = new (mem) SinkTryCalling(where_, callWho);
        return callWho->caller(run, *where_);
	}

	const Step *SinkTryCallingWho::called(Runner &run, const NodeExpress &call)
	{
		const Any *where_ = this->where_;
		const Any *callWho = this->call->callWho(who);
        void* mem = static_cast<void*>(reinterpret_cast<char*>(this + 1) - sizeof(SinkTryCalling));
        run.sink = new (mem) SinkTryCalling(where_, callWho);
        return callWho->caller(run, *where_);
	}

	const Step *SinkTryCallingWho::called(Runner &run, const Any &call, const Any *assignValue)
	{
		const Any *where_ = this->where_;
		const Any *callWho = this->call->callWho(who);
        void* mem = static_cast<void*>(reinterpret_cast<char*>(this + 1) - sizeof(SinkTryCalling));
        run.sink = new (mem) SinkTryCalling(where_, callWho);
        return where_->calling(run, *callWho, assignValue);
	}

	const NodeExpressShort *BuiltinClicheNeed::node(const Express *element) const
	{
        return new Need(*this, element);
	}

	const Any *BuiltinClicheNeed::node(const Constant *element) const
	{
		return new Need(*this, element);
	}

	const Step *Need::catching(Runner &run, Catch &catching) const
	{
		new (run.allocate(sizeof(SinkNeeding))) SinkNeeding(catching);
		return element[0];
	}

	const Step *NeedTrailer::catching(Runner &run, Catch &catching) const
	{
		new (run.allocate(sizeof(SinkNeeding))) SinkNeeding(catching);
		return element[0];
	}

	const Step *SinkNeeding::pass(Runner &run, const Any *value)
	{
		run.sink = kick(run);
		return value->passCounted(run);
	}

	const Step *SinkNeeding::tailStep(Runner &run, const Any *thing, const Any *where_)
	{
		return (run.sink = kick(run))->tailStep(run, thing, where_);
	}

	const Step *SinkNeeding::miss(Runner &run)
	{
		Sink *trial = catching.trial = stackTrial;
		for (Sink *sink = run.sink->kick(run); sink != trial; sink = sink->kick(run));
		return (run.sink = trial)->pass(run, Empty::singleton);
	}

/*
	const Step *SinkNeeding::called(Runner &run, const Empty &call)
	{
		Sink *trial = catching.trial = stackTrial;
		for (Sink *sink = this + 1; sink != trial; sink = sink->kick(run));
		return (run.sink = trial)->pass(run, Empty::singleton);
	}
*/
    const Any *BuiltinClicheTag::node(const Any *const *elements) const
	{
        if (elements[0]->as_Constant())
            return new Tag(*this, elements);
		else
            return BuiltinPokerClicheTrailer::node(elements);
	}

	const Step *Tag::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhereabout))) SinkWhereabout(run.where_);
		run.where_->retain();
		element[1]->retain();
		const Any *legs[] = {run.where_, element[1]};
        run.where_ = new Tag((const BuiltinPokerClicheTrailer &)*cliche, legs);
		return element[0];
	}

	const Step *Tag::calling(Runner &run, const Constant &call) const
	{
		return element[0]->calling(run, call);
	}

	const Step *Tag::calling(Runner &run, const Integer &call) const
	{
		return element[0]->calling(run, call);
	}

	const Step *Tag::calling(Runner &run, const Empty &call) const
	{
		return element[0]->calling(run, call);
	}

	const Step *Tag::calling(Runner &run, const NodeConstant &call) const
	{
		return element[0]->calling(run, call);
	}

	const Step *Tag::calling(Runner &run, const ListConstant &call) const
	{
		return element[0]->calling(run, call);
	}

	const Step *Tag::calling(Runner &run, const NodeExpress &call) const
	{
		return element[0]->calling(run, call);
	}

	const Step *Tag::calling(Runner &run, const ListExpress &call) const
	{
		return element[0]->calling(run, call);
	}

	const Step *Tag::calling(Runner &run, const Any &call, const Any *assignValue) const
	{
		return element[0]->calling(run, call, assignValue);
	}

	const Express *Tag::findCatchTag() const
	{
		return element[0]->findCatchTag();
	}

	const Express *Tag::findCatchTag(const Constant &tag) const
	{
		if (&tag == this->tag)
			return element[0]->findCatchTag();
		else
			return element[0]->findCatchTag(tag);
	}

	const Express *Using::findCatchTag(const Constant &tag) const
	{
		return element[0]->findCatchTag(tag);
	}

	const Express *Building::findCatchTag(const Constant &tag) const
	{
		return element[0]->findCatchTag(tag);
	}
}
