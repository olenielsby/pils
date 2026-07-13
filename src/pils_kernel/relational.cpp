/* This file is public domain */
#include "relational.h"
namespace PILS
{
	const Step *Sink::falseCompare(Runner &run, const Express &what, Sink &next)
	{
		new (run.allocate(sizeof(MissCall))) MissCall(what);
		run.calling.what = &what;
		return next.miss(run);
	}

	const Step *SinkWhoCompareRawInteger::miss(Runner &run)
	{
		Sink &next = this[1];
		return next.miss(run);
	}

	const Step *SinkWhoCompareRawFloat::miss(Runner &run)
	{
		Sink &next = this[1];
		return next.miss(run);
	}

	const Step *SinkWhoCompareAny::miss(Runner &run)
	{
		Sink &next = this[1];
		return next.miss(run);
	}

	const Step *SinkWhoCompareUncounted::miss(Runner &run)
	{
		Sink &next = this[1];
		return next.miss(run);
	}

	const Step *SinkCompareIntegerRaw::miss(Runner &run)
	{
		Sink &next = this[1];
		return next.miss(run);
	}

	const Step *SinkCompareFloatRaw::miss(Runner &run)
	{
		Sink &next = this[1];
		return next.miss(run);
	}

	const Step *SinkCompareConstant::miss(Runner &run)
	{
		Sink &next = this[1];
		return next.miss(run);
	}

	const NodeConstantShort *BuiltinClicheOperationEqual::newNode(const Constant *&link, const Integer *value) const
	{
        return new const OperationEqualInteger(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationEqual::newNode(const Constant *&link, const Float *value) const
	{
        return new const OperationEqualFloat(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationEqual::newNode(const Constant *&link, const PilsString *value) const
	{
        return new const OperationEqualString(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationEqual::newNode(const Constant *&link, const PilsColor *value) const
	{
        return new const OperationEqualConstant(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationEqual::newNode(const Constant *&link, const Timestamp *value) const
	{
        return new const OperationEqualConstant(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationEqual::newNode(const Constant *&link, const Duration *value) const
	{
        return new const OperationEqualConstant(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationEqual::newNode(const Constant *&link, const PilsDate *value) const
	{
        return new const OperationEqualConstant(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationEqual::newNode(const Constant *&link, const Cliche *value) const
	{
        return new const OperationEqualConstant(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationEqual::newNode(const Constant *&link, const ListConstant *value) const
	{
        return new const OperationEqualConstant(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationEqual::newNode(const Constant *&link, const NodeConstant *value) const
	{
        return new const OperationEqualConstant(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationEqual::newNode(const Constant *&link, const Special *value) const
	{
        return new const OperationEqualConstant(link, value);
	}

	const CallWho *BuiltinClicheOperationEqual::whoOperation(const NodeExpressShort *operation, const Any *who) const
	{
        return new const WhoExpressEqual(operation, who);
	}

	const CallWho *OperationEqualConstant::callWho(const Any *who) const
	{
        return new const WhoEqualConstant(this, who);
	}

	const CallWho *OperationEqualInteger::callWho(const Any *who) const
	{
        return new const WhoEqualInteger(this, who);
	}

	const CallWho *OperationEqualFloat::callWho(const Any *who) const
	{
        return new const WhoEqualFloat(this, who);
	}

	const CallWho *OperationEqualString::callWho(const Any *who) const
	{
        return new const WhoEqualString(this, who);
	}

	const Step *WhoEqualConstant::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoEqualUncountedConstant)))
			SinkWhoEqualUncountedConstant(*this, *((const NodeConstantShort*)element[0])->element[0]);
		return whoAttribute();
	}

	void WhoEqualConstant::compilePattern(Compiling &compiling) const
	{
		((const OperationEqualString*)callAttribute())->element[0]->compilePattern(compiling);
		whoAttribute()->compilePattern(compiling);
	}

	const Step *WhoEqualInteger::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoEqualUncountedInteger)))
			SinkWhoEqualUncountedInteger(*this, *(const Integer*)((const NodeConstantShort*)element[0])->element[0]);
		return whoAttribute();
	}

	const Step *WhoEqualFloat::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoEqualUncountedFloat)))
			SinkWhoEqualUncountedFloat(*this, *(const Float*)((const NodeConstantShort*)element[0])->element[0]);
		return whoAttribute();
	}

	const Step *WhoEqualString::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoEqualUncountedString)))
			SinkWhoEqualUncountedString(*this, *(const PilsString*)((const NodeConstantShort*)element[0])->element[0]);
		return whoAttribute();
	}

	const Step *WhoExpressEqual::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkEqualOperand))) SinkEqualOperand(*this);
		return ((const NodeExpressShort*)element[0])->element[0];
	}

	void WhoExpressEqual::compilePattern(Compiling &compiling) const
	{
		((const NodeExpressShort*)callAttribute())->element[0]->compilePattern(compiling);
		whoAttribute()->compilePattern(compiling);
	}


	const Step *SinkEqualOperand::pass(Runner &run, long value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualRawInteger))) SinkWhoEqualRawInteger(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, double value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualRawFloat))) SinkWhoEqualRawFloat(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const Integer &value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualUncountedInteger))) SinkWhoEqualUncountedInteger(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const Float &value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualUncountedFloat))) SinkWhoEqualUncountedFloat(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const PilsString &value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualUncountedString))) SinkWhoEqualUncountedString(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const Cliche &value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualUncountedConstant))) SinkWhoEqualUncountedConstant(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const ListConstant &value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualUncountedConstant))) SinkWhoEqualUncountedConstant(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const NodeConstantShort &value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualUncountedConstant))) SinkWhoEqualUncountedConstant(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const NodeConstantLong &value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualUncountedConstant))) SinkWhoEqualUncountedConstant(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const Special &value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualUncountedConstant))) SinkWhoEqualUncountedConstant(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const ListExpress &value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualUncountedExpress))) SinkWhoEqualUncountedExpress(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const NodeExpressShort &value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualUncountedExpress))) SinkWhoEqualUncountedExpress(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const NodeExpressLong &value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualUncountedExpress))) SinkWhoEqualUncountedExpress(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const Integer *value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualInteger))) SinkWhoEqualInteger(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const Float *value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualFloat))) SinkWhoEqualFloat(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const PilsString *value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualString))) SinkWhoEqualString(what, value);
		return what.element[1];
	}
	
	const Step *SinkEqualOperand::pass(Runner &run, const Timestamp *value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualConstant))) SinkWhoEqualConstant(what, value);
		return what.element[1];
	}
	
	const Step *SinkEqualOperand::pass(Runner &run, const Duration *value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualConstant))) SinkWhoEqualConstant(what, value);
		return what.element[1];
	}
	
	const Step *SinkEqualOperand::pass(Runner &run, const PilsDate *value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualConstant))) SinkWhoEqualConstant(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const Cliche *value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualConstant))) SinkWhoEqualConstant(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const ListConstant *value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualConstant))) SinkWhoEqualConstant(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const NodeConstantShort *value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualConstant))) SinkWhoEqualConstant(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const NodeConstantLong *value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualConstant))) SinkWhoEqualConstant(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const Special *value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualConstant))) SinkWhoEqualConstant(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const ListExpress *value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualExpress))) SinkWhoEqualExpress(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const NodeExpressShort *value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualExpress))) SinkWhoEqualExpress(what, value);
		return what.element[1];
	}

	const Step *SinkEqualOperand::pass(Runner &run, const NodeExpressLong *value)
	{
		WhoExpressEqual &what = (WhoExpressEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoEqualExpress))) SinkWhoEqualExpress(what, value);
		return what.element[1];
	}

	const Step *SinkWhoEqualRawInteger::pass(Runner &run, long value)
	{
		if (value == operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualRawInteger::pass(Runner &run, double value)
	{
		if (value == operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}
	
	const Step *SinkWhoEqualRawInteger::pass(Runner &run, const Integer &value)
	{
		if (value.value == operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualRawInteger::pass(Runner &run, const Float &value)
	{
		if (value.value == operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualRawInteger::pass(Runner &run, const PilsString &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualRawInteger::pass(Runner &run, const Integer *value)
	{
		if (value->value == operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualRawInteger::pass(Runner &run, const Float *value)
	{
		if(value->value == operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualRawInteger::pass(Runner &run, const PilsString *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualRawInteger::pass(Runner &run, const Any *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualRawFloat::pass(Runner &run, long value)
	{
		if (value == operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualRawFloat::pass(Runner &run, double value)
	{
		if (value == operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}
	
	const Step *SinkWhoEqualRawFloat::pass(Runner &run, const Integer &value)
	{
		if (value.value == operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualRawFloat::pass(Runner &run, const Float &value)
	{
		if (value.value == operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualRawFloat::pass(Runner &run, const PilsString &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualRawFloat::pass(Runner &run, const Integer *value)
	{
		if (value->value == operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualRawFloat::pass(Runner &run, const Float *value)
	{
		if (value->value == operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualRawFloat::pass(Runner &run, const PilsString *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualRawFloat::pass(Runner &run, const Any *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, long value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, double value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const Integer &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const Float &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const PilsString &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const Cliche &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const ListConstant &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const NodeConstantShort &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const NodeConstantLong &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const Special &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const ListExpress &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const NodeExpressShort &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const NodeExpressLong &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const Integer *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const Float *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const PilsString *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const Timestamp *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const Duration *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const PilsDate *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const Cliche *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const ListConstant *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const NodeConstantShort *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const NodeConstantLong *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const Special *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const ListExpress *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const NodeExpressShort *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const NodeExpressLong *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedBad::pass(Runner &run, const Any *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedConstant::pass(Runner &run, const Cliche &value)
	{
		if (&value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedConstant::pass(Runner &run, const ListConstant &value)
	{
		if (&value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedConstant::pass(Runner &run, const NodeConstantShort &value)
	{
		if (&value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedConstant::pass(Runner &run, const NodeConstantLong &value)
	{
		if (&value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedConstant::pass(Runner &run, const Special &value)
	{
		if (&value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedConstant::pass(Runner &run, const Timestamp *value)
	{
		if (value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualUncountedConstant::pass(Runner &run, const Duration *value)
	{
		if (value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualUncountedConstant::pass(Runner &run, const PilsDate *value)
	{
		if (value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualUncountedConstant::pass(Runner &run, const Cliche *value)
	{
		if (value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualUncountedConstant::pass(Runner &run, const ListConstant *value)
	{
		if (value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualUncountedConstant::pass(Runner &run, const NodeConstantShort *value)
	{
		if (value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualUncountedConstant::pass(Runner &run, const NodeConstantLong *value)
	{
		if (value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualUncountedConstant::pass(Runner &run, const Special *value)
	{
		if (value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualUncountedInteger::pass(Runner &run, long value)
	{
		if (value == ((const Integer &)operand).value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedInteger::pass(Runner &run, double value)
	{
		if (value == ((const Integer &)operand).value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedInteger::pass(Runner &run, const Integer &value)
	{
		if (&value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedInteger::pass(Runner &run, const Integer *value)
	{
		if (value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualUncountedFloat::pass(Runner &run, double value)
	{
		if (value == ((const Float&)operand).value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedFloat::pass(Runner &run, const Float &value)
	{
		if (&value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedFloat::pass(Runner &run, const Float *value)
	{
		if (value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualUncountedString::pass(Runner &run, const PilsString &value)
	{
		if (&value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedString::pass(Runner &run, const PilsString *value)
	{
		if (value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualUncountedExpress::pass(Runner &run, const ListExpress &value)
	{
		if (&value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedExpress::pass(Runner &run, const NodeExpressShort &value)
	{
		if (&value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedExpress::pass(Runner &run, const NodeExpressLong &value)
	{
		if (&value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualUncountedExpress::pass(Runner &run, const ListExpress *value)
	{
		if (value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualUncountedExpress::pass(Runner &run, const NodeExpressShort *value)
	{
		if (value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualUncountedExpress::pass(Runner &run, const NodeExpressLong *value)
	{
		if (value == &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}


	const Step *SinkWhoEqualBad::pass(Runner &run, long value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, double value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const Integer &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const Float &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const PilsString &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const Cliche &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const ListConstant &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const NodeConstantShort &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const NodeConstantLong &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const Special &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const ListExpress &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const NodeExpressShort &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const NodeExpressLong &value)
	{
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const Integer *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const Float *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const PilsString *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const Timestamp *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const Duration *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const PilsDate *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const Any *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const Cliche *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const ListConstant *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const NodeConstantShort *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const NodeConstantLong *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const Special *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const ListExpress *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const NodeExpressShort *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualBad::pass(Runner &run, const NodeExpressLong *value)
	{
        run.release(value);
		return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualInteger::pass(Runner &run, long value)
	{
		if (((const Integer*)operand)->value == value)
			return (run.sink = this + 1)->pass(run, (const Integer*)operand);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualInteger::pass(Runner &run, double value)
	{
		if (((const Integer*)operand)->value == value)
			return (run.sink = this + 1)->pass(run, (const Integer*)operand);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualInteger::pass(Runner &run, const Integer &value)
	{
		if (operand == &value)
			return (run.sink = this + 1)->pass(run, &value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualInteger::pass(Runner &run, const Integer *value)
	{
		if (operand == value)
		{
			operand->unduplicateReference();
			return (run.sink = this + 1)->pass(run, value);
		}
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualFloat::pass(Runner &run, double value)
	{
		if (((const Float*)operand)->value == value)
			return (run.sink = this + 1)->pass(run, (const Float*)operand);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualFloat::pass(Runner &run, const Float &value)
	{
		if (operand == &value)
			return (run.sink = this + 1)->pass(run, &value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualFloat::pass(Runner &run, const Float *value)
	{
		if (operand == value)
		{
			operand->unduplicateReference();
			return (run.sink = this + 1)->pass(run, value);
		}
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualString::pass(Runner &run, const PilsString &value)
	{
		if (operand == &value)
			return (run.sink = this + 1)->pass(run, &value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualString::pass(Runner &run, const PilsString *value)
	{
		if (operand == value)
		{
			operand->unduplicateReference();
			return (run.sink = this + 1)->pass(run, value);
		}
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualConstant::pass(Runner &run, const Cliche &value)
	{
		if (operand == &value)
			return (run.sink = this + 1)->pass(run, &value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualConstant::pass(Runner &run, const ListConstant &value)
	{
		if (operand == &value)
			return (run.sink = this + 1)->pass(run, &value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualConstant::pass(Runner &run, const NodeConstantShort &value)
	{
		if (operand == &value)
			return (run.sink = this + 1)->pass(run, &value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualConstant::pass(Runner &run, const NodeConstantLong &value)
	{
		if (operand == &value)
			return (run.sink = this + 1)->pass(run, &value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualConstant::pass(Runner &run, const Special &value)
	{
		if (operand == &value)
			return (run.sink = this + 1)->pass(run, &value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualConstant::pass(Runner &run, const Timestamp *value)
	{
		if (operand == value)
		{
			operand->unduplicateReference();
			return (run.sink = this + 1)->pass(run, value);
		}
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualConstant::pass(Runner &run, const Duration *value)
	{
		if (operand == value)
		{
			operand->unduplicateReference();
			return (run.sink = this + 1)->pass(run, value);
		}
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualConstant::pass(Runner &run, const PilsDate *value)
	{
		if (operand == value)
		{
			operand->unduplicateReference();
			return (run.sink = this + 1)->pass(run, value);
		}
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualConstant::pass(Runner &run, const Cliche *value)
	{
		if (operand == value)
		{
			operand->unduplicateReference();
			return (run.sink = this + 1)->pass(run, value);
		}
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualConstant::pass(Runner &run, const ListConstant *value)
	{
		if (operand == value)
		{
			operand->unduplicateReference();
			return (run.sink = this + 1)->pass(run, value);
		}
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualConstant::pass(Runner &run, const NodeConstantShort *value)
	{
		if (operand == value)
		{
			operand->unduplicateReference();
			return (run.sink = this + 1)->pass(run, value);
		}
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualConstant::pass(Runner &run, const NodeConstantLong *value)
	{
		if (operand == value)
		{
			operand->unduplicateReference();
			return (run.sink = this + 1)->pass(run, value);
		}
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualConstant::pass(Runner &run, const Special *value)
	{
		if (operand == value)
		{
			operand->unduplicateReference();
			return (run.sink = this + 1)->pass(run, value);
		}
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualExpress::pass(Runner &run, const ListExpress &value)
	{
		if (operand == &value)
			return (run.sink = this + 1)->pass(run, &value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualExpress::pass(Runner &run, const NodeExpressShort &value)
	{
		if (operand == &value)
			return (run.sink = this + 1)->pass(run, &value);
		else
		{
            run.release(operand);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualExpress::pass(Runner &run, const NodeExpressLong &value)
	{
		if (operand == &value)
			return (run.sink = this + 1)->pass(run, &value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoEqualExpress::pass(Runner &run, const ListExpress *value)
	{
		if (operand == value)
		{
			operand->unduplicateReference();
			return (run.sink = this + 1)->pass(run, value);
		}
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualExpress::pass(Runner &run, const NodeExpressShort *value)
	{
		if (operand == value)
		{
			operand->unduplicateReference();
			return (run.sink = this + 1)->pass(run, value);
		}
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoEqualExpress::pass(Runner &run, const NodeExpressLong *value)
	{
		if (operand == value)
		{
			operand->unduplicateReference();
			return (run.sink = this + 1)->pass(run, value);
		}
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const NodeConstantShort *BuiltinClicheOperationNotEqual::newNode(const Constant *&link, const Integer *value) const
	{
        return new const OperationNotEqualInteger(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationNotEqual::newNode(const Constant *&link, const Float *value) const
	{
        return new const OperationNotEqualFloat(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationNotEqual::newNode(const Constant *&link, const PilsString *value) const
	{
        return new const OperationNotEqualString(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationNotEqual::newNode(const Constant *&link, const PilsColor *value) const
	{
        return new const OperationNotEqualConstant(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationNotEqual::newNode(const Constant *&link, const Timestamp *value) const
	{
        return new const OperationNotEqualConstant(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationNotEqual::newNode(const Constant *&link, const Duration *value) const
	{
        return new const OperationNotEqualConstant(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationNotEqual::newNode(const Constant *&link, const PilsDate *value) const
	{
        return new const OperationNotEqualConstant(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationNotEqual::newNode(const Constant *&link, const Cliche *value) const
	{
        return new const OperationNotEqualConstant(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationNotEqual::newNode(const Constant *&link, const ListConstant *value) const
	{
        return new const OperationNotEqualConstant(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationNotEqual::newNode(const Constant *&link, const NodeConstant *value) const
	{
        return new const OperationNotEqualConstant(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationNotEqual::newNode(const Constant *&link, const Special *value) const
	{
        return new const OperationNotEqualConstant(link, value);
	}

	const CallWho *BuiltinClicheOperationNotEqual::whoOperation(const NodeExpressShort *operation, const Any *who) const
	{
        return new const WhoExpressNotEqual(operation, who);
	}

	const CallWho *OperationNotEqualConstant::callWho(const Any *who) const
	{
        return new const WhoNotEqualConstant(this, who);
	}

	const CallWho *OperationNotEqualInteger::callWho(const Any *who) const
	{
        return new const WhoNotEqualInteger(this, who);
	}

	const CallWho *OperationNotEqualFloat::callWho(const Any *who) const
	{
        return new const WhoNotEqualFloat(this, who);
	}

	const CallWho *OperationNotEqualString::callWho(const Any *who) const
	{
        return new const WhoNotEqualString(this, who);
	}

	const Step *WhoNotEqualConstant::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoNotEqualUncountedConstant)))
			SinkWhoNotEqualUncountedConstant(*this, *((const NodeConstantShort*)element[0])->element[0]);
		return whoAttribute();
	}

	const Step *WhoNotEqualInteger::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoNotEqualUncountedInteger)))
			SinkWhoNotEqualUncountedInteger(*this, *(const Integer*)((const NodeConstantShort*)element[0])->element[0]);
		return whoAttribute();
	}

	const Step *WhoNotEqualFloat::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoNotEqualUncountedFloat)))
			SinkWhoNotEqualUncountedFloat(*this, *(const Float*)((const NodeConstantShort*)element[0])->element[0]);
		return whoAttribute();
	}

	const Step *WhoNotEqualString::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkWhoNotEqualUncountedString)))
			SinkWhoNotEqualUncountedString(*this, *(const PilsString*)((const NodeConstantShort*)element[0])->element[0]);
		return whoAttribute();
	}

	const Step *WhoExpressNotEqual::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkNotEqualOperand))) SinkNotEqualOperand(*this);
		return ((const NodeExpressShort*)element[0])->element[0];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, long value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualRawInteger))) SinkWhoNotEqualRawInteger(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, double value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualRawFloat))) SinkWhoNotEqualRawFloat(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const Integer &value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualUncountedInteger))) SinkWhoNotEqualUncountedInteger(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const Float &value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualUncountedFloat))) SinkWhoNotEqualUncountedFloat(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const PilsString &value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualUncountedString))) SinkWhoNotEqualUncountedString(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const Cliche &value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualUncountedConstant))) SinkWhoNotEqualUncountedConstant(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const ListConstant &value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualUncountedConstant))) SinkWhoNotEqualUncountedConstant(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const NodeConstantShort &value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualUncountedConstant))) SinkWhoNotEqualUncountedConstant(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const NodeConstantLong &value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualUncountedConstant))) SinkWhoNotEqualUncountedConstant(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const Special &value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualUncountedConstant))) SinkWhoNotEqualUncountedConstant(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const ListExpress &value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualUncountedExpress))) SinkWhoNotEqualUncountedExpress(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const NodeExpressShort &value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualUncountedExpress))) SinkWhoNotEqualUncountedExpress(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const NodeExpressLong &value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualUncountedExpress))) SinkWhoNotEqualUncountedExpress(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const Integer *value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualInteger))) SinkWhoNotEqualInteger(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const Float *value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualFloat))) SinkWhoNotEqualFloat(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const PilsString *value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualString))) SinkWhoNotEqualString(what, value);
		return what.element[1];
	}
	
	const Step *SinkNotEqualOperand::pass(Runner &run, const Timestamp *value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualConstant))) SinkWhoNotEqualConstant(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const Duration *value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualConstant))) SinkWhoNotEqualConstant(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const PilsDate *value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualConstant))) SinkWhoNotEqualConstant(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const Cliche *value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualConstant))) SinkWhoNotEqualConstant(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const ListConstant *value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualConstant))) SinkWhoNotEqualConstant(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const NodeConstantShort *value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualConstant))) SinkWhoNotEqualConstant(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const NodeConstantLong *value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualConstant))) SinkWhoNotEqualConstant(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const Special *value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualConstant))) SinkWhoNotEqualConstant(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const ListExpress *value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualExpress))) SinkWhoNotEqualExpress(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const NodeExpressShort *value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualExpress))) SinkWhoNotEqualExpress(what, value);
		return what.element[1];
	}

	const Step *SinkNotEqualOperand::pass(Runner &run, const NodeExpressLong *value)
	{
		WhoExpressNotEqual &what = (WhoExpressNotEqual&)this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWhoNotEqualExpress))) SinkWhoNotEqualExpress(what, value);
		return what.element[1];
	}

	const Step *SinkWhoNotEqualRawInteger::pass(Runner &run, long value)
	{
		if (value != operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualRawInteger::pass(Runner &run, double value)
	{
		if (value != operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}
	
	const Step *SinkWhoNotEqualRawInteger::pass(Runner &run, const Integer &value)
	{
		if (value.value != operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualRawInteger::pass(Runner &run, const Float &value)
	{
		if (value.value != operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualRawInteger::pass(Runner &run, const PilsString &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualRawInteger::pass(Runner &run, const Integer *value)
	{
		if (value->value != operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoNotEqualRawInteger::pass(Runner &run, const Float *value)
	{
		if (value->value != operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoNotEqualRawInteger::pass(Runner &run, const PilsString *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualRawInteger::pass(Runner &run, const Any *value)
	{
		run.sink = this + 1;
		return value->passCounted(run);
	}

	const Step *SinkWhoNotEqualRawFloat::pass(Runner &run, long value)
	{
		if (value != operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualRawFloat::pass(Runner &run, double value)
	{
		if (value != operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}
	
	const Step *SinkWhoNotEqualRawFloat::pass(Runner &run, const Integer &value)
	{
		if (value.value != operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualRawFloat::pass(Runner &run, const Float &value)
	{
		if (value.value != operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualRawFloat::pass(Runner &run, const PilsString &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualRawFloat::pass(Runner &run, const Integer *value)
	{
		if (value->value != operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoNotEqualRawFloat::pass(Runner &run, const Float *value)
	{
		if (value->value != operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoNotEqualRawFloat::pass(Runner &run, const PilsString *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualRawFloat::pass(Runner &run, const Any *value)
	{
		run.sink = this + 1;
		return value->passCounted(run);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, long value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, double value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const Integer &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const Float &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const PilsString &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const Cliche &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const ListConstant &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const NodeConstantShort &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const NodeConstantLong &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const Special &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const ListExpress &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const NodeExpressShort &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const NodeExpressLong &value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const Integer *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const Float *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const PilsString *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const Timestamp *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const Duration *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const PilsDate *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const Cliche *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const ListConstant *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const NodeConstantShort *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const NodeConstantLong *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const Special *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const ListExpress *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const NodeExpressShort *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const NodeExpressLong *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedBad::pass(Runner &run, const Any *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualUncountedConstant::pass(Runner &run, const Cliche &value)
	{
		if (&value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualUncountedConstant::pass(Runner &run, const ListConstant &value)
	{
		if (&value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualUncountedConstant::pass(Runner &run, const NodeConstantShort &value)
	{
		if (&value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualUncountedConstant::pass(Runner &run, const NodeConstantLong &value)
	{
		if (&value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualUncountedConstant::pass(Runner &run, const Special &value)
	{
		if (&value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualUncountedConstant::pass(Runner &run, const Timestamp *value)
	{
		if (value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoNotEqualUncountedConstant::pass(Runner &run, const Duration *value)
	{
		if (value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoNotEqualUncountedConstant::pass(Runner &run, const PilsDate *value)
	{
		if (value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoNotEqualUncountedConstant::pass(Runner &run, const Cliche *value)
	{
		if (value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoNotEqualUncountedConstant::pass(Runner &run, const ListConstant *value)
	{
		if (value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoNotEqualUncountedConstant::pass(Runner &run, const NodeConstantShort *value)
	{
		if (value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoNotEqualUncountedConstant::pass(Runner &run, const NodeConstantLong *value)
	{
		if (value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoNotEqualUncountedConstant::pass(Runner &run, const Special *value)
	{
		if (value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoNotEqualUncountedInteger::pass(Runner &run, long value)
	{
		if (value != ((const Integer&)operand).value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualUncountedInteger::pass(Runner &run, double value)
	{
		if (value != ((const Integer&)operand).value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualUncountedInteger::pass(Runner &run, const Integer &value)
	{
		if (&value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualUncountedInteger::pass(Runner &run, const Integer *value)
	{
		if (value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoNotEqualUncountedFloat::pass(Runner &run, double value)
	{
		if (value != ((const Float&)operand).value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualUncountedFloat::pass(Runner &run, const Float &value)
	{
		if (&value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualUncountedFloat::pass(Runner &run, const Float *value)
	{
		if (value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoNotEqualUncountedString::pass(Runner &run, const PilsString &value)
	{
		if (&value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualUncountedString::pass(Runner &run, const PilsString *value)
	{
		if (value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoNotEqualUncountedExpress::pass(Runner &run, const ListExpress &value)
	{
		long result = (long)(&value != &operand);
		return (run.sink = this + 1)->pass(run, result);
	}

	const Step *SinkWhoNotEqualUncountedExpress::pass(Runner &run, const NodeExpressShort &value)
	{
		long result = (long)(&value != &operand);
		return (run.sink = this + 1)->pass(run, result);
	}

	const Step *SinkWhoNotEqualUncountedExpress::pass(Runner &run, const NodeExpressLong &value)
	{
		long result = (long)(&value != &operand);
		return (run.sink = this + 1)->pass(run, result);
	}

	const Step *SinkWhoNotEqualUncountedExpress::pass(Runner &run, const ListExpress *value)
	{
		if (value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoNotEqualUncountedExpress::pass(Runner &run, const NodeExpressShort *value)
	{
		if (value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkWhoNotEqualUncountedExpress::pass(Runner &run, const NodeExpressLong *value)
	{
		if (value != &operand)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}


	const Step *SinkWhoNotEqualBad::pass(Runner &run, long value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, double value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const Integer &value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const Float &value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const PilsString &value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const Cliche &value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const ListConstant &value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const NodeConstantShort &value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const NodeConstantLong &value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const Special &value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const ListExpress &value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const NodeExpressShort &value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const NodeExpressLong &value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const Integer *value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const Float *value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const PilsString *value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const Timestamp *value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const Duration *value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const PilsDate *value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const Any *value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const Cliche *value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const ListConstant *value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const NodeConstantShort *value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const NodeConstantLong *value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const Special *value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const ListExpress *value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const NodeExpressShort *value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkWhoNotEqualBad::pass(Runner &run, const NodeExpressLong *value)
	{
        run.release(operand);
		return (run.sink = this + 1)->pass(run, value);
	}
	const Step *SinkWhoNotEqualInteger::pass(Runner &run, long value)
	{
		if (((const Integer*)operand)->value != value)
		{
            run.release(operand);
			return (run.sink = this + 1)->pass(run, value);
		}
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualInteger::pass(Runner &run, double value)
	{
		if (((const Integer*)operand)->value != value)
		{
            run.release(operand);
			return (run.sink = this + 1)->pass(run, value);
		}
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualInteger::pass(Runner &run, const Integer &value)
	{
		if (operand != &value)
		{
            run.release(operand);
			return (run.sink = this + 1)->pass(run, value);
		}
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualInteger::pass(Runner &run, const Integer *value)
	{
        run.release(operand);
		if (operand != value)
			return (run.sink = this + 1)->pass(run, value);
		else
			return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualFloat::pass(Runner &run, double value)
	{
		long result = (long)(((const Float*)operand)->value != value);
        run.release(operand);
		return (run.sink = this + 1)->pass(run, result);
	}

	const Step *SinkWhoNotEqualFloat::pass(Runner &run, const Float &value)
	{
		long result = (long)(operand != &value);
        run.release(operand);
		return (run.sink = this + 1)->pass(run, result);
	}

	const Step *SinkWhoNotEqualFloat::pass(Runner &run, const Float *value)
	{
        run.release(operand);
		if (operand != value)
			return (run.sink = this + 1)->pass(run, value);
		else
			return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualString::pass(Runner &run, const PilsString &value)
	{
		if (operand != &value)
		{
            run.release(operand);
			return (run.sink = this + 1)->pass(run, value);
		}
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualString::pass(Runner &run, const PilsString *value)
	{
        run.release(operand);
		if (operand != value)
			return (run.sink = this + 1)->pass(run, value);
		else
			return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualConstant::pass(Runner &run, const Cliche &value)
	{
		if (operand != &value)
		{
            run.release(operand);
			return (run.sink = this + 1)->pass(run, value);
		}
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualConstant::pass(Runner &run, const ListConstant &value)
	{
		if (operand != &value)
		{
            run.release(operand);
			return (run.sink = this + 1)->pass(run, value);
		}
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualConstant::pass(Runner &run, const NodeConstantShort &value)
	{
		if (operand != &value)
		{
            run.release(operand);
			return (run.sink = this + 1)->pass(run, value);
		}
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualConstant::pass(Runner &run, const NodeConstantLong &value)
	{
		if (operand != &value)
		{
            run.release(operand);
			return (run.sink = this + 1)->pass(run, value);
		}
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualConstant::pass(Runner &run, const Special &value)
	{
		if (operand != &value)
		{
            run.release(operand);
			return (run.sink = this + 1)->pass(run, value);
		}
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualConstant::pass(Runner &run, const Timestamp *value)
	{
        run.release(operand);
		if (operand != value)
			return (run.sink = this + 1)->pass(run, value);
		else
			return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualConstant::pass(Runner &run, const Duration *value)
	{
        run.release(operand);
		if (operand != value)
			return (run.sink = this + 1)->pass(run, value);
		else
			return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualConstant::pass(Runner &run, const PilsDate *value)
	{
        run.release(operand);
		if (operand != value)
			return (run.sink = this + 1)->pass(run, value);
		else
			return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualConstant::pass(Runner &run, const Cliche *value)
	{
        run.release(operand);
		if (operand != value)
			return (run.sink = this + 1)->pass(run, value);
		else
			return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualConstant::pass(Runner &run, const ListConstant *value)
	{
        run.release(operand);
		if (operand != value)
			return (run.sink = this + 1)->pass(run, value);
		else
			return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualConstant::pass(Runner &run, const NodeConstantShort *value)
	{
        run.release(operand);
		if (operand != value)
			return (run.sink = this + 1)->pass(run, value);
		else
			return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualConstant::pass(Runner &run, const NodeConstantLong *value)
	{
        run.release(operand);
		if (operand != value)
			return (run.sink = this + 1)->pass(run, value);
		else
			return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualConstant::pass(Runner &run, const Special *value)
	{
        run.release(operand);
		if (operand != value)
			return (run.sink = this + 1)->pass(run, value);
		else
			return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualExpress::pass(Runner &run, const ListExpress &value)
	{
		if (operand != &value)
		{
            run.release(operand);
			return (run.sink = this + 1)->pass(run, value);
		}
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualExpress::pass(Runner &run, const NodeExpressShort &value)
	{
		if (operand != &value)
		{
            run.release(operand);
			return (run.sink = this + 1)->pass(run, value);
		}
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualExpress::pass(Runner &run, const NodeExpressLong &value)
	{
		if (operand != &value)
		{
            run.release(operand);
			return (run.sink = this + 1)->pass(run, value);
		}
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualExpress::pass(Runner &run, const ListExpress *value)
	{
        run.release(operand);
		if (operand != value)
			return (run.sink = this + 1)->pass(run, value);
		else
			return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualExpress::pass(Runner &run, const NodeExpressShort *value)
	{
        run.release(operand);
		if (operand != value)
			return (run.sink = this + 1)->pass(run, value);
		else
			return falseCompare(run, what, this[1]);
	}

	const Step *SinkWhoNotEqualExpress::pass(Runner &run, const NodeExpressLong *value)
	{
        run.release(operand);
		if (operand != value)
			return (run.sink = this + 1)->pass(run, value);
		else
			return falseCompare(run, what, this[1]);
	}

	const BuiltinClicheCompare &BuiltinClicheOperationLess::opposite() const
	{
		return BuiltinClicheOperationGreater::singleton;
	}

	const BuiltinClicheCompare &BuiltinClicheOperationLessEqual::opposite() const
	{
		return BuiltinClicheOperationGreaterEqual::singleton;
	}

	const BuiltinClicheCompare &BuiltinClicheOperationGreater::opposite() const
	{
		return BuiltinClicheOperationLess::singleton;
	}

	const BuiltinClicheCompare &BuiltinClicheOperationGreaterEqual::opposite() const
	{
		return BuiltinClicheOperationLessEqual::singleton;
	}

	bool BuiltinClicheOperationLess::compare(double a, double b) const
	{
		return a < b;
	}

	bool BuiltinClicheOperationLessEqual::compare(double a, double b) const
	{
		return a <= b;
	}

	bool BuiltinClicheOperationGreater::compare(double a, double b) const
	{
		return a > b;
	}

	bool BuiltinClicheOperationGreaterEqual::compare(double a, double b) const
	{
		return a >= b;
	}

	const NodeConstantShort *BuiltinClicheOperationLess::newNode(const Constant *&link, const Integer *value) const
	{
        return new const OperationLessInteger(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationLess::newNode(const Constant *&link, const Float *value) const
	{
        return new const OperationLessFloat(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationLess::newNode(const Constant *&link, const PilsString *value) const
	{
        return new const OperationLessString(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationLessEqual::newNode(const Constant *&link, const Integer *value) const
	{
        return new const OperationLessEqualInteger(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationLessEqual::newNode(const Constant *&link, const Float *value) const
	{
        return new const OperationLessEqualFloat(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationLessEqual::newNode(const Constant *&link, const PilsString *value) const
	{
        return new const OperationLessEqualString(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationGreater::newNode(const Constant *&link, const Integer *value) const
	{
        return new const OperationGreaterInteger(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationGreater::newNode(const Constant *&link, const Float *value) const
	{
        return new const OperationGreaterFloat(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationGreater::newNode(const Constant *&link, const PilsString *value) const
	{
        return new const OperationGreaterString(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationGreaterEqual::newNode(const Constant *&link, const Integer *value) const
	{
        return new const OperationGreaterEqualInteger(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationGreaterEqual::newNode(const Constant *&link, const Float *value) const
	{
        return new const OperationGreaterEqualFloat(link, value);
	}

	const NodeConstantShort *BuiltinClicheOperationGreaterEqual::newNode(const Constant *&link, const PilsString *value) const
	{
        return new const OperationGreaterEqualString(link, value);
	}

	const CallWho *OperationLessInteger::callWho(const Any *who) const
	{
        return new const WhoLessInteger(this, who);
	}

	const CallWho *OperationLessFloat::callWho(const Any *who) const
	{
        return new const WhoLessFloat(this, who);
	}

	const CallWho *OperationLessString::callWho(const Any *who) const
	{
        return new const WhoLessString(this, who);
	}

	const CallWho *BuiltinClicheOperationLess::whoOperation(const NodeExpressShort *operation, const Any *who) const
	{
        return new const WhoLessExpress((NodeExpressTiny*)operation, who);
	}

	const CallWho *OperationLessEqualInteger::callWho(const Any *who) const
	{
        return new const WhoLessEqualInteger(this, who);
	}

	const CallWho *OperationLessEqualFloat::callWho(const Any *who) const
	{
        return new const WhoLessEqualFloat(this, who);
	}

	const CallWho *OperationLessEqualString::callWho(const Any *who) const
	{
        return new const WhoLessEqualString(this, who);
	}

	const CallWho *BuiltinClicheOperationLessEqual::whoOperation(const NodeExpressShort *operation, const Any *who) const
	{
        return new const WhoLessEqualExpress((NodeExpressTiny*)operation, who);
	}

	const CallWho *OperationGreaterInteger::callWho(const Any *who) const
	{
        return new const WhoGreaterInteger(this, who);
	}

	const CallWho *OperationGreaterFloat::callWho(const Any *who) const
	{
        return new const WhoGreaterFloat(this, who);
	}

	const CallWho *OperationGreaterString::callWho(const Any *who) const
	{
        return new const WhoGreaterString(this, who);
	}

	const CallWho *BuiltinClicheOperationGreater::whoOperation(const NodeExpressShort *operation, const Any *who) const
	{
        return new const WhoGreaterExpress((NodeExpressTiny*)operation, who);
	}

	const CallWho *OperationGreaterEqualInteger::callWho(const Any *who) const
	{
        return new const WhoGreaterEqualInteger(this, who);
	}

	const CallWho *OperationGreaterEqualFloat::callWho(const Any *who) const
	{
        return new const WhoGreaterEqualFloat(this, who);
	}

	const CallWho *OperationGreaterEqualString::callWho(const Any *who) const
	{
        return new const WhoGreaterEqualString(this, who);
	}

	const CallWho *BuiltinClicheOperationGreaterEqual::whoOperation(const NodeExpressShort *operation, const Any *who) const
	{
        return new const WhoGreaterEqualExpress((NodeExpressTiny*)operation, who);
	}

	const Step *WhoLessInteger::step_(Runner &run) const
	{
		long value = ((const Integer*)((NodeConstantTiny*)callAttribute())->element[0])->value;
		new (run.allocate(sizeof(SinkLessIntegerRaw))) SinkLessIntegerRaw(*this, value);
		return whoAttribute();
	}

	const Step *WhoLessFloat::step_(Runner &run) const
	{
		double value = ((const Float*)((NodeConstantTiny*)callAttribute())->element[0])->value;
		new (run.allocate(sizeof(SinkLessFloatRaw))) SinkLessFloatRaw(*this, value);
		return whoAttribute();
	}

	const Step *WhoLessString::step_(Runner &run) const
	{
		const PilsString *value = (const PilsString*)((NodeConstantTiny*)callAttribute())->element[0];
		value->retain();
		new (run.allocate(sizeof(SinkLessString))) SinkLessString(*this, value);
		return whoAttribute();
	}

	const Step *WhoLessExpress::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkLessOperand))) SinkLessOperand(*this);
		return ((NodeExpressTiny*)callAttribute())->element[0];
	}

	const Step *WhoLessEqualInteger::step_(Runner &run) const
	{
		long value = ((const Integer*)((NodeConstantTiny*)callAttribute())->element[0])->value;
		new (run.allocate(sizeof(SinkLessEqualIntegerRaw))) SinkLessEqualIntegerRaw(*this, value);
		return whoAttribute();
	}

	const Step *WhoLessEqualFloat::step_(Runner &run) const
	{
		double value = ((const Float*)((NodeConstantTiny*)callAttribute())->element[0])->value;
		new (run.allocate(sizeof(SinkLessEqualFloatRaw))) SinkLessEqualFloatRaw(*this, value);
		return whoAttribute();
	}

	const Step *WhoLessEqualString::step_(Runner &run) const
	{
		const PilsString *value = (const PilsString*)((NodeConstantTiny*)callAttribute())->element[0];
		value->retain();
		new (run.allocate(sizeof(SinkLessEqualString))) SinkLessEqualString(*this, value);
		return whoAttribute();
	}

	const Step *WhoLessEqualExpress::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkLessEqualOperand))) SinkLessEqualOperand(*this);
		return ((NodeExpressTiny*)callAttribute())->element[0];
	}

	const Step *WhoGreaterInteger::step_(Runner &run) const
	{
		long value = ((const Integer*)((NodeConstantTiny*)callAttribute())->element[0])->value;
		new (run.allocate(sizeof(SinkGreaterIntegerRaw))) SinkGreaterIntegerRaw(*this, value);
		return whoAttribute();
	}

	const Step *WhoGreaterFloat::step_(Runner &run) const
	{
		double value = ((const Float*)((NodeConstantTiny*)callAttribute())->element[0])->value;
		new (run.allocate(sizeof(SinkGreaterFloatRaw))) SinkGreaterFloatRaw(*this, value);
		return whoAttribute();
	}

	const Step *WhoGreaterString::step_(Runner &run) const
	{
		const PilsString *value = (const PilsString*)((NodeConstantTiny*)callAttribute())->element[0];
		value->retain();
		new (run.allocate(sizeof(SinkGreaterString))) SinkGreaterString(*this, value);
		return whoAttribute();
	}

	const Step *WhoGreaterExpress::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkGreaterOperand))) SinkGreaterOperand(*this);
		return ((NodeExpressTiny*)callAttribute())->element[0];
	}

	const Step *WhoGreaterEqualInteger::step_(Runner &run) const
	{
		long value = ((const Integer*)((NodeConstantTiny*)callAttribute())->element[0])->value;
		new (run.allocate(sizeof(SinkGreaterEqualIntegerRaw))) SinkGreaterEqualIntegerRaw(*this, value);
		return whoAttribute();
	}

	const Step *WhoGreaterEqualFloat::step_(Runner &run) const
	{
		double value = ((const Float*)((NodeConstantTiny*)callAttribute())->element[0])->value;
		new (run.allocate(sizeof(SinkGreaterEqualFloatRaw))) SinkGreaterEqualFloatRaw(*this, value);
		return whoAttribute();
	}

	const Step *WhoGreaterEqualString::step_(Runner &run) const
	{
		const PilsString *value = (const PilsString*)((NodeConstantTiny*)callAttribute())->element[0];
		value->retain();
		new (run.allocate(sizeof(SinkGreaterEqualString))) SinkGreaterEqualString(*this, value);
		return whoAttribute();
	}

	const Step *WhoGreaterEqualExpress::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkGreaterEqualOperand))) SinkGreaterEqualOperand(*this);
		return ((NodeExpressTiny*)callAttribute())->element[0];
	}

	Sink *SinkCompareOperand::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkCompareOperand::pass(Runner &run, const Any *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		const ClicheShort *cliche = (const ClicheTiny*) ((NodeExpressTiny*)what.callAttribute())->cliche;
		new (run.allocate(sizeof(SinkWho))) SinkWho(what, cliche->node(value));
		return what.whoAttribute();
	}

	const Step *SinkCompareOperand::pass(Runner &run, const Integer &value)
	{
		return pass(run, value.value);
	}

	const Step *SinkCompareOperand::pass(Runner &run, const Float &value)
	{
		return pass(run, value.value);
	}

	const Step *SinkCompareOperand::pass(Runner &run, const Integer *value)
	{
		long v = value->value;
        run.release(value);
		return pass(run, v);
	}

	const Step *SinkCompareOperand::pass(Runner &run, const Float *value)
	{
		double v = value->value;
        run.release(value);
		return pass(run, v);
	}

	const Step *SinkCompareIntegerRaw::pass(Runner &run, const Any *who)
	{
		const CallWho &what = this->what;
		const Any *call = what.callAttribute();
		const NodeExpress *expressCall = call->as_NodeExpress();
		if (expressCall)
		{
			call = expressCall->cliche->as_ClicheTiny()->nodeConstant(Integer::get(value));
		}
		else call->retain();
		return (run.sink = this + 1)->call(run, what, call, who);
	}

	Sink *SinkCompareIntegerRaw::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkCompareFloatRaw::pass(Runner &run, const Any *who)
	{
		const CallWho &what = this->what;
		const Any *call = what.callAttribute();
		const NodeExpress *expressCall = call->as_NodeExpress();
		if (expressCall)
		{
			call = expressCall->cliche->as_ClicheTiny()->nodeConstant(Number::get(value));
		}
		else call->retain();
		return (run.sink = this + 1)->call(run, what, call, who);
	}

	Sink *SinkCompareFloatRaw::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkCompareConstant::pass(Runner &run, const Any *who)
	{
		const CallWho &what = this->what;
		const Any *call = what.callAttribute();
		const NodeExpress *expressCall = call->as_NodeExpress();
		if (expressCall)
		{
			call = expressCall->cliche->as_ClicheTiny()->nodeConstant(value);
		}
		else
		{
			call->retain();
            run.release(value);
		}
		return (run.sink = this + 1)->call(run, what, call, who);
	}

	Sink *SinkCompareConstant::kick(Runner &run)
	{
        run.release(value);
		return this + 1;
	}

	const Step *SinkLessOperand::pass(Runner &run, long value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkLessIntegerRaw))) SinkLessIntegerRaw(what, value);
		return what.whoAttribute();
	}

	const Step *SinkLessOperand::pass(Runner &run, double value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkLessFloatRaw))) SinkLessFloatRaw(what, value);
		return what.whoAttribute();
	}

	const Step *SinkLessOperand::pass(Runner &run, const PilsString *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkLessString))) SinkLessString(what, value);
		return what.whoAttribute();
	}

	const Step *SinkLessOperand::pass(Runner &run, const Timestamp *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkLessTimestamp))) SinkLessTimestamp(what, value);
		return what.whoAttribute();
	}

	const Step *SinkLessOperand::pass(Runner &run, const Duration *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkLessDuration))) SinkLessDuration(what, value);
		return what.whoAttribute();
	}

	const Step *SinkLessOperand::pass(Runner &run, const PilsDate *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkLessPilsDate))) SinkLessPilsDate(what, value);
		return what.whoAttribute();
	}

	const Step *SinkLessEqualOperand::pass(Runner &run, long value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkLessEqualIntegerRaw))) SinkLessEqualIntegerRaw(what, value);
		return what.whoAttribute();
	}

	const Step *SinkLessEqualOperand::pass(Runner &run, double value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkLessEqualFloatRaw))) SinkLessEqualFloatRaw(what, value);
		return what.whoAttribute();
	}

	const Step *SinkLessEqualOperand::pass(Runner &run, const PilsString *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkLessEqualString))) SinkLessEqualString(what, value);
		return what.whoAttribute();
	}

	const Step *SinkLessEqualOperand::pass(Runner &run, const Timestamp *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkLessEqualTimestamp))) SinkLessEqualTimestamp(what, value);
		return what.whoAttribute();
	}

	const Step *SinkLessEqualOperand::pass(Runner &run, const Duration *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkLessEqualDuration))) SinkLessEqualDuration(what, value);
		return what.whoAttribute();
	}

	const Step *SinkLessEqualOperand::pass(Runner &run, const PilsDate *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkLessEqualPilsDate))) SinkLessEqualPilsDate(what, value);
		return what.whoAttribute();
	}

	const Step *SinkGreaterOperand::pass(Runner &run, long value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkGreaterIntegerRaw))) SinkGreaterIntegerRaw(what, value);
		return what.whoAttribute();
	}

	const Step *SinkGreaterOperand::pass(Runner &run, double value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkGreaterFloatRaw))) SinkGreaterFloatRaw(what, value);
		return what.whoAttribute();
	}

	const Step *SinkGreaterOperand::pass(Runner &run, const PilsString *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkGreaterString))) SinkGreaterString(what, value);
		return what.whoAttribute();
	}

	const Step *SinkGreaterOperand::pass(Runner &run, const Timestamp *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkGreaterTimestamp))) SinkGreaterTimestamp(what, value);
		return what.whoAttribute();
	}

	const Step *SinkGreaterOperand::pass(Runner &run, const Duration *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkGreaterDuration))) SinkGreaterDuration(what, value);
		return what.whoAttribute();
	}

	const Step *SinkGreaterOperand::pass(Runner &run, const PilsDate *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkGreaterPilsDate))) SinkGreaterPilsDate(what, value);
		return what.whoAttribute();
	}

	const Step *SinkGreaterEqualOperand::pass(Runner &run, long value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkGreaterEqualIntegerRaw))) SinkGreaterEqualIntegerRaw(what, value);
		return what.whoAttribute();
	}

	const Step *SinkGreaterEqualOperand::pass(Runner &run, double value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkGreaterEqualFloatRaw))) SinkGreaterEqualFloatRaw(what, value);
		return what.whoAttribute();
	}

	const Step *SinkGreaterEqualOperand::pass(Runner &run, const PilsString *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkGreaterEqualString))) SinkGreaterEqualString(what, value);
		return what.whoAttribute();
	}

	const Step *SinkGreaterEqualOperand::pass(Runner &run, const Timestamp *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkGreaterEqualTimestamp))) SinkGreaterEqualTimestamp(what, value);
		return what.whoAttribute();
	}

	const Step *SinkGreaterEqualOperand::pass(Runner &run, const Duration *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkGreaterEqualDuration))) SinkGreaterEqualDuration(what, value);
		return what.whoAttribute();
	}

	const Step *SinkGreaterEqualOperand::pass(Runner &run, const PilsDate *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkGreaterEqualPilsDate))) SinkGreaterEqualPilsDate(what, value);
		return what.whoAttribute();
	}

	const Step *SinkLessIntegerRaw::pass(Runner &run, long value)
	{
		if (value < this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkLessIntegerRaw::pass(Runner &run, double value)
	{
		if (value < this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkLessIntegerRaw::pass(Runner &run, const Integer &value)
	{
		if (value.value < this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkLessIntegerRaw::pass(Runner &run, const Float &value)
	{
		if (value.value < this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkLessIntegerRaw::pass(Runner &run, const Integer *value)
	{
		if (value->value < this->value)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkLessIntegerRaw::pass(Runner &run, const Float *value)
	{
		if (value->value < this->value)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkLessEqualIntegerRaw::pass(Runner &run, long value)
	{
		if (value <= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkLessEqualIntegerRaw::pass(Runner &run, double value)
	{
		if (value <= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkLessEqualIntegerRaw::pass(Runner &run, const Integer &value)
	{
		if (value.value <= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkLessEqualIntegerRaw::pass(Runner &run, const Float &value)
	{
		if (value.value <= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkLessEqualIntegerRaw::pass(Runner &run, const Integer *value)
	{
		if (value->value <= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkLessEqualIntegerRaw::pass(Runner &run, const Float *value)
	{
		if (value->value <= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkGreaterIntegerRaw::pass(Runner &run, long value)
	{
		if (value > this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkGreaterIntegerRaw::pass(Runner &run, double value)
	{
		if (value > this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkGreaterIntegerRaw::pass(Runner &run, const Integer &value)
	{
		if (value.value > this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkGreaterIntegerRaw::pass(Runner &run, const Float &value)
	{
		if (value.value > this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkGreaterIntegerRaw::pass(Runner &run, const Integer *value)
	{
		if (value->value > this->value)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkGreaterIntegerRaw::pass(Runner &run, const Float *value)
	{
		if (value->value > this->value)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkGreaterEqualIntegerRaw::pass(Runner &run, long value)
	{
		if (value >= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkGreaterEqualIntegerRaw::pass(Runner &run, double value)
	{
		if (value >= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkGreaterEqualIntegerRaw::pass(Runner &run, const Integer &value)
	{
		if (value.value >= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkGreaterEqualIntegerRaw::pass(Runner &run, const Float &value)
	{
		if (value.value >= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkGreaterEqualIntegerRaw::pass(Runner &run, const Integer *value)
	{
		if (value->value >= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkGreaterEqualIntegerRaw::pass(Runner &run, const Float *value)
	{
		if (value->value >= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkLessFloatRaw::pass(Runner &run, long value)
	{
		if (value < this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkLessFloatRaw::pass(Runner &run, double value)
	{
		if (value < this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkLessFloatRaw::pass(Runner &run, const Integer &value)
	{
		if (value.value < this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkLessFloatRaw::pass(Runner &run, const Float &value)
	{
		if (value.value < this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkLessFloatRaw::pass(Runner &run, const Integer *value)
	{
		if (value->value < this->value)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkLessFloatRaw::pass(Runner &run, const Float *value)
	{
		if (value->value < this->value)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkLessEqualFloatRaw::pass(Runner &run, long value)
	{
		if (value <= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkLessEqualFloatRaw::pass(Runner &run, double value)
	{
		if (value <= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkLessEqualFloatRaw::pass(Runner &run, const Integer &value)
	{
		if (value.value <= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkLessEqualFloatRaw::pass(Runner &run, const Float &value)
	{
		if (value.value <= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkLessEqualFloatRaw::pass(Runner &run, const Integer *value)
	{
		if (value->value <= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkLessEqualFloatRaw::pass(Runner &run, const Float *value)
	{
		if (value->value <= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkGreaterFloatRaw::pass(Runner &run, long value)
	{
		if (value > this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkGreaterFloatRaw::pass(Runner &run, double value)
	{
		if (value > this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkGreaterFloatRaw::pass(Runner &run, const Integer &value)
	{
		if (value.value > this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkGreaterFloatRaw::pass(Runner &run, const Float &value)
	{
		if (value.value > this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkGreaterFloatRaw::pass(Runner &run, const Integer *value)
	{
		if (value->value > this->value)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkGreaterFloatRaw::pass(Runner &run, const Float *value)
	{
		if (value->value > this->value)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkGreaterEqualFloatRaw::pass(Runner &run, long value)
	{
		if (value >= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkGreaterEqualFloatRaw::pass(Runner &run, double value)
	{
		if (value >= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkGreaterEqualFloatRaw::pass(Runner &run, const Integer &value)
	{
		if (value.value >= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkGreaterEqualFloatRaw::pass(Runner &run, const Float &value)
	{
		if (value.value >= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else return falseCompare(run, what, this[1]);
	}

	const Step *SinkGreaterEqualFloatRaw::pass(Runner &run, const Integer *value)
	{
		if (value->value >= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkGreaterEqualFloatRaw::pass(Runner &run, const Float *value)
	{
		if (value->value >= this->value)
			return (run.sink = this + 1)->pass(run, value);
		else
		{
            run.release(value);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkLessString::pass(Runner &run, const PilsString *that)
	{
		if (that->less((const PilsString&)*value))
		{
            run.release(value);
			return (run.sink = this + 1)->pass(run, that);
		}
		else
		{
            run.release(that);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkLessEqualString::pass(Runner &run, const PilsString *that)
	{
		if (!((const PilsString*)value)->less(*that))
		{
            run.release(value);
			return (run.sink = this + 1)->pass(run, that);
		}
		else
		{
            run.release(that);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkGreaterString::pass(Runner &run, const PilsString *that)
	{
		if(((const PilsString*)value)->less(*that))
		{
            run.release(value);
			return (run.sink = this + 1)->pass(run, that);
		}
		else
		{
            run.release(that);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkGreaterEqualString::pass(Runner &run, const PilsString *that)
	{
		if (!that->less((const PilsString&)*value))
		{
            run.release(value);
			return (run.sink = this + 1)->pass(run, that);
		}
		else
		{
            run.release(that);
			return falseCompare(run, what, this[1]);
		}
	}

	bool PilsString::less(const PilsString &that) const
	{
		for (long i = 0; i < count->value && i < that.count->value; i++)
			if (value[i] != that.value[i]) return (unsigned char) value[i] < (unsigned char) that.value[i];
		return count->value < that.count->value;
	}

	const Step *SinkLessTimestamp::pass(Runner &run, const Timestamp *that)
	{
		if (that->value < ((const Timevalue&)*value).value)
		{
            run.release(value);
			return (run.sink = this + 1)->pass(run, that);
		}
		else
		{
            run.release(that);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkLessEqualTimestamp::pass(Runner &run, const Timestamp *that)
	{
		if (that->value <= ((const Timevalue&)*value).value)
		{
            run.release(value);
			return (run.sink = this + 1)->pass(run, that);
		}
		else
		{
            run.release(that);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkGreaterTimestamp::pass(Runner &run, const Timestamp *that)
	{
		if (that->value > ((const Timevalue&)*value).value)
		{
            run.release(value);
			return (run.sink = this + 1)->pass(run, that);
		}
		else
		{
            run.release(that);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkGreaterEqualTimestamp::pass(Runner &run, const Timestamp *that)
	{
		if (that->value >= ((const Timevalue&)*value).value)
		{
            run.release(value);
			return (run.sink = this + 1)->pass(run, that);
		}
		else
		{
            run.release(that);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkLessDuration::pass(Runner &run, const Duration *that)
	{
		if (that->value < ((const Timevalue&)*value).value)
		{
            run.release(value);
			return (run.sink = this + 1)->pass(run, that);
		}
		else
		{
            run.release(that);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkLessEqualDuration::pass(Runner &run, const Duration *that)
	{
		if (that->value <= ((const Timevalue&)*value).value)
		{
            run.release(value);
			return (run.sink = this + 1)->pass(run, that);
		}
		else
		{
            run.release(that);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkGreaterDuration::pass(Runner &run, const Duration *that)
	{
		if (that->value > ((const Timevalue&)*value).value)
		{
            run.release(value);
			return (run.sink = this + 1)->pass(run, that);
		}
		else
		{
            run.release(that);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkGreaterEqualDuration::pass(Runner &run, const Duration *that)
	{
		if (that->value >= ((const Timevalue&)*value).value)
		{
            run.release(value);
			return (run.sink = this + 1)->pass(run, that);
		}
		else
		{
            run.release(that);
			return falseCompare(run, what, this[1]);
		}
	}


	const Step *SinkLessPilsDate::pass(Runner &run, const PilsDate *that)
	{
		if (that->value < ((const Timevalue&)*value).value)
		{
            run.release(value);
			return (run.sink = this + 1)->pass(run, that);
		}
		else
		{
            run.release(that);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkLessEqualPilsDate::pass(Runner &run, const PilsDate *that)
	{
		if (that->value <= ((const Timevalue&)*value).value)
		{
            run.release(value);
			return (run.sink = this + 1)->pass(run, that);
		}
		else
		{
            run.release(that);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkGreaterPilsDate::pass(Runner &run, const PilsDate *that)
	{
		if (that->value > ((const Timevalue&)*value).value)
		{
            run.release(value);
			return (run.sink = this + 1)->pass(run, that);
		}
		else
		{
            run.release(that);
			return falseCompare(run, what, this[1]);
		}
	}

	const Step *SinkGreaterEqualPilsDate::pass(Runner &run, const PilsDate *that)
	{
		if (that->value >= ((const Timevalue&)*value).value)
		{
            run.release(value);
			return (run.sink = this + 1)->pass(run, that);
		}
		else
		{
            run.release(that);
			return falseCompare(run, what, this[1]);
		}
	}
}
