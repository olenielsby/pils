/* This file is public domain */
#include "sink.h"

namespace PILS
{
    Runner::Runner(size_t stackSize)
    : oldTimer(true), threadStrapSticker(*this)
	{
		stackLimit = new char[stackSize];
		pessimistStackLimit = stackLimit + sizeof(void*) * 0x1000;
		stackOverflowSink = sink = new
			(stackLimit + stackSize - sizeof(SinkFinal))
			SinkFinal(stackLimit);
		sinkTagChain = nullptr;
		temporaryStrapSticker = &threadStrapSticker;
	}

	Runner::~Runner()
	{
		while(sink) sink = sink->kick(*this);
        release(where_);
	}

	void Runner::run(const Step *step_)
	{
		while (step_ != nullptr)
			step_ = step_->step_(*this);
	}

    void Runner::release(const Any *thing)
    {
        assert(thing);
        if(thing->refcount.release())
        {
            Mutex::Lock lock(Mutex::singleMutex);
            const_cast<Any*>(thing)->disposeRoot(*this);
        }
    }

    bool Runner::isMainThread() const
	{
		return true;
	}

	const Step *Runner::thread(const Any &what)
	{
		return &what;
	}

    const Constant *Runner::as_Thread() const
    {
        return nullptr;
    }

    void *Runner::allocate(size_t size)
    {
        char *aim = (char*)sink - size;
		if (aim < stackLimit)
			throw L"Stack overflow";
		sink = (Sink*)(void*)aim;
		return (void*)aim;
	}

	bool Runner::stackOverflow() const
	{
		return sink < (void*)pessimistStackLimit;
	}

	const Step *Runner::callingStackOverflow()
	{
		const Any *where_ = this->where_;
		where_->retain();
		where_->retain();
		const Express *what = this->calling.what;
		what->retain();
		while(sink != stackOverflowSink)
		{
			sink = sink->kick(*this);
		}
		Builtin::name.stackOverflow.retain();
		return pushWhere(where_)->error(*this, &Builtin::name.stackOverflow, what, where_);
	}

	Sink *Runner::pushWhere(const Any *where_)
	{
		return sink->pushWhere(*this, where_);
	}

	const Step *Runner::pass(const Any *thing)
	{
		return new (allocate(sizeof(SinkResultStep))) SinkResultStep(thing);
	}

	const Step *Sink::step_(Runner &run) const
	{
		throw "bad step_";
	}

	const Step *Miss::pass(Runner &run, const Any *thing)
	{
		throw "bad pass";
	}

	Sink *Sink::pushWhere(Runner &run, const Any *where_)
	{
		const Any *whence = run.where_;
		run.where_ = where_;
		return new (run.allocate(sizeof(SinkWhereabout))) SinkWhereabout(whence);
	}

	Sink *SinkWhereabout::pushWhere(Runner &run, const Any *where_)
	{
        run.release(run.where_);
		run.where_ = where_;
		return run.sink;
	}

	Sink *SinkWhereaboutUncounted::pushWhere(Runner &run, const Any *where_)
	{
		return (run.sink = kick(run))->pushWhere(run, where_);
	}

	Sink *SinkHoldTail::pushWhere(Runner &run, const Any *where_)
	{
        run.release(run.where_);
        run.where_ = where_;
		return run.sink;
	}

	const Step *Integer::step_(Runner &run) const
	{return run.sink->pass(run, (const Integer&)*this);}
	const Step *Float::step_(Runner &run) const
	{return run.sink->pass(run, (const Float&)*this);}
	const Step *PilsString::step_(Runner &run) const
	{return run.sink->pass(run, (const PilsString&)*this);}
	const Step *PilsColor::step_(Runner &run) const
	{return run.sink->pass(run, (const PilsColor&)*this);}
	const Step *Cliche::step_(Runner &run) const
	{return run.sink->pass(run, (const Cliche&)*this);}
	const Step *NodeConstantLong::step_(Runner &run) const
	{return run.sink->pass(run, (const NodeConstantLong&)*this);}
	const Step *NodeConstantShort::step_(Runner &run) const
	{return run.sink->pass(run, (const NodeConstantShort&)*this);}
	const Step *ListConstant::step_(Runner &run) const
	{return run.sink->pass(run, (const ListConstant&)*this);}

	const Step *NodeExpressShort::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkNodeShort)))
			SinkNodeShort((const ClicheShort&)(*cliche));
		return element[0];
	}

	const Step *NodeExpressLong::step_(Runner &run) const
	{
		const Any **done = (const Any**)run.sink;
		new (run.allocate(sizeof(SinkNodeLong) + cliche->count * sizeof(Any*)))
			SinkNodeLong(*this, done);
		return element[cliche->count - 1];
	}

	const Step *CallWho::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkArgument))) SinkArgument(*this);
		return element[0];
	}

	const Step *Sink::pass(Runner &run, const Integer &value)
	{
		value.retain();
		return pass(run, &value);
	}

	const Step *Sink::pass(Runner &run, const Float &value)
	{
		value.retain();
		return pass(run, &value);
	}

	const Step *Sink::pass(Runner &run, const PilsString &value)
	{
		value.retain();
		return pass(run, &value);
	}

	const Step *Sink::pass(Runner &run, const PilsColor &value)
	{
		value.retain();
		return pass(run, &value);
	}

	const Step *Sink::pass(Runner &run, const Cliche &value)
	{
		value.retain();
		return pass(run, &value);
	}

	const Step *Sink::pass(Runner &run, const ListConstant &value)
	{
		value.retain();
		return pass(run, &value);
	}

	const Step *Sink::pass(Runner &run, const ListExpress &value)
	{
		value.retain();
		return pass(run, &value);
	}

	const Step *Sink::pass(Runner &run, const NodeConstantLong &value)
	{
		value.retain();
		return pass(run, &value);
	}

	const Step *Sink::pass(Runner &run, const NodeConstantShort &value)
	{
		value.retain();
		return pass(run, &value);
	}

	const Step *Sink::pass(Runner &run, const NodeExpressLong &value)
	{
		value.retain();
		return pass(run, &value);
	}

	const Step *Sink::pass(Runner &run, const NodeExpressShort &value)
	{
		value.retain();
		return pass(run, &value);
	}

	const Step *Sink::pass(Runner &run, const Special &value)
	{
		value.retain();
		return pass(run, &value);
	}

	const Step *Sink::pass(Runner &run, const Integer *value)
	{
		return pass(run, (const Any*)value);
	}

	const Step *Sink::pass(Runner &run, const Float *value)
	{
		return pass(run, (const Any*)value);
	}

	const Step *Sink::pass(Runner &run, const PilsColor *value)
	{
		return pass(run, (const Any*)value);
	}

	const Step *Sink::pass(Runner &run, const Timestamp *value)
	{
		return pass(run, (const Any*)value);
	}

	const Step *Sink::pass(Runner &run, const Duration *value)
	{
		return pass(run, (const Any*)value);
	}

	const Step *Sink::pass(Runner &run, const PilsDate *value)
	{
		return pass(run, (const Any*)value);
	}

	const Step *Sink::pass(Runner &run, const PilsString *value)
	{
		return pass(run, (const Any*)value);
	}

	const Step *Sink::pass(Runner &run, const Cliche *value)
	{
		return pass(run, (const Any*)value);
	}

	const Step *Sink::pass(Runner &run, const ListConstant *value)
	{
		return pass(run, (const Any*)value);
	}

	const Step *Sink::pass(Runner &run, const ListExpress *value)
	{
		return pass(run, (const Any*)value);
	}

	const Step *Sink::pass(Runner &run, const NodeConstantLong *value)
	{
		return pass(run, (const Any*)value);
	}

	const Step *Sink::pass(Runner &run, const NodeConstantShort *value)
	{
		return pass(run, (const Any*)value);
	}

	const Step *Sink::pass(Runner &run, const NodeExpressLong *value)
	{
		return pass(run, (const Any*)value);
	}

	const Step *Sink::pass(Runner &run, const NodeExpressShort *value)
	{
		return pass(run, (const Any*)value);
	}

	const Step *Sink::pass(Runner &run, const Special *value)
	{
		return pass(run, (const Any*)value);
	}

	const Step *Sink::tailStep(Runner &run, const Any *thing, const Any *where_)
	{
		new (run.allocate(sizeof(SinkHoldTail))) SinkHoldTail(thing, run.where_);
		run.where_ = where_;
		return thing;
	}

	const Step *Sink::tailStep(Runner &run, const Any *thing)
	{
		new (run.allocate(sizeof(SinkHold))) SinkHold(thing);
		return thing;
	}

	bool Sink::needsResult()
	{
		return true;
	}

	const Step *SinkResultStep::step_(Runner &run) const
	{
		const Any *thing = this->thing;
		run.sink = (SinkResultStep *)this + 1;
		return thing->passCounted(run);
	}

	const Step *SinkConstant::pass(Runner &run, const Integer *value)
	{
		return pass(run, (const Constant*)value);
	}

	const Step *SinkConstant::pass(Runner &run, const Float *value)
	{
		return pass(run, (const Constant*)value);
	}

	const Step *SinkConstant::pass(Runner &run, const Timestamp *value)
	{
		return pass(run, (const Constant*)value);
	}

	const Step *SinkConstant::pass(Runner &run, const Duration *value)
	{
		return pass(run, (const Constant*)value);
	}

	const Step *SinkConstant::pass(Runner &run, const PilsDate *value)
	{
		return pass(run, (const Constant*)value);
	}

	const Step *SinkConstant::pass(Runner &run, const PilsString *value)
	{
		return pass(run, (const Constant*)value);
	}

	const Step *SinkConstant::pass(Runner &run, const Cliche *value)
	{
		return pass(run, (const Constant*)value);
	}

	const Step *SinkConstant::pass(Runner &run, const ListConstant *value)
	{
		return pass(run, (const Constant*)value);
	}

	const Step *SinkConstant::pass(Runner &run, const NodeConstantLong *value)
	{
		return pass(run, (const Constant*)value);
	}

	const Step *SinkConstant::pass(Runner &run, const NodeConstantShort *value)
	{
		return pass(run, (const Constant*)value);
	}

	const Step *SinkConstant::pass(Runner &run, const Special *value)
	{
		return pass(run, (const Constant*)value);
	}

	Sink *SinkFinal::kick(Runner &run)
	{
		free(block);
		return nullptr;
	}

	const Step *SinkFinal::pass(Runner &run, const Any *value)
	{
        run.release(run.where_);
        run.where_ = value;
		return &Runner::Done::singleton;
	}

	Runner::Done Runner::Done::singleton;
	const Step *Runner::Done::step_(Runner &run) const
	{
		return nullptr;
	}

	SinkConstantCall::SinkConstantCall(const CallWho &what)
		: what(what)
	{
	}

	const Step *SinkConstantCall::pass(Runner &run, const Any *value)
	{
		const Any* call = what.callAttribute();
		call->retain();
		return (run.sink = this + 1)->call(run, what, call, value);
	}

	const Step *SinkArgument::pass(Runner &run, const Any *value)
	{
		const Any *who = what.element[1];
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWho))) SinkWho(what, value);
		return who;
	}

	Sink *SinkArgument::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *WhoExpressOperation::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkOperand))) SinkOperand(*this);
		return ((const NodeExpressShort*)element[0])->element[0];
	}

	const Step *WhoExpressOperation::pass(Runner &run, long value)
	{
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(Integer::get(value));
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, double value)
	{
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(Number::get(value));
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const Integer &value)
	{
		value.retain();
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(&value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const Float &value)
	{
		value.retain();
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(&value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const PilsString &value)
	{
		value.retain();
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(&value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const Cliche &value)
	{
		value.retain();
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(&value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const ListConstant &value)
	{
		value.retain();
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(&value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const NodeConstantShort &value)
	{
		value.retain();
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(&value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const NodeConstantLong &value)
	{
		value.retain();
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(&value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const Special &value)
	{
		value.retain();
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(&value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const ListExpress &value)
	{
		value.retain();
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(&value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const NodeExpressShort &value)
	{
		value.retain();
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(&value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const NodeExpressLong &value)
	{
		value.retain();
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(&value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const Integer *value)
	{
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const Float *value)
	{
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const Timestamp *value)
	{
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const Duration *value)
	{
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const PilsDate *value)
	{
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const PilsString *value)
	{
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const Cliche *value)
	{
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const ListConstant *value)
	{
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const NodeConstantLong *value)
	{
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const NodeConstantShort *value)
	{
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const Special *value)
	{
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const ListExpress *value)
	{
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const NodeExpressLong *value)
	{
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	const Step *WhoExpressOperation::pass(Runner &run, const NodeExpressShort *value)
	{
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)element[0])->cliche)->node(value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(*this, argument);
		return element[1];
	}

	Sink *SinkOperand::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkOperand::pass(Runner &run, long value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, double value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const Integer &value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const Float &value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const PilsString &value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const Cliche &value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const ListConstant &value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const NodeConstantShort &value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const NodeConstantLong &value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const Special &value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const ListExpress &value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const NodeExpressShort &value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const NodeExpressLong &value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const Integer *value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const Float *value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const Timestamp *value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const Duration *value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const PilsDate *value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const PilsString *value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const Cliche *value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const ListConstant *value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const ListExpress *value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const NodeConstantLong *value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const NodeConstantShort *value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const Special *value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const NodeExpressLong *value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const NodeExpressShort *value)
	{
		WhoExpressOperation &what = (WhoExpressOperation&)this->what;
		run.sink = this + 1;
		return what.pass(run, value);
	}

	const Step *SinkOperand::pass(Runner &run, const Any *value)
	{
		const Any &who = *what.element[1];
		const Any *argument = ((const ClicheShort*)((const NodeExpressShort*)what.element[0])->cliche)->node(value);
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWho)))
			SinkWho(what, argument);
		return &who;
	}

	Sink *SinkWho::kick(Runner &run)
	{
        run.release(argument);
		return this + 1;
	}

	const Step *SinkWho::pass(Runner &run, const Any *value)
	{
		const CallWho &what = this->what;
		const Any *call = argument;
		return (run.sink = this + 1)->call(run, what, call, value);
	}

	Sink *SinkProperty::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkProperty::pass(Runner &run, const Any *who)
	{
		const CallWho &what = this->what;
		return (run.sink = this + 1)->call(run, what, *what.callAttribute(), who);
	}

	const Step *SinkProperty::pass(Runner &run, SinkTaggedNodeBuilding &nodeBuilding)
	{
		const CallWho &what = this->what;
		const Any *argument = what.callAttribute();
		argument->retain();
		run.sink = this + 1;
		return (new (run.allocate(sizeof(SinkWho))) SinkWho(what, argument))->pass(run, nodeBuilding);
	}

	Sink *SinkWhoOperationAny::kick(Runner &run)
	{
        run.release(operand);
		return this + 1;
	}

	const Step *SinkWhoOperationAny::pass(Runner &run, const Any *value)
	{
		const ClicheShort &cliche = *(const ClicheShort*)((const NodeExpressShort*)what.element[0])->cliche;
		const Any *argument = cliche.node(operand);
		const Express &what = this->what;
		return (run.sink = this + 1)->call(run, what, argument, value);
	}

	Sink *SinkWhoOperationRawInteger::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkWhoOperationRawInteger::pass(Runner &run, const Any *value)
	{
		const ClicheShort &cliche = *(const ClicheShort*)((const NodeExpressShort*)what.element[0])->cliche;
		const Any *argument = cliche.node(Integer::get(operand));
		const Express &what = this->what;
		return (run.sink = this + 1)->call(run, what, argument, value);
	}

	Sink *SinkWhoOperationRawFloat::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkWhoOperationRawFloat::pass(Runner &run, const Any *value)
	{
		const ClicheShort &cliche = *(const ClicheShort*)((const NodeExpressShort*)what.element[0])->cliche;
		const Any *argument = cliche.node(Number::get(operand));
		const Express &what = this->what;
		return (run.sink = this + 1)->call(run, what, argument, value);
	}

	SinkWhoOperationUncounted::SinkWhoOperationUncounted(const CallWho &what, const Any &operand)
		: what(what), operand(operand)
	{
	}

	Sink *SinkWhoOperationUncounted::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkWhoOperationUncounted::pass(Runner &run, const Any *value)
	{
		// This sink is being used for constant operations.
		// Tries to bypass reconstruction of operation node.
		const Any *argument = what.element[0];
		const Any *const *element;
		const ClicheShort *cliche;
		argument->isNode(element, (const Cliche*&)cliche);
		if (element[0] == &operand)
		{
			// Recycle operation node
			argument->retain();
		}
		else
		{
			// New operation node
			operand.retain();
			argument = cliche->node(&operand);
		}
		const Express &what = this->what;
		return (run.sink = this + 1)->call(run, what, argument, value);
	}

	const Step *SinkForget::pass(Runner &run, double value)
	{
		return pass(run, 0L);
	}

	const Step *SinkForget::pass(Runner &run, const Integer &value)
	{
		return pass(run, 0L);
	}
	const Step *SinkForget::pass(Runner &run, const Float &value)
	{
		return pass(run, 0L);
	}
	const Step *SinkForget::pass(Runner &run, const PilsString &value)
	{
		return pass(run, 0L);
	}
	const Step *SinkForget::pass(Runner &run, const Cliche &value)
	{
		return pass(run, 0L);
	}
	const Step *SinkForget::pass(Runner &run, const ListConstant &value)
	{
		return pass(run, 0L);
	}
	const Step *SinkForget::pass(Runner &run, const NodeConstantLong &value)
	{
		return pass(run, 0L);
	}
	const Step *SinkForget::pass(Runner &run, const NodeConstantShort &value)
	{
		return pass(run, 0L);
	}
	const Step *SinkForget::pass(Runner &run, const ListExpress &value)
	{
		return pass(run, 0L);
	}
	const Step *SinkForget::pass(Runner &run, const NodeExpressLong &value)
	{
		return pass(run, 0L);
	}
	const Step *SinkForget::pass(Runner &run, const NodeExpressShort &value)
	{
		return pass(run, 0L);
	}
	const Step *SinkForget::pass(Runner &run, const Any *value)
	{
        run.release(value);
		return pass(run, 0L);
	}

	bool SinkForget::needsResult()
	{
		return false;
	}

	Sink *SinkWhereabout::kick(Runner &run)
	{
        run.release(run.where_);
		run.where_ = where_;
		return this + 1;
	}

	const Step *SinkWhereabout::pass(Runner &run, const Any *thing)
	{
		run.sink = kick(run);
		return thing->passCounted(run);
	}

	const Step *SinkWhereabout::tailStep(Runner &run, const Any *thing, const Any *where_)
	{
		return (run.sink = kick(run))->tailStep(run, thing, where_);
	}

	const Step *SinkWhereabout::tailStep(Runner &run, const Any *thing)
	{
		const Any *where_ = run.where_;
		run.where_ = this->where_;
		return (run.sink = this + 1)->tailStep(run, thing, where_);
	}

	bool SinkWhereabout::needsResult()
	{
		Sink &next = this[1];
		return next.needsResult();
	}

	Sink *SinkWhereaboutUncounted::kick(Runner &run)
	{
		run.where_ = where_;
		return this + 1;
	}

	const Step *SinkWhereaboutUncounted::tailStep(Runner &run, const Any *thing)
	{
		const Any *where_ = run.where_;
		where_->retain();
		run.where_ = this->where_;
		return (run.sink = this + 1)->tailStep(run, thing, where_);
	}

	Sink *SinkHolding::kick(Runner &run)
	{
        run.release(thing);
		return this + 1;
	}

	bool SinkHolding::needsResult()
	{
		Sink &next = this[1];
		return next.needsResult();
	}

	const Step *SinkHoldCalling::pass(Runner &run, long value)
	{
        run.release(thing);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldCalling::pass(Runner &run, double value)
	{
        run.release(thing);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldCalling::pass(Runner &run, const Integer *value)
	{
        run.release(thing);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldCalling::pass(Runner &run, const Float *value)
	{
        run.release(thing);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldCalling::pass(Runner &run, const Timestamp *value)
	{
        run.release(thing);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldCalling::pass(Runner &run, const Duration *value)
	{
        run.release(thing);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldCalling::pass(Runner &run, const PilsDate *value)
	{
        run.release(thing);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldCalling::pass(Runner &run, const PilsString *value)
	{
        run.release(thing);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldCalling::pass(Runner &run, const Cliche *value)
	{
        run.release(thing);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldCalling::pass(Runner &run, const Special *value)
	{
        run.release(thing);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldCalling::pass(Runner &run, const ListConstant *value)
	{
        run.release(thing);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldCalling::pass(Runner &run, const ListExpress *value)
	{
        run.release(thing);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldCalling::pass(Runner &run, const NodeConstantLong *value)
	{
        run.release(thing);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldCalling::pass(Runner &run, const NodeConstantShort *value)
	{
        run.release(thing);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldCalling::pass(Runner &run, const NodeExpressLong *value)
	{
        run.release(thing);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldCalling::pass(Runner &run, const NodeExpressShort *value)
	{
        run.release(thing);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldCalling::pass(Runner &run, const Any *value)
	{
        run.release(thing);
		run.sink = this + 1;
		return value->passCounted(run);
	}

	const Step *SinkHoldCalling::pass(Runner &run, PassingMind *mind, const Express *what)
	{
        run.release(thing);
		return (run.sink = this + 1)->pass(run, mind, what);
	}

	const Step *SinkHoldCalling::tailStep(Runner &run, const Any *thing, const Any *where_)
	{
        run.release(this->thing);
		return (run.sink = this + 1)->tailStep(run, thing, where_);
	}

	const Step *SinkHoldCalling::tailStep(Runner &run, const Any *thing)
	{
        run.release(this->thing);
		return (run.sink = this + 1)->tailStep(run, thing);
	}

	const Step *SinkHoldCalling::error(Runner &run, const Any *error, const Express *what, const Any *who)
	{
		return (run.sink = kick(run))->error(run, error, what, who);
	}

	const Step *SinkHoldCalling::miss(Runner &run)
	{
		Sink &next = this[1];
		return next.miss(run);
	}

	Pipe *SinkHoldCalling::connectPipe(Runner &run)
	{
        run.release(this->thing);
		return (run.sink = this + 1)->connectPipe(run);
	}

	const Step *SinkHoldTail::pass(Runner &run, long value)
	{
        run.release(thing);
        run.release(run.where_);
		run.where_ = whence;
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldTail::pass(Runner &run, double value)
	{
        run.release(thing);
        run.release(run.where_);;
		run.where_ = whence;
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldTail::pass(Runner &run, const Integer *value)
	{
        run.release(thing);
        run.release(run.where_);;
		run.where_ = whence;
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldTail::pass(Runner &run, const Float *value)
	{
        run.release(thing);
        run.release(run.where_);;
		run.where_ = whence;
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldTail::pass(Runner &run, const Timestamp *value)
	{
        run.release(thing);
        run.release(run.where_);;
		run.where_ = whence;
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldTail::pass(Runner &run, const Duration *value)
	{
        run.release(thing);
        run.release(run.where_);;
		run.where_ = whence;
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldTail::pass(Runner &run, const PilsDate *value)
	{
        run.release(thing);
        run.release(run.where_);;
		run.where_ = whence;
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldTail::pass(Runner &run, const PilsString *value)
	{
        run.release(thing);
        run.release(run.where_);;
		run.where_ = whence;
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldTail::pass(Runner &run, const Cliche *value)
	{
        run.release(thing);
        run.release(run.where_);;
		run.where_ = whence;
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldTail::pass(Runner &run, const ListConstant *value)
	{
        run.release(thing);
        run.release(run.where_);
		run.where_ = whence;
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldTail::pass(Runner &run, const ListExpress *value)
	{
        run.release(thing);
        run.release(run.where_);
        run.where_ = whence;
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldTail::pass(Runner &run, const NodeConstantLong *value)
	{
        run.release(thing);
        run.release(run.where_);
        run.where_ = whence;
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldTail::pass(Runner &run, const NodeConstantShort *value)
	{
        run.release(thing);
        run.release(run.where_);
        run.where_ = whence;
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldTail::pass(Runner &run, const NodeExpressLong *value)
	{
        run.release(thing);
        run.release(run.where_);
        run.where_ = whence;
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldTail::pass(Runner &run, const NodeExpressShort *value)
	{
        run.release(thing);
        run.release(run.where_);
        run.where_ = whence;
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkHoldTail::pass(Runner &run, const Any *value)
	{
        run.release(thing);
        run.release(run.where_);
        run.where_ = whence;
		run.sink = this + 1;
		return value->passCounted(run);
	}

	Sink *SinkHoldTail::kick(Runner &run)
	{
        run.release(thing);
        run.release(run.where_);
        run.where_ = whence;
		return this + 1;
	}

	const Step *SinkHoldTail::tailStep(Runner &run, const Any *thing, const Any *where_)
	{
		//reuse sink
        run.release(run.where_);
        run.where_ = where_;
        run.release(this->thing);
        return this->thing = thing;
	}

	const Step *SinkHoldTail::tailStep(Runner &run, const Any *thing)
	{
		//reuse sink
        run.release(this->thing);
        return this->thing = thing;
	}

	bool SinkHoldTail::needsResult()
	{
		Sink &next = this[1];
		return next.needsResult();
	}

	const Step *Integer::passUncounted(Runner &run) const
	{
		return run.sink->pass(run, *this);
	}

	const Step *Float::passUncounted(Runner &run) const
	{
		return run.sink->pass(run, *this);
	}

	const Step *PilsString::passUncounted(Runner &run) const
	{
		return run.sink->pass(run, *this);
	}

	const Step *PilsColor::passUncounted(Runner &run) const
	{
		return run.sink->pass(run, *this);
	}

	const Step *Cliche::passUncounted(Runner &run) const
	{
		return run.sink->pass(run, *this);
	}

	const Step *NodeConstantShort::passUncounted(Runner &run) const
	{
		return run.sink->pass(run, *this);
	}

	const Step *NodeConstantLong::passUncounted(Runner &run) const
	{
		return run.sink->pass(run, *this);
	}

	const Step *ListConstant::passUncounted(Runner &run) const
	{
		return run.sink->pass(run, *this);
	}

	const Step *NodeExpressShort::passUncounted(Runner &run) const
	{
		return run.sink->pass(run, *this);
	}

	const Step *NodeExpressLong::passUncounted(Runner &run) const
	{
		return run.sink->pass(run, *this);
	}

	const Step *ListExpress::passUncounted(Runner &run) const
	{
		return run.sink->pass(run, *this);
	}

	const Step *Special::passUncounted(Runner &run) const
	{
		retain();
		return run.sink->pass(run, this);
	}

	const Step *Integer::passCounted(Runner &run) const
	{
		return run.sink->pass(run, this);
	}

	const Step *Float::passCounted(Runner &run) const
	{
		return run.sink->pass(run, this);
	}

	const Step *PilsString::passCounted(Runner &run) const
	{
		return run.sink->pass(run, this);
	}

	const Step *PilsColor::passCounted(Runner &run) const
	{
		return run.sink->pass(run, this);
	}

	const Step *Cliche::passCounted(Runner &run) const
	{
		return run.sink->pass(run, this);
	}

	const Step *NodeConstantShort::passCounted(Runner &run) const
	{
		return run.sink->pass(run, this);
	}

	const Step *NodeConstantLong::passCounted(Runner &run) const
	{
		return run.sink->pass(run, this);
	}

	const Step *ListConstant::passCounted(Runner &run) const
	{
		return run.sink->pass(run, this);
	}

	const Step *NodeExpressShort::passCounted(Runner &run) const
	{
		return run.sink->pass(run, this);
	}

	const Step *NodeExpressLong::passCounted(Runner &run) const
	{
		return run.sink->pass(run, this);
	}

	const Step *ListExpress::passCounted(Runner &run) const
	{
		return run.sink->pass(run, this);
	}

	const Step *Special::passCounted(Runner &run) const
	{
		return run.sink->pass(run, this);
	}

	Sink *SinkNodeShort::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkNodeShort::pass(Runner &run, const Any *thing)
	{
		thing = cliche.node(thing);
		run.sink = this + 1;
		return thing->passCounted(run);
	}

	Sink *SinkNodeLong::kick(Runner &run)
	{
		const Any *const *end = (const Any *const*)(this + 1) + node.cliche->count;
		for (const Any *const* finger = done; finger < end; finger++)
            run.release(*finger);
		return (Sink*)end;
	}

	const Step *SinkNodeLong::pass(Runner &run, const Any *thing)
	{
		*--done = thing;
		if (done > (const Any**)(this + 1))
			return node.element[done - (const Any**)(this + 1) - 1];
		thing = node.cliche->node(done);
		run.sink = (Sink*)(done + node.cliche->count);
		return thing->passCounted(run);
	}

	const Step *Special::step_(Runner &run) const
	{
		retain();
		return run.sink->pass(run, this);
	}

	const Step *MissSpecial::called(Runner &run, const Constant &call)
	{
		return miss(run);
	}

	const Step *MissSpecial::called(Runner &run, const Integer &call)
	{
		return miss(run);
	}

	const Step *MissSpecial::called(Runner &run, const ListConstant &call)
	{
		return miss(run);
	}

	const Step *MissSpecial::called(Runner &run, const NodeConstant &call)
	{
		return miss(run);
	}

	const Step *MissSpecial::called(Runner &run, const Empty &call)
	{
		return miss(run);
	}

	const Step *MissSpecial::called(Runner &run, const ListExpress &call)
	{
		return miss(run);
	}

	const Step *MissSpecial::called(Runner &run, const NodeExpress &call)
	{
		return miss(run);
	}

	const Step *MissSpecial::called(Runner &run, const Any &call, const Any *assignValue)
	{
        run.release(assignValue);
		return miss(run);
	}

	const Step *MissSpecial::missing(Runner &run, Sink *sink)
	{
		const Any *errorData = this->errorData();
		const Any *who = run.calling.who;
		who->retain();
		const Express *what = run.calling.what;
		what->retain();
		for (Sink *s = this; s != sink; s = s->kick(run));
		return (run.sink = sink)->error(run, errorData, what, who);
	}

    PassingMind::~PassingMind()
	{
        for (auto& [k, v] : map) {
            run.release(k);
            run.release(v);
        }
	}

    const Any *PassingMind::get(const Constant &key) const
	{
        auto found = map.find(&key);
        if (found != map.end())
		{
			const Any *value = found->second;
			value->retain();
			return value;
		}
        else return nullptr;
	}

    const Any *PassingMind::set(const Constant *key, const Any *value)
	{
        auto [it, inserted] = map.emplace(key, value);
        if (!inserted)
        {
            key->unduplicateReference();
            const Any *old = it->second;
            it->second = value;
            return old;
        }
        else return nullptr;
	}

    template <> const Any *NodeBuilder<const Constant>::build()
    {
        size_t count = this->count();
        const Any *node;
        switch (count)
        {
        case 0:
            return nullptr;
        case 1:
            if (joker)
            {
                const ClicheTiny *cliche = head->clichefy();
                node = cliche->ClicheShort::node(joker);
                cliche->unduplicateReference();
            }
            else
            {
                map::iterator run = mapping.begin();
                const ClicheShort *cliche = head->clichefy(run->first);
                node = cliche->node(run->second);
                cliche->unduplicateReference();
            }
            break;
        default:
        {
            const Constant** attributes = new const Constant*[count];
            const Constant** values = new const Constant*[count];
            const Constant** a = attributes;
            const Constant** v = values;
            if (joker)
            {
                *a++ = &Empty::singleton;
                *v++ = joker;
            }
            for (map::iterator run = mapping.begin(); run != mapping.end(); run++)
            {
                *a++ = run->first;
                *v++ = (const Constant*)run->second;
            }
            const Cliche *cliche = head->clichefy(attributes, count);
            delete[] attributes;
            node = cliche->node(values);
            delete[] values;
            cliche->unduplicateReference();
        }
        }
        alive = false;
        return node;
    }

    template <> const Any *NodeBuilder<const Any>::build()
    {
        size_t count = this->count();
        const Any *node;
        switch (count)
        {
        case 0:
            return nullptr;
        case 1:
            if (joker)
            {
                const ClicheTiny *cliche = head->clichefy();
                node = cliche->ClicheShort::node(joker);
                run.release(cliche);
            }
            else
            {
                map::iterator r = mapping.begin();
                const ClicheShort *cliche = head->clichefy(r->first);
                node = cliche->node(r->second);
                run.release(cliche);
            }
            break;
        default:
            {
                const Constant** attributes = new const Constant*[count];
                const Any** values = new const Any*[count];
                const Constant** a = attributes;
                const Any** v = values;
                if (joker)
                {
                    *a++ = &Empty::singleton;
                    *v++ = joker;
                }
                for (map::iterator r = mapping.begin(); r != mapping.end(); r++)
                {
                    *a++ = r->first;
                    *v++ = r->second;
                }
                const Cliche *cliche = head->clichefy(attributes, count);
                delete[] attributes;
                node = cliche->node(values);
                delete[] values;
                run.release(cliche);
            }
        }
        alive = false;
        return node;
    }
}
