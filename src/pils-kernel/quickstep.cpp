/* This file is public domain */
#include "quickstep.h"
namespace PILS
{
	const QuickCalling *QuickCalling::quickCalling(Runner &run, const Any &call, const Any &assignValue, const void *key) const
	{
		throw L"Bad rule compilation - assignment not expected";
	}

	const QuickCalling *QuickBeginRule::quickCalling(Runner &run, const Any &call, const Any &assignValue, const void *key) const
	{
		void **stack = (void**)run.sink - variableCount - 1;
		*stack = (void*)&assignValue;
		return call.matching(run, stack, *(const QuickMatch*)(this + 1));
	}

	const QuickCalling *QuickStore::match(Runner &run, void **stack, const Integer &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = &value;
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickStore::match(Runner &run, void **stack, const Float &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = &value;
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickStore::match(Runner &run, void **stack, const PilsColor &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = &value;
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickStore::match(Runner &run, void **stack, const Timestamp &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = &value;
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickStore::match(Runner &run, void **stack, const Duration &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = &value;
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickStore::match(Runner &run, void **stack, const PilsDate &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = &value;
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickStore::match(Runner &run, void **stack, const PilsString &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = &value;
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickStore::match(Runner &run, void **stack, const Cliche &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = &value;
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickStore::match(Runner &run, void **stack, const ListConstant &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = &value;
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickStore::match(Runner &run, void **stack, const ListExpress &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = &value;
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickStore::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = &value;
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickStore::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = &value;
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickStore::match(Runner &run, void **stack, const NodeExpressShort &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = &value;
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickStore::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = &value;
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickStore::match(Runner &run, void **stack, const Special &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = &value;
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickStore::match(Runner &run, void **stack, const Listener &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = &value;
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickIdentical::match(Runner &run, void **stack, const Integer &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == &value)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickIdentical::match(Runner &run, void **stack, const Float &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == &value)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickIdentical::match(Runner &run, void **stack, const PilsColor &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == &value)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickIdentical::match(Runner &run, void **stack, const Timestamp &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == &value)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickIdentical::match(Runner &run, void **stack, const Duration &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == &value)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickIdentical::match(Runner &run, void **stack, const PilsDate &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == &value)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickIdentical::match(Runner &run, void **stack, const PilsString &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == &value)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickIdentical::match(Runner &run, void **stack, const Cliche &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == &value)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickIdentical::match(Runner &run, void **stack, const ListConstant &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == &value)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickIdentical::match(Runner &run, void **stack, const ListExpress &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == &value)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickIdentical::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == &value)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickIdentical::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == &value)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickIdentical::match(Runner &run, void **stack, const NodeExpressShort &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == &value)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickIdentical::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == &value)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickIdentical::match(Runner &run, void **stack, const Special &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == &value)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickIdentical::match(Runner &run, void **stack, const Listener &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == &value)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const Any *QuickFetchWhen::specialAttribute(const Special &value) const
	{
		return value.when;
	}

	const QuickCalling *QuickIndex::quickCalling(Runner &run, const Any &call, const void *key) const
	{
		const void *const *bound = std::lower_bound(begin, end, key);
		if (*bound == key)
			return (const QuickCalling*)begin[bound - end];
		else return (const QuickCalling*)*end;
	}

	const QuickCalling *QuickIndex::quickCalling(Runner &run, const Any &call, const Any &assignValue, const void *key) const
	{
		const void *const *bound = std::lower_bound(begin, end, key);
		if (*bound == key)
			return (const QuickCalling*)begin[bound - end];
		else return (const QuickCalling*)*end;
	}

	const QuickCalling *QuickBeginRule::quickCalling(Runner &run, const Any &call, const void *key) const
	{
		return call.matching(run, (void**)run.sink - variableCount, *(const QuickMatch*)(this + 1));
	}

	const QuickCalling *Integer::matching(Runner &run, void **stack, const QuickMatch &match) const
	{
		return match.match(run, stack, *this);
	}

	const QuickCalling *Float::matching(Runner &run, void **stack, const QuickMatch &match) const
	{
		return match.match(run, stack, *this);
	}

	const QuickCalling *PilsColor::matching(Runner &run, void **stack, const QuickMatch &match) const
	{
		return match.match(run, stack, *this);
	}

	const QuickCalling *Timestamp::matching(Runner &run, void **stack, const QuickMatch &match) const
	{
		return match.match(run, stack, *this);
	}

	const QuickCalling *Duration::matching(Runner &run, void **stack, const QuickMatch &match) const
	{
		return match.match(run, stack, *this);
	}

	const QuickCalling *PilsDate::matching(Runner &run, void **stack, const QuickMatch &match) const
	{
		return match.match(run, stack, *this);
	}

	const QuickCalling *PilsString::matching(Runner &run, void **stack, const QuickMatch &match) const
	{
		return match.match(run, stack, *this);
	}

	const QuickCalling *Cliche::matching(Runner &run, void **stack, const QuickMatch &match) const
	{
		return match.match(run, stack, *this);
	}

	const QuickCalling *NodeConstantShort::matching(Runner &run, void **stack, const QuickMatch &match) const
	{
		return match.match(run, stack, *this);
	}

	const QuickCalling *NodeConstantLong::matching(Runner &run, void **stack, const QuickMatch &match) const
	{
		return match.match(run, stack, *this);
	}

	const QuickCalling *ListConstant::matching(Runner &run, void **stack, const QuickMatch &match) const
	{
		return match.match(run, stack, *this);
	}

	const QuickCalling *NodeExpressShort::matching(Runner &run, void **stack, const QuickMatch &match) const
	{
		return match.match(run, stack, *this);
	}

	const QuickCalling *NodeExpressLong::matching(Runner &run, void **stack, const QuickMatch &match) const
	{
		return match.match(run, stack, *this);
	}

	const QuickCalling *ListExpress::matching(Runner &run, void **stack, const QuickMatch &match) const
	{
		return match.match(run, stack, *this);
	}

	const QuickCalling *Special::matching(Runner &run, void **stack, const QuickMatch &match) const
	{
		return match.match(run, stack, *this);
	}

	const QuickCalling *Listener::matching(Runner &run, void** stack, const QuickMatch &match) const
	{
		return match.match(run, stack, *this);
	}

	const QuickCalling *QuickAction::match(Runner &run, void **stack, const Integer &value) const
	{
		action(run);
		return NULL;
	}

	const QuickCalling *QuickAction::match(Runner &run, void **stack, const Float &value) const
	{
		action(run);
		return NULL;
	}

	const QuickCalling *QuickAction::match(Runner &run, void **stack, const PilsColor &value) const
	{
		action(run);
		return NULL;
	}

	const QuickCalling *QuickAction::match(Runner &run, void **stack, const Timestamp &value) const
	{
		action(run);
		return NULL;
	}

	const QuickCalling *QuickAction::match(Runner &run, void **stack, const Duration &value) const
	{
		action(run);
		return NULL;
	}

	const QuickCalling *QuickAction::match(Runner &run, void **stack, const PilsDate &value) const
	{
		action(run);
		return NULL;
	}

	const QuickCalling *QuickAction::match(Runner &run, void **stack, const PilsString &value) const
	{
		action(run);
		return NULL;
	}

	const QuickCalling *QuickAction::match(Runner &run, void **stack, const Cliche &value) const
	{
		action(run);
		return NULL;
	}

	const QuickCalling *QuickAction::match(Runner &run, void **stack, const ListConstant &value) const
	{
		action(run);
		return NULL;
	}

	const QuickCalling *QuickAction::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		action(run);
		return NULL;
	}

	const QuickCalling *QuickAction::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		action(run);
		return NULL;
	}

	const QuickCalling *QuickAction::match(Runner &run, void **stack, const ListExpress &value) const
	{
		action(run);
		return NULL;
	}

	const QuickCalling *QuickAction::match(Runner &run, void **stack, const NodeExpressShort &value) const
	{
		action(run);
		return NULL;
	}

	const QuickCalling *QuickAction::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		action(run);
		return NULL;
	}

	const QuickCalling *QuickAction::match(Runner &run, void **stack, const Special &value) const
	{
		action(run);
		return NULL;
	}

	const QuickCalling *QuickAction::match(Runner &run, void **stack, const Listener &value) const
	{
		action(run);
		return NULL;
	}

	const QuickCalling *QuickBuild::match(Runner &run, void **stack, const Integer &value) const
	{
		return build(run, stack);
	}

	const QuickCalling *QuickBuild::match(Runner &run, void **stack, const Float &value) const
	{
		return build(run, stack);
	}

	const QuickCalling *QuickBuild::match(Runner &run, void **stack, const PilsColor &value) const
	{
		return build(run, stack);
	}

	const QuickCalling *QuickBuild::match(Runner &run, void **stack, const Timestamp &value) const
	{
		return build(run, stack);
	}

	const QuickCalling *QuickBuild::match(Runner &run, void **stack, const Duration &value) const
	{
		return build(run, stack);
	}

	const QuickCalling *QuickBuild::match(Runner &run, void **stack, const PilsDate &value) const
	{
		return build(run, stack);
	}

	const QuickCalling *QuickBuild::match(Runner &run, void **stack, const PilsString &value) const
	{
		return build(run, stack);
	}

	const QuickCalling *QuickBuild::match(Runner &run, void **stack, const Cliche &value) const
	{
		return build(run, stack);
	}

	const QuickCalling *QuickBuild::match(Runner &run, void **stack, const ListConstant &value) const
	{
		return build(run, stack);
	}

	const QuickCalling *QuickBuild::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		return build(run, stack);
	}

	const QuickCalling *QuickBuild::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		return build(run, stack);
	}

	const QuickCalling *QuickBuild::match(Runner &run, void **stack, const ListExpress &value) const
	{
		return build(run, stack);
	}

	const QuickCalling *QuickBuild::match(Runner &run, void **stack, const NodeExpressShort &value) const
	{
		return build(run, stack);
	}

	const QuickCalling *QuickBuild::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		return build(run, stack);
	}

	const QuickCalling *QuickBuild::match(Runner &run, void **stack, const Special &value) const
	{
		return build(run, stack);
	}

	const QuickCalling *QuickBuild::match(Runner &run, void **stack, const Listener &value) const
	{
		return build(run, stack);
	}

	Sink *SinkCompiled::kick(Runner &run)
	{
		throw L"Bad state";
	}

	const Step *SinkCompiled::pass(Runner &run, const Any *thing)
	{
		throw L"Bad state";
	}

	void QuickActionOkConstant::action(Runner &run) const
	{
		constant.addReference();
		new (run.allocate(sizeof(SinkCompiledOkValue)))
			SinkCompiledOkValue(&constant);
	}

	const Step *SinkCompiledStep::called(Runner &run, const Constant &call)
	{
		return this;
	}

	const Step *SinkCompiledStep::called(Runner &run, const Integer &call)
	{
		return this;
	}

	const Step *SinkCompiledStep::called(Runner &run, const Empty &call)
	{
		return this;
	}

	const Step *SinkCompiledStep::called(Runner &run, const ListConstant &call)
	{
		return this;
	}

	const Step *SinkCompiledStep::called(Runner &run, const NodeConstant &call)
	{
		return this;
	}

	const Step *SinkCompiledStep::called(Runner &run, const ListExpress &call)
	{
		return this;
	}

	const Step *SinkCompiledStep::called(Runner &run, const NodeExpress &call)
	{
		return this;
	}

	const Step *SinkCompiledStep::called(Runner &run, const Any &call, const Any *assignValue)
	{
		assignValue->releaseReference();
		return this;
	}

	const Step *SinkCompiledOkValue::step_(Runner &run) const
	{
		const Any *value = this->value;
		run.sink = (SinkCompiledOkValue*)this + 1;
		return value->passCounted(run);
	}

	void QuickActionOk::action(Runner &run) const
	{
		const Any **stack = (const Any**)run.sink - cliche.count;
		*stack = run.calling.closure->element[0];
		const Any *whereabout = cliche.node(stack);
		for(;stack < (const Any**)run.sink;stack++) (*stack)->addReference();
		thing.addReference();
		new (run.allocate(sizeof(SinkCompiledOk)))
			SinkCompiledOk(&thing, whereabout);
	}

	void QuickActionOkArgument::action(Runner &run) const
	{
		const Any *value = *(const Any**)((const char *)run.sink + offset);
		value->addReference();
		new (run.allocate(sizeof(SinkCompiledOkValue)))
			SinkCompiledOkValue(value);
	}

	const QuickCalling *QuickBuilt::build(Runner &run, void **stack) const
	{
		const Any *value = *(const Any**)(stack);
		new (run.allocate(sizeof(SinkCompiledOkValue)))
			SinkCompiledOkValue(value);
		return NULL;
	}

	const Step *SinkCompiledOk::called(Runner &run, const Constant &call)
	{
		const Any *thing = this->thing;
		const Any *whereabout = this->whereabout;
		return (run.sink = this + 1)->tailStep(run, thing, whereabout);
	}

	const Step *SinkCompiledOk::called(Runner &run, const Integer &call)
	{
		const Any *thing = this->thing;
		const Any *whereabout = this->whereabout;
		return (run.sink = this + 1)->tailStep(run, thing, whereabout);
	}

	const Step *SinkCompiledOk::called(Runner &run, const Empty &call)
	{
		const Any *thing = this->thing;
		const Any *whereabout = this->whereabout;
		return (run.sink = this + 1)->tailStep(run, thing, whereabout);
	}

	const Step *SinkCompiledOk::called(Runner &run, const ListConstant &call)
	{
		const Any *thing = this->thing;
		const Any *whereabout = this->whereabout;
		return (run.sink = this + 1)->tailStep(run, thing, whereabout);
	}

	const Step *SinkCompiledOk::called(Runner &run, const NodeConstant &call)
	{
		const Any *thing = this->thing;
		const Any *whereabout = this->whereabout;
		return (run.sink = this + 1)->tailStep(run, thing, whereabout);
	}

	const Step *SinkCompiledOk::called(Runner &run, const ListExpress &call)
	{
		const Any *thing = this->thing;
		const Any *whereabout = this->whereabout;
		return (run.sink = this + 1)->tailStep(run, thing, whereabout);
	}

	const Step *SinkCompiledOk::called(Runner &run, const NodeExpress &call)
	{
		const Any *thing = this->thing;
		const Any *whereabout = this->whereabout;
		return (run.sink = this + 1)->tailStep(run, thing, whereabout);
	}

	const Step *SinkCompiledOk::called(Runner &run, const Any &call, const Any *assignValue)
	{
		assignValue->releaseReference();
		const Any *thing = this->thing;
		const Any *whereabout = this->whereabout;
		return (run.sink = this + 1)->tailStep(run, thing, whereabout);
	}

	void QuickActionAny::action(Runner &run) const
	{
		const Any **stack = (const Any**)run.sink - cliche.count;
		*stack = run.calling.closure->element[0];
		const NodeExpress *where_ = (NodeExpress *)cliche.node(stack);
		for(;stack < (const Any**)run.sink;stack++) (*stack)->addReference();
		new (run.allocate(sizeof(SinkCompiledAny)))	SinkCompiledAny(*this, where_);
	}

	const Step *SinkCompiledAny::called(Runner &run, const Constant &call)
	{
		const QuickActionAny &action = this->action;
		const NodeExpress *where_ = this->where_;
		new (run.allocate(sizeof(CatchConstant) - sizeof(SinkCompiledAny)))
			CatchConstant(run, action, where_, call);
		return &action.thing;
	}

	const Step *SinkCompiledAny::called(Runner &run, const Integer &call)
	{
		const QuickActionAny &action = this->action;
		const NodeExpress *where_ = this->where_;
		new (run.allocate(sizeof(CatchConstant) - sizeof(SinkCompiledAny)))
			CatchConstant(run, action, where_, call);
		return &action.thing;
	}

	const Step *SinkCompiledAny::called(Runner &run, const Empty &call)
	{
		const QuickActionAny &action = this->action;
		const NodeExpress *where_ = this->where_;
		new (run.allocate(sizeof(CatchEmpty) - sizeof(SinkCompiledAny)))
			CatchEmpty(run, action, where_, call);
		return &action.thing;
	}

	const Step *SinkCompiledAny::called(Runner &run, const ListConstant &call)
	{
		const QuickActionAny &action = this->action;
		const NodeExpress *where_ = this->where_;
		new (run.allocate(sizeof(CatchListConstant) - sizeof(SinkCompiledAny)))
			CatchListConstant(run, action, where_, call);
		return &action.thing;
	}

	const Step *SinkCompiledAny::called(Runner &run, const NodeConstant &call)
	{
		const QuickActionAny &action = this->action;
		const NodeExpress *where_ = this->where_;
		new (run.allocate(sizeof(CatchNodeConstant) - sizeof(SinkCompiledAny)))
			CatchNodeConstant(run, action, where_, call);
		return &action.thing;
	}

	const Step *SinkCompiledAny::called(Runner &run, const ListExpress &call)
	{
		const QuickActionAny &action = this->action;
		const NodeExpress *where_ = this->where_;
		new (run.allocate(sizeof(CatchListExpress) - sizeof(SinkCompiledAny)))
			CatchListExpress(run, action, where_, call);
		return &action.thing;
	}

	const Step *SinkCompiledAny::called(Runner &run, const NodeExpress &call)
	{
		const QuickActionAny &action = this->action;
		const NodeExpress *where_ = this->where_;
		new (run.allocate(sizeof(CatchNodeExpress) - sizeof(SinkCompiledAny)))
			CatchNodeExpress(run, action, where_, call);
		return &action.thing;
	}

	const Step *SinkCompiledAny::called(Runner &run, const Any &call, const Any *assignValue)
	{
		const QuickActionAny &action = this->action;
		const NodeExpress *where_ = this->where_;
		new (run.allocate(sizeof(CatchAssign) - sizeof(SinkCompiledAny)))
			CatchAssign(run, action, where_, call, assignValue);
		return &action.thing;
	}

	Sink *SinkCompiledAny::kick(Runner &run)
	{
		run.where_->releaseReference();
		run.where_ = where_;
		return this + 1;
	}

	const QuickCalling *QuickImplicit::match(Runner &run, void **stack, const Integer &value) const
	{
		*(const Any**)((const char*)stack + slotOffset) = &fetch(run);
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickImplicit::match(Runner &run, void **stack, const Float &value) const
	{
		*(const Any**)((const char*)stack + slotOffset) = &fetch(run);
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickImplicit::match(Runner &run, void **stack, const PilsColor &value) const
	{
		*(const Any**)((const char*)stack + slotOffset) = &fetch(run);
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickImplicit::match(Runner &run, void **stack, const Timestamp &value) const
	{
		*(const Any**)((const char*)stack + slotOffset) = &fetch(run);
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickImplicit::match(Runner &run, void **stack, const Duration &value) const
	{
		*(const Any**)((const char*)stack + slotOffset) = &fetch(run);
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickImplicit::match(Runner &run, void **stack, const PilsDate &value) const
	{
		*(const Any**)((const char*)stack + slotOffset) = &fetch(run);
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickImplicit::match(Runner &run, void **stack, const PilsString &value) const
	{
		*(const Any**)((const char*)stack + slotOffset) = &fetch(run);
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickImplicit::match(Runner &run, void **stack, const Cliche &value) const
	{
		*(const Any**)((const char*)stack + slotOffset) = &fetch(run);
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickImplicit::match(Runner &run, void **stack, const ListConstant &value) const
	{
		*(const Any**)((const char*)stack + slotOffset) = &fetch(run);
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickImplicit::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		*(const Any**)((const char*)stack + slotOffset) = &fetch(run);
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickImplicit::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		*(const Any**)((const char*)stack + slotOffset) = &fetch(run);
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickImplicit::match(Runner &run, void **stack, const ListExpress &value) const
	{
		*(const Any**)((const char*)stack + slotOffset) = &fetch(run);
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickImplicit::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		*(const Any**)((const char*)stack + slotOffset) = &fetch(run);
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickImplicit::match(Runner &run, void **stack, const NodeExpressShort &value) const
	{
		*(const Any**)((const char*)stack + slotOffset) = &fetch(run);
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickImplicit::match(Runner &run, void **stack, const Special &value) const
	{
		*(const Any**)((const char*)stack + slotOffset) = &fetch(run);
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickImplicit::match(Runner &run, void **stack, const Listener &value) const
	{
		*(const Any**)((const char*)stack + slotOffset) = &fetch(run);
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickBuildFetch::build(Runner &run, void **stack) const
	{
		const Any *value = *(const Any**)((const char*)stack + offset);
		value->addReference();
		*(const Any**)(--stack) = value;
		return ((QuickBuild*)(this + 1))->build(run, stack);
	}

	const QuickCalling *QuickBuildQuote::build(Runner &run, void **stack) const
	{
		value.addReference();
		*(const Any**)(--stack) = &value;
		return ((QuickBuild*)(this + 1))->build(run, stack);
	}

	const QuickCalling *QuickBuildList::build(Runner &run, void **stack) const
	{
		bool constant = true;
		for (size_t i = 0; i < count && constant; i++)
			constant = (*((const Any **)(stack)))->as_Constant() != NULL;
		const Any *value;
		if (constant)
			value = ListConstant::get((const Constant **)stack, count);
		else
            value =	new ((count - 1)*sizeof(const Any *)) ListExpress((const Any **)stack, count);
		stack += count - 1;
		*(const Any**)(stack) = value;
		return ((QuickBuild*)(this + 1))->build(run, stack);
	}

	const QuickCalling *QuickBuildNodeShort::build(Runner &run, void **stack) const
	{
		*(const Any **)stack = cliche.node(*(const Any **)stack);
		return ((QuickBuild*)(this + 1))->build(run, stack);
	}

	const QuickCalling *QuickBuildNodeLong::build(Runner &run, void **stack) const
	{
		const Any *value = cliche.node((const Any **)stack);
		stack += cliche.count - 1;
		*(const Any **)stack = value;
		return ((QuickBuild*)(this + 1))->build(run, stack);
	}

	const Any &QuickImplicitWho::fetch(Runner &run) const
	{
		return *run.calling.who;
	}

	const Any &QuickImplicitWhere::fetch(Runner &run) const
	{
		return *run.where_;
	}

	const Any &QuickImplicitWhat::fetch(Runner &run) const
	{
		return *run.calling.what;
	}

	const Any &QuickImplicitSelf::fetch(Runner &run) const
	{
		return (const Any&)*run.calling.closure;
	}

	const QuickCalling *QuickMatchLiteral::match(Runner &run, void **stack, const Integer &value) const
	{
		if (&value == &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchLiteral::match(Runner &run, void **stack, const Float &value) const
	{
		if (&value == &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchLiteral::match(Runner &run, void **stack, const PilsColor &value) const
	{
		if (&value == &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchLiteral::match(Runner &run, void **stack, const Timestamp &value) const
	{
		if (&value == &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchLiteral::match(Runner &run, void **stack, const Duration &value) const
	{
		if (&value == &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchLiteral::match(Runner &run, void **stack, const PilsDate &value) const
	{
		if (&value == &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchLiteral::match(Runner &run, void **stack, const PilsString &value) const
	{
		if (&value == &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchLiteral::match(Runner &run, void **stack, const Cliche &value) const
	{
		if (&value == &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchLiteral::match(Runner &run, void **stack, const ListConstant &value) const
	{
		if (&value == &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchLiteral::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		if (&value == &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchLiteral::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		if (&value == &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchLiteral::match(Runner &run, void **stack, const ListExpress &value) const
	{
		if (&value == &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchLiteral::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		if (&value == &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchLiteral::match(Runner &run, void **stack, const NodeExpressShort &value) const
	{
		if (&value == &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchLiteral::match(Runner &run, void **stack, const Special &value) const
	{
		if (&value == &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchLiteral::match(Runner &run, void **stack, const Listener &value) const
	{
		if (&value == &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchNotEqual::match(Runner &run, void **stack, const Integer &value) const
	{
		if (&value != &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchNotEqual::match(Runner &run, void **stack, const Float &value) const
	{
		if (&value != &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchNotEqual::match(Runner &run, void **stack, const PilsColor &value) const
	{
		if (&value != &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchNotEqual::match(Runner &run, void **stack, const Timestamp &value) const
	{
		if (&value != &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchNotEqual::match(Runner &run, void **stack, const Duration &value) const
	{
		if (&value != &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchNotEqual::match(Runner &run, void **stack, const PilsDate &value) const
	{
		if (&value != &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchNotEqual::match(Runner &run, void **stack, const PilsString &value) const
	{
		if (&value != &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchNotEqual::match(Runner &run, void **stack, const Cliche &value) const
	{
		if (&value != &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchNotEqual::match(Runner &run, void **stack, const ListConstant &value) const
	{
		if (&value != &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchNotEqual::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		if (&value != &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchNotEqual::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		if (&value != &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchNotEqual::match(Runner &run, void **stack, const ListExpress &value) const
	{
		if (&value != &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchNotEqual::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		if (&value != &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchNotEqual::match(Runner &run, void **stack, const NodeExpressShort &value) const
	{
		if (&value != &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchNotEqual::match(Runner &run, void **stack, const Special &value) const
	{
		if (&value != &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickMatchNotEqual::match(Runner &run, void **stack, const Listener &value) const
	{
		if (&value != &thing)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return failChain.target;
	}

	const QuickCalling *QuickFetch::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		*--stack = (void*)&value;
		return value.element[0]->matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickFetch::match(Runner &run, void **stack, const NodeExpressShort &value) const
	{
		*--stack = (void*)&value;
		return value.element[0]->matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickFetch::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		*--stack = (void*)&value;
		return value.element[offset]->matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickFetch::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		*--stack = (void*)&value;
		return value.element[offset]->matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickFetch::match(Runner &run, void **stack, const ListConstant &value) const
	{
		*--stack = (void*)&value;
		return value.element[offset]->matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickFetch::match(Runner &run, void **stack, const ListExpress &value) const
	{
		*--stack = (void*)&value;
		return value.element[offset]->matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickFetch::match(Runner &run, void **stack, const Integer &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickFetch::match(Runner &run, void **stack, const Float &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickFetch::match(Runner &run, void **stack, const PilsColor &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickFetch::match(Runner &run, void **stack, const Timestamp &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickFetch::match(Runner &run, void **stack, const Duration &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickFetch::match(Runner &run, void **stack, const PilsDate &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickFetch::match(Runner &run, void **stack, const PilsString &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickFetch::match(Runner &run, void **stack, const Cliche &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickFetch::match(Runner &run, void **stack, const Special &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickFetch::match(Runner &run, void **stack, const Listener &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickPop::match(Runner &run, void **stack, const Integer &value) const
	{
		const Any &thing = *(const Any*)*(stack++);
		return thing.matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickPop::match(Runner &run, void **stack, const Float &value) const
	{
		const Any &thing = *(const Any*)*(stack++);
		return thing.matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickPop::match(Runner &run, void **stack, const PilsColor &value) const
	{
		const Any &thing = *(const Any*)*(stack++);
		return thing.matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickPop::match(Runner &run, void **stack, const Timestamp &value) const
	{
		const Any &thing = *(const Any*)*(stack++);
		return thing.matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickPop::match(Runner &run, void **stack, const Duration &value) const
	{
		const Any &thing = *(const Any*)*(stack++);
		return thing.matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickPop::match(Runner &run, void **stack, const PilsDate &value) const
	{
		const Any &thing = *(const Any*)*(stack++);
		return thing.matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickPop::match(Runner &run, void **stack, const PilsString &value) const
	{
		const Any &thing = *(const Any*)*(stack++);
		return thing.matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickPop::match(Runner &run, void **stack, const Cliche &value) const
	{
		const Any &thing = *(const Any*)*(stack++);
		return thing.matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickPop::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		const Any &thing = *(const Any*)*(stack++);
		return thing.matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickPop::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		const Any &thing = *(const Any*)*(stack++);
		return thing.matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickPop::match(Runner &run, void **stack, const ListConstant &value) const
	{
		const Any &thing = *(const Any*)*(stack++);
		return thing.matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickPop::match(Runner &run, void **stack, const NodeExpressShort &value) const
	{
		const Any &thing = *(const Any*)*(stack++);
		return thing.matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickPop::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		const Any &thing = *(const Any*)*(stack++);
		return thing.matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickPop::match(Runner &run, void **stack, const ListExpress &value) const
	{
		const Any &thing = *(const Any*)*(stack++);
		return thing.matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickPop::match(Runner &run, void **stack, const Special &value) const
	{
		const Any &thing = *(const Any*)*(stack++);
		return thing.matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickPop::match(Runner &run, void **stack, const Listener &value) const
	{
		const Any &thing = *(const Any*)*(stack++);
		return thing.matching(run, stack, *(this + 1));
	}

	const QuickCalling *QuickFail::match(Runner &run, void **stack, const Integer &value) const
	{
		return fail.target;
	}

	const QuickCalling *QuickFail::match(Runner &run, void **stack, const Float &value) const
	{
		return fail.target;
	}

	const QuickCalling *QuickFail::match(Runner &run, void **stack, const PilsColor &value) const
	{
		return fail.target;
	}

	const QuickCalling *QuickFail::match(Runner &run, void **stack, const Timestamp &value) const
	{
		return fail.target;
	}

	const QuickCalling *QuickFail::match(Runner &run, void **stack, const Duration &value) const
	{
		return fail.target;
	}

	const QuickCalling *QuickFail::match(Runner &run, void **stack, const PilsDate &value) const
	{
		return fail.target;
	}

	const QuickCalling *QuickFail::match(Runner &run, void **stack, const PilsString &value) const
	{
		return fail.target;
	}

	const QuickCalling *QuickFail::match(Runner &run, void **stack, const Cliche &value) const
	{
		return fail.target;
	}

	const QuickCalling *QuickFail::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		return fail.target;
	}

	const QuickCalling *QuickFail::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		return fail.target;
	}

	const QuickCalling *QuickFail::match(Runner &run, void **stack, const ListConstant &value) const
	{
		return fail.target;
	}

	const QuickCalling *QuickFail::match(Runner &run, void **stack, const NodeExpressShort &value) const
	{
		return fail.target;
	}

	const QuickCalling *QuickFail::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		return fail.target;
	}

	const QuickCalling *QuickFail::match(Runner &run, void **stack, const ListExpress &value) const
	{
		return fail.target;
	}

	const QuickCalling *QuickFail::match(Runner &run, void **stack, const Special &value) const
	{
		return fail.target;
	}

	const QuickCalling *QuickFail::match(Runner &run, void **stack, const Listener &value) const
	{
		return fail.target;
	}

	const QuickCalling *QuickMatchListCountOrNodeCliche::match(Runner &run, void **stack, const ListConstant &value) const
	{
		if (value.count == &key)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickMatchListCountOrNodeCliche::match(Runner &run, void **stack, const ListExpress &value) const
	{
		if (value.count == &key)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickMatchListCountOrNodeCliche::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		if (value.cliche == &key)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickMatchListCountOrNodeCliche::match(Runner &run, void **stack, const NodeExpressShort &value) const
	{
		if (value.cliche == &key)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickMatchListCountOrNodeCliche::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		if (value.cliche == &key)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickMatchListCountOrNodeCliche::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		if (value.cliche == &key)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickOffsetStore::match(Runner &run, void **stack, const Integer &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickOffsetStore::match(Runner &run, void **stack, const Float &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickOffsetStore::match(Runner &run, void **stack, const PilsColor &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickOffsetStore::match(Runner &run, void **stack, const Timestamp &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickOffsetStore::match(Runner &run, void **stack, const Duration &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickOffsetStore::match(Runner &run, void **stack, const PilsDate &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickOffsetStore::match(Runner &run, void **stack, const PilsString &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickOffsetStore::match(Runner &run, void **stack, const Cliche &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickOffsetStore::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = value.element[offset];
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickOffsetStore::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = value.element[offset];
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickOffsetStore::match(Runner &run, void **stack, const ListConstant &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = value.element[offset];
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickOffsetStore::match(Runner &run, void **stack, const NodeExpressShort &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = value.element[offset];
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickOffsetStore::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = value.element[offset];
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickOffsetStore::match(Runner &run, void **stack, const ListExpress &value) const
	{
		*((const Any**)((const char*)stack + slotOffset)) = value.element[offset];
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickOffsetStore::match(Runner &run, void **stack, const Special &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickOffsetStore::match(Runner &run, void **stack, const Listener &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickOffsetIdentical::match(Runner &run, void **stack, const Integer &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickOffsetIdentical::match(Runner &run, void **stack, const Float &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickOffsetIdentical::match(Runner &run, void **stack, const PilsColor &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickOffsetIdentical::match(Runner &run, void **stack, const Timestamp &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickOffsetIdentical::match(Runner &run, void **stack, const Duration &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickOffsetIdentical::match(Runner &run, void **stack, const PilsDate &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickOffsetIdentical::match(Runner &run, void **stack, const PilsString &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickOffsetIdentical::match(Runner &run, void **stack, const Cliche &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickOffsetIdentical::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == value.element[offset])
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickOffsetIdentical::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == value.element[offset])
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickOffsetIdentical::match(Runner &run, void **stack, const ListConstant &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == value.element[offset])
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickOffsetIdentical::match(Runner &run, void **stack, const NodeExpressShort &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == value.element[offset])
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickOffsetIdentical::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == value.element[offset])
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickOffsetIdentical::match(Runner &run, void **stack, const ListExpress &value) const
	{
		if (*((const Any**)((const char*)stack + slotOffset)) == value.element[offset])
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickOffsetIdentical::match(Runner &run, void **stack, const Special &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickOffsetIdentical::match(Runner &run, void **stack, const Listener &value) const
	{
		throw L"Bad compiled code";
	}

	const QuickCalling *QuickTestPlus::match(Runner &run, void **stack, const Integer &value) const
	{
		if (value.value > 0)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestCount::match(Runner &run, void **stack, const Integer &value) const
	{
		if (value.value >= 0)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestInteger::match(Runner &run, void **stack, const Integer &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestNumber::match(Runner &run, void **stack, const Integer &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestNumber::match(Runner &run, void **stack, const Float &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestPilsColor::match(Runner &run, void **stack, const PilsColor &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestTimestamp::match(Runner &run, void **stack, const Timestamp &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestPilsDate::match(Runner &run, void **stack, const PilsDate &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestDuration::match(Runner &run, void **stack, const Duration &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestString::match(Runner &run, void **stack, const PilsString &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestPlusString::match(Runner &run, void **stack, const PilsString &value) const
	{
		if (value.count->value)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestPlusPlusString::match(Runner &run, void **stack, const PilsString &value) const
	{
		if (value.count->value > 1)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestList::match(Runner &run, void **stack, const ListConstant &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestPlusList::match(Runner &run, void **stack, const ListConstant &value) const
	{
		if (value.count->value)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestPlusPlusList::match(Runner &run, void **stack, const ListConstant &value) const
	{
		if (value.count->value > 1)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestList::match(Runner &run, void **stack, const ListExpress &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestPlusList::match(Runner &run, void **stack, const ListExpress &value) const
	{
		if (value.count->value)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestPlusPlusList::match(Runner &run, void **stack, const ListExpress &value) const
	{
		if (value.count->value > 1)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestCliche::match(Runner &run, void **stack, const Cliche &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestNode::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestNode::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestNode::match(Runner &run, void **stack, const NodeExpressShort &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestNode::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestLegs::match(Runner &run, void **stack, const ListConstant &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestLegs::match(Runner &run, void **stack, const ListExpress &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestConstant::match(Runner &run, void **stack, const Integer &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestConstant::match(Runner &run, void **stack, const Float &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestConstant::match(Runner &run, void **stack, const PilsColor &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestConstant::match(Runner &run, void **stack, const Timestamp &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestConstant::match(Runner &run, void **stack, const Duration &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestConstant::match(Runner &run, void **stack, const PilsDate &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestConstant::match(Runner &run, void **stack, const PilsString &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestConstant::match(Runner &run, void **stack, const Cliche &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestConstant::match(Runner &run, void **stack, const ListConstant &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestConstant::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestConstant::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestConstant::match(Runner &run, void **stack, const Special &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestConstant::match(Runner &run, void **stack, const Listener &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestLanguage::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		if (value.as_Language())
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestListener::match(Runner &run, void **stack, const Listener &value) const
	{
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickTestSpecialTypecheck::match(Runner &run, void **stack, const Special &value) const
	{
		if (value.convert(check_))
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestSpecialTypecheck::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		if (value.convert(check_))
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestRecognizerTypecheck::match(Runner &run, void **stack, const Integer &value) const
	{
		if (value.recognize(check_))
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestRecognizerTypecheck::match(Runner &run, void **stack, const Float &value) const
	{
		if (value.recognize(check_))
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestRecognizerTypecheck::match(Runner &run, void **stack, const PilsDate &value) const
	{
		if (value.recognize(check_))
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestRecognizerTypecheck::match(Runner &run, void **stack, const PilsColor &value) const
	{
		if (value.recognize(check_))
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestRecognizerTypecheck::match(Runner &run, void **stack, const Timestamp &value) const
	{
		if (value.recognize(check_))
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestRecognizerTypecheck::match(Runner &run, void **stack, const Duration &value) const
	{
		if (value.recognize(check_))
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestRecognizerTypecheck::match(Runner &run, void **stack, const PilsString &value) const
	{
		if (value.recognize(check_))
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestRecognizerTypecheck::match(Runner &run, void **stack, const Cliche &value) const
	{
		if (value.recognize(check_))
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestRecognizerTypecheck::match(Runner &run, void **stack, const ListConstant &value) const
	{
		if (value.recognize(check_))
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestRecognizerTypecheck::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		if (value.recognize(check_))
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestRecognizerTypecheck::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		if (value.recognize(check_))
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestRecognizerTypecheck::match(Runner &run, void **stack, const ListExpress &value) const
	{
		if (value.recognize(check_))
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestRecognizerTypecheck::match(Runner &run, void **stack, const NodeExpressShort &value) const
	{
		if (value.recognize(check_))
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestRecognizerTypecheck::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		if (value.recognize(check_))
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestRecognizerTypecheck::match(Runner &run, void **stack, const Special &value) const
	{
		if (value.recognize(check_))
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestRecognizerTypecheck::match(Runner &run, void **stack, const Listener &value) const
	{
		if (value.recognize(check_))
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickTestSearchString::match(Runner &run, void **stack, const PilsString &a) const
	{
		const PilsString &b = (const PilsString&)*search.element[0];
		if (((BuiltinClicheSearchAbstract*)search.cliche)->search(a.value, a.count->value, b.value, b.count->value))
			return ((const QuickMatch*)(this + 1))->match(run, stack, a);
		else return fail.target;
	}

	const QuickCalling *QuickTestSearchListConstant::match(Runner &run, void **stack, const ListConstant &a) const
	{
		const ListConstant &b = (const ListConstant&)*search.element[0];
		if (((BuiltinClicheSearchAbstract*)search.cliche)->search((const Any *const *)a.element, a.count->value, (const Any *const *)b.element, b.count->value))
			return ((const QuickMatch*)(this + 1))->match(run, stack, a);
		else return fail.target;
	}

	const QuickCalling *QuickTestSearchListConstant::match(Runner &run, void **stack, const ListExpress &a) const
	{
		const ListConstant &b = (const ListConstant&)*search.element[0];
		if (((BuiltinClicheSearchAbstract*)search.cliche)->search(a.element, a.count->value, (const Any *const *)b.element, b.count->value))
			return ((const QuickMatch*)(this + 1))->match(run, stack, a);
		else return fail.target;
	}

	const QuickCalling *QuickFetchNodeHead::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		*--stack = (void*)&value;
		return value.cliche->head->matching(run, stack, *(const QuickMatch*)(this + 1));
	}

	const QuickCalling *QuickFetchNodeHead::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		*--stack = (void*)&value;
		return value.cliche->head->matching(run, stack, *(const QuickMatch*)(this + 1));
	}

	const QuickCalling *QuickFetchNodeHead::match(Runner &run, void **stack, const NodeExpressShort &value) const
	{
		*--stack = (void*)&value;
		return value.cliche->head->matching(run, stack, *(const QuickMatch*)(this + 1));
	}

	const QuickCalling *QuickFetchNodeHead::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		*--stack = (void*)&value;
		return value.cliche->head->matching(run, stack, *(const QuickMatch*)(this + 1));
	}

	const QuickCalling *QuickFetchNodeAttribute::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		if (&name == value.cliche->attributes[0])
		{
			*--stack = (void*)&value;
			return value.element[0]->matching(run, stack, *(const QuickMatch*)(this + 1));
		}
		else return fail.target;
	}

	const QuickCalling *QuickFetchNodeAttribute::match(Runner &run, void **stack, const NodeExpressShort &value) const
	{
		if (&name == value.cliche->attributes[0])
		{
			*--stack = (void*)&value;
			return value.element[0]->matching(run, stack, *(const QuickMatch*)(this + 1));
		}
		else return fail.target;
	}

	const QuickCalling *QuickFetchNodeAttribute::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		if (const Constant *fetched = value.getAttribute(name))
		{
			*--stack = (void*)&value;
			return fetched->matching(run, stack, *(const QuickMatch*)(this + 1));
		}
		else return fail.target;
	}

	const QuickCalling *QuickFetchNodeAttribute::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		if (const Any *fetched = value.getAttribute(name))
		{
			*--stack = (void*)&value;
			return fetched->matching(run, stack, *(const QuickMatch*)(this + 1));
		}
		else return fail.target;
	}

	const QuickCalling *QuickFetchNodeAttributeDefault::match(Runner &run, void **stack, const Cliche &value) const
	{
		*--stack = (void*)&value;
		return defaultValue.matching(run, stack, *(const QuickMatch*)(this + 1));
	}

	const QuickCalling *QuickFetchNodeAttributeDefault::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		*--stack = (void*)&value;
		if (&name == value.cliche->attributes[0])
			return value.element[0]->matching(run, stack, *(const QuickMatch*)(this + 1));
		else return defaultValue.matching(run, stack, *(const QuickMatch*)(this + 1));
	}

	const QuickCalling *QuickFetchNodeAttributeDefault::match(Runner &run, void **stack, const NodeExpressShort &value) const
	{
		*--stack = (void*)&value;
		if (&name == value.cliche->attributes[0])
			return value.element[0]->matching(run, stack, *(const QuickMatch*)(this + 1));
		else return defaultValue.matching(run, stack, *(const QuickMatch*)(this + 1));
	}

	const QuickCalling *QuickFetchNodeAttributeDefault::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		*--stack = (void*)&value;
		const Any *fetched = value.getAttribute(name);
		if (!fetched) fetched = &defaultValue;
		return fetched->matching(run, stack, *(const QuickMatch*)(this + 1));
	}

	const QuickCalling *QuickFetchNodeAttributeDefault::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		*--stack = (void*)&value;
		const Any *fetched = value.getAttribute(name);
		if (!fetched) fetched = &defaultValue;
		return fetched->matching(run, stack, *(const QuickMatch*)(this + 1));
	}

	const QuickCalling *QuickFetchClicheName::match(Runner &run, void **stack, const Cliche &value) const
	{
		*--stack = (void*)&value;
		return value.head->matching(run, stack, *(const QuickMatch*)(this + 1));
	}

	const QuickCalling *QuickFetchClicheShortAttribute::match(Runner &run, void **stack, const Cliche &value) const
	{
		if (value.count == 1)
		{
			*--stack = (void*)&value;
			return value.attributes[0]->matching(run, stack, *(const QuickMatch*)(this + 1));
		}
		else return fail.target;
	}

	const QuickCalling *QuickFetchStringCount::match(Runner &run, void **stack, const PilsString &value) const
	{
		*--stack = (void*)&value;
		return value.count->matching(run, stack, *(const QuickMatch*)(this + 1));
	}

	const QuickCalling *QuickFetchListCount::match(Runner &run, void **stack, const ListConstant &value) const
	{
		*--stack = (void*)&value;
		return value.count->matching(run, stack, *(const QuickMatch*)(this + 1));
	}

	const QuickCalling *QuickFetchListCount::match(Runner &run, void **stack, const ListExpress &value) const
	{
		*--stack = (void*)&value;
		return value.count->matching(run, stack, *(const QuickMatch*)(this + 1));
	}

	const QuickCalling *QuickFetchSpecialAttribute::match(Runner &run, void **stack, const Special &value) const
	{
		const Any *attribute = specialAttribute(value);
		if (attribute)
		{
			*--stack = (void*)&value;
			return attribute->matching(run, stack, *(const QuickMatch*)(this + 1));
		}
		else return fail.target;
	}

	const QuickCalling *QuickFetchListElement::match(Runner &run, void **stack, const ListConstant &value) const
	{
		if (index < (size_t)value.count->value)
		{
			*--stack = (void*)&value;
			return value.element[index]->matching(run, stack, *(const QuickMatch*)(this + 1));
		}
		else return fail.target;
	}

	const QuickCalling *QuickFetchListElement::match(Runner &run, void **stack, const ListExpress &value) const
	{
		if (index < (size_t)value.count->value)
		{
			*--stack = (void*)&value;
			return value.element[index]->matching(run, stack, *(const QuickMatch*)(this + 1));
		}
		else return fail.target;
	}

	const QuickCalling *QuickFetchListElementReverse::match(Runner &run, void **stack, const ListConstant &value) const
	{
		if (index < (size_t)value.count->value)
		{
			*--stack = (void*)&value;
			return value.element[value.count->value - index - 1]->matching(run, stack, *(const QuickMatch*)(this + 1));
		}
		else return fail.target;
	}

	const QuickCalling *QuickFetchListElementReverse::match(Runner &run, void **stack, const ListExpress &value) const
	{
		if (index < (size_t)value.count->value)
		{
			*--stack = (void*)&value;
			return value.element[value.count->value - index - 1]->matching(run, stack, *(const QuickMatch*)(this + 1));
		}
		else return fail.target;
	}

	const QuickCalling *QuickVerifyNodeAttributes::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		if (cliche.count == 1 && cliche.attributes[0] == value.cliche->attributes[0])
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickVerifyNodeAttributes::match(Runner &run, void **stack, const NodeExpressShort &value) const
	{
		if (cliche.count == 1 && cliche.attributes[0] == value.cliche->attributes[0])
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickVerifyNodeAttributes::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		const Cliche &vc = *value.cliche;
		if (cliche.count != vc.count) return fail.target;
		for (size_t i = 0; i < cliche.count; i++)
			if (cliche.attributes[i] != vc.attributes[i]) return fail.target;
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickVerifyNodeAttributes::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		const Cliche &vc = *value.cliche;
		if (cliche.count != vc.count) return fail.target;
		for (size_t i = 0; i < cliche.count; i++)
			if (cliche.attributes[i] != vc.attributes[i]) return fail.target;
		return ((const QuickMatch*)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickVerifyDefaultCliche::match(Runner &run, void **stack, const Cliche &value) const
	{
		if (&value == cliche.head)
			return ((const QuickMatch*)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickVerifyDefaultCliche::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		if (value.cliche->head == cliche.head)
		{
			for (size_t i = 0; i < cliche.count; i++)
			{
				if (cliche.attributes[i] == value.cliche->attributes[0])
					return ((const QuickMatch*)(this + 1))->match(run, stack, value);
			}
		}
		return fail.target;
	}

	const QuickCalling *QuickVerifyDefaultCliche::match(Runner &run, void **stack, const NodeExpressShort &value) const
	{
		if (value.cliche->head == cliche.head)
		{
			for (size_t i = 0; i < cliche.count; i++)
			{
				if (cliche.attributes[i] == value.cliche->attributes[0])
					return ((const QuickMatch*)(this + 1))->match(run, stack, value);
			}
		}
		return fail.target;
	}

	const QuickCalling *QuickVerifyDefaultCliche::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		if (value.cliche->head == cliche.head)
		{
			const Constant *const *at = value.cliche->attributes;
			const Constant *const *const end = at + value.cliche->count;
			for (size_t i = 0; i < cliche.count; i++)
			{
				if (cliche.attributes[i] == *at && ++at == end)
					return ((const QuickMatch*)(this + 1))->match(run, stack, value);
			}
		}
		return fail.target;
	}

	const QuickCalling *QuickVerifyDefaultCliche::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		if (value.cliche->head == cliche.head)
		{
			const Constant *const *at = value.cliche->attributes;
			const Constant *const *const end = at + value.cliche->count;
			for (size_t i = 0; i < cliche.count; i++)
			{
				if (cliche.attributes[i] == *at && ++at == end)
					return ((const QuickMatch*)(this + 1))->match(run, stack, value);
			}
		}
		return fail.target;
	}

	const QuickCalling *QuickClicheShortFetchHeadFetchAttribute::match(Runner &run, void **stack, const Cliche &value) const
	{
		if (value.count != 1) return fail.target;
		*--stack = (void*)&value;
		*--stack = (void*)value.head;
		return value.attributes[0]->matching(run, stack, *(const QuickMatch*)(this + 1));
	}

	const QuickCalling *QuickFetchThroughCall::match(Runner &run, void **stack, const Cliche &value) const
	{
		return matching(run, stack, value, NULL);
	}

	const QuickCalling *QuickFetchThroughCall::match(Runner &run, void **stack, const Integer &value) const
	{
		return matching(run, stack, value, NULL);
	}

	const QuickCalling *QuickFetchThroughCall::match(Runner &run, void **stack, const Float &value) const
	{
		return matching(run, stack, value, NULL);
	}

	const QuickCalling *QuickFetchThroughCall::match(Runner &run, void **stack, const PilsColor &value) const
	{
		return matching(run, stack, value, NULL);
	}

	const QuickCalling *QuickFetchThroughCall::match(Runner &run, void **stack, const Timestamp &value) const
	{
		return matching(run, stack, value, NULL);
	}

	const QuickCalling *QuickFetchThroughCall::match(Runner &run, void **stack, const Duration &value) const
	{
		return matching(run, stack, value, NULL);
	}

	const QuickCalling *QuickFetchThroughCall::match(Runner &run, void **stack, const PilsDate &value) const
	{
		return matching(run, stack, value, NULL);
	}

	const QuickCalling *QuickFetchThroughCall::match(Runner &run, void **stack, const PilsString &value) const
	{
		return matching(run, stack, value, NULL);
	}

	const QuickCalling *QuickFetchThroughCall::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		return matching(run, stack, value, NULL);
	}

	const QuickCalling *QuickFetchThroughCall::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		return matching(run, stack, value, NULL);
	}

	const QuickCalling *QuickFetchThroughCall::match(Runner &run, void **stack, const ListConstant &value) const
	{
		return matching(run, stack, value, NULL);
	}

	const QuickCalling *QuickFetchThroughCall::match(Runner &run, void **stack, const Listener &value) const
	{
		return matching(run, stack, value, NULL);
	}

	const QuickCalling *QuickFetchThroughCall::match(Runner &run, void **stack, const Special &value) const
	{
		return matching(run, stack, value, NULL);
	}

	const QuickCalling *QuickFetchThroughTry::match(Runner &run, void **stack, const Cliche &value) const
	{
		return matching(run, stack, value, &value);
	}

	const QuickCalling *QuickFetchThroughTry::match(Runner &run, void **stack, const Integer &value) const
	{
		return matching(run, stack, value, &value);
	}

	const QuickCalling *QuickFetchThroughTry::match(Runner &run, void **stack, const Float &value) const
	{
		return matching(run, stack, value, &value);
	}

	const QuickCalling *QuickFetchThroughTry::match(Runner &run, void **stack, const PilsColor &value) const
	{
		return matching(run, stack, value, &value);
	}

	const QuickCalling *QuickFetchThroughTry::match(Runner &run, void **stack, const Timestamp &value) const
	{
		return matching(run, stack, value, &value);
	}

	const QuickCalling *QuickFetchThroughTry::match(Runner &run, void **stack, const Duration &value) const
	{
		return matching(run, stack, value, &value);
	}

	const QuickCalling *QuickFetchThroughTry::match(Runner &run, void **stack, const PilsDate &value) const
	{
		return matching(run, stack, value, &value);
	}

	const QuickCalling *QuickFetchThroughTry::match(Runner &run, void **stack, const PilsString &value) const
	{
		return matching(run, stack, value, &value);
	}

	const QuickCalling *QuickFetchThroughTry::match(Runner &run, void **stack, const NodeConstantShort &value) const
	{
		return matching(run, stack, value, &value);
	}

	const QuickCalling *QuickFetchThroughTry::match(Runner &run, void **stack, const NodeConstantLong &value) const
	{
		return matching(run, stack, value, &value);
	}

	const QuickCalling *QuickFetchThroughTry::match(Runner &run, void **stack, const ListConstant &value) const
	{
		return matching(run, stack, value, &value);
	}

	const QuickCalling *QuickFetchThroughTry::match(Runner &run, void **stack, const Listener &value) const
	{
		return matching(run, stack, value, &value);
	}

	const QuickCalling *QuickFetchThroughTry::match(Runner &run, void **stack, const Special &value) const
	{
		return matching(run, stack, value, &value);
	}

	const QuickCalling *QuickFetchThrough::matching(Runner &run, void **stack, const Constant &value, const Constant *result) const
	{
		if (const Constant *replacement = through.getAttribute(value))
			result = replacement;
		if (result)
		{
			*--stack = (void*)&value;
			return result->matching(run, stack, this[1]);
		}
		else return fail.target;
	}

	const QuickCalling *QuickFetchThroughTry::match(Runner &run, void **stack, const ListExpress &value) const
	{
		*--stack = (void*)&value;
		return ((QuickMatch *)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickFetchThroughTry::match(Runner &run, void **stack, const NodeExpressShort &value) const
	{
		*--stack = (void*)&value;
		return ((QuickMatch *)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickFetchThroughTry::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		*--stack = (void*)&value;
		return ((QuickMatch *)(this + 1))->match(run, stack, value);
	}

	const QuickCalling *QuickCompareDouble::match(Runner &run, void **stack, const Integer &value) const
	{
		if (compare.compare(this->value, value.value))
			return ((QuickMatch *)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickCompareDouble::match(Runner &run, void **stack, const Float &value) const
	{
		if (compare.compare(this->value, value.value))
			return ((QuickMatch *)(this + 1))->match(run, stack, value);
		else return fail.target;
	}

	const QuickCalling *QuickFetchSpecialType::match(Runner &run, void **stack, const Special &value) const
	{
		const Constant *type = value.type();
		if (type)
		{
			*--stack = (void*)&value;
			return type->matching(run, stack, this[1]);
		}
		else return fail.target;
	}

	const QuickCalling *QuickFetchSpecialType::match(Runner &run, void **stack, const NodeExpressLong &value) const
	{
		class TypeExtractor : public Converter
		{
		public:
			bool convert(const ReallySpecial &special)
			{
				return (type = ((Special &)special).type()) != NULL;
			}
			const Constant *type;
		} typeExtractor;
		if (value.convert(typeExtractor))
		{
			*--stack = (void*)&value;
			return typeExtractor.type->matching(run, stack, this[1]);
		}
		else return fail.target;
	}

	const QuickCalling *QuickMatchQueryInterface::match(Runner &run, void **stack, const Special &value) const
	{
		const Any *thing = value.queryInterface(designator);
		if (thing)
		{
			*--stack = (void*)&value;
			const QuickCalling *next = thing->matching(run, stack, this[1]);
			thing->releaseReference();
			return next;
		}
		else return fail.target;
	}
}
