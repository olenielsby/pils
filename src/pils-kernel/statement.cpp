/* This file is public domain */
#include "statement.h"
namespace PILS
{
	const Any *BuiltinClicheCall::node(const Constant *element) const
	{
		return element->callHere();
	}

	const Any *BuiltinClicheCallWho::node(const Any *const *element) const
	{
		return element[0]->callWho(element[1]);
	}

	const NodeExpressShort *BuiltinClicheCall::node(const Express *element) const
	{
		return element->callHere();
	}

	Sink *SinkContinue::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkContinue::pass(Runner &run, long dummy)
	{
		const Any *thing = &tail;
		run.sink = this + 1;
		return thing;
	}

	const Any *BuiltinClicheAssign::node(const Constant *element) const
	{
		return new
			(Heap::allocate(sizeof(StatementAssignConstant)))
			StatementAssignConstant(*this, element);
	}

	const NodeExpressShort *BuiltinClicheAssign::node(const Express *element) const
	{
		return new
			(Heap::allocate(sizeof(StatementAssignExpress)))
			StatementAssignExpress(*this, element);
	}

	const Any *BuiltinClicheAssignContinue::node(const Any *const *element) const
	{
		if (element[1]->as_Constant()) return new
			(Heap::allocate(sizeof(StatementAssignConstantContinue)))
			StatementAssignConstantContinue(*this, element);
		else return new
			(Heap::allocate(sizeof(StatementAssignExpressContinue)))
			StatementAssignExpressContinue(*this, element);
	}

	const CallWho *StatementAssignConstant::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoAssignConstant)))
			WhoAssignConstant(this, who);
	}

	const CallWho *StatementAssignExpress::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoAssignExpress)))
			WhoAssignExpress(this, who);
	}

	const CallWho *StatementAssignConstantContinue::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoAssignConstantContinue)))
			WhoAssignConstantContinue(this, who);
	}

	const CallWho *StatementAssignExpressContinue::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoAssignExpressContinue)))
			WhoAssignExpressContinue(this, who);
	}

	const Step *WhoAssignConstant::step_(Runner &run) const
	{
		const Any *value = ((StatementAssignConstant*)callAttribute())->element[0];
		value->addReference();
		return whoAttribute()->assign(run, value, *this);
	}


	const Step *WhoAssignExpress::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkAssign))) SinkAssign(*this);
		return ((StatementAssignExpress*)callAttribute())->element[0];
	}

	const Step *WhoAssignConstantContinue::step_(Runner &run) const
	{
		const StatementAssignConstantContinue &assignment = *(const StatementAssignConstantContinue*)callAttribute();
		run.sink->pushAssignTail(run, *assignment.element[0]);
		const Any *value = assignment.element[1];
		value->addReference();
		return whoAttribute()->assign(run, value, *this);
	}

	const Step *WhoAssignExpressContinue::step_(Runner &run) const
	{
		const StatementAssignConstantContinue &assignment = *(const StatementAssignConstantContinue*)callAttribute();
		run.sink->pushAssignTail(run, *assignment.element[0]);
		new (run.allocate(sizeof(SinkAssign))) SinkAssign(*this);
		return assignment.element[1];
	}

	Sink *SinkAssign::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkAssign::pass(Runner &run, const Any *assignValue)
	{
		const WhoAssign &what = this->what;
		run.sink = this + 1;
		return what.whoAttribute()->assign(run, assignValue, what);
	}

	const Step *Any::assign(Runner &run, const Any *assignValue, const WhoAssign &what) const
	{
		what.addReference();
		run.where_->addReference();
		return run.sink->error(run, assignValue, &what, run.where_);
	}

	const Step *Call::assign(Runner &run, const Any *assignValue, const WhoAssign &what) const
	{
		new (run.allocate(sizeof(SinkAssigningCall))) SinkAssigningCall(what, assignValue);
		return element[0];
	}

	const Step *Slot::assign(Runner &run, const Any *assignValue, const WhoAssign &what) const
	{
		run.calling.what = &what;
		return (run.calling.who = run.where_)->calling(run, *element[0], assignValue);
	}

	const Step *CallWho::assign(Runner &run, const Any *assignValue, const WhoAssign &what) const
	{
		new (run.allocate(sizeof(SinkAssigningArgument))) SinkAssigningArgument(what, assignValue);
		return callAttribute();
	}

	Sink *SinkAssigning::kick(Runner &run)
	{
		assignValue->releaseReference();
		return this + 1;
	}

	const Step *SinkAssigningCall::pass(Runner &run, const Any *thing)
	{
		const Any *assignValue = this->assignValue;
		const Express &what = this->what;
		run.sink = this + 1;
		return run.sink->assignCall(run, what, thing, assignValue);
	}

	Sink *SinkAssigningWho::kick(Runner &run)
	{
		assignValue->releaseReference();
		argument->releaseReference();
		return this + 1;
	}

	const Step *SinkAssigningArgument::pass(Runner &run, const Any *thing)
	{
		const WhoAssign &what = this->what;
		const Any *assignValue = this->assignValue;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkAssigningWho))) SinkAssigningWho(what, assignValue, thing);
		return ((const CallWho*)what.whoAttribute())->whoAttribute();
	}

	const Step *SinkAssigningWho::pass(Runner &run, const Any *who)
	{
		const Any *assignValue = this->assignValue;
		const Any *argument = this->argument;
		const Express &what = this->what;
		run.calling.what = &what;
		return (run.sink = this + 1)->assignCall(run, what, argument, who, assignValue);
	}

	const Step *SinkAssigningWho::pass(Runner &run, SinkTaggedNodeBuilding &nodeBuilding)
	{
		run.calling.what = &what;
		const Any *assignValue = this->assignValue;
		const Any *argument = this->argument;
		run.sink = this + 1;
		const Constant *attributeName = argument->as_Constant();
		if (attributeName)
		{
			if (attributeName == &Empty::singleton)
			{
				if (nodeBuilding.joker)
				{
					nodeBuilding.joker->releaseReference();
					attributeName->releaseReference();
				}
				nodeBuilding.joker = assignValue;
			}
			else
			{
				std::pair<std::map<const Constant*, const Any*>::iterator, bool> insertion
					= nodeBuilding.building.insert(std::pair<const Constant*, const Any*>(attributeName, assignValue));
				if (!insertion.second)
				{
					insertion.first->second->releaseReference();
					insertion.first->second = assignValue;
					attributeName->releaseReference();
				}
			}
			return assignValue->passUncounted(run);
		}
		run.calling.what->addReference();
		if (assignValue->as_Constant())
			assignValue = BuiltinClicheAssign::singleton.node((const Constant*)assignValue);
		else
			assignValue = BuiltinClicheAssign::singleton.node((const Express*)assignValue);
		argument = assignValue->callWho(argument);
		run.calling.who->addReference();
		return run.sink->error(run, argument, run.calling.what, run.calling.who);
	}

	const Step *SinkAssigningWho::pass(Runner &run, PassingMind *mind, const Express *what)
	{
		what->releaseReference();
		run.calling.what = &this->what;
		const Any *assignValue = this->assignValue;
		const Any *argument = this->argument;
		run.sink = this + 1;
		const Constant *key = argument->as_Constant();
		if (key)
		{
			const Any *old = mind->mindSet(key, assignValue);
			if (old) return old->passCounted(run);
			else return Empty::singleton.passUncounted(run);
		}
		run.calling.what->addReference();
		if (assignValue->as_Constant())
			assignValue = BuiltinClicheAssign::singleton.node((const Constant*)assignValue);
		else
			assignValue = BuiltinClicheAssign::singleton.node((const Express*)assignValue);
		argument = assignValue->callWho(argument);
		run.calling.who->addReference();
		return run.sink->error(run, argument, run.calling.what, run.calling.who);
	}

	void Sink::pushAssignTail(Runner &run, const Any &tail)
	{
		new (run.allocate(sizeof(SinkContinue))) SinkContinue(tail);
	}

	const Step *Bind::step_(Runner &run) const
	{
		size_t count = cliche->count - 1;
		const Any *const *end = (const Any *const *)(void*)run.sink;
		new	(run.allocate(sizeof(SinkBind) + count * sizeof(Any*))) SinkBind(*this, (const Any **)end);
		return element[count];
	}

	Sink *SinkBind::kick(Runner &run)
	{
		const Any *const *end = (const Any *const *)(this + 1) + what.cliche->count - 1;
		while (done < end) (*(done++))->releaseReference();
		return (Sink*)done;
	}

	const Step *SinkBind::pass(Runner &run, const Any *thing)
	{
		*--done = thing;
		const Any *next = what.element[done - (const Any *const *)(this + 1)];
		if (done == (const Any *const *)(this + 1))
		{
			const Cliche *cliche = what.cliche;
			//prepend old whereabout to values, trashing last word of the Sink.
			const Any **e = done - 1;
			const Any *where_ = run.where_;
			*e = where_;
			where_->addReference();
			run.sink = (Sink*)(e + cliche->count);
			run.pushWhere(cliche->node(e));
		}
		return next;
	}

	const CallWho *OperatorEval::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoEval))) const WhoEval(this, who);
	}

	const NodeConstantShort *BuiltinClicheEval::newNode(const HashedConstant *&link, const Integer *value) const
	{
		return new (Heap::allocate(sizeof(OperationEvalConstant))) OperationEvalConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheEval::newNode(const HashedConstant *&link, const Float *value) const
	{
		return new (Heap::allocate(sizeof(OperationEvalConstant))) OperationEvalConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheEval::newNode(const HashedConstant *&link, const PilsColor *value) const
	{
		return new (Heap::allocate(sizeof(OperationEvalConstant))) OperationEvalConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheEval::newNode(const HashedConstant *&link, const Timestamp *value) const
	{
		return new (Heap::allocate(sizeof(OperationEvalConstant))) OperationEvalConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheEval::newNode(const HashedConstant *&link, const Duration *value) const
	{
		return new (Heap::allocate(sizeof(OperationEvalConstant))) OperationEvalConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheEval::newNode(const HashedConstant *&link, const PilsDate *value) const
	{
		return new (Heap::allocate(sizeof(OperationEvalConstant))) OperationEvalConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheEval::newNode(const HashedConstant *&link, const PilsString *value) const
	{
		return new (Heap::allocate(sizeof(OperationEvalConstant))) OperationEvalConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheEval::newNode(const HashedConstant *&link, const Cliche *value) const
	{
		return new (Heap::allocate(sizeof(OperationEvalConstant))) OperationEvalConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheEval::newNode(const HashedConstant *&link, const ListConstant *value) const
	{
		return new (Heap::allocate(sizeof(OperationEvalConstant))) OperationEvalConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheEval::newNode(const HashedConstant *&link, const NodeConstant *value) const
	{
		return new (Heap::allocate(sizeof(OperationEvalConstant))) OperationEvalConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheEval::newNode(const HashedConstant *&link, const Special *value) const
	{
		return new (Heap::allocate(sizeof(OperationEvalConstant))) OperationEvalConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheEval::newNode(const HashedConstant *&link, const Listener *value) const
	{
		return new (Heap::allocate(sizeof(OperationEvalConstant))) OperationEvalConstant(link, *this, value);
	}

	const NodeExpressShort *BuiltinClicheEval::node(const Express *value) const
	{
		return new (Heap::allocate(sizeof(OperationEvalExpress))) OperationEvalExpress(*this, value);
	}

	const CallWho *OperationEvalConstant::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoEvalConstant))) const WhoEvalConstant(this, who);
	}

	const CallWho *OperationEvalExpress::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoEvalExpress))) const WhoEvalExpress(this, who);
	}

	const Step *WhoEval::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkEval))) SinkEval();
		return whoAttribute();
	}

	const Step *WhoEvalConstant::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhereaboutUncounted))) SinkWhereaboutUncounted(run.where_);
		new (run.allocate(sizeof(SinkEval))) SinkEval();
		new (run.allocate(sizeof(SinkWhereaboutUncounted))) SinkWhereaboutUncounted(((const NodeConstant*)callAttribute())->element[0]);
		return whoAttribute();
	}

	const Step *WhoEvalExpress::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkEvalOperand))) SinkEvalOperand(*whoAttribute());
		return ((const NodeExpress*)callAttribute())->element[0];
	}

	Sink *SinkEval::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkEval::pass(Runner &run, const Any *value)
	{
		return (run.sink = kick(run))->tailStep(run, value);
	}

	Sink *SinkEvalOperand::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkEvalOperand::pass(Runner &run, const Any *value)
	{
		const Any &who = this->who;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhereabout))) SinkWhereabout(run.where_);
		new (run.allocate(sizeof(SinkEval))) SinkEval();
		new (run.allocate(sizeof(SinkWhereaboutUncounted))) SinkWhereaboutUncounted(value);
		return &who;
	}

	const Step *WhoUntypedOperationConstant::step_(Runner &run) const
	{
		const UntypedOperationConstant &call = *(const UntypedOperationConstant*)callAttribute();
		const Any *operand = call.element[0];
		operand->addReference();
		return ((BuiltinClicheUntypedOperation*)call.cliche)->gotOperand(run, *this, operand);
	}

	const Step *WhoUntypedOperationConstant::assign(Runner &run, const Any *assignValue, const WhoAssign &what) const
	{
		const UntypedOperationConstant &call = *(const UntypedOperationConstant*)callAttribute();
		const Any *operand = call.element[0];
		operand->addReference();
		return ((BuiltinClicheUntypedOperation*)call.cliche)->gotOperand(run, what, operand, assignValue);
	}

	const Step *WhoUntypedOperationExpress::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkUntypedOperand))) SinkUntypedOperand(*this);
		return ((const UntypedOperationExpress*)callAttribute())->element[0];
	}

	const Step *WhoUntypedOperationExpress::assign(Runner &run, const Any *assignValue, const WhoAssign &what) const
	{
		new (run.allocate(sizeof(SinkUntypedOperandAssign))) SinkUntypedOperandAssign(what, assignValue);
		return ((const UntypedOperationExpress*)callAttribute())->element[0];
	}

	const Step *BuiltinClicheUntypedOperation::gotOperand(Runner &run, const WhoAssign &what, const Any *value, const Any *assignValue) const
	{
		const CallWho &whoOperation = (const CallWho&)*what.whoAttribute();
		const Any *argument = whoOperation.callAttribute()->as_NodeConstant();
		if (argument)
		{
			argument->addReference();
			value->unduplicateReference();
		}
		else
			argument = ((const ClicheShort*)this)->node(value);
		new (run.allocate(sizeof(SinkAssigningWho))) SinkAssigningWho(what, assignValue, argument);
		return whoOperation.whoAttribute();
	}

	Sink *SinkUntypedOperand::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkUntypedOperand::pass(Runner &run, const Any *value)
	{
		const WhoUntypedOperationExpress &what = this->what;
		run.sink = this + 1;
		return ((BuiltinClicheUntypedOperation*)((const UntypedOperationExpress*)what.callAttribute())->cliche)->gotOperand(run, what, value);
	}

	Sink *SinkUntypedOperandAssign::kick(Runner &run)
	{
		assignValue->releaseReference();
		return this + 1;
	}

	const Step *SinkUntypedOperandAssign::pass(Runner &run, const Any *value)
	{
		const WhoAssign &what = this->what;
		const Any *assignValue = this->assignValue;
		run.sink = this + 1;
		WhoUntypedOperationExpress *whoOperation = (WhoUntypedOperationExpress*)what.whoAttribute();
		const UntypedOperationExpress *operation = (const UntypedOperationExpress*) whoOperation->callAttribute();
		BuiltinClicheUntypedOperation *cliche = (BuiltinClicheUntypedOperation*)operation->cliche;
		return cliche->gotOperand(run, what, value, assignValue);
	}

	const NodeExpressShort *BuiltinClicheQuote::node(const Express *element) const
	{
		return new (Heap::allocate(sizeof(Quote))) Quote(*this, element);
	}

	const Any *BuiltinClicheQuote::node(const Constant *element) const
	{
		return new (Heap::allocate(sizeof(Quote))) Quote(*this, element);
	}

	const Step *Quote::step_(Runner &run) const
	{
		return element[0]->passUncounted(run);
	}

	const NodeConstantShort *BuiltinClicheUseline::newNode(const HashedConstant *&link, const Integer *value) const
	{
		return new (Heap::allocate(sizeof(UselineConstant))) UselineConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUseline::newNode(const HashedConstant *&link, const Float *value) const
	{
		return new (Heap::allocate(sizeof(UselineConstant))) UselineConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUseline::newNode(const HashedConstant *&link, const PilsColor *value) const
	{
		return new (Heap::allocate(sizeof(UselineConstant))) UselineConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUseline::newNode(const HashedConstant *&link, const Timestamp *value) const
	{
		return new (Heap::allocate(sizeof(UselineConstant))) UselineConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUseline::newNode(const HashedConstant *&link, const Duration *value) const
	{
		return new (Heap::allocate(sizeof(UselineConstant))) UselineConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUseline::newNode(const HashedConstant *&link, const PilsDate *value) const
	{
		return new (Heap::allocate(sizeof(UselineConstant))) UselineConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUseline::newNode(const HashedConstant *&link, const PilsString *value) const
	{
		return new (Heap::allocate(sizeof(UselineConstant))) UselineConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUseline::newNode(const HashedConstant *&link, const Cliche *value) const
	{
		return new (Heap::allocate(sizeof(UselineConstant))) UselineConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUseline::newNode(const HashedConstant *&link, const ListConstant *value) const
	{
		return new (Heap::allocate(sizeof(UselineConstant))) UselineConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUseline::newNode(const HashedConstant *&link, const NodeConstant *value) const
	{
		return new (Heap::allocate(sizeof(UselineConstant))) UselineConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUseline::newNode(const HashedConstant *&link, const Special *value) const
	{
		return new (Heap::allocate(sizeof(UselineConstant))) UselineConstant(link, *this, value);
	}

	const NodeExpressShort *BuiltinClicheUseline::node(const Express *value) const
	{
		return new (Heap::allocate(sizeof(UselineExpress))) UselineExpress(*this, value);
	}

	const NodeConstantShort *BuiltinClicheUseline::newNode(const HashedConstant *&link, const Listener *value) const
	{
		return
			new (Heap::allocate(sizeof(UselineConstant)))
			UselineConstant(link, *this, value);
	}

	const CallWho *UselineConstant::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoUselineConstant))) const WhoUselineConstant(this, who);
	}

	const CallWho *UselineExpress::callWho(const Any *who) const
	{
		if (element[0]->as_Ruleset())
			return new (Heap::allocate(sizeof(WhoUselineRuleset))) const WhoUselineRuleset(this, who);
		else return new (Heap::allocate(sizeof(WhoUselineExpress))) const WhoUselineExpress(this, who);
	}

	const Any *BuiltinClicheUse::node(const Any *const *element) const
	{
		if (element[1]->as_Ruleset())
			return new (Heap::allocate(sizeof(UseRuleset))) UseRuleset(*this, element);
		else return new (Heap::allocate(sizeof(Use))) Use(*this, element);
	}

	const Any *BuiltinClicheUsing::node(const Any *const *element) const
	{
		return new (Heap::allocate(sizeof(Using))) Using(*this, element);
	}

	const Any *BuiltinClicheThrough::node(const Any *const *element) const
	{
		return new (Heap::allocate(sizeof(Through))) Through(*this, element);
	}

	const Any *BuiltinClicheAround::node(const Any *const *element) const
	{
		return new (Heap::allocate(sizeof(Around))) Around(*this, element);
	}

	const Step *WhoUselineConstant::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkUse))) SinkUse(*whoAttribute());
		return ((const NodeConstant*)callAttribute())->element[0]->passUncounted(run);
	}

	const Step *WhoUselineExpress::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkUse))) SinkUse(*whoAttribute());
		return ((const NodeExpress*)callAttribute())->element[0];
	}

	const Step *Use::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkUse))) SinkUse(*element[0]);
		return element[1];
	}

	Sink *SinkUse::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkUse::pass(Runner &run, const ListConstant *value)
	{
		if (value != &Empty::singleton) return pass(run, (const Any*)value);
		const Any &statement = this->statement;
		run.sink = this + 1;
		return &statement;
	}

	const Step *SinkUse::pass(Runner &run, const Any *value)
	{
		const Any &statement = this->statement;
		run.sink = this + 1;
		run.where_->addReference();
		new (run.allocate(sizeof(SinkWhereabout))) SinkWhereabout(run.where_);
		run.where_ = new (Heap::allocate(sizeof(Using))) Using(run.where_, value);
		return &statement;
	}

	const Step *BuiltinClicheBut::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		if (value == &Empty::singleton)
			value->releaseReference();
		else
			new (run.allocate(sizeof(SinkBut))) SinkBut(value);
		return what.whoAttribute();
	}

	Sink *SinkBut::kick(Runner &run)
	{
		but->releaseReference();
		return this + 1;
	}

	const Step *SinkBut::pass(Runner &run, const Any *value)
	{
		Using *thing = new (Heap::allocate(sizeof(Using))) Using(value, but);
		return (run.sink = this + 1)->pass(run, thing);
	}

	const Step *BuiltinClicheThroughOperation::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		if (value == &Empty::singleton)
			value->releaseReference();
		else
			new (run.allocate(sizeof(SinkThrough))) SinkThrough(value);
		return what.whoAttribute();
	}

	const Step *SinkThrough::pass(Runner &run, const Any *value)
	{
		Through *thing = new (Heap::allocate(sizeof(Through))) Through(value, but);
		return (run.sink = this + 1)->pass(run, thing);
	}

	const Step *BuiltinClicheAroundOperation::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		new (run.allocate(sizeof(SinkAround))) SinkAround(value);
		return what.whoAttribute();
	}

	const Step *SinkAround::pass(Runner &run, const Any *value)
	{
		Around *thing = new (Heap::allocate(sizeof(Around))) Around(value, but);
		return (run.sink = this + 1)->pass(run, thing);
	}

	const Step *BuiltinClicheRepeat::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		new (run.allocate(sizeof(SinkRepeat))) SinkRepeat(value, what);
		return what.whoAttribute();
	}

	Sink *SinkRepeat::kick(Runner &run)
	{
		who->releaseReference();
		return this + 1;
	}

	const Step *SinkRepeat::pass(Runner &run, const Any *item)
	{
		const Any *who = this->who;
		const WhoUntypedOperation &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkRepeating))) SinkRepeating(item, who, what);
		run.calling.who = who;
		run.calling.what = &what;
		return item->caller(run, *who);
	}

	Sink *SinkRepeating::kick(Runner &run)
	{
		who->releaseReference();
		item->releaseReference();
		return this + 1;
	}

	const Step *SinkRepeating::pass(Runner &run, const Any *value)
	{
		item->releaseReference();
		item = value;
		run.calling.who = who;
		run.calling.what = &what;
		return value->caller(run, *who);
	}

	const Step *SinkRepeating::called(Runner &run, const Constant &call)
	{
		const Any *item = this->item;
		who->releaseReference();
		run.sink = this + 1;
		return item->passCounted(run);
	}

	const Step *SinkRepeating::called(Runner &run, const Integer &call)
	{
		const Any *item = this->item;
		who->releaseReference();
		run.sink = this + 1;
		return item->passCounted(run);
	}

	const Step *SinkRepeating::called(Runner &run, const Empty &call)
	{
		const Any *item = this->item;
		who->releaseReference();
		run.sink = this + 1;
		return item->passCounted(run);
	}

	const Step *SinkRepeating::called(Runner &run, const ListConstant &call)
	{
		const Any *item = this->item;
		who->releaseReference();
		run.sink = this + 1;
		return item->passCounted(run);
	}

	const Step *SinkRepeating::called(Runner &run, const NodeConstant &call)
	{
		const Any *item = this->item;
		who->releaseReference();
		run.sink = this + 1;
		return item->passCounted(run);
	}

	const Step *SinkRepeating::called(Runner &run, const ListExpress &call)
	{
		const Any *item = this->item;
		who->releaseReference();
		run.sink = this + 1;
		return item->passCounted(run);
	}

	const Step *SinkRepeating::called(Runner &run, const NodeExpress &call)
	{
		const Any *item = this->item;
		who->releaseReference();
		run.sink = this + 1;
		return item->passCounted(run);
	}

	const Step *BuiltinClicheAgain::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		new (run.allocate(sizeof(SinkAgain))) SinkAgain(value, what);
		return what.whoAttribute();
	}

	Sink *SinkAgain::kick(Runner &run)
	{
		if (old) old->releaseReference();
		if (antique) antique->releaseReference();
		who->releaseReference();
		return this + 1;
	}

	const Step *SinkAgain::miss(Runner &run)
	{
		return ((Sink *)(this + 1))->miss(run);
	}

	const Step *SinkAgain::pass(Runner &run, const Any *item)
	{
		run.calling.what = &what;
		run.calling.who = who;
		new (run.allocate(sizeof(MissAssignCall))) MissAssignCall((old ? *old : Empty::singleton), item);
		return miss(run);
	}

	const Step *SinkAgain::pass(Runner &run, const Constant *value)
	{
		if (old == value)
		{
			run.sink = kick(run);
			return value->passCounted(run);
		}
		if (antique == value)
			return pass(run, (const Any *)value); // reject - cycle detected
		if (old)
			old->releaseReference();
		old = value;
		if (--antiqueCountdown == 0)
		{
			antiqueCountdown = antiqueNumber;
			antiqueNumber *= 2;
			if (antique) antique->releaseReference();
			value->addReference();
			antique = value;
		}
		run.calling.who = who;
		run.calling.what = &what;
		return value->caller(run, *who);
	}

	const Step *SinkAgain::called(Runner &run, const Constant &call)
	{
		run.calling.what = &what;
		run.calling.who = who;
		new (run.allocate(sizeof(MissCall))) MissCall(call);
		return miss(run);
	}

	const Step *SinkAgain::called(Runner &run, const Integer &call)
	{
		return called (run, (const Constant &)call);
	}

	const Step *SinkAgain::called(Runner &run, const Empty &call)
	{
		return called (run, (const Constant &)call);
	}

	const Step *SinkAgain::called(Runner &run, const ListConstant &call)
	{
		return called (run, (const Constant &)call);
	}

	const Step *SinkAgain::called(Runner &run, const NodeConstant &call)
	{
		return called (run, (const Constant &)call);
	}

	const Step *BuiltinClicheTrial::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		new (run.allocate(sizeof(SinkTrial))) SinkTrial(value, what);
		return what.whoAttribute();
	}

	const Step *SinkTrial::pass(Runner &run, const Any *item)
	{
		const Any *who = this->who;
		const WhoUntypedOperation &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkTrialing))) SinkTrialing(item, who, what);
		run.calling.who = who;
		run.calling.what = &what;
		return item->caller(run, *who);
	}

	const Step *SinkTrialing::pass(Runner &run, const Any *item)
	{
		this->item->releaseReference();
		who->releaseReference();
		run.sink = this + 1;
		return item->passCounted(run);
	}

	const Step *SinkTrialing::tailStep(Runner &run, const Any *thing)
	{
		item->releaseReference();
		who->releaseReference();
		return (run.sink = this + 1)->tailStep(run, thing);
	}

	const Step *SinkTrialing::tailStep(Runner &run, const Any *thing, const Any *where_)
	{
		item->releaseReference();
		who->releaseReference();
		return (run.sink = this + 1)->tailStep(run, thing, where_);
	}

	const Any *BuiltinClicheIf::node(const Any *const *element) const
	{
		return new (Heap::allocate(sizeof(If))) If(*this, element);
	}

	const Any *BuiltinClicheIfElse::node(const Any *const *element) const
	{
		return new (Heap::allocate(sizeof(IfElse))) IfElse(*this, element);
	}

	const Step *If::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkIf))) SinkIf(*run.where_, *element[0]);
		return element[1];
	}

	const Step *IfElse::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkIf))) SinkIf(*run.where_, *element[0], *element[2]);
		return element[1];
	}

	const Step *SinkCondition::miss(Runner &run)
	{
		for (Sink *sink = run.sink->kick(run); sink != this; sink = sink->kick(run));
		return fail(run);
	}

	const Step *SinkCondition::pass(Runner &run, long value)
	{
		return succeed(run);
	}

	const Step *SinkCondition::pass(Runner &run, double value)
	{
		return succeed(run);
	}

	const Step *SinkCondition::pass(Runner &run, const Integer &value)
	{
		return succeed(run);
	}

	const Step *SinkCondition::pass(Runner &run, const Float &value)
	{
		return succeed(run);
	}

	const Step *SinkCondition::pass(Runner &run, const PilsString &value)
	{
		return succeed(run);
	}

	const Step *SinkCondition::pass(Runner &run, const Cliche &value)
	{
		return succeed(run);
	}

	const Step *SinkCondition::pass(Runner &run, const ListConstant &value)
	{
		return succeed(run);
	}

	const Step *SinkCondition::pass(Runner &run, const NodeConstantShort &value)
	{
		return succeed(run);
	}

	const Step *SinkCondition::pass(Runner &run, const NodeConstantLong &value)
	{
		return succeed(run);
	}

	const Step *SinkCondition::pass(Runner &run, const Special &value)
	{
		return succeed(run);
	}

	const Step *SinkCondition::pass(Runner &run, const ListExpress &value)
	{
		return succeed(run);
	}

	const Step *SinkCondition::pass(Runner &run, const NodeExpressShort &value)
	{
		return succeed(run);
	}

	const Step *SinkCondition::pass(Runner &run, const NodeExpressLong &value)
	{
		return succeed(run);
	}

	const Step *SinkCondition::pass(Runner &run, const Integer *value)
	{
		value->releaseReference();
		return succeed(run);
	}

	const Step *SinkCondition::pass(Runner &run, const Any *value)
	{
		value->releaseReference();
		return succeed(run);
	}

	Sink *SinkIf::kick(Runner &run)
	{
		if (&where_ != run.where_)
		{
			where_.addReference();
			run.where_->releaseReference();
			run.where_ = &where_;
		}
		return this + 1;
	}

	const Step *SinkIf::fail(Runner &run)
	{
		if (&where_ != run.where_)
		{
			where_.addReference();
			run.where_->releaseReference();
			run.where_ = &where_;
		}
		const Any &elseClause = this->elseClause;
		run.sink = this + 1;
		return &elseClause;
	}

	const Step *SinkIf::succeed(Runner &run)
	{
		const Any &clause = this->clause;
		const Any &where_ = this->where_;
		run.sink = this + 1;
		if (&where_ != run.where_)
		{
			where_.addReference();
			new (run.allocate(sizeof(SinkWhereabout))) SinkWhereabout(&where_);
		}
		return &clause;
	}

	const Step *BuiltinClicheTransform::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		new (run.allocate(sizeof(SinkWhoWorkaround))) SinkWhoWorkaround(what, value);
		return what.whoAttribute();
	}

	const Step *SinkWhoWorkaround::pass(Runner &run, const Any *value)
	{
		const Any *who = this->who;
		const WhoUntypedOperation &what = this->what;
		if ((run.sink = this + 1)->needsResult())
			new (run.allocate(sizeof(SinkTransformSaveBase))) SinkTransformSaveBase(what, who, value);
		else new (run.allocate(sizeof(SinkTransformForgetBase))) SinkTransformForgetBase(what, who, value);
		run.calling.what = &what;
		run.calling.who = who;
		return value->caller(run, *who);
	}

	Sink *SinkTransformSaveBase::kick(Runner &run)
	{
		who->releaseReference();
		original->releaseReference();
		return this + 1;
	}

	const Step *SinkTransformSaveBase::pass(Runner &run, const Any *value)
	{
		run.sink = kick(run);
		return value->passCounted(run);
	}

	const Step *SinkTransformSaveBase::pass(Runner &run, const Any &value)
	{
		value.addReference();
		return pass(run, &value);
	}

	const Step *SinkTransformSaveBase::tailStep(Runner &run, const Any *thing)
	{
		return (run.sink = kick(run))->tailStep(run, thing);
	}

	const Step *SinkTransformSaveBase::tailStep(Runner &run, const Any *thing, const Any *where_)
	{
		return (run.sink = kick(run))->tailStep(run, thing, where_);
	}

	const Step *SinkTransformSave::called(Runner &run, const Constant &call)
	{
		return pass(run, (const Any&)call);
	}

	const Step *SinkTransformSave::called(Runner &run, const Integer &call)
	{
		return pass(run, (const Any&)call);
	}

	const Step *SinkTransformSave::called(Runner &run, const Empty &call)
	{
		return pass(run, (const Any&)call);
	}

	const Step *SinkTransformSave::called(Runner &run, const ListConstant &call)
	{
		size_t count = call.count->value;
		return new (run.allocate(sizeof(SinkTransformSaveListElement)))
			SinkTransformSaveListElement(what, *who, call, (const Any* const *)call.element, (const Any *const *)call.element + count);
	}

	const Step *SinkTransformSave::called(Runner &run, const NodeConstant &call)
	{
		size_t count = call.cliche->count;
		return new (run.allocate(sizeof(SinkTransformSaveLeg)))
			SinkTransformSaveLeg(what, *who, call, (const Any* const *)call.element, (const Any *const *)call.element + count, &call.cliche->attributes[0]);
	}

	const Step *SinkTransformSave::called(Runner &run, const ListExpress &call)
	{
		size_t count = call.count->value;
		return new (run.allocate(sizeof(SinkTransformSaveListElement)))
			SinkTransformSaveListElement(what, *who, call, (const Any *const *)call.element, (const Any *const *)call.element + count);
	}

	const Step *SinkTransformSave::called(Runner &run, const NodeExpress &call)
	{
		size_t count = call.cliche->count;
		return new (run.allocate(sizeof(SinkTransformSaveLeg)))
			SinkTransformSaveLeg(what, *who, call, (const Any*const *)call.element, (const Any *const *)&call.element[count], call.cliche->attributes);
	}

	const Step *SinkTransformSave::called(Runner &run, const Any &call, const Any *assignValue)
	{
		assignValue->unduplicateReference();
		return assignValue->caller(run, *who);
	}

	Sink *SinkTransformSaveListElement::kick(Runner &run)
	{
		if (altered)
		{
			end += altered - element;
			const Integer *count;
			original->isList(element, count);
			end -= count->value;
			while (altered > end) (*--altered)->releaseReference();
			delete altered;
		}
		counting->releaseReference();
		return this + 1;
	}

	const Step *SinkTransformSaveElement::pass(Runner &run, const Any &value)
	{
		if (altered || &value != *element)
		{
			value.addReference();
			return pass(run, &value);
		}
		element++;
		return this;
	}

	const Step *SinkTransformSaveElement::pass(Runner &run, const Any *value)
	{
		if (!altered)
		{
			if (value == *element)
			{
				value->unduplicateReference();
				element++;
				return this;
			}
			else
			{
				const Cliche *cliche;
				const Integer *countInteger;
				size_t count;
				const Any *const *originalElement;
				if (original->isNode(originalElement, cliche))
					count = cliche->count;
				else if (original->isList(originalElement, countInteger))
					count = countInteger->value;
				else throw L"Bad workout state";
				for (altered = new const Any*[count]; originalElement < element; altered++)
					(*altered = *originalElement++)->addReference();
			}
		}
		*altered++ = value;
		element++;
		return this;
	}

	const Step *SinkTransformSaveListElement::step_(Runner &run) const
	{
		return ((SinkTransformSaveListElement *)this)->step_(run);
	}

	const Step *SinkTransformSaveListElement::step_(Runner &run)
	{
		const Any *value;
		if (element != end)
		{
			long c = counting->value;
			counting->releaseReference();
			counting = Integer::get(c + 1);
			run.calling.who = who;
			run.calling.what = &what;
			value = *element;
			value->addReference();
			return who->calling(run, *counting, value);
		}
		if (altered)
		{
			const Integer *count;
			original->isList(element, count);
			end = altered;
			altered -= count->value;
			for (const Any*const * p = altered;; p++)
			{
				if (p == end)
				{
					value = ListConstant::get((const Constant* const *)altered, count->value);
					break;
				}
				if (!(*p)->as_Constant())
				{
					value = new (Heap::allocate(sizeof(ListExpress) + (count->value - 1) * sizeof(Any*))) const ListExpress(altered, count->value);
					break;
				}
			}
			delete altered;
		}
		else
		{
			value = original;
			value->addReference();
		}
		run.sink = this + 1;
		return value->passCounted(run);
	}

	Sink *SinkTransformSaveLeg::kick(Runner &run)
	{
		if (altered)
		{
			end += altered - element;
			const Cliche *cliche;
			original->isNode(element, cliche);
			end -= cliche->count;
			while (altered > end) (*--altered)->releaseReference();
			delete altered;
		}
		return this + 1;
	}

	const Step *SinkTransformSaveLeg::step_(Runner &run) const
	{
		return ((SinkTransformSaveLeg *)this)->step_(run);
	}

	const Step *SinkTransformSaveLeg::step_(Runner &run)
	{
		const Any *value;
		if (element != end)
		{
			run.calling.who = who;
			run.calling.what = &what;
			value = *element;
			value->addReference();
			return who->calling(run, **((const Constant *const *)((char *)element + nameOffset)), value);
		}
		if (altered)
		{
			const Cliche *cliche;
			original->isNode(element, cliche);
			altered -= cliche->count;
			value = cliche->node(altered);
			delete altered;
		}
		else
		{
			value = original;
			value->addReference();
		}
		run.sink = this + 1;
		return value->passCounted(run);
	}

	const Step *SinkTransformForget::called(Runner &run, const Constant &call)
	{
		return pass(run, 0L);
	}

	const Step *SinkTransformForget::called(Runner &run, const Integer &call)
	{
		return pass(run, 0L);
	}

	const Step *SinkTransformForget::called(Runner &run, const Empty &call)
	{
		return pass(run, 0L);
	}

	const Step *SinkTransformForget::called(Runner &run, const Any &call, const Any *assignValue)
	{
		assignValue->unduplicateReference();
		return assignValue->caller(run, *who);
	}

	const Step *SinkTransformForget::called(Runner &run, const ListConstant &call)
	{
		size_t count = call.count->value;
		return new (run.allocate(sizeof(SinkTransformForgetListElement)))
			SinkTransformForgetListElement(what, *who, (const Any *const *)call.element, (const Any *const *)call.element + count);
	}

	const Step *SinkTransformForget::called(Runner &run, const NodeConstant &call)
	{
		size_t count = call.cliche->count;
		return new (run.allocate(sizeof(SinkTransformForgetLeg)))
			SinkTransformForgetLeg(what, *who, (const Any *const *)call.element, (const Any *const *)call.element + count, call.cliche->attributes);
	}

	const Step *SinkTransformForget::called(Runner &run, const ListExpress &call)
	{
		size_t count = call.count->value;
		return new (run.allocate(sizeof(SinkTransformForgetListElement)))
			SinkTransformForgetListElement(what, *who, call.element, call.element + count);
	}

	const Step *SinkTransformForget::called(Runner &run, const NodeExpress &call)
	{
		size_t count = call.cliche->count;
		return new (run.allocate(sizeof(SinkTransformForgetLeg)))
			SinkTransformForgetLeg(what, *who, call.element, call.element + count, call.cliche->attributes);
	}

	Sink *SinkTransformForgetBase::kick(Runner &run)
	{
		original->releaseReference();
		who->releaseReference();
		return this + 1;
	}

	const Step *SinkTransformForgetBase::pass(Runner &run, long dummy)
	{
		return (run.sink = kick(run))->pass(run, dummy);
	}

	const Step *SinkTransformForgetBase::tailStep(Runner &run, const Any *thing)
	{
		return (run.sink = kick(run))->tailStep(run, thing);
	}

	const Step *SinkTransformForgetBase::tailStep(Runner &run, const Any *thing, const Any *where_)
	{
		return (run.sink = kick(run))->tailStep(run, thing, where_);
	}

	Sink *SinkTransformForgetListElement::kick(Runner &run)
	{
		counting->releaseReference();
		return this + 1;
	}

	const Step *SinkTransformForgetElement::pass(Runner &run, long dummy)
	{
		element++;
		return this;
	}

	const Step *SinkTransformForgetListElement::step_(Runner &run) const
	{
		return ((SinkTransformForgetListElement *)this)->step_(run);
	}

	const Step *SinkTransformForgetListElement::step_(Runner &run)
	{
		if (element == end)
			return (run.sink = this + 1)->pass(run, 0L);
		else
		{
			long c = counting->value;
			counting->releaseReference();
			counting = Integer::get(c + 1);
			run.calling.who = who;
			run.calling.what = &what;
			const Any *value = *element;
			value->addReference();
			return who->calling(run, *counting, value);
		}
	}

	Sink *SinkTransformForgetLeg::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkTransformForgetLeg::step_(Runner &run) const
	{
		return ((SinkTransformForgetLeg *)this)->step_(run);
	}

	const Step *SinkTransformForgetLeg::step_(Runner &run)
	{
		if (element == end)
			return (run.sink = this + 1)->pass(run, 0L);
		else
		{
			run.calling.who = who;
			run.calling.what = &what;
			const Any *value = *element;
			value->addReference();
			return who->calling(run, **((const Constant *const *)((char *)element + nameOffset)), value);
		}
	}

	const NodeConstantShort *BuiltinClicheOr::newNode(const HashedConstant *&link, const Integer *value) const
	{
		return new (Heap::allocate(sizeof(OrConstant))) OrConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheOr::newNode(const HashedConstant *&link, const Float *value) const
	{
		return new (Heap::allocate(sizeof(OrConstant))) OrConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheOr::newNode(const HashedConstant *&link, const PilsColor *value) const
	{
		return new (Heap::allocate(sizeof(OrConstant))) OrConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheOr::newNode(const HashedConstant *&link, const Timestamp *value) const
	{
		return new (Heap::allocate(sizeof(OrConstant))) OrConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheOr::newNode(const HashedConstant *&link, const Duration *value) const
	{
		return new (Heap::allocate(sizeof(OrConstant))) OrConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheOr::newNode(const HashedConstant *&link, const PilsDate *value) const
	{
		return new (Heap::allocate(sizeof(OrConstant))) OrConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheOr::newNode(const HashedConstant *&link, const PilsString *value) const
	{
		return new (Heap::allocate(sizeof(OrConstant))) OrConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheOr::newNode(const HashedConstant *&link, const Cliche *value) const
	{
		return new (Heap::allocate(sizeof(OrConstant))) OrConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheOr::newNode(const HashedConstant *&link, const Special *value) const
	{
		return new (Heap::allocate(sizeof(OrConstant))) OrConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheOr::newNode(const HashedConstant *&link, const Listener *value) const
	{
		return new (Heap::allocate(sizeof(OrConstant))) OrConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheOr::newNode(const HashedConstant *&link, const ListConstant *value) const
	{
		return new (Heap::allocate(sizeof(OrConstant))) OrConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheOr::newNode(const HashedConstant *&link, const NodeConstant *value) const
	{
		return new (Heap::allocate(sizeof(OrConstant))) OrConstant(link, *this, value);
	}

	const NodeExpressShort *BuiltinClicheOr::node(const Express *value) const
	{
		return new (Heap::allocate(sizeof(OrExpress))) OrExpress(*this, value);
	}

	const CallWho *OrConstant::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoOrConstant))) WhoOrConstant(this, who);
	}

	const CallWho *OrExpress::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoOrExpress))) WhoOrExpress(this, who);
	}

	const NodeConstantShort *BuiltinClicheAnd::newNode(const HashedConstant *&link, const Integer *value) const
	{
		return new (Heap::allocate(sizeof(AndConstant))) AndConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnd::newNode(const HashedConstant *&link, const Float *value) const
	{
		return new (Heap::allocate(sizeof(AndConstant))) AndConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnd::newNode(const HashedConstant *&link, const PilsColor *value) const
	{
		return new (Heap::allocate(sizeof(AndConstant))) AndConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnd::newNode(const HashedConstant *&link, const Timestamp *value) const
	{
		return new (Heap::allocate(sizeof(AndConstant))) AndConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnd::newNode(const HashedConstant *&link, const Duration *value) const
	{
		return new (Heap::allocate(sizeof(AndConstant))) AndConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnd::newNode(const HashedConstant *&link, const PilsDate *value) const
	{
		return new (Heap::allocate(sizeof(AndConstant))) AndConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnd::newNode(const HashedConstant *&link, const PilsString *value) const
	{
		return new (Heap::allocate(sizeof(AndConstant))) AndConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnd::newNode(const HashedConstant *&link, const Cliche *value) const
	{
		return new (Heap::allocate(sizeof(AndConstant))) AndConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnd::newNode(const HashedConstant *&link, const Special *value) const
	{
		return new (Heap::allocate(sizeof(AndConstant))) AndConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnd::newNode(const HashedConstant *&link, const Listener *value) const
	{
		return new (Heap::allocate(sizeof(AndConstant))) AndConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnd::newNode(const HashedConstant *&link, const ListConstant *value) const
	{
		return new (Heap::allocate(sizeof(AndConstant))) AndConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnd::newNode(const HashedConstant *&link, const NodeConstant *value) const
	{
		return new (Heap::allocate(sizeof(AndConstant))) AndConstant(link, *this, value);
	}

	const NodeExpressShort *BuiltinClicheAnd::node(const Express *value) const
	{
		return new (Heap::allocate(sizeof(AndExpress))) AndExpress(*this, value);
	}

	const CallWho *AndConstant::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoAndConstant))) WhoAndConstant(this, who);
	}

	const CallWho *AndExpress::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoAndExpress))) WhoAndExpress(this, who);
	}

	const NodeConstantShort *BuiltinClicheAnyway::newNode(const HashedConstant *&link, const Integer *value) const
	{
		return new (Heap::allocate(sizeof(AnywayConstant))) AnywayConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnyway::newNode(const HashedConstant *&link, const Float *value) const
	{
		return new (Heap::allocate(sizeof(AnywayConstant))) AnywayConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnyway::newNode(const HashedConstant *&link, const PilsColor *value) const
	{
		return new (Heap::allocate(sizeof(AnywayConstant))) AnywayConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnyway::newNode(const HashedConstant *&link, const Timestamp *value) const
	{
		return new (Heap::allocate(sizeof(AnywayConstant))) AnywayConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnyway::newNode(const HashedConstant *&link, const Duration *value) const
	{
		return new (Heap::allocate(sizeof(AnywayConstant))) AnywayConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnyway::newNode(const HashedConstant *&link, const PilsDate *value) const
	{
		return new (Heap::allocate(sizeof(AnywayConstant))) AnywayConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnyway::newNode(const HashedConstant *&link, const PilsString *value) const
	{
		return new (Heap::allocate(sizeof(AnywayConstant))) AnywayConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnyway::newNode(const HashedConstant *&link, const Cliche *value) const
	{
		return new (Heap::allocate(sizeof(AnywayConstant))) AnywayConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnyway::newNode(const HashedConstant *&link, const Special *value) const
	{
		return new (Heap::allocate(sizeof(AnywayConstant))) AnywayConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnyway::newNode(const HashedConstant *&link, const Listener *value) const
	{
		return new (Heap::allocate(sizeof(AnywayConstant))) AnywayConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnyway::newNode(const HashedConstant *&link, const ListConstant *value) const
	{
		return new (Heap::allocate(sizeof(AnywayConstant))) AnywayConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheAnyway::newNode(const HashedConstant *&link, const NodeConstant *value) const
	{
		return new (Heap::allocate(sizeof(AnywayConstant))) AnywayConstant(link, *this, value);
	}

	const NodeExpressShort *BuiltinClicheAnyway::node(const Express *value) const
	{
		return new (Heap::allocate(sizeof(AnywayExpress))) AnywayExpress(*this, value);
	}

	const CallWho *AnywayConstant::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoAnywayConstant))) WhoAnywayConstant(this, who);
	}

	const CallWho *AnywayExpress::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoAnywayExpress))) WhoAnywayExpress(this, who);
	}

	const Step *WhoOrConstant::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoOrConstant))) SinkWhoOrConstant(*this);
		return whoAttribute();
	}

	const Step *WhoOrExpress::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoOrExpress))) SinkWhoOrExpress(*this);
		return whoAttribute();
	}

	const Step *WhoAndConstant::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoAndConstant))) SinkWhoAndConstant(*this);
		return whoAttribute();
	}

	const Step *WhoAndExpress::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoAndExpress))) SinkWhoAndExpress(*this);
		return whoAttribute();
	}

	const Step *WhoAnywayConstant::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoAnywayConstant))) SinkWhoAnywayConstant(*this);
		return whoAttribute();
	}

	const Step *WhoAnywayExpress::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoAnywayExpress))) SinkWhoAnywayExpress(*this);
		return whoAttribute();
	}

	Sink *SinkWhoOr::kick(Runner &run)
	{
		return this + 1;
	}

	Sink *SinkWhoAnd::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkWhoOr::pass(Runner &run, long value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoOr::pass(Runner &run, double value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoOr::pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count)
	{
		return (run.sink = this + 1)->pass(run, anchor, range, count);
	}

	const Step *SinkWhoOr::pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count)
	{
		return (run.sink = this + 1)->pass(run, anchor, range, count);
	}

	const Step *SinkWhoOr::pass(Runner &run, const Any *anchor, const Any *const *range, size_t count)
	{
		return (run.sink = this + 1)->pass(run, anchor, range, count);
	}

	const Step *SinkWhoOr::pass(Runner &run, const Any *value)
	{
		run.sink = this + 1;
		return value->passCounted(run);
	}

	const Step *SinkWhoOr::tailStep(Runner &run, const Any *thing, const Any *where_)
	{
		return (run.sink = this + 1)->tailStep(run, thing, where_);
	}

	const Step *SinkWhoOr::tailStep(Runner &run, const Any *thing)
	{
		return (run.sink = this + 1)->tailStep(run, thing);
	}

	bool SinkWhoOr::needsResult()
	{
		Sink *sink = this + 1;
		return sink->needsResult();
	}

	const Step *SinkWhoOrConstant::miss(Runner &run)
	{
		for (Sink *sink = run.sink->kick(run); sink != this; sink = sink->kick(run));
		const Constant *result = ((const OrConstant*)this->what.callAttribute())->element[0];
		run.sink = this + 1;
		return result->passUncounted(run);
	}

	const Step *SinkWhoOrConstant::error(Runner &run, const Any *error, const Express *what, const Any *who)
	{
		error->releaseReference();
		what->releaseReference();
		who->releaseReference();
		const Constant *result = ((const OrConstant*)this->what.callAttribute())->element[0];
		run.sink = this + 1;
		return result->passUncounted(run);
	}

	const Step *SinkWhoOrExpress::miss(Runner &run)
	{
		for (Sink *sink = run.sink->kick(run); sink != this; sink = sink->kick(run));
		const Express *result = (const Express *)((const OrExpress*)this->what.callAttribute())->element[0];
		run.sink = this + 1;
		return result;
	}

	const Step *SinkWhoOrExpress::error(Runner &run, const Any *error, const Express *what, const Any *who)
	{
		error->releaseReference();
		what->releaseReference();
		who->releaseReference();
		const Express *result = (const Express *)((const OrExpress*)this->what.callAttribute())->element[0];
		run.sink = this + 1;
		return result;
	}

	const Step *SinkWhoAnd::error(Runner &run, const Any *error, const Express *what, const Any *who)
	{
		return (run.sink = this + 1)->error(run, error, what, who);
	}

	const Step *SinkWhoAnd::miss(Runner &run)
	{
		Sink &next = this[1];
		return next.miss(run);
	}

	const Step *SinkWhoAndConstant::pass(Runner &run, long value)
	{
		const Constant &result = *((NodeConstantTiny*)what.callAttribute())->element[0];
		run.sink = this + 1;
		return result.passUncounted(run);
	}

	const Step *SinkWhoAndExpress::pass(Runner &run, long value)
	{
		const Any &result = *((NodeExpressTiny*)what.callAttribute())->element[0];
		run.sink = this + 1;
		return &result;
	}

	const Step *SinkWhoAnywayConstant::error(Runner &run, const Any *error, const Express *what, const Any *who)
	{
		error->releaseReference();
		what->releaseReference();
		who->releaseReference();
		const Constant *result = ((const AnywayConstant*)this->what.callAttribute())->element[0];
		run.sink = this + 1;
		return result->passUncounted(run);
	}

	const Step *SinkWhoAnywayConstant::miss(Runner &run)
	{
		for (Sink *sink = run.sink->kick(run); sink != this; sink = sink->kick(run));
		const Constant *result = ((const AnywayConstant*)this->what.callAttribute())->element[0];
		run.sink = this + 1;
		return result->passUncounted(run);
	}

	const Step *SinkWhoAnywayExpress::miss(Runner &run)
	{
		for (Sink *sink = run.sink->kick(run); sink != this; sink = sink->kick(run));
		const Express *result = (const Express *)((const AnywayExpress*)this->what.callAttribute())->element[0];
		run.sink = this + 1;
		return result;
	}

	const Step *SinkWhoAnywayExpress::error(Runner &run, const Any *error, const Express *what, const Any *who)
	{
		error->releaseReference();
		what->releaseReference();
		who->releaseReference();
		const Express *result = (const Express *)((const AnywayExpress*)this->what.callAttribute())->element[0];
		run.sink = this + 1;
		return result;
	}

	const Step *BuiltinClicheDistinct::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *filter) const
	{
		run.sink->connectPipe(run);
		new (run.allocate(sizeof(PipeDistinctFilter))) PipeDistinctFilter(what, filter);
		return what.whoAttribute();
	}

	const Step *BuiltinClicheGroups::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *filter) const
	{
		new (run.allocate(sizeof(PipeToGroups))) PipeToGroups(what, filter);
		return what.whoAttribute();
	}

	Sink *PipeToGroups::kick(Runner &run)
	{
		filter->releaseReference();
		for (std::multimap<const Constant *, const Any *>::iterator i = multimap.begin(); i != multimap.end(); i++)
		{
			i->first->releaseReference();
			i->second->releaseReference();
		}
		multimap.~multimap();
		return this + 1;
	}

	const Step *PipeToGroups::miss(Runner &run)
	{
		Sink &next = this[1];
		return next.miss(run);
	}

	void PipeToGroups::refer(Runner &run, const Express &what)
	{
		Sink &next = this[1];
		next.refer(run, what);
	}

	const Step *PipeToGroups::pass(Runner &run, const Any *who)
	{
		multimap.~multimap();
		const Any *call = BuiltinClicheGroups::singleton.node(filter);
		const Express &what = this->what;
		return (run.sink = this + 1)->call(run, what, call, who);
	}

	const Step *PipeToGroups::pipeItem(Runner &run, const Any *item)
	{
		new (run.allocate(sizeof(PipingToGroups))) PipingToGroups(*this, item);
		((Sink &)this[1]).refer(run, what);
		run.calling.who = filter;
		return item->caller(run, *filter);
	}

	const Step *PipeToGroups::pipeEnd(Runner &run)
	{
		filter->releaseReference();
		const Any *result;
		if (multimap.empty())
			(result = &Empty::singleton)->addReference();
		else
		{
			Builtin::name.groups.addReference();
			struct ReusableListBuilder
			{
			public:
				void add(const Any *element)
				{
					vector.push_back(element);
					constant = constant && element->as_Constant() != NULL;
				}
				const Any *build()
				{
					const Any *result;
					size_t count = vector.size();
					if (constant)
						result = ListConstant::get((const Constant *const *)(&vector[0]), count);
					else
						result = new (Heap::allocate(sizeof(ListExpress) + (count - 1) *  sizeof(const Any *))) ListExpress(&vector[0], count);
					vector.clear();
					constant = true;
					return result;
				}
				ReusableListBuilder() : constant(true) {}
			private:
				std::vector<const Any *> vector;
				bool constant;
			} list;
			NodeBuilder<const Any> build(&Builtin::name.groups);
			for (std::multimap<const Constant *, const Any *>::iterator i = multimap.begin(); i != multimap.end();)
			{
				const Constant *currentName = i->first;
				build.aim(currentName);
				list.add(i->second);
				for (i++; i != multimap.end() && i->first == currentName; i++)
				{
					currentName->unduplicateReference();
					list.add(i->second);
				}
				build.set(list.build());
			}
			result = build.build();
		}
		multimap.~multimap();
		run.sink = this + 1;
		return result->passCounted(run);
	}

	Sink *PipingToGroups::kick(Runner &run)
	{
		item->releaseReference();
		return this + 1;
	}

	const Step *PipingToGroups::pass(Runner &run, const Any *value)
	{
		run.calling.what = &pipe.what;
		run.calling.who = pipe.filter;
		const Any *assignValue = item;
		item = value;
		new (run.allocate(sizeof(MissAssignCall))) MissAssignCall(*item, assignValue);
		return pipe.miss(run);
	}

	const Step *PipingToGroups::pass(Runner &run, const Constant *key)
	{
		pipe.multimap.insert(std::pair<const Constant *, const Any *>(key, item));
		return (Pipesource *)(run.sink = this + 1);
	}

	const Step *PipingToGroups::pass(Runner &run, const NodeExpressLong *pair)
	{
		const Constant *name;
		const Any *value;
		if (!pair->isNameValuePair(name, value))
			return pass(run, (const Any*)pair);
		name->addReference();
		value->addReference();
		pair->releaseReference();
		item->releaseReference();
		pipe.multimap.insert(std::pair<const Constant *, const Any *>(name, value));
		return (Pipesource *)(run.sink = this + 1);
	}

	const Step *PipingToGroups::miss(Runner &run)
	{
		while (run.sink != this + 1)
			run.sink = run.sink->kick(run);
		return (Pipesource *)(run.sink);
	}

	const Step *BuiltinClicheFirsts::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *filter) const
	{
		new (run.allocate(sizeof(PipeToFirsts))) PipeToFirsts(what, filter);
		return what.whoAttribute();
	}

	Sink *PipeToFirsts::kick(Runner &run)
	{
		filter->releaseReference();
		for (std::map<const Constant *, const Any *>::iterator i = map.begin(); i != map.end(); i++)
		{
			i->first->releaseReference();
			i->second->releaseReference();
		}
		map.~map();
		return this + 1;
	}

	const Step *PipeToFirsts::miss(Runner &run)
	{
		Sink &next = this[1];
		return next.miss(run);
	}

	void PipeToFirsts::refer(Runner &run, const Express &what)
	{
		Sink &next = this[1];
		next.refer(run, what);
	}

	const Step *PipeToFirsts::pass(Runner &run, const Any *who)
	{
		map.~map();
		const Any *call = BuiltinClicheFirsts::singleton.node(filter);
		const Express &what = this->what;
		return (run.sink = this + 1)->call(run, what, call, who);
	}

	const Step *PipeToFirsts::pipeItem(Runner &run, const Any *item)
	{
		new (run.allocate(sizeof(PipingToFirsts))) PipingToFirsts(*this, item);
		((Sink &)this[1]).refer(run, what);
		run.calling.who = filter;
		return item->caller(run, *filter);
	}

	const Step *PipeToFirsts::pipeEnd(Runner &run)
	{
		filter->releaseReference();
		const Any *result;
		if (map.empty())
			(result = &Empty::singleton)->addReference();
		else
		{
			const Cliche *cliche = NULL;
			const Any *const *dummy;
			what.callAttribute()->isNode(dummy, cliche);
			const Constant *name = cliche->head;
			name->addReference();
			NodeBuilder<const Any> build(name);
			for (std::map<const Constant *, const Any *>::iterator i = map.begin(); i != map.end(); i++)
			{
				build.aim(i->first);
				build.set(i->second);
			}
			result = build.build();
		}
		map.~map();
		run.sink = this + 1;
		return result->passCounted(run);
	}

	Sink *PipingToFirsts::kick(Runner &run)
	{
		item->releaseReference();
		return this + 1;
	}

	const Step *PipingToFirsts::pass(Runner &run, const Any *value)
	{
		run.calling.what = &pipe.what;
		run.calling.who = pipe.filter;
		const Any *assignValue = item;
		item = value;
		new (run.allocate(sizeof(MissAssignCall))) MissAssignCall(*item, assignValue);
		return pipe.miss(run);
	}

	const Step *PipingToFirsts::pass(Runner &run, const Constant *key)
	{
		if (!pipe.map.insert(std::pair<const Constant *, const Any *>(key, item)).second)
		{
			key->unduplicateReference();
			item->releaseReference();
		}
		return (Pipesource *)(run.sink = this + 1);
	}

	const Step *PipingToFirsts::pass(Runner &run, const NodeExpressLong *pair)
	{
		const Constant *name;
		const Any *value;
		if (!pair->isNameValuePair(name, value))
			return pass(run, (const Any*)pair);
		item->releaseReference();
		item = value;
		item->addReference();
		name->addReference();
		pair->releaseReference();
		return pass(run, name);
	}

	const Step *PipingToFirsts::miss(Runner &run)
	{
		while (run.sink != this + 1)
			run.sink = run.sink->kick(run);
		return (Pipesource *)(run.sink);
	}

	const Step *BuiltinClicheLasts::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *filter) const
	{
		new (run.allocate(sizeof(PipeToLasts))) PipeToLasts(what, filter);
		return what.whoAttribute();
	}

	const Step *PipeToLasts::pipeItem(Runner &run, const Any *item)
	{
		new (run.allocate(sizeof(PipingToLasts))) PipingToLasts(*this, item);
		((Sink &)this[1]).refer(run, what);
		run.calling.who = filter;
		return item->caller(run, *filter);
	}

	const Step *PipingToLasts::pass(Runner &run, const Constant *key)
	{
		std::pair<std::map<const Constant *, const Any *>::iterator, bool> inserted = pipe.map.insert(std::pair<const Constant *, const Any *>(key, item));
		if (!inserted.second)
		{
			key->unduplicateReference();
			inserted.first->second->releaseReference();
			inserted.first->second = item;
		}
		return (Pipesource *)(run.sink = this + 1);
	}

	const Step *BuiltinClicheSingles::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *filter) const
	{
		new (run.allocate(sizeof(PipeToSingles))) PipeToSingles(what, filter);
		return what.whoAttribute();
	}

	const Step *PipeToSingles::pipeItem(Runner &run, const Any *item)
	{
		new (run.allocate(sizeof(PipingToSingles))) PipingToSingles(*this, item);
		((Sink &)this[1]).refer(run, what);
		run.calling.who = filter;
		return item->caller(run, *filter);
	}

	const Step *PipingToSingles::pass(Runner &run, const Constant *key)
	{
		if (pipe.map.insert(std::pair<const Constant *, const Any *>(key, item)).second)
			return (Pipesource *)(run.sink = this + 1);
		return PipingToFirsts::pass(run, (const Any *)key);
	}

	const Step *BuiltinClicheFolds::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *filter) const
	{
		new (run.allocate(sizeof(PipeToFolds))) PipeToFolds(what, filter);
		return what.whoAttribute();
	}

	const Step *PipeToFolds::pipeItem(Runner &run, const Any *item)
	{
		new (run.allocate(sizeof(PipingToFolds))) PipingToFolds(*this, item);
		((Sink &)this[1]).refer(run, what);
		run.calling.who = filter;
		return item->caller(run, *filter);
	}

	const Step *PipingToFolds::pass(Runner &run, const Constant *key)
	{
		std::pair<std::map<const Constant *, const Any *>::iterator, bool> insert = pipe.map.insert(std::pair<const Constant *, const Any *>(key, item));
		if (insert.second)
			return (Pipesource *)(run.sink = this + 1);
		key->unduplicateReference();
		const Any *value = this->item;
		PipeToFolds &pipe = (PipeToFolds &)this->pipe;
		run.sink = this + 1;
		const Any *oldValue = insert.first->second;
		oldValue->addReference();
		new (run.allocate(sizeof(FoldingToFolds))) FoldingToFolds(pipe, *key, oldValue);
		((Sink &)(&pipe)[1]).refer(run, pipe.what);
		return (run.calling.who = pipe.filter)->calling(run, *oldValue, value);
	}

	const Step *BuiltinClicheBug::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		const Language *language = value->as_Language();
		if (language) new (run.allocate(sizeof(SinkBug))) SinkBug(language);
		else value->releaseReference();
		return what.whoAttribute();
	}

	Sink *FoldingToFolds::kick(Runner &run)
	{
		oldValue->releaseReference();
		return this + 1;
	}

	const Step *FoldingToFolds::miss(Runner &run)
	{
		return ((Sink &)((& pipe)[1])).miss(run);
	}

	const Step *FoldingToFolds::pass(Runner &run, const Any *value)
	{
		std::map<const Constant *, const Any *>::iterator iterator = pipe.map.find(&key);
		iterator->second->releaseReference();
		iterator->second = value;
		oldValue->releaseReference();
		return (Pipesource *)(run.sink = this + 1);
	}

	Sink *SinkBug::kick(Runner &run)
	{
		language->releaseReference();
		return this + 1;
	}

	const Step *SinkBug::pass(Runner &run, const PilsString *value)
	{
		bug(run, *value);
		return (run.sink = kick(run))->pass(run, value);
	}

	const Any *BuiltinClicheComment::node(const Any *const *element) const
	{
		return new (Heap::allocate(sizeof(Comment))) Comment(*this, element);
	}

	const Step *Comment::step_(Runner &run) const
	{
		return element[0];
	}

	void Comment::compilePattern(Compiling &compiling) const
	{
		element[0]->compilePattern(compiling);
	}

	void Comment::compilePattern(Compiling &compiling, size_t offset) const
	{
		element[0]->compilePattern(compiling, offset);
	}

	const void *Comment::compilePatternIndex() const
	{
		return element[0]->compilePatternIndex();
	}

	void Comment::compileRulePattern(Compiling &compiling, const Rule &rule) const
	{
		element[0]->compileRulePattern(compiling, rule);
	}

	void Comment::compileAction(Compiling &compiling) const
	{
		element[0]->compileAction(compiling);
	}

	const Step *BuiltinClicheCombine::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		new (run.allocate(sizeof(SinkCombine))) SinkCombine(value);
		return what.whoAttribute();
	}

	const Any *BuiltinClicheCombined::node(const Any *const *element) const
	{
		return new (Heap::allocate(sizeof(Combined))) Combined(*this, element);
	}

	const Step *SinkCombine::pass(Runner &run, const Any *value)
	{
		const Any *thing = this->thing;
		return (run.sink = this + 1)->pass(run, new (Heap::allocate(sizeof(Combined))) Combined(BuiltinClicheCombined::singleton, thing, value));
	}

	const Step *Combined::calling(Runner &run, const Constant &call) const
	{
		new (run.allocate(sizeof(SinkCallingCombined<Constant>))) SinkCallingCombined<Constant>(call);
		new (run.allocate(sizeof(SinkCallingCombinedHead))) SinkCallingCombinedHead(*element[0], *run.calling.who, *run.calling.what);
		return element[1]->calling(run, call);
	}

	const Step *Combined::calling(Runner &run, const Integer &call) const
	{
		new (run.allocate(sizeof(SinkCallingCombined<Integer>))) SinkCallingCombined<Integer>(call);
		new (run.allocate(sizeof(SinkCallingCombinedHead))) SinkCallingCombinedHead(*element[0], *run.calling.who, *run.calling.what);
		return element[1]->calling(run, call);
	}

	const Step *Combined::calling(Runner &run, const Empty &call) const
	{
		new (run.allocate(sizeof(SinkCallingCombined<Empty>))) SinkCallingCombined<Empty>(call);
		new (run.allocate(sizeof(SinkCallingCombinedHead))) SinkCallingCombinedHead(*element[0], *run.calling.who, *run.calling.what);
		return element[1]->calling(run, call);
	}

	const Step *Combined::calling(Runner &run, const NodeConstant &call) const
	{
		new (run.allocate(sizeof(SinkCallingCombined<NodeConstant>))) SinkCallingCombined<NodeConstant>(call);
		new (run.allocate(sizeof(SinkCallingCombinedHead))) SinkCallingCombinedHead(*element[0], *run.calling.who, *run.calling.what);
		return element[1]->calling(run, call);
	}

	const Step *Combined::calling(Runner &run, const ListConstant &call) const
	{
		new (run.allocate(sizeof(SinkCallingCombined<ListConstant>))) SinkCallingCombined<ListConstant>(call);
		new (run.allocate(sizeof(SinkCallingCombinedHead))) SinkCallingCombinedHead(*element[0], *run.calling.who, *run.calling.what);
		return element[1]->calling(run, call);
	}

	const Step *Combined::calling(Runner &run, const NodeExpress &call) const
	{
		new (run.allocate(sizeof(SinkCallingCombined<NodeExpress>))) SinkCallingCombined<NodeExpress>(call);
		new (run.allocate(sizeof(SinkCallingCombinedHead))) SinkCallingCombinedHead(*element[0], *run.calling.who, *run.calling.what);
		return element[1]->calling(run, call);
	}

	const Step *Combined::calling(Runner &run, const ListExpress &call) const
	{
		new (run.allocate(sizeof(SinkCallingCombined<ListExpress>))) SinkCallingCombined<ListExpress>(call);
		new (run.allocate(sizeof(SinkCallingCombinedHead))) SinkCallingCombinedHead(*element[0], *run.calling.who, *run.calling.what);
		return element[1]->calling(run, call);
	}

	Sink *SinkCallingCombinedHead::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkCallingCombinedHead::called(Runner &run, const Constant &call)
	{
		run.calling.what = &what;
		run.calling.who = &who;
		return ((Sink*) (this + 1))->called(run, Empty::singleton);
	}

	const Step *SinkCallingCombinedHead::called(Runner &run, const Integer &call)
	{
		run.calling.what = &what;
		run.calling.who = &who;
		return ((Sink*) (this + 1))->called(run, Empty::singleton);
	}

	const Step *SinkCallingCombinedHead::called(Runner &run, const Empty &call)
	{
		run.calling.what = &what;
		run.calling.who = &who;
		return ((Sink*) (this + 1))->called(run, Empty::singleton);
	}

	const Step *SinkCallingCombinedHead::called(Runner &run, const NodeConstant &call)
	{
		run.calling.what = &what;
		run.calling.who = &who;
		return ((Sink*) (this + 1))->called(run, Empty::singleton);
	}

	const Step *SinkCallingCombinedHead::called(Runner &run, const ListConstant &call)
	{
		run.calling.what = &what;
		run.calling.who = &who;
		return ((Sink*) (this + 1))->called(run, Empty::singleton);
	}

	const Step *SinkCallingCombinedHead::called(Runner &run, const NodeExpress &call)
	{
		run.calling.what = &what;
		run.calling.who = &who;
		return ((Sink*) (this + 1))->called(run, Empty::singleton);
	}

	const Step *SinkCallingCombinedHead::called(Runner &run, const ListExpress &call)
	{
		run.calling.what = &what;
		run.calling.who = &who;
		return ((Sink*) (this + 1))->called(run, Empty::singleton);
	}

	const Step *SinkCallingCombinedHead::pass(Runner &run, const Any *value)
	{
		run.calling.what = &what;
		run.calling.who = &who;
		const Any &tail = this->tail;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkCallingCombinedTail))) SinkCallingCombinedTail(value);
		return value->caller(run, tail);
	}

	const Step *SinkCallingCombinedTail::called(Runner &run, const Constant &call)
	{
		thing->releaseReference();
		return ((Sink*) (this + 1))->called(run, Empty::singleton);
	}

	const Step *SinkCallingCombinedTail::called(Runner &run, const Integer &call)
	{
		thing->releaseReference();
		return ((Sink*) (this + 1))->called(run, Empty::singleton);
	}

	const Step *SinkCallingCombinedTail::called(Runner &run, const Empty &call)
	{
		thing->releaseReference();
		return ((Sink*) (this + 1))->called(run, Empty::singleton);
	}

	const Step *SinkCallingCombinedTail::called(Runner &run, const NodeConstant &call)
	{
		thing->releaseReference();
		return ((Sink*) (this + 1))->called(run, Empty::singleton);
	}

	const Step *SinkCallingCombinedTail::called(Runner &run, const ListConstant &call)
	{
		thing->releaseReference();
		return ((Sink*) (this + 1))->called(run, Empty::singleton);
	}

	const Step *SinkCallingCombinedTail::called(Runner &run, const NodeExpress &call)
	{
		thing->releaseReference();
		return ((Sink*) (this + 1))->called(run, Empty::singleton);
	}

	const Step *SinkCallingCombinedTail::called(Runner &run, const ListExpress &call)
	{
		thing->releaseReference();
		return ((Sink*) (this + 1))->called(run, Empty::singleton);
	}

	const ClicheShort *PredefinedNameCall::newCliche(const HashedConstant *&link, const Constant *a) const
	{
		return new (Heap::allocate(sizeof(SwitchClicheShort))) SwitchClicheShort(link, this, a);
	}

	const ClicheLong *PredefinedNameCall::newCliche(const HashedConstant *&link, const Constant *const *a, size_t c) const
	{
		void *chunk = Heap::allocate(sizeof(ClicheLong) + (c - 1) * sizeof(Constant*));
		if (a[0] == &Empty::singleton)
			return	new (chunk) const SwitchClicheTrailer(link, this, a, c);
		else return	new (chunk) const SwitchClicheLong(link, this, a, c);
	}

	const NodeConstantShort *SwitchClicheShort::newNode(const HashedConstant *&link, const Integer *value) const
	{
		return new (Heap::allocate(sizeof(SwitchConstantShort))) SwitchConstantShort(link, *this, value);
	}

	const NodeConstantShort *SwitchClicheShort::newNode(const HashedConstant *&link, const Float *value) const
	{
		return new (Heap::allocate(sizeof(SwitchConstantShort))) SwitchConstantShort(link, *this, value);
	}

	const NodeConstantShort *SwitchClicheShort::newNode(const HashedConstant *&link, const PilsColor *value) const
	{
		return new (Heap::allocate(sizeof(SwitchConstantShort))) SwitchConstantShort(link, *this, value);
	}

	const NodeConstantShort *SwitchClicheShort::newNode(const HashedConstant *&link, const Timestamp *value) const
	{
		return new (Heap::allocate(sizeof(SwitchConstantShort))) SwitchConstantShort(link, *this, value);
	}

	const NodeConstantShort *SwitchClicheShort::newNode(const HashedConstant *&link, const Duration *value) const
	{
		return new (Heap::allocate(sizeof(SwitchConstantShort))) SwitchConstantShort(link, *this, value);
	}

	const NodeConstantShort *SwitchClicheShort::newNode(const HashedConstant *&link, const PilsDate *value) const
	{
		return new (Heap::allocate(sizeof(SwitchConstantShort))) SwitchConstantShort(link, *this, value);
	}

	const NodeConstantShort *SwitchClicheShort::newNode(const HashedConstant *&link, const PilsString *value) const
	{
		return new (Heap::allocate(sizeof(SwitchConstantShort))) SwitchConstantShort(link, *this, value);
	}

	const NodeConstantShort *SwitchClicheShort::newNode(const HashedConstant *&link, const Cliche *value) const
	{
		return new (Heap::allocate(sizeof(SwitchConstantShort))) SwitchConstantShort(link, *this, value);
	}

	const NodeConstantShort *SwitchClicheShort::newNode(const HashedConstant *&link, const ListConstant *value) const
	{
		return new (Heap::allocate(sizeof(SwitchConstantShort))) SwitchConstantShort(link, *this, value);
	}

	const NodeConstantShort *SwitchClicheShort::newNode(const HashedConstant *&link, const NodeConstant *value) const
	{
		return new (Heap::allocate(sizeof(SwitchConstantShort))) SwitchConstantShort(link, *this, value);
	}

	const NodeConstantShort *SwitchClicheShort::newNode(const HashedConstant *&link, const Special *value) const
	{
		return new (Heap::allocate(sizeof(SwitchConstantShort))) SwitchConstantShort(link, *this, value);
	}

	const NodeConstantShort *SwitchClicheShort::newNode(const HashedConstant *&link, const Listener *value) const
	{
		return new (Heap::allocate(sizeof(SwitchConstantShort))) SwitchConstantShort(link, *this, value);
	}

	const NodeConstantLong *SwitchClicheLong::newNodeConstant(const HashedConstant *&link, const Constant *const *value) const
	{
		return
			new (Heap::allocate(sizeof(SwitchConstantLong) + (count - 1) * sizeof(Constant*)))
			const SwitchConstantLong(link, *this, value);
	}

	const NodeConstantLong *SwitchClicheTrailer::newNodeConstant(const HashedConstant *&link, const Constant *const *value) const
	{
		return
			new (Heap::allocate(sizeof(SwitchConstantTrailer) + (count - 1) * sizeof(Constant*)))
			const SwitchConstantTrailer(link, *this, value);
	}

	const Any *SwitchClicheLong::node(const Any *const *element) const
	{
		for(size_t i = 0; i < count; i++)
		{
			if(element[i]->as_Constant() == NULL)
			{
				return new
					(Heap::allocate(sizeof(SwitchExpressLong) + (count - 1) * sizeof(Constant*)))
					SwitchExpressLong(*this, element);
			}
		}
		return ClicheLong::node((const Constant *const *)(void *const *)element);
	}

	const Any *SwitchClicheTrailer::node(const Any *const *element) const
	{
		for(size_t i = 0; i < count; i++)
		{
			if(element[i]->as_Constant() == NULL)
			{
				return new
					(Heap::allocate(sizeof(SwitchExpressTrailer) + (count - 1) * sizeof(Constant*)))
					SwitchExpressTrailer(*this, element);
			}
		}
		return ClicheLong::node((const Constant *const *)(void *const *)element);
	}

	const CallWho *SwitchClicheShort::whoOperation(const NodeExpressShort *operation, const Any *who) const
	{
		return ((const PredefinedNameCall*)head)->callWho(operation, who);
	}

	const CallWho *SwitchConstantShort::callWho(const Any *who) const
	{
		return ((const PredefinedNameCall*)cliche->head)->callWho(this, who);
	}

	const CallWho *SwitchConstantLong::callWho(const Any *who) const
	{
		return ((const PredefinedNameCall*)cliche->head)->callWho(this, who);
	}

	const CallWho *SwitchConstantTrailer::callWho(const Any *who) const
	{
		return ((const PredefinedNameCall*)cliche->head)->callWho(this, who);
	}

	const CallWho *SwitchExpressLong::callWho(const Any *who) const
	{
		return ((const PredefinedNameCall*)cliche->head)->callWho(this, who);
	}

	const CallWho *SwitchExpressTrailer::callWho(const Any *who) const
	{
		return ((const PredefinedNameCall*)cliche->head)->callWho(this, who);
	}

	const CallWho *PredefinedNameCall::callWho(const NodeConstant *call, const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoSwitchCall))) WhoSwitchCall(call, who);
	}

	const CallWho *PredefinedNameCall::callWho(const NodeExpress *call, const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoSwitchCall))) WhoSwitchCall(call, who);
	}

	const CallWho *PredefinedNameTry::callWho(const NodeConstant *call, const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoSwitchTry))) WhoSwitchTry(call, who);
	}

	const CallWho *PredefinedNameTry::callWho(const NodeExpress *call, const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoSwitchTry))) WhoSwitchTry(call, who);
	}

	const Step *WhoSwitch::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkSwitch))) SinkSwitch(*this);
		return whoAttribute();
	}

	Sink *SinkSwitch::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkSwitch::pass(Runner &run, const Any *value)
	{
		const WhoSwitch &what = this->what;
		run.sink = this + 1;
		const Constant *key = value->as_Constant();
		if (key)
		{
			const Any *result;
			if (const NodeConstant *node = what.callAttribute()->as_NodeConstant())
				result = node->getAttribute(*key);
			else result = what.callAttribute()->as_NodeExpress()->getAttribute(*key);
			if (result)
			{
				key->unduplicateReference();
				return result;
			}
		}
		return what.miss(run, value);
	}

	const Step *WhoSwitchTry::miss(Runner &run, const Any *value) const
	{
		return value->passCounted(run);
	}

	const Step *WhoSwitchCall::miss(Runner &run, const Any *value) const
	{
		Sink *sink = run.sink;
		new (run.allocate(sizeof(SinkHold))) SinkHold(value);
		new (run.allocate(sizeof(MissCall))) MissCall(*value);
		return sink->miss(run);
	}

	const CallWho *PropertyDistinct::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoPropertyDistinct))) WhoPropertyDistinct(this, who);
	}

	const Step *WhoPropertyDistinct::step_(Runner &run) const
	{
		run.sink->connectPipe(run);
		new (run.allocate(sizeof(PipeDistinct))) PipeDistinct(*this);
		return whoAttribute();
	}

	const CallWho *PropertyCounts::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoPropertyCounts))) WhoPropertyCounts(this, who);
	}

	const Step *WhoPropertyCounts::step_(Runner &run) const
	{
		new (run.allocate(sizeof(PipeToCounts))) PipeToCounts(*this);
		return whoAttribute();
	}

	Sink *PipeDistinct::kick(Runner &run)
	{
		for (std::set<const Any *>::const_iterator i = set.begin(); i != set.end(); i++)
			(*i)->releaseReference();
		set.~set();
		return this + 1;
	}

	const Step *PipeDistinct::pass(Runner &run, const Any *value)
	{
		const WhoPropertyDistinct &what = this->what;
		return (run.sink = kick(run))->call(run, what, Builtin::name.distinct, value);
	}

	const Step *PipeDistinct::pipeBegin(Runner &run)
	{
		return ((Pipe*)(this + 1))->pipeBegin(run);
	}

	const Step *PipeDistinct::pipeItem(Runner &run, const Any *item)
	{
		if (this->set.insert(item).second)
		{
			item->addReference(); // memory might be recycled while piping
			return ((Pipe*)(this + 1))->pipeItem(run, item);
		}
		else
		{
			item->unduplicateReference();
			return (Pipesource *)run.sink;
		}
	}

	const Step *PipeDistinct::pipeEnd(Runner &run)
	{
		return ((Pipe*)(run.sink = kick(run)))->pipeEnd(run);
	}

	Sink *PipeDistinctFilter::kick(Runner &run)
	{
		for (std::set<const Constant *>::const_iterator i = set.begin(); i != set.end(); i++)
			(*i)->releaseReference();
		set.~set();
		filter->releaseReference();
		return this + 1;
	}

	const Step *PipeDistinctFilter::pass(Runner &run, const Any *value)
	{
		const WhoUntypedOperation &what = this->what;
		const Any *filter = this->filter;
		set.~set();
		return (run.sink = this + 1)->call(run, what, BuiltinClicheDistinct::singleton.node(filter), value);
	}

	const Step *PipeDistinctFilter::pipeBegin(Runner &run)
	{
		return ((Pipe*)(this + 1))->pipeBegin(run);
	}

	const Step *PipeDistinctFilter::pipeItem(Runner &run, const Any *item)
	{
		new (run.allocate(sizeof(PipingDistinctFilter))) PipingDistinctFilter(*this, item);
		((Sink &)this[1]).refer(run, what);
		run.calling.who = filter;
		return item->caller(run, *filter);
	}

	const Step *PipeDistinctFilter::pipeEnd(Runner &run)
	{
		return ((Pipe*)(run.sink = kick(run)))->pipeEnd(run);
	}

	Sink *PipingDistinctFilter::kick(Runner &run)
	{
		item->releaseReference();
		return this + 1;
	}


	const Step *PipingDistinctFilter::pass(Runner &run, const Any *value)
	{
		run.calling.what = &pipe.what;
		run.calling.who = pipe.filter;
		const Any *assignValue = item;
		item = value;
		new (run.allocate(sizeof(MissAssignCall))) MissAssignCall(*item, assignValue);
		return pipe.miss(run);
	}

	const Step *PipingDistinctFilter::pass(Runner &run, const Constant *key)
	{
		const Any *item = this->item;
		run.sink = this + 1;
		if (pipe.set.insert(key).second)
		{
			return ((Pipe*)(&pipe + 1))->pipeItem(run, item);
		}
		else
		{
			item->releaseReference();
			key->unduplicateReference();
			return (Pipesource *)(run.sink);
		}
	}

	const Step *PipingDistinctFilter::pass(Runner &run, const NodeExpressLong *pair)
	{
		const Constant *name;
		const Any *value;
		if (!pair->isNameValuePair(name, value))
			return pass(run, (const Any*)pair);
		item->releaseReference();
		item = value;
		item->addReference();
		name->addReference();
		pair->releaseReference();
		return pass(run, name);
	}

	const Step *PipingDistinctFilter::miss(Runner &run)
	{
		while (run.sink != this + 1)
			run.sink = run.sink->kick(run);
		return (Pipesource *)(run.sink);
	}

	Sink *PipeToCounts::kick(Runner &run)
	{
		for (std::map<const Constant *, double>::iterator i = map.begin(); i != map.end(); i++)
		{
			i->first->releaseReference();
		}
		map.~map();
		return this + 1;
	}

	const Step *PipeToCounts::pass(Runner &run, const Any * who)
	{
		map.~map();
		const WhoPropertyCounts &what = this->what;
		return (run.sink = this + 1)->call(run, what, *what.callAttribute(), who);
	}

	const Step *PipeToCounts::pipeBegin(Runner &run)
	{
		return (Pipesource *)run.sink;
	}

	const Step *PipeToCounts::pipeItem(Runner &run, const Any *item)
	{
		const Constant *key = item->as_Constant();
		if (key)
		{
			std::pair<std::map<const Constant *, double>::iterator, bool> insert = map.insert(std::pair<const Constant *, double>(key, 1));
			if (!insert.second)
			{
				insert.first->second += 1;
				key->releaseReference();
			}
			return (Pipesource *)run.sink;
		}
		else
		{
			run.calling.what = &what;
			run.calling.who = run.where_;
			new (run.allocate(sizeof(SinkHold))) SinkHold(item);
			new (run.allocate(sizeof(MissCall))) MissCall(*item);
			return ((Sink *)(this + 1))->miss(run);
		}
	}

	const Step *PipeToCounts::pipeEnd(Runner &run)
	{
		const Any *result;
		if (map.empty())
			(result = &Empty::singleton)->addReference();
		else
		{
			Builtin::name.counts.addReference();
			NodeBuilder<const Constant> build(&Builtin::name.counts);
			for (std::map<const Constant *, double>::const_iterator i = map.begin(); i != map.end(); i++)
			{
				build.aim(i->first);
				build.set(Number::get(i->second));
			}
			result = build.build();
		}
		map.~map();
		run.sink = this + 1;
		return result->passCounted(run);
	}

	const Any *BuiltinClicheWhen::specialOperation(Runner &run, const ReallySpecial &reallySpecial, const Any &argument) const
	{
		const Special *special = reinterpret_cast<const Special *>(&reallySpecial);
		if (special->isMultipleReferenced())
		{
			return NULL;
		}
		special->addReference();
		if (&argument != &Empty::singleton)
		{
			argument.addReference();
			if (special->when)
			{
				special->when = new (Heap::allocate(sizeof(Using))) Using(special->when, &argument);
			}
			else special->when = &argument;
		}
		return special;
	}
}
