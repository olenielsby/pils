/* This file is public domain */
#include "numeric.h"

namespace PILS
{
	const Step *Sink::pass(Runner &run, long value)
	{
		return pass(run, Integer::get(value));
	}

	const Step *Sink::pass(Runner &run, double value)
	{
		return Number::get(value)->passCounted(run);
	}

	const CallWho *PropertyMinus::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoPropertyMinus))) const WhoPropertyMinus(this, who);
	}

	const Step *WhoPropertyMinus::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkPropertyMinus))) SinkPropertyMinus(*this);
		return whoAttribute();
	}

	Sink *SinkPropertyMinus::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkPropertyMinus::pass(Runner &run, long value)
	{
		long result = -value;
		if (value == result && value != 0)
			return (run.sink = this + 1)->pass(run, -(double)value);
		else return (run.sink = this + 1)->pass(run, result);
	}

	const Step *SinkPropertyMinus::pass(Runner &run, double value)
	{
		return (run.sink = this + 1)->pass(run, -value);
	}

	const Step *SinkPropertyMinus::pass(Runner &run, const Integer &value)
	{
		long result = -value.value;
		if (value.value == result && value.value != 0)
			return (run.sink = this + 1)->pass(run, -(double)value.value);
		else return (run.sink = this + 1)->pass(run, result);
	}

	const Step *SinkPropertyMinus::pass(Runner &run, const Float &value)
	{
		return (run.sink = this + 1)->pass(run, -value.value);
	}

	const Step *SinkPropertyMinus::pass(Runner &run, const Integer *value)
	{
		long v = value->value;
		value->releaseReference();
		long result = -v;
		if (v == result && v != 0)
			return (run.sink = this + 1)->pass(run, -(double)v);
		else return (run.sink = this + 1)->pass(run, result);
	}

	const Step *SinkPropertyMinus::pass(Runner &run, const Float *value)
	{
		double result = -value->value;
		value->releaseReference();
		return (run.sink = this + 1)->pass(run, result);
	}

	const Step *SinkPropertyMinus::pass(Runner &run, const Duration *value)
	{
		const Duration *result = Duration::get(-value->value);
		value->releaseReference();
		return (run.sink = this + 1)->pass(run, result);
	}

	FloatProperty::FloatProperty(const PILS_CHAR *name, double (*function)(double))
		:  PredefinedName(name), function(function)
	{}

	const CallWho *FloatProperty::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoFloatProperty)))
			WhoFloatProperty(this, who);
	}

	size_t WhoFloatProperty::unlinkAndGetSize()
	{
		return CallWho::unlinkAndGetSize() + sizeof(double (*)(double));
	}

	const Step *WhoFloatProperty::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkFloatProperty))) SinkFloatProperty(*this);
		return element[1];
	}

	const Step *SinkFloatProperty::pass(Runner &run, long value)
	{
		WhoFloatProperty &what = (WhoFloatProperty &)this->what;
		return (run.sink = this + 1)->pass(run, what.function(value));
	}

	const Step *SinkFloatProperty::pass(Runner &run, double value)
	{
		WhoFloatProperty &what = (WhoFloatProperty &)this->what;
		return (run.sink = this + 1)->pass(run, what.function(value));
	}

	const Step *SinkFloatProperty::pass(Runner &run, const Integer &value)
	{
		WhoFloatProperty &what = (WhoFloatProperty &)this->what;
		return (run.sink = this + 1)->pass(run, what.function(value.value));
	}

	const Step *SinkFloatProperty::pass(Runner &run, const Float &value)
	{
		WhoFloatProperty &what = (WhoFloatProperty &)this->what;
		return (run.sink = this + 1)->pass(run, what.function(value.value));
	}

	const Step *SinkFloatProperty::pass(Runner &run, const Integer *value)
	{
		WhoFloatProperty &what = (WhoFloatProperty &)this->what;
		double result = what.function(value->value);
		value->releaseReference();
		return (run.sink = this + 1)->pass(run, result);
	}

	const Step *SinkFloatProperty::pass(Runner &run, const Float *value)
	{
		WhoFloatProperty &what = (WhoFloatProperty &)this->what;
		double result = what.function(value->value);
		value->releaseReference();
		return (run.sink = this + 1)->pass(run, result);
	}

	const NodeConstantShort *BuiltinClicheOperationPlus::newNode(const HashedConstant *&link, const Integer *value) const
	{
		return new
			(Heap::allocate(sizeof(OperationPlusInteger)))
			OperationPlusInteger(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationPlus::newNode(const HashedConstant *&link, const Float *value) const
	{
		return new
			(Heap::allocate(sizeof(OperationPlusFloat)))
			OperationPlusFloat(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationPlus::newNode(const HashedConstant *&link, const Timestamp *value) const
	{
		return new
			(Heap::allocate(sizeof(OperationPlusTimestamp)))
			OperationPlusTimestamp(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationPlus::newNode(const HashedConstant *&link, const Duration *value) const
	{
		return new
			(Heap::allocate(sizeof(OperationPlusDuration)))
			OperationPlusDuration(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationPlus::newNode(const HashedConstant *&link, const PilsDate *value) const
	{
		return new
			(Heap::allocate(sizeof(OperationPlusPilsDate)))
			OperationPlusPilsDate(link, value);
	}

	const CallWho *OperationPlusInteger::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoPlusInteger)))
			WhoPlusInteger(this, who);
	}

	const CallWho *OperationPlusFloat::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoPlusFloat)))
			WhoPlusFloat(this, who);
	}

	const CallWho *OperationPlusTimestamp::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoPlusTimestamp)))
			WhoPlusTimestamp(this, who);
	}

	const CallWho *OperationPlusDuration::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoPlusDuration)))
			WhoPlusDuration(this, who);
	}

	const CallWho *OperationPlusPilsDate::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoPlusPilsDate)))
			WhoPlusPilsDate(this, who);
	}

	const Step *WhoPlusInteger::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoPlusUncountedInteger)))
			SinkWhoPlusUncountedInteger(*this, *(const Integer*)((const NodeConstantShort*)element[0])->element[0]);
		return whoAttribute();
	}

	const Step *WhoPlusFloat::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoPlusUncountedFloat)))
			SinkWhoPlusUncountedFloat(*this, *(const Float*)((const NodeConstantShort*)element[0])->element[0]);
		return whoAttribute();
	}

	const Step *WhoPlusTimestamp::step_(Runner &run) const
	{
		const Timestamp *operand = (const Timestamp*)((const NodeConstantShort*)element[0])->element[0];
		new (run.allocate(sizeof(SinkWhoPlusUncountedTimestamp)))
			SinkWhoPlusUncountedTimestamp(*this, *operand);
		return whoAttribute();
	}

	const Step *WhoPlusDuration::step_(Runner &run) const
	{
		const Duration *operand = (const Duration*)((const NodeConstantShort*)element[0])->element[0];
		new (run.allocate(sizeof(SinkWhoPlusUncountedDuration)))
			SinkWhoPlusUncountedDuration(*this, *operand);
		return whoAttribute();
	}

	const Step *WhoPlusPilsDate::step_(Runner &run) const
	{
		const PilsDate *operand = (const PilsDate*)((const NodeConstantShort*)element[0])->element[0];
		new (run.allocate(sizeof(SinkWhoPlusUncountedPilsDate)))
			SinkWhoPlusUncountedPilsDate(*this, *operand);
		return whoAttribute();
	}

	const CallWho *BuiltinClicheOperationPlus::whoOperation(const NodeExpressShort *operation, const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoExpressPlus)))
			WhoExpressPlus(operation, who);
	}

	const Step *WhoExpressPlus::pass(Runner &run, long value)
	{
		new (run.allocate(sizeof(SinkWhoPlusRawInteger))) SinkWhoPlusRawInteger(*this, value);
		return element[1];
	}

	const Step *WhoExpressPlus::pass(Runner &run, double value)
	{
		new (run.allocate(sizeof(SinkWhoPlusRawFloat))) SinkWhoPlusRawFloat(*this, value);
		return element[1];
	}

	const Step *WhoExpressPlus::pass(Runner &run, const Integer &value)
	{
		new (run.allocate(sizeof(SinkWhoPlusUncountedInteger))) SinkWhoPlusUncountedInteger(*this, value);
		return element[1];
	}

	const Step *WhoExpressPlus::pass(Runner &run, const Float &value)
	{
		new (run.allocate(sizeof(SinkWhoPlusUncountedFloat))) SinkWhoPlusUncountedFloat(*this, value);
		return element[1];
	}

	const Step *WhoExpressPlus::pass(Runner &run, const Integer *value)
	{
		new (run.allocate(sizeof(SinkWhoPlusInteger))) SinkWhoPlusInteger(*this, value);
		return element[1];
	}

	const Step *WhoExpressPlus::pass(Runner &run, const Float *value)
	{
		new (run.allocate(sizeof(SinkWhoPlusFloat))) SinkWhoPlusFloat(*this, value);
		return element[1];
	}

	const Step *WhoExpressPlus::pass(Runner &run, const Timestamp *value)
	{
		new (run.allocate(sizeof(SinkWhoPlusTimestamp))) SinkWhoPlusTimestamp(*this, value);
		return element[1];
	}

	const Step *WhoExpressPlus::pass(Runner &run, const Duration *value)
	{
		new (run.allocate(sizeof(SinkWhoPlusDuration))) SinkWhoPlusDuration(*this, value);
		return element[1];
	}

	const Step *WhoExpressPlus::pass(Runner &run, const PilsDate *value)
	{
		new (run.allocate(sizeof(SinkWhoPlusPilsDate))) SinkWhoPlusPilsDate(*this, value);
		return element[1];
	}

	const Step *SinkWhoPlusRawInteger::pass(Runner &run, long value)
	{
		double result = (double)value + operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusRawInteger::pass(Runner &run, double value)
	{
		double result = value + operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusRawInteger::pass(Runner &run, const Integer &value)
	{
		double result = (double)value.value + operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusRawInteger::pass(Runner &run, const Float &value)
	{
		double result = value.value + operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusRawInteger::pass(Runner &run, const Integer *value)
	{
		double result = (double)value->value + operand;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusRawInteger::pass(Runner &run, const Float *value)
	{
		double result = value->value + operand;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusRawFloat::pass(Runner &run, long value)
	{
		double result = value + operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusRawFloat::pass(Runner &run, double value)
	{
		double result = value + operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusRawFloat::pass(Runner &run, const Integer &value)
	{
		double result = value.value + operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusRawFloat::pass(Runner &run, const Float &value)
	{
		double result = value.value + operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusRawFloat::pass(Runner &run, const Integer *value)
	{
		double result = value->value + operand;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusRawFloat::pass(Runner &run, const Float *value)
	{
		double result = value->value + operand;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusUncountedInteger::pass(Runner &run, long value)
	{
		double result = (double)value + ((const Integer&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusUncountedInteger::pass(Runner &run, double value)
	{
		double result = value + ((const Integer&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusUncountedInteger::pass(Runner &run, const Integer &value)
	{
		double result = (double)value.value + ((const Integer&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusUncountedInteger::pass(Runner &run, const Float &value)
	{
		double result = value.value + ((const Integer&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusUncountedInteger::pass(Runner &run, const Integer *value)
	{
		double result = (double)value->value + ((const Integer&)operand).value;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusUncountedInteger::pass(Runner &run, const Float *value)
	{
		double result = value->value + ((const Integer&)operand).value;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusUncountedFloat::pass(Runner &run, long value)
	{
		double result = value + ((const Float&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusUncountedFloat::pass(Runner &run, double value)
	{
		double result = value + ((const Float&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusUncountedFloat::pass(Runner &run, const Integer *value)
	{
		double result = value->value + ((const Float&)operand).value;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusUncountedFloat::pass(Runner &run, const Float *value)
	{
		double result = value->value + ((const Float&)operand).value;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusUncountedFloat::pass(Runner &run, const Integer &value)
	{
		double result = value.value + ((const Float&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusUncountedFloat::pass(Runner &run, const Float &value)
	{
		double result = value.value + ((const Float&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusUncountedTimestamp::pass(Runner &run, const Duration *value)
	{
		const Timestamp *result = Timestamp::get(value->value + ((const Timestamp&)operand).value);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusUncountedDuration::pass(Runner &run, const Timestamp *value)
	{
		const Timestamp *result = Timestamp::get(value->value + ((const Duration&)operand).value);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusUncountedDuration::pass(Runner &run, const PilsDate *value)
	{
		const PilsDate *result = PilsDate::get(value->value + ((const Duration&)operand).value);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusUncountedDuration::pass(Runner &run, const Duration *value)
	{
		const Duration *result = Duration::get(value->value + ((const Duration&)operand).value);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusUncountedPilsDate::pass(Runner &run, const Duration *value)
	{
		const PilsDate *result = PilsDate::get(value->value + ((const PilsDate&)operand).value);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusInteger::pass(Runner &run, long value)
	{
		double result = (double)value + ((const Integer*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusInteger::pass(Runner &run, double value)
	{
		double result = value + ((const Integer*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusInteger::pass(Runner &run, const Integer &value)
	{
		double result = (double)value.value + ((const Integer*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusInteger::pass(Runner &run, const Float &value)
	{
		double result = value.value + ((const Integer*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusInteger::pass(Runner &run, const Integer *value)
	{
		double result = (double)value->value + ((const Integer*)operand)->value;
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusInteger::pass(Runner &run, const Float *value)
	{
		double result = value->value + ((const Integer*)operand)->value;
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusFloat::pass(Runner &run, long value)
	{
		double result = value + ((const Float*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusFloat::pass(Runner &run, double value)
	{
		double result = value + ((const Float*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusFloat::pass(Runner &run, const Integer &value)
	{
		double result = value.value + ((const Float*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusFloat::pass(Runner &run, const Float &value)
	{
		double result = value.value + ((const Float*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusFloat::pass(Runner &run, const Integer *value)
	{
		double result = value->value + ((const Float*)operand)->value;
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusFloat::pass(Runner &run, const Float *value)
	{
		double result = value->value + ((const Float*)operand)->value;
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusTimestamp::pass(Runner &run, const Duration *value)
	{
		const Timestamp *result = Timestamp::get(value->value + ((const Timestamp*)operand)->value);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusDuration::pass(Runner &run, const Timestamp *value)
	{
		const Timestamp *result = Timestamp::get(value->value + ((const Duration*)operand)->value);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusDuration::pass(Runner &run, const PilsDate *value)
	{
		const PilsDate *result = PilsDate::get(value->value + ((const Duration*)operand)->value);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusDuration::pass(Runner &run, const Duration *value)
	{
		const Duration *result = Duration::get(value->value + ((const Duration*)operand)->value);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoPlusPilsDate::pass(Runner &run, const Duration *value)
	{
		const PilsDate *result = PilsDate::get(value->value + ((const PilsDate*)operand)->value);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const NodeConstantShort *BuiltinClicheOperationMinus::newNode(const HashedConstant *&link, const Integer *value) const
	{
		return new
			(Heap::allocate(sizeof(OperationMinusInteger)))
			OperationMinusInteger(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationMinus::newNode(const HashedConstant *&link, const Float *value) const
	{
		return new
			(Heap::allocate(sizeof(OperationMinusFloat)))
			OperationMinusFloat(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationMinus::newNode(const HashedConstant *&link, const Timestamp *value) const
	{
		return new
			(Heap::allocate(sizeof(OperationMinusTimestamp)))
			OperationMinusTimestamp(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationMinus::newNode(const HashedConstant *&link, const Duration *value) const
	{
		return new
			(Heap::allocate(sizeof(OperationMinusDuration)))
			OperationMinusDuration(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationMinus::newNode(const HashedConstant *&link, const PilsDate *value) const
	{
		return new
			(Heap::allocate(sizeof(OperationMinusPilsDate)))
			OperationMinusPilsDate(link, value);
	}

	const CallWho *OperationMinusInteger::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoMinusInteger)))
			WhoMinusInteger(this, who);
	}

	const CallWho *OperationMinusFloat::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoMinusFloat)))
			WhoMinusFloat(this, who);
	}

	const CallWho *OperationMinusTimestamp::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoMinusTimestamp)))
			WhoMinusTimestamp(this, who);
	}

	const CallWho *OperationMinusDuration::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoMinusDuration)))
			WhoMinusDuration(this, who);
	}

	const CallWho *OperationMinusPilsDate::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoMinusPilsDate)))
			WhoMinusPilsDate(this, who);
	}

	const Step *WhoMinusInteger::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoMinusUncountedInteger)))
			SinkWhoMinusUncountedInteger(*this, *(const Integer*)((const NodeConstantShort*)element[0])->element[0]);
		return whoAttribute();
	}

	const Step *WhoMinusFloat::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoMinusUncountedFloat)))
			SinkWhoMinusUncountedFloat(*this, *(const Float*)((const NodeConstantShort*)element[0])->element[0]);
		return whoAttribute();
	}

	const Step *WhoMinusTimestamp::step_(Runner &run) const
	{
		const Timestamp *operand = (const Timestamp*)((const NodeConstantShort*)element[0])->element[0];
		new (run.allocate(sizeof(SinkWhoMinusUncountedTimestamp)))
			SinkWhoMinusUncountedTimestamp(*this, *operand);
		return whoAttribute();
	}

	const Step *WhoMinusDuration::step_(Runner &run) const
	{
		const Duration *operand = (const Duration*)((const NodeConstantShort*)element[0])->element[0];
		new (run.allocate(sizeof(SinkWhoMinusUncountedDuration)))
			SinkWhoMinusUncountedDuration(*this, *operand);
		return whoAttribute();
	}

	const Step *WhoMinusPilsDate::step_(Runner &run) const
	{
		const PilsDate *operand = (const PilsDate*)((const NodeConstantShort*)element[0])->element[0];
		new (run.allocate(sizeof(SinkWhoMinusUncountedPilsDate)))
			SinkWhoMinusUncountedPilsDate(*this, *operand);
		return whoAttribute();
	}

	const CallWho *BuiltinClicheOperationMinus::whoOperation(const NodeExpressShort *operation, const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoExpressMinus)))
			WhoExpressMinus(operation, who);
	}

	const Step *WhoExpressMinus::pass(Runner &run, long value)
	{
		new (run.allocate(sizeof(SinkWhoMinusRawInteger))) SinkWhoMinusRawInteger(*this, value);
		return element[1];
	}

	const Step *WhoExpressMinus::pass(Runner &run, double value)
	{
		new (run.allocate(sizeof(SinkWhoMinusRawFloat))) SinkWhoMinusRawFloat(*this, value);
		return element[1];
	}

	const Step *WhoExpressMinus::pass(Runner &run, const Integer &value)
	{
		new (run.allocate(sizeof(SinkWhoMinusUncountedInteger))) SinkWhoMinusUncountedInteger(*this, value);
		return element[1];
	}

	const Step *WhoExpressMinus::pass(Runner &run, const Float &value)
	{
		new (run.allocate(sizeof(SinkWhoMinusUncountedFloat))) SinkWhoMinusUncountedFloat(*this, value);
		return element[1];
	}

	const Step *WhoExpressMinus::pass(Runner &run, const Integer *value)
	{
		new (run.allocate(sizeof(SinkWhoMinusInteger))) SinkWhoMinusInteger(*this, value);
		return element[1];
	}

	const Step *WhoExpressMinus::pass(Runner &run, const Float *value)
	{
		new (run.allocate(sizeof(SinkWhoMinusFloat))) SinkWhoMinusFloat(*this, value);
		return element[1];
	}

	const Step *WhoExpressMinus::pass(Runner &run, const Timestamp *value)
	{
		new (run.allocate(sizeof(SinkWhoMinusTimestamp))) SinkWhoMinusTimestamp(*this, value);
		return element[1];
	}

	const Step *WhoExpressMinus::pass(Runner &run, const Duration *value)
	{
		new (run.allocate(sizeof(SinkWhoMinusDuration))) SinkWhoMinusDuration(*this, value);
		return element[1];
	}

	const Step *WhoExpressMinus::pass(Runner &run, const PilsDate *value)
	{
		new (run.allocate(sizeof(SinkWhoMinusPilsDate))) SinkWhoMinusPilsDate(*this, value);
		return element[1];
	}

	const Step *SinkWhoMinusRawInteger::pass(Runner &run, long value)
	{
		double result = (double)value - operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusRawInteger::pass(Runner &run, double value)
	{
		double result = value - operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusRawInteger::pass(Runner &run, const Integer &value)
	{
		double result = (double)value.value - operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusRawInteger::pass(Runner &run, const Float &value)
	{
		double result = value.value - operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusRawInteger::pass(Runner &run, const Integer *value)
	{
		double result = (double)value->value - operand;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusRawInteger::pass(Runner &run, const Float *value)
	{
		double result = value->value - operand;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusRawFloat::pass(Runner &run, long value)
	{
		double result = value - operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusRawFloat::pass(Runner &run, double value)
	{
		double result = value - operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusRawFloat::pass(Runner &run, const Integer &value)
	{
		double result = value.value - operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusRawFloat::pass(Runner &run, const Float &value)
	{
		double result = value.value - operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusRawFloat::pass(Runner &run, const Integer *value)
	{
		double result = value->value - operand;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusRawFloat::pass(Runner &run, const Float *value)
	{
		double result = value->value - operand;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusUncountedInteger::pass(Runner &run, long value)
	{
		double result = (double)value - ((const Integer&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusUncountedInteger::pass(Runner &run, double value)
	{
		double result = value - ((const Integer&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusUncountedInteger::pass(Runner &run, const Integer &value)
	{
		double result = (double)value.value - ((const Integer&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusUncountedInteger::pass(Runner &run, const Float &value)
	{
		double result = value.value - ((const Integer&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusUncountedInteger::pass(Runner &run, const Integer *value)
	{
		double result = (double)value->value - ((const Integer&)operand).value;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusUncountedInteger::pass(Runner &run, const Float *value)
	{
		double result = value->value - ((const Integer&)operand).value;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusUncountedFloat::pass(Runner &run, long value)
	{
		double result = value - ((const Float&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusUncountedFloat::pass(Runner &run, double value)
	{
		double result = value - ((const Float&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusUncountedFloat::pass(Runner &run, const Integer *value)
	{
		double result = value->value - ((const Float&)operand).value;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusUncountedFloat::pass(Runner &run, const Float *value)
	{
		double result = value->value - ((const Float&)operand).value;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusUncountedFloat::pass(Runner &run, const Integer &value)
	{
		double result = value.value - ((const Float&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusUncountedFloat::pass(Runner &run, const Float &value)
	{
		double result = value.value - ((const Float&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusUncountedTimestamp::pass(Runner &run, const Timestamp *value)
	{
		const Duration *result = Duration::get(value->value - ((const Timestamp&)operand).value);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusUncountedDuration::pass(Runner &run, const Timestamp *value)
	{
		const Timestamp *result = Timestamp::get(value->value - ((const Duration&)operand).value);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusUncountedDuration::pass(Runner &run, const PilsDate *value)
	{
		const PilsDate *result = PilsDate::get(value->value - ((const Duration&)operand).value);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusUncountedDuration::pass(Runner &run, const Duration *value)
	{
		const Duration *result = Duration::get(value->value - ((const Duration&)operand).value);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusUncountedPilsDate::pass(Runner &run, const PilsDate *value)
	{
		const Duration *result = Duration::get(value->value - ((const PilsDate&)operand).value);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusInteger::pass(Runner &run, long value)
	{
		double result = (double)value - ((const Integer*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusInteger::pass(Runner &run, double value)
	{
		double result = value - ((const Integer*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusInteger::pass(Runner &run, const Integer &value)
	{
		double result = (double)value.value - ((const Integer*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusInteger::pass(Runner &run, const Float &value)
	{
		double result = value.value - ((const Integer*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusInteger::pass(Runner &run, const Integer *value)
	{
		double result = (double)value->value - ((const Integer*)operand)->value;
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusInteger::pass(Runner &run, const Float *value)
	{
		double result = value->value - ((const Integer*)operand)->value;
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusFloat::pass(Runner &run, long value)
	{
		double result = value - ((const Float*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusFloat::pass(Runner &run, double value)
	{
		double result = value - ((const Float*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusFloat::pass(Runner &run, const Integer &value)
	{
		double result = value.value - ((const Float*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusFloat::pass(Runner &run, const Float &value)
	{
		double result = value.value - ((const Float*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusFloat::pass(Runner &run, const Integer *value)
	{
		double result = value->value - ((const Float*)operand)->value;
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusFloat::pass(Runner &run, const Float *value)
	{
		double result = value->value - ((const Float*)operand)->value;
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusTimestamp::pass(Runner &run, const Timestamp *value)
	{
		const Duration *result = Duration::get(value->value - ((const Timestamp*)operand)->value);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusDuration::pass(Runner &run, const Timestamp *value)
	{
		const Timestamp *result = Timestamp::get(value->value - ((const Duration*)operand)->value);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusDuration::pass(Runner &run, const PilsDate *value)
	{
		const PilsDate *result = PilsDate::get(value->value - ((const Duration*)operand)->value);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusDuration::pass(Runner &run, const Duration *value)
	{
		const Duration *result = Duration::get(value->value - ((const Duration*)operand)->value);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoMinusPilsDate::pass(Runner &run, const PilsDate *value)
	{
		const Duration *result = Duration::get(value->value - ((const PilsDate*)operand)->value);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const NodeConstantShort *BuiltinClicheOperationTimes::newNode(const HashedConstant *&link, const Integer *value) const
	{
		return new
			(Heap::allocate(sizeof(OperationTimesInteger)))
			OperationTimesInteger(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationTimes::newNode(const HashedConstant *&link, const Float *value) const
	{
		return new
			(Heap::allocate(sizeof(OperationTimesFloat)))
			OperationTimesFloat(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationTimes::newNode(const HashedConstant *&link, const Duration *value) const
	{
		return new
			(Heap::allocate(sizeof(OperationTimesDuration)))
			OperationTimesDuration(link, value);
	}

	const CallWho *OperationTimesInteger::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoTimesInteger)))
			WhoTimesInteger(this, who);
	}

	const CallWho *OperationTimesFloat::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoTimesFloat)))
			WhoTimesFloat(this, who);
	}

	const CallWho *OperationTimesDuration::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoTimesDuration)))
			WhoTimesDuration(this, who);
	}

	const Step *WhoTimesInteger::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoTimesUncountedInteger)))
			SinkWhoTimesUncountedInteger(*this, *(const Integer*)((const NodeConstantShort*)element[0])->element[0]);
		return whoAttribute();
	}

	const Step *WhoTimesFloat::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoTimesUncountedFloat)))
			SinkWhoTimesUncountedFloat(*this, *(const Float*)((const NodeConstantShort*)element[0])->element[0]);
		return whoAttribute();
	}

	const Step *WhoTimesDuration::step_(Runner &run) const
	{
		const Duration *operand = (const Duration*)((const NodeConstantShort*)element[0])->element[0];
		new (run.allocate(sizeof(SinkWhoTimesUncountedDuration)))
			SinkWhoTimesUncountedDuration(*this, *operand);
		return whoAttribute();
	}

	const CallWho *BuiltinClicheOperationTimes::whoOperation(const NodeExpressShort *operation, const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoExpressTimes)))
			WhoExpressTimes(operation, who);
	}

	const Step *WhoExpressTimes::pass(Runner &run, long value)
	{
		new (run.allocate(sizeof(SinkWhoTimesRawInteger))) SinkWhoTimesRawInteger(*this, value);
		return element[1];
	}

	const Step *WhoExpressTimes::pass(Runner &run, double value)
	{
		new (run.allocate(sizeof(SinkWhoTimesRawFloat))) SinkWhoTimesRawFloat(*this, value);
		return element[1];
	}

	const Step *WhoExpressTimes::pass(Runner &run, const Integer &value)
	{
		new (run.allocate(sizeof(SinkWhoTimesUncountedInteger))) SinkWhoTimesUncountedInteger(*this, value);
		return element[1];
	}

	const Step *WhoExpressTimes::pass(Runner &run, const Float &value)
	{
		new (run.allocate(sizeof(SinkWhoTimesUncountedFloat))) SinkWhoTimesUncountedFloat(*this, value);
		return element[1];
	}

	const Step *WhoExpressTimes::pass(Runner &run, const Integer *value)
	{
		new (run.allocate(sizeof(SinkWhoTimesInteger))) SinkWhoTimesInteger(*this, value);
		return element[1];
	}

	const Step *WhoExpressTimes::pass(Runner &run, const Float *value)
	{
		new (run.allocate(sizeof(SinkWhoTimesFloat))) SinkWhoTimesFloat(*this, value);
		return element[1];
	}

	const Step *WhoExpressTimes::pass(Runner &run, const Duration *value)
	{
		new (run.allocate(sizeof(SinkWhoTimesDuration))) SinkWhoTimesDuration(*this, value);
		return element[1];
	}

	const Step *SinkWhoTimesRawInteger::pass(Runner &run, long value)
	{
		double result = (double)value * operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesRawInteger::pass(Runner &run, double value)
	{
		double result = value * operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesRawInteger::pass(Runner &run, const Integer &value)
	{
		double result = (double)value.value * operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesRawInteger::pass(Runner &run, const Float &value)
	{
		double result = value.value * operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesRawInteger::pass(Runner &run, const Integer *value)
	{
		double result = (double)value->value * operand;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesRawInteger::pass(Runner &run, const Float *value)
	{
		double result = value->value * operand;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesRawInteger::pass(Runner &run, const Duration *value)
	{
		const Duration *result = Duration::get(value->value * operand);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesRawFloat::pass(Runner &run, long value)
	{
		double result = value * operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesRawFloat::pass(Runner &run, double value)
	{
		double result = value * operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesRawFloat::pass(Runner &run, const Integer &value)
	{
		double result = value.value * operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesRawFloat::pass(Runner &run, const Float &value)
	{
		double result = value.value * operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesRawFloat::pass(Runner &run, const Integer *value)
	{
		double result = value->value * operand;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesRawFloat::pass(Runner &run, const Float *value)
	{
		double result = value->value * operand;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesRawFloat::pass(Runner &run, const Duration *value)
	{
		const Duration *result = Duration::get((long long)(value->value * operand));
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesUncountedInteger::pass(Runner &run, long value)
	{
		double result = (double)value * ((const Integer&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesUncountedInteger::pass(Runner &run, double value)
	{
		double result = value * ((const Integer&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesUncountedInteger::pass(Runner &run, const Integer &value)
	{
		double result = (double)value.value * ((const Integer&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesUncountedInteger::pass(Runner &run, const Float &value)
	{
		double result = value.value * ((const Integer&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesUncountedInteger::pass(Runner &run, const Integer *value)
	{
		double result = (double)value->value * ((const Integer&)operand).value;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesUncountedInteger::pass(Runner &run, const Float *value)
	{
		double result = value->value * ((const Integer&)operand).value;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesUncountedInteger::pass(Runner &run, const Duration *value)
	{
		const Duration *result = Duration::get(value->value * ((const Integer&)operand).value);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesUncountedFloat::pass(Runner &run, long value)
	{
		double result = value * ((const Float&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesUncountedFloat::pass(Runner &run, double value)
	{
		double result = value * ((const Float&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesUncountedFloat::pass(Runner &run, const Integer *value)
	{
		double result = value->value * ((const Float&)operand).value;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesUncountedFloat::pass(Runner &run, const Float *value)
	{
		double result = value->value * ((const Float&)operand).value;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesUncountedFloat::pass(Runner &run, const Duration *value)
	{
		const Duration *result = Duration::get((long long)(value->value * ((const Float&)operand).value));
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesUncountedFloat::pass(Runner &run, const Integer &value)
	{
		double result = value.value * ((const Float&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesUncountedFloat::pass(Runner &run, const Float &value)
	{
		double result = value.value * ((const Float&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}



	const Step *SinkWhoTimesUncountedDuration::pass(Runner &run, long value)
	{
		const Duration *result = Duration::get(value * ((const Duration&)operand).value);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesUncountedDuration::pass(Runner &run, double value)
	{
		const Duration *result = Duration::get((long long)(value * ((const Duration&)operand).value));
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesUncountedDuration::pass(Runner &run, const Integer *value)
	{
		const Duration *result = Duration::get(value->value * ((const Duration&)operand).value);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesUncountedDuration::pass(Runner &run, const Float *value)
	{
		const Duration *result = Duration::get((long long)(value->value * ((const Duration&)operand).value));
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesUncountedDuration::pass(Runner &run, const Integer &value)
	{
		const Duration *result = Duration::get(value.value * ((const Duration&)operand).value);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesUncountedDuration::pass(Runner &run, const Float &value)
	{
		const Duration *result = Duration::get((long long)(value.value * ((const Duration&)operand).value));
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesInteger::pass(Runner &run, long value)
	{
		double result = (double)value * ((const Integer*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesInteger::pass(Runner &run, double value)
	{
		double result = value * ((const Integer*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesInteger::pass(Runner &run, const Integer &value)
	{
		double result = (double)value.value * ((const Integer*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesInteger::pass(Runner &run, const Float &value)
	{
		double result = value.value * ((const Integer*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesInteger::pass(Runner &run, const Integer *value)
	{
		double result = (double)value->value * ((const Integer*)operand)->value;
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesInteger::pass(Runner &run, const Float *value)
	{
		double result = value->value * ((const Integer*)operand)->value;
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesInteger::pass(Runner &run, const Duration *value)
	{
		const Duration *result = Duration::get(value->value * ((const Integer*)operand)->value);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesFloat::pass(Runner &run, long value)
	{
		double result = value * ((const Float*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesFloat::pass(Runner &run, double value)
	{
		double result = value * ((const Float*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesFloat::pass(Runner &run, const Integer &value)
	{
		double result = value.value * ((const Float*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesFloat::pass(Runner &run, const Float &value)
	{
		double result = value.value * ((const Float*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesFloat::pass(Runner &run, const Integer *value)
	{
		double result = value->value * ((const Float*)operand)->value;
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesFloat::pass(Runner &run, const Float *value)
	{
		double result = value->value * ((const Float*)operand)->value;
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesFloat::pass(Runner &run, const Duration *value)
	{
		const Duration *result = Duration::get((long long)(value->value * ((const Float*)operand)->value));
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesDuration::pass(Runner &run, long value)
	{
		const Duration *result = Duration::get(value * ((const Duration*)operand)->value);
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesDuration::pass(Runner &run, double value)
	{
		const Duration *result = Duration::get((long long)(value * ((const Duration*)operand)->value));
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesDuration::pass(Runner &run, const Integer &value)
	{
		const Duration *result = Duration::get(value.value * ((const Duration*)operand)->value);
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesDuration::pass(Runner &run, const Float &value)
	{
		const Duration *result = Duration::get((long long)(value.value * ((const Duration*)operand)->value));
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesDuration::pass(Runner &run, const Integer *value)
	{
		const Duration *result = Duration::get(value->value * ((const Duration*)operand)->value);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoTimesDuration::pass(Runner &run, const Float *value)
	{
		const Duration *result = Duration::get((long long)(value->value * ((const Duration*)operand)->value));
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const NodeConstantShort *BuiltinClicheOperationDivide::newNode(const HashedConstant *&link, const Integer *value) const
	{
		return new
			(Heap::allocate(sizeof(OperationDivideInteger)))
			OperationDivideInteger(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationDivide::newNode(const HashedConstant *&link, const Float *value) const
	{
		return new
			(Heap::allocate(sizeof(OperationDivideFloat)))
			OperationDivideFloat(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationDivide::newNode(const HashedConstant *&link, const Duration *value) const
	{
		return new
			(Heap::allocate(sizeof(OperationDivideDuration)))
			OperationDivideDuration(link, value);
	}

	const CallWho *OperationDivideInteger::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoDivideInteger)))
			WhoDivideInteger(this, who);
	}

	const CallWho *OperationDivideFloat::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoDivideFloat)))
			WhoDivideFloat(this, who);
	}

	const CallWho *OperationDivideDuration::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoDivideDuration)))
			WhoDivideDuration(this, who);
	}

	const Step *WhoDivideInteger::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoDivideUncountedInteger)))
			SinkWhoDivideUncountedInteger(*this, *(const Integer*)((const NodeConstantShort*)element[0])->element[0]);
		return whoAttribute();
	}

	const Step *WhoDivideFloat::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoDivideUncountedFloat)))
			SinkWhoDivideUncountedFloat(*this, *(const Float*)((const NodeConstantShort*)element[0])->element[0]);
		return whoAttribute();
	}

	const Step *WhoDivideDuration::step_(Runner &run) const
	{
		const Duration *operand = (const Duration*)((const NodeConstantShort*)element[0])->element[0];
		new (run.allocate(sizeof(SinkWhoDivideUncountedDuration)))
			SinkWhoDivideUncountedDuration(*this, *operand);
		return whoAttribute();
	}

	const CallWho *BuiltinClicheOperationDivide::whoOperation(const NodeExpressShort *operation, const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoExpressDivide)))
			WhoExpressDivide(operation, who);
	}

	const Step *WhoExpressDivide::pass(Runner &run, long value)
	{
		new (run.allocate(sizeof(SinkWhoDivideRawInteger))) SinkWhoDivideRawInteger(*this, value);
		return element[1];
	}

	const Step *WhoExpressDivide::pass(Runner &run, double value)
	{
		new (run.allocate(sizeof(SinkWhoDivideRawFloat))) SinkWhoDivideRawFloat(*this, value);
		return element[1];
	}

	const Step *WhoExpressDivide::pass(Runner &run, const Integer &value)
	{
		new (run.allocate(sizeof(SinkWhoDivideUncountedInteger))) SinkWhoDivideUncountedInteger(*this, value);
		return element[1];
	}

	const Step *WhoExpressDivide::pass(Runner &run, const Float &value)
	{
		new (run.allocate(sizeof(SinkWhoDivideUncountedFloat))) SinkWhoDivideUncountedFloat(*this, value);
		return element[1];
	}

	const Step *WhoExpressDivide::pass(Runner &run, const Integer *value)
	{
		new (run.allocate(sizeof(SinkWhoDivideInteger))) SinkWhoDivideInteger(*this, value);
		return element[1];
	}

	const Step *WhoExpressDivide::pass(Runner &run, const Float *value)
	{
		new (run.allocate(sizeof(SinkWhoDivideFloat))) SinkWhoDivideFloat(*this, value);
		return element[1];
	}

	const Step *WhoExpressDivide::pass(Runner &run, const Duration *value)
	{
		new (run.allocate(sizeof(SinkWhoDivideDuration))) SinkWhoDivideDuration(*this, value);
		return element[1];
	}

	const Step *SinkWhoDivideRawInteger::pass(Runner &run, long value)
	{
		double result = (double)value / operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideRawInteger::pass(Runner &run, double value)
	{
		double result = value / operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideRawInteger::pass(Runner &run, const Integer &value)
	{
		double result = (double)value.value / operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideRawInteger::pass(Runner &run, const Float &value)
	{
		double result = value.value / operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideRawInteger::pass(Runner &run, const Integer *value)
	{
		double result = (double)value->value / operand;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideRawInteger::pass(Runner &run, const Float *value)
	{
		double result = value->value / operand;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideRawInteger::pass(Runner &run, const Duration *value)
	{
		const Duration *result = Duration::get(value->value / operand);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideRawFloat::pass(Runner &run, long value)
	{
		double result = value / operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideRawFloat::pass(Runner &run, double value)
	{
		double result = value / operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideRawFloat::pass(Runner &run, const Integer &value)
	{
		double result = value.value / operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideRawFloat::pass(Runner &run, const Float &value)
	{
		double result = value.value / operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideRawFloat::pass(Runner &run, const Integer *value)
	{
		double result = value->value / operand;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideRawFloat::pass(Runner &run, const Float *value)
	{
		double result = value->value / operand;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideRawFloat::pass(Runner &run, const Duration *value)
	{
		const Duration *result = Duration::get((long long)(value->value / operand));
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideUncountedInteger::pass(Runner &run, long value)
	{
		double result = (double)value / ((const Integer&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideUncountedInteger::pass(Runner &run, double value)
	{
		double result = value / ((const Integer&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideUncountedInteger::pass(Runner &run, const Integer &value)
	{
		double result = (double)value.value / ((const Integer&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideUncountedInteger::pass(Runner &run, const Float &value)
	{
		double result = value.value / ((const Integer&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideUncountedInteger::pass(Runner &run, const Integer *value)
	{
		double result = (double)value->value / ((const Integer&)operand).value;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideUncountedInteger::pass(Runner &run, const Float *value)
	{
		double result = value->value / ((const Integer&)operand).value;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideUncountedInteger::pass(Runner &run, const Duration *value)
	{
		const Duration *result = Duration::get(value->value / ((const Integer&)operand).value);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideUncountedFloat::pass(Runner &run, long value)
	{
		double result = value / ((const Float&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideUncountedFloat::pass(Runner &run, double value)
	{
		double result = value / ((const Float&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideUncountedFloat::pass(Runner &run, const Integer *value)
	{
		double result = value->value / ((const Float&)operand).value;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideUncountedFloat::pass(Runner &run, const Float *value)
	{
		double result = value->value / ((const Float&)operand).value;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideUncountedFloat::pass(Runner &run, const Duration *value)
	{
		const Duration *result = Duration::get((long long)(value->value / ((const Float&)operand).value));
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideUncountedFloat::pass(Runner &run, const Integer &value)
	{
		double result = value.value / ((const Float&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideUncountedFloat::pass(Runner &run, const Float &value)
	{
		double result = value.value / ((const Float&)operand).value;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideUncountedDuration::pass(Runner &run, const Duration *value)
	{
		double result = (double)value->value / ((const Duration&)operand).value;
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideInteger::pass(Runner &run, long value)
	{
		double result = (double)value / ((const Integer*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideInteger::pass(Runner &run, double value)
	{
		double result = value / ((const Integer*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideInteger::pass(Runner &run, const Integer &value)
	{
		double result = (double)value.value / ((const Integer*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideInteger::pass(Runner &run, const Float &value)
	{
		double result = value.value / ((const Integer*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideInteger::pass(Runner &run, const Integer *value)
	{
		double result = (double)value->value / ((const Integer*)operand)->value;
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideInteger::pass(Runner &run, const Float *value)
	{
		double result = value->value / ((const Integer*)operand)->value;
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideInteger::pass(Runner &run, const Duration *value)
	{
		const Duration *result = Duration::get(value->value / ((const Integer*)operand)->value);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideFloat::pass(Runner &run, long value)
	{
		double result = value / ((const Float*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideFloat::pass(Runner &run, double value)
	{
		double result = value / ((const Float*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideFloat::pass(Runner &run, const Integer &value)
	{
		double result = value.value / ((const Float*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideFloat::pass(Runner &run, const Float &value)
	{
		double result = value.value / ((const Float*)operand)->value;
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideFloat::pass(Runner &run, const Integer *value)
	{
		double result = value->value / ((const Float*)operand)->value;
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideFloat::pass(Runner &run, const Float *value)
	{
		double result = value->value / ((const Float*)operand)->value;
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideFloat::pass(Runner &run, const Duration *value)
	{
		const Duration *result = Duration::get((long long)(value->value / ((const Float*)operand)->value));
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoDivideDuration::pass(Runner &run, const Duration *value)
	{
		double result = value->value / (double)((const Duration *)operand)->value;
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const NodeConstantShort *BuiltinClicheOperationIntegerDivide::newNode(const HashedConstant *&link, const Integer *value) const
	{
		return new
			(Heap::allocate(sizeof(OperationIntegerDivideInteger)))
			OperationIntegerDivideInteger(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationIntegerDivide::newNode(const HashedConstant *&link, const Float *value) const
	{
		return new
			(Heap::allocate(sizeof(OperationIntegerDivideFloat)))
			OperationIntegerDivideFloat(link, value);
	}

	const CallWho *OperationIntegerDivideInteger::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoIntegerDivideInteger)))
			WhoIntegerDivideInteger(this, who);
	}

	const CallWho *OperationIntegerDivideFloat::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoIntegerDivideFloat)))
			WhoIntegerDivideFloat(this, who);
	}

	const CallWho *OperationIntegerDivideDuration::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoIntegerDivideDuration)))
			WhoIntegerDivideDuration(this, who);
	}

	const Step *WhoIntegerDivideInteger::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoIntegerDivideUncountedInteger)))
			SinkWhoIntegerDivideUncountedInteger(*this, *(const Integer*)((const NodeConstantShort*)element[0])->element[0]);
		return whoAttribute();
	}

	const Step *WhoIntegerDivideFloat::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoIntegerDivideUncountedFloat)))
			SinkWhoIntegerDivideUncountedFloat(*this, *(const Float*)((const NodeConstantShort*)element[0])->element[0]);
		return whoAttribute();
	}

	const Step *WhoIntegerDivideDuration::step_(Runner &run) const
	{
		const Duration *operand = (const Duration*)((const NodeConstantShort*)element[0])->element[0];
		new (run.allocate(sizeof(SinkWhoIntegerDivideUncountedDuration)))
			SinkWhoIntegerDivideUncountedDuration(*this, *operand);
		return whoAttribute();
	}

	const CallWho *BuiltinClicheOperationIntegerDivide::whoOperation(const NodeExpressShort *operation, const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoExpressIntegerDivide)))
			WhoExpressIntegerDivide(operation, who);
	}

	const NodeConstantShort *BuiltinClicheOperationIntegerDivide::newNode(const HashedConstant *&link, const Duration *value) const
	{
		return new
			(Heap::allocate(sizeof(OperationIntegerDivideDuration)))
			OperationIntegerDivideDuration(link, value);
	}

	const Step *WhoExpressIntegerDivide::pass(Runner &run, long value)
	{
		new (run.allocate(sizeof(SinkWhoIntegerDivideRawInteger))) SinkWhoIntegerDivideRawInteger(*this, value);
		return element[1];
	}

	const Step *WhoExpressIntegerDivide::pass(Runner &run, double value)
	{
		new (run.allocate(sizeof(SinkWhoIntegerDivideRawFloat))) SinkWhoIntegerDivideRawFloat(*this, value);
		return element[1];
	}

	const Step *WhoExpressIntegerDivide::pass(Runner &run, const Integer &value)
	{
		new (run.allocate(sizeof(SinkWhoIntegerDivideUncountedInteger))) SinkWhoIntegerDivideUncountedInteger(*this, value);
		return element[1];
	}

	const Step *WhoExpressIntegerDivide::pass(Runner &run, const Float &value)
	{
		new (run.allocate(sizeof(SinkWhoIntegerDivideUncountedFloat))) SinkWhoIntegerDivideUncountedFloat(*this, value);
		return element[1];
	}

	const Step *WhoExpressIntegerDivide::pass(Runner &run, const Integer *value)
	{
		new (run.allocate(sizeof(SinkWhoIntegerDivideInteger))) SinkWhoIntegerDivideInteger(*this, value);
		return element[1];
	}

	const Step *WhoExpressIntegerDivide::pass(Runner &run, const Float *value)
	{
		new (run.allocate(sizeof(SinkWhoIntegerDivideFloat))) SinkWhoIntegerDivideFloat(*this, value);
		return element[1];
	}

	const Step *WhoExpressIntegerDivide::pass(Runner &run, const Duration *value)
	{
		new (run.allocate(sizeof(SinkWhoIntegerDivideDuration))) SinkWhoIntegerDivideDuration(*this, value);
		return element[1];
	}

	const Step *SinkWhoIntegerDivideRawInteger::pass(Runner &run, long value)
	{
		long result = value / operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideRawInteger::pass(Runner &run, double value)
	{
		double result = value / operand;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideRawInteger::pass(Runner &run, const Integer &value)
	{
		double result = (double)value.value / operand;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideRawInteger::pass(Runner &run, const Float &value)
	{
		double result = value.value / operand;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideRawInteger::pass(Runner &run, const Integer *value)
	{
		double result = (double)value->value / operand;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideRawInteger::pass(Runner &run, const Float *value)
	{
		double result = value->value / operand;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideRawFloat::pass(Runner &run, long value)
	{
		double result = value / operand;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideRawFloat::pass(Runner &run, double value)
	{
		double result = value / operand;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideRawFloat::pass(Runner &run, const Integer &value)
	{
		double result = value.value / operand;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideRawFloat::pass(Runner &run, const Float &value)
	{
		double result = value.value / operand;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideRawFloat::pass(Runner &run, const Integer *value)
	{
		double result = value->value / operand;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideRawFloat::pass(Runner &run, const Float *value)
	{
		double result = value->value / operand;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideUncountedInteger::pass(Runner &run, long value)
	{
		double result = (double)value / ((const Integer&)operand).value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideUncountedInteger::pass(Runner &run, double value)
	{
		double result = value / ((const Integer&)operand).value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideUncountedInteger::pass(Runner &run, const Integer &value)
	{
		double result = (double)value.value / ((const Integer&)operand).value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideUncountedInteger::pass(Runner &run, const Float &value)
	{
		double result = value.value / ((const Integer&)operand).value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideUncountedInteger::pass(Runner &run, const Integer *value)
	{
		double result = (double)value->value / ((const Integer&)operand).value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideUncountedInteger::pass(Runner &run, const Float *value)
	{
		double result = value->value / ((const Integer&)operand).value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideUncountedFloat::pass(Runner &run, long value)
	{
		double result = value / ((const Float&)operand).value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideUncountedFloat::pass(Runner &run, double value)
	{
		double result = value / ((const Float&)operand).value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideUncountedFloat::pass(Runner &run, const Integer *value)
	{
		double result = value->value / ((const Float&)operand).value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideUncountedFloat::pass(Runner &run, const Float *value)
	{
		double result = value->value / ((const Float&)operand).value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideUncountedFloat::pass(Runner &run, const Integer &value)
	{
		double result = value.value / ((const Float&)operand).value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideUncountedFloat::pass(Runner &run, const Float &value)
	{
		double result = value.value / ((const Float&)operand).value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideUncountedDuration::pass(Runner &run, const Duration *value)
	{
		double result = (double)(value->value / ((const Duration&)operand).value);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideInteger::pass(Runner &run, long value)
	{
		double result = (double)value / ((const Integer*)operand)->value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideInteger::pass(Runner &run, double value)
	{
		double result = value / ((const Integer*)operand)->value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideInteger::pass(Runner &run, const Integer &value)
	{
		double result = (double)value.value / ((const Integer*)operand)->value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideInteger::pass(Runner &run, const Float &value)
	{
		double result = value.value / ((const Integer*)operand)->value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideInteger::pass(Runner &run, const Integer *value)
	{
		double result = (double)value->value / ((const Integer*)operand)->value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideInteger::pass(Runner &run, const Float *value)
	{
		double result = value->value / ((const Integer*)operand)->value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideFloat::pass(Runner &run, long value)
	{
		double result = value / ((const Float*)operand)->value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideFloat::pass(Runner &run, double value)
	{
		double result = value / ((const Float*)operand)->value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideFloat::pass(Runner &run, const Integer &value)
	{
		double result = value.value / ((const Float*)operand)->value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideFloat::pass(Runner &run, const Float &value)
	{
		double result = value.value / ((const Float*)operand)->value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideFloat::pass(Runner &run, const Integer *value)
	{
		double result = value->value / ((const Float*)operand)->value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideFloat::pass(Runner &run, const Float *value)
	{
		double result = value->value / ((const Float*)operand)->value;
		if (result >= 0) result = floor(result);
		else result = -floor(-result);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoIntegerDivideDuration::pass(Runner &run, const Duration *value)
	{
		double result = (double)(value->value / ((const Duration*)operand)->value);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const NodeConstantShort *BuiltinClicheOperationModulo::newNode(const HashedConstant *&link, const Integer *value) const
	{
		return new
			(Heap::allocate(sizeof(OperationModuloInteger)))
			OperationModuloInteger(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationModulo::newNode(const HashedConstant *&link, const Float *value) const
	{
		return new
			(Heap::allocate(sizeof(OperationModuloFloat)))
			OperationModuloFloat(link, value);
	}

	const CallWho *OperationModuloInteger::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoModuloInteger)))
			WhoModuloInteger(this, who);
	}

	const CallWho *OperationModuloFloat::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoModuloFloat)))
			WhoModuloFloat(this, who);
	}

	const Step *WhoModuloInteger::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoModuloUncountedInteger)))
			SinkWhoModuloUncountedInteger(*this, *(const Integer*)((const NodeConstantShort*)element[0])->element[0]);
		return whoAttribute();
	}

	const Step *WhoModuloFloat::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoModuloUncountedFloat)))
			SinkWhoModuloUncountedFloat(*this, *(const Float*)((const NodeConstantShort*)element[0])->element[0]);
		return whoAttribute();
	}

	const CallWho *BuiltinClicheOperationModulo::whoOperation(const NodeExpressShort *operation, const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoExpressModulo)))
			WhoExpressModulo(operation, who);
	}

	const Step *WhoExpressModulo::pass(Runner &run, long value)
	{
		new (run.allocate(sizeof(SinkWhoModuloRawInteger))) SinkWhoModuloRawInteger(*this, value);
		return element[1];
	}

	const Step *WhoExpressModulo::pass(Runner &run, double value)
	{
		new (run.allocate(sizeof(SinkWhoModuloRawFloat))) SinkWhoModuloRawFloat(*this, value);
		return element[1];
	}

	const Step *WhoExpressModulo::pass(Runner &run, const Integer &value)
	{
		new (run.allocate(sizeof(SinkWhoModuloUncountedInteger))) SinkWhoModuloUncountedInteger(*this, value);
		return element[1];
	}

	const Step *WhoExpressModulo::pass(Runner &run, const Float &value)
	{
		new (run.allocate(sizeof(SinkWhoModuloUncountedFloat))) SinkWhoModuloUncountedFloat(*this, value);
		return element[1];
	}

	const Step *WhoExpressModulo::pass(Runner &run, const Integer *value)
	{
		new (run.allocate(sizeof(SinkWhoModuloInteger))) SinkWhoModuloInteger(*this, value);
		return element[1];
	}

	const Step *WhoExpressModulo::pass(Runner &run, const Float *value)
	{
		new (run.allocate(sizeof(SinkWhoModuloFloat))) SinkWhoModuloFloat(*this, value);
		return element[1];
	}

	const Step *SinkWhoModuloRawInteger::pass(Runner &run, long value)
	{
		long result = value % operand;
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloRawInteger::pass(Runner &run, double value)
	{
		double result = fmod(value, operand);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloRawInteger::pass(Runner &run, const Integer &value)
	{
		double result = fmod((double)value.value, operand);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloRawInteger::pass(Runner &run, const Float &value)
	{
		double result = fmod(value.value, operand);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloRawInteger::pass(Runner &run, const Integer *value)
	{
		double result = fmod((double)value->value, operand);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloRawInteger::pass(Runner &run, const Float *value)
	{
		double result = fmod(value->value, operand);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloRawFloat::pass(Runner &run, long value)
	{
		double result = fmod(value, operand);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloRawFloat::pass(Runner &run, double value)
	{
		double result = fmod(value, operand);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloRawFloat::pass(Runner &run, const Integer &value)
	{
		double result = fmod(value.value, operand);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloRawFloat::pass(Runner &run, const Float &value)
	{
		double result = fmod(value.value, operand);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloRawFloat::pass(Runner &run, const Integer *value)
	{
		double result = fmod(value->value, operand);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloRawFloat::pass(Runner &run, const Float *value)
	{
		double result = fmod(value->value, operand);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloUncountedInteger::pass(Runner &run, long value)
	{
		double result = fmod((double)value, ((const Integer&)operand).value);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloUncountedInteger::pass(Runner &run, double value)
	{
		double result = fmod(value, ((const Integer&)operand).value);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloUncountedInteger::pass(Runner &run, const Integer &value)
	{
		double result = fmod((double)value.value, ((const Integer&)operand).value);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloUncountedInteger::pass(Runner &run, const Float &value)
	{
		double result = fmod(value.value, ((const Integer&)operand).value);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloUncountedInteger::pass(Runner &run, const Integer *value)
	{
		double result = fmod((double)value->value, ((const Integer&)operand).value);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloUncountedInteger::pass(Runner &run, const Float *value)
	{
		double result = fmod(value->value, ((const Integer&)operand).value);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloUncountedFloat::pass(Runner &run, long value)
	{
		double result = fmod(value, ((const Float&)operand).value);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloUncountedFloat::pass(Runner &run, double value)
	{
		double result = fmod(value, ((const Float&)operand).value);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloUncountedFloat::pass(Runner &run, const Integer *value)
	{
		double result = fmod(value->value, ((const Float&)operand).value);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloUncountedFloat::pass(Runner &run, const Float *value)
	{
		double result = fmod(value->value, ((const Float&)operand).value);
		value->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloUncountedFloat::pass(Runner &run, const Integer &value)
	{
		double result = fmod(value.value, ((const Float&)operand).value);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloUncountedFloat::pass(Runner &run, const Float &value)
	{
		double result = fmod(value.value, ((const Float&)operand).value);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloInteger::pass(Runner &run, long value)
	{
		double result = fmod((double)value, ((const Integer*)operand)->value);
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloInteger::pass(Runner &run, double value)
	{
		double result = fmod(value, ((const Integer*)operand)->value);
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloInteger::pass(Runner &run, const Integer &value)
	{
		double result = fmod((double)value.value, ((const Integer*)operand)->value);
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloInteger::pass(Runner &run, const Float &value)
	{
		double result = fmod(value.value, ((const Integer*)operand)->value);
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloInteger::pass(Runner &run, const Integer *value)
	{
		double result = fmod((double)value->value, ((const Integer*)operand)->value);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloInteger::pass(Runner &run, const Float *value)
	{
		double result = fmod(value->value, ((const Integer*)operand)->value);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloFloat::pass(Runner &run, long value)
	{
		double result = fmod(value, ((const Float*)operand)->value);
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloFloat::pass(Runner &run, double value)
	{
		double result = fmod(value, ((const Float*)operand)->value);
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloFloat::pass(Runner &run, const Integer &value)
	{
		double result = fmod(value.value, ((const Float*)operand)->value);
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloFloat::pass(Runner &run, const Float &value)
	{
		double result = fmod(value.value, ((const Float*)operand)->value);
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloFloat::pass(Runner &run, const Integer *value)
	{
		double result = fmod(value->value, ((const Float*)operand)->value);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *SinkWhoModuloFloat::pass(Runner &run, const Float *value)
	{
		double result = fmod(value->value, ((const Float*)operand)->value);
		value->releaseReference();
		operand->releaseReference();
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	SinkTimescale *Sink::as_SinkTimescale()
	{
		return NULL;
	}

	SinkTimescale *SinkTimescale::as_SinkTimescale() const
	{
		return NULL;
	}

	const CallWho *PropertyHexadecimal::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoPropertyHexadecimal))) const WhoPropertyHexadecimal(this, who);
	}

	const Step *WhoPropertyHexadecimal::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkPropertyHexadecimal))) SinkPropertyHexadecimal(*this);
		return whoAttribute();
	}

	const Step *SinkPropertyHexadecimal::pass(Runner &run, const Integer *value)
	{
		long v = value->value;
		value->releaseReference();
		PILS_CHAR buffer[10] = {'0', 'x'};
		for (int i = 7; i >= 0; i--)
			buffer[9 - i] = "0123456789abcdef"[0xf & v >> i * 4];
		const PilsString *result = PilsString::get(buffer, 10);
		run.sink = this + 1;
		return run.sink->pass(run, result);
	}

	const Step *BuiltinClicheRound::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		if (const Constant *constant = value->as_Constant())
		{
			new (run.allocate(sizeof(SinkRound))) SinkRound(what, constant);
		}
		else
		{
			new (run.allocate(sizeof(SinkWho))) SinkWho(what, node(value));
		}
		return what.whoAttribute();
	}

	const Step *BuiltinClicheTruncate::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		if (const Constant *constant = value->as_Constant())
		{
			new (run.allocate(sizeof(SinkTruncate))) SinkTruncate(what, constant);
		}
		else
		{
			new (run.allocate(sizeof(SinkWho))) SinkWho(what, node(value));
		}
		return what.whoAttribute();
	}

	double abs(double n) {return n < 0 ? -n : n;}
	double round(double n) {return (double)(n < 0 ? (long long)(n - 0.5):(long long)(n + 0.5));}
	double truncate(double n) {return (double)(long long)n;}

	const Step *SinkRound::pass(Runner &run, const Integer *value)
	{
		double unit;
		if (operand->isNumber(unit) && unit != 0)
		{
			double result = round(value->value / unit) * unit;
			value->releaseReference();
			return (run.sink = kick(run))->pass(run, result);
		}
		else return pass(run, (const Any *)value);
	}

	const Step *SinkRound::pass(Runner &run, const Float *value)
	{
		double unit;
		if (operand->isNumber(unit) && unit > 0)
		{
			double result = round(value->value / unit) * unit;
			value->releaseReference();
			return (run.sink = kick(run))->pass(run, result);
		}
		else return pass(run, (const Any *)value);
	}

	const Step *SinkRound::pass(Runner &run, const Timestamp *value)
	{
		const Duration *unit = operand->as_Duration();
		if (unit && unit->value > 0)
		{
			long long time = value->value;
			bool negative = time < 0;
			if (negative)
			{
				time = -time;
			}
			time += unit->value / 2;
			time -= time % unit->value;
			if (negative)
			{
				time = -time;
			}
			value->releaseReference();
			return (run.sink = kick(run))->pass(run, Timestamp::get(time));
		}
		else return pass(run, (const Any *)value);
	}

	const Step *SinkRound::pass(Runner &run, const PilsDate *value)
	{
		const Duration *unit = operand->as_Duration();
		if (unit && unit->value > 0)
		{
			long long time = value->value;
			bool negative = time < 0;
			if (negative)
			{
				time = -time;
			}
			time += unit->value / 2;
			time -= time % unit->value;
			if (negative)
			{
				time = -time;
			}
			value->releaseReference();
			return (run.sink = kick(run))->pass(run, PilsDate::get(time));
		}
		else return pass(run, (const Any *)value);
	}

	const Step *SinkRound::pass(Runner &run, const Duration *value)
	{
		const Duration *unit = operand->as_Duration();
		if (unit && unit->value > 0)
		{
			long long time = value->value;
			bool negative = time < 0;
			if (negative)
			{
				time = -time;
			}
			time += unit->value / 2;
			time -= time % unit->value;
			if (negative)
			{
				time = -time;
			}
			value->releaseReference();
			return (run.sink = kick(run))->pass(run, Duration::get(time));
		}
		else return pass(run, (const Any *)value);
	}

	const Step *SinkTruncate::pass(Runner &run, const Integer *value)
	{
		double unit;
		if (operand->isNumber(unit) && unit != 0)
		{
			double result = truncate(value->value / unit) * unit;
			value->releaseReference();
			return (run.sink = kick(run))->pass(run, result);
		}
		else return pass(run, (const Any *)value);
	}

	const Step *SinkTruncate::pass(Runner &run, const Float *value)
	{
		double unit;
		if (operand->isNumber(unit) && unit > 0)
		{
			double result = truncate(value->value / unit) * unit;
			value->releaseReference();
			return (run.sink = kick(run))->pass(run, result);
		}
		else return pass(run, (const Any *)value);
	}

	const Step *SinkTruncate::pass(Runner &run, const Timestamp *value)
	{
		const Duration *unit = operand->as_Duration();
		if (unit && unit->value > 0)
		{
			long long time = value->value;
			time -= time % unit->value;
			value->releaseReference();
			return (run.sink = kick(run))->pass(run, Timestamp::get(time));
		}
		else return pass(run, (const Any *)value);
	}

	const Step *SinkTruncate::pass(Runner &run, const PilsDate *value)
	{
		const Duration *unit = operand->as_Duration();
		if (unit && unit->value > 0)
		{
			long long time = value->value;
			time -= time % unit->value;
			value->releaseReference();
			return (run.sink = kick(run))->pass(run, PilsDate::get(time));
		}
		else return pass(run, (const Any *)value);
	}

	const Step *SinkTruncate::pass(Runner &run, const Duration *value)
	{
		const Duration *unit = operand->as_Duration();
		if (unit && unit->value > 0)
		{
			long long time = value->value;
			time -= time % unit->value;
			value->releaseReference();
			return (run.sink = kick(run))->pass(run, Duration::get(time));
		}
		else return pass(run, (const Any *)value);
	}

	const CallWho *PropertyLocalTime::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoPropertyLocalTime))) const WhoPropertyLocalTime(this, who);
	}

	const CallWho *PropertyGreenwichMeanTime::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoPropertyGreenwichMeanTime))) const WhoPropertyGreenwichMeanTime(this, who);
	}

	const Step *WhoPropertyLocalTime::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkPropertyLocalTime))) SinkPropertyLocalTime(*this);
		return whoAttribute();
	}

	const Step *WhoPropertyGreenwichMeanTime::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkPropertyGreenwichMeanTime))) SinkPropertyGreenwichMeanTime(*this);
		return whoAttribute();
	}

	const Step *SinkPropertyGreenwichMeanTime::pass(Runner &run, const PilsDate *value)
	{
		const Timestamp *result = Timestamp::get(value->value);
		value->releaseReference();
		return (run.sink = kick(run))->pass(run, result);
	}

	const Step *SinkPropertyGreenwichMeanTime::pass(Runner &run, const Timestamp *value)
	{
		const PilsDate *result = PilsDate::get(value->value);
		value->releaseReference();
		run.sink = kick(run);
		return (run.sink = kick(run))->pass(run, result);
	}

	const Step *SinkPropertyLocalTime::pass(Runner &run, const PilsDate *value)
	{
		PilsDate::Split local;
		local.put(value->value);
		value->releaseReference();
		run.sink = kick(run);
		const Timestamp *result = Timestamp::get(local.getTimestampFromLocalTime());
		return (run.sink = kick(run))->pass(run, result);
	}

	const Step *SinkPropertyLocalTime::pass(Runner &run, const Timestamp *value)
	{
		Timestamp::Split stamp;
		stamp.put(value->value);
		value->releaseReference();
		stamp.zoneSecond = 0;
		const PilsDate *result = PilsDate::get(stamp.get());
		return (run.sink = kick(run))->pass(run, result);
	}
}
