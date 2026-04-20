/* This file is public domain */
#ifndef DEFINE_PILS_NUMERIC_H
#define DEFINE_PILS_NUMERIC_H
#include "node.h"
#include <math.h>
namespace PILS
{
	class WhoPropertyMinus
		: public CallWho
	{
	public:
		WhoPropertyMinus(const PropertyMinus *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class SinkPropertyMinus
		: public SinkProperty
	{
	public:
		SinkPropertyMinus(const WhoPropertyMinus &what)
			: SinkProperty(what)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class WhoFloatProperty
		: public CallWho
	{
	public:
		WhoFloatProperty(const FloatProperty *call, const Any *who)
			:  CallWho(call, who), function(call->function)
		{}
        const Step *step_(Runner &run) const override;
		double (*function)(double);
	};

	class SinkFloatProperty
		: public SinkProperty
	{
	public:
		SinkFloatProperty(const WhoFloatProperty &what)
			: SinkProperty(what)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class OperationPlusInteger
		: public NodeConstantTiny
	{
	public:
		OperationPlusInteger(const Constant *&link, const Integer *value)
			: NodeConstantTiny(link, BuiltinClicheOperationPlus::singleton, value)
		{}
        const CallWho* callWho(const Any *who) const override;
	};

	class OperationPlusFloat
		: public NodeConstantTiny
	{
	public:
		OperationPlusFloat(const Constant *&link, const Float *value)
			: NodeConstantTiny(link, BuiltinClicheOperationPlus::singleton, value)
		{}
        const CallWho* callWho(const Any *who) const override;
	};

	class OperationPlusTimestamp
		: public NodeConstantTiny
	{
	public:
		OperationPlusTimestamp(const Constant *&link, const Timestamp *value)
			: NodeConstantTiny(link, BuiltinClicheOperationPlus::singleton, value)
		{}
        const CallWho* callWho(const Any *who) const override;
	};

	class OperationPlusDuration
		: public NodeConstantTiny
	{
	public:
		OperationPlusDuration(const Constant *&link, const Duration *value)
			: NodeConstantTiny(link, BuiltinClicheOperationPlus::singleton, value)
		{}
        const CallWho* callWho(const Any *who) const override;
	};

	class OperationPlusPilsDate
		: public NodeConstantTiny
	{
	public:
		OperationPlusPilsDate(const Constant *&link, const PilsDate *value)
			: NodeConstantTiny(link, BuiltinClicheOperationPlus::singleton, value)
		{}
        const CallWho* callWho(const Any *who) const override;
	};

	class WhoPlusInteger
		: public CallWho
	{
	public:
		WhoPlusInteger(const OperationPlusInteger *value, const Any *who)
			: CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoPlusFloat
		: public CallWho
	{
	public:
		WhoPlusFloat(const OperationPlusFloat *value, const Any *who)
			: CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoPlusTimestamp
		: public CallWho
	{
	public:
		WhoPlusTimestamp(const OperationPlusTimestamp *value, const Any *who)
			: CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoPlusDuration
		: public CallWho
	{
	public:
		WhoPlusDuration(const OperationPlusDuration *value, const Any *who)
			: CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoPlusPilsDate
		: public CallWho
	{
	public:
		WhoPlusPilsDate(const OperationPlusPilsDate *value, const Any *who)
			: CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoExpressPlus
		: public WhoExpressOperation
	{
	public:
		WhoExpressPlus(const NodeExpressShort *call, const Any *who)
			: WhoExpressOperation(call, who)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const PilsDate *value) override;
        const Step *pass(Runner &run, const Timestamp *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoPlusRawInteger
		: public SinkWhoOperationRawInteger
	{
	public:
		SinkWhoPlusRawInteger(const WhoExpressOperation &what, long operand)
			: SinkWhoOperationRawInteger(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoPlusRawFloat
		: public SinkWhoOperationRawFloat
	{
	public:
		SinkWhoPlusRawFloat(const WhoExpressOperation &what, double operand)
			: SinkWhoOperationRawFloat(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoPlusUncountedInteger
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoPlusUncountedInteger(const CallWho &what, const Integer &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoPlusUncountedFloat
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoPlusUncountedFloat(const CallWho &what, const Float &operand)
			: SinkWhoOperationUncounted(what, operand)
        {}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoPlusUncountedTimestamp
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoPlusUncountedTimestamp(const CallWho &what, const Timestamp &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoPlusUncountedDuration
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoPlusUncountedDuration(const CallWho &what, const Duration &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
        const Step *pass(Runner &run, const Timestamp *value) override;
        const Step *pass(Runner &run, const PilsDate *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoPlusUncountedPilsDate
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoPlusUncountedPilsDate(const CallWho &what, const PilsDate &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoPlusInteger
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoPlusInteger(WhoExpressOperation &what, const Integer *operand)
			: SinkWhoOperationAny(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoPlusFloat
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoPlusFloat(WhoExpressOperation &what, const Float *operand)
			: SinkWhoOperationAny(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoPlusTimestamp
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoPlusTimestamp(WhoExpressOperation &what, const Timestamp *operand)
			: SinkWhoOperationAny(what, operand)
		{}
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoPlusDuration
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoPlusDuration(WhoExpressOperation &what, const Duration *operand)
			: SinkWhoOperationAny(what, operand)
		{}
        const Step *pass(Runner &run, const Timestamp *value) override;
        const Step *pass(Runner &run, const PilsDate *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoPlusPilsDate
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoPlusPilsDate(WhoExpressOperation &what, const PilsDate *operand)
			: SinkWhoOperationAny(what, operand)
		{}
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class OperationMinusInteger
		: public NodeConstantTiny
	{
	public:
		OperationMinusInteger(const Constant *&link, const Integer *value)
			: NodeConstantTiny(link, BuiltinClicheOperationMinus::singleton, value)
		{}
        const CallWho* callWho(const Any *who) const override;
	};

	class OperationMinusFloat
		: public NodeConstantTiny
	{
	public:
		OperationMinusFloat(const Constant *&link, const Float *value)
			: NodeConstantTiny(link, BuiltinClicheOperationMinus::singleton, value)
		{}
        const CallWho* callWho(const Any *who) const override;
	};

	class OperationMinusTimestamp
		: public NodeConstantTiny
	{
	public:
		OperationMinusTimestamp(const Constant *&link, const Timestamp *value)
			: NodeConstantTiny(link, BuiltinClicheOperationMinus::singleton, value)
		{}
        const CallWho* callWho(const Any *who) const override;
	};

	class OperationMinusDuration
		: public NodeConstantTiny
	{
	public:
		OperationMinusDuration(const Constant *&link, const Duration *value)
			: NodeConstantTiny(link, BuiltinClicheOperationMinus::singleton, value)
		{}
        const CallWho* callWho(const Any *who) const override;
	};

	class OperationMinusPilsDate
		: public NodeConstantTiny
	{
	public:
		OperationMinusPilsDate(const Constant *&link, const PilsDate *value)
			: NodeConstantTiny(link, BuiltinClicheOperationMinus::singleton, value)
		{}
        const CallWho* callWho(const Any *who) const override;
	};

	class WhoMinusInteger
		: public CallWho
	{
	public:
		WhoMinusInteger(const OperationMinusInteger *value, const Any *who)
			:  CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoMinusFloat
		: public CallWho
	{
	public:
		WhoMinusFloat(const OperationMinusFloat *value, const Any *who)
			:  CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoMinusTimestamp
		: public CallWho
	{
	public:
		WhoMinusTimestamp(const OperationMinusTimestamp *value, const Any *who)
			: CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoMinusDuration
		: public CallWho
	{
	public:
		WhoMinusDuration(const OperationMinusDuration *value, const Any *who)
			: CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoMinusPilsDate
		: public CallWho
	{
	public:
		WhoMinusPilsDate(const OperationMinusPilsDate *value, const Any *who)
			: CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoExpressMinus
		: public WhoExpressOperation
	{
	public:
		WhoExpressMinus(const NodeExpressShort *call, const Any *who)
			: WhoExpressOperation(call, who)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const PilsDate *value) override;
        const Step *pass(Runner &run, const Timestamp *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoMinusRawInteger
		: public SinkWhoOperationRawInteger
	{
	public:
		SinkWhoMinusRawInteger(const WhoExpressOperation &what, long operand)
			: SinkWhoOperationRawInteger(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoMinusRawFloat
		: public SinkWhoOperationRawFloat
	{
	public:
		SinkWhoMinusRawFloat(const WhoExpressOperation &what, double operand)
			: SinkWhoOperationRawFloat(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoMinusUncountedInteger
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoMinusUncountedInteger(const CallWho &what, const Integer &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoMinusUncountedFloat
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoMinusUncountedFloat(const CallWho &what, const Float &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoMinusUncountedTimestamp
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoMinusUncountedTimestamp(const CallWho &what, const Timestamp &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
        const Step *pass(Runner &run, const Timestamp *value) override;
	};

	class SinkWhoMinusUncountedDuration
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoMinusUncountedDuration(const CallWho &what, const Duration &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
        const Step *pass(Runner &run, const Timestamp *value) override;
        const Step *pass(Runner &run, const PilsDate *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoMinusUncountedPilsDate
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoMinusUncountedPilsDate(const CallWho &what, const PilsDate &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
        const Step *pass(Runner &run, const PilsDate *value) override;
	};

	class SinkWhoMinusInteger
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoMinusInteger(const WhoExpressOperation &what, const Integer *operand)
			: SinkWhoOperationAny(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoMinusFloat
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoMinusFloat(const WhoExpressOperation &what, const Float *operand)
			: SinkWhoOperationAny(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoMinusTimestamp
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoMinusTimestamp(const WhoExpressOperation &what, const Timestamp *operand)
			: SinkWhoOperationAny(what, operand)
		{}
        const Step *pass(Runner &run, const Timestamp *value) override;
	};

	class SinkWhoMinusDuration
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoMinusDuration(const WhoExpressOperation &what, const Duration *operand)
			: SinkWhoOperationAny(what, operand)
		{}
        const Step *pass(Runner &run, const Timestamp *value) override;
        const Step *pass(Runner &run, const PilsDate *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoMinusPilsDate
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoMinusPilsDate(const WhoExpressOperation &what, const PilsDate *operand)
			: SinkWhoOperationAny(what, operand)
		{}
        const Step *pass(Runner &run, const PilsDate *value) override;
	};

	class OperationTimesInteger
		: public NodeConstantTiny
	{
	public:
		OperationTimesInteger(const Constant *&link, const Integer *value)
			: NodeConstantTiny(link, BuiltinClicheOperationTimes::singleton, value)
		{}
        const CallWho* callWho(const Any *who) const override;
	};

	class OperationTimesFloat
		: public NodeConstantTiny
	{
	public:
		OperationTimesFloat(const Constant *&link, const Float *value)
			: NodeConstantTiny(link, BuiltinClicheOperationTimes::singleton, value)
		{}
        const CallWho* callWho(const Any *who) const override;
	};

	class OperationTimesDuration
		: public NodeConstantTiny
	{
	public:
		OperationTimesDuration(const Constant *&link, const Duration *value)
			: NodeConstantTiny(link, BuiltinClicheOperationTimes::singleton, value)
		{}
        const CallWho* callWho(const Any *who) const override;
	};

	class WhoTimesInteger
		: public CallWho
	{
	public:
		WhoTimesInteger(const OperationTimesInteger *value, const Any *who)
			:  CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoTimesFloat
		: public CallWho
	{
	public:
		WhoTimesFloat(const OperationTimesFloat *value, const Any *who)
			:  CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoTimesDuration
		: public CallWho
	{
	public:
		WhoTimesDuration(const OperationTimesDuration *value, const Any *who)
			: CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoExpressTimes
		: public WhoExpressOperation
	{
	public:
		WhoExpressTimes(const NodeExpressShort *call, const Any *who)
			: WhoExpressOperation(call, who)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoTimesRawInteger
		: public SinkWhoOperationRawInteger
	{
	public:
		SinkWhoTimesRawInteger(const WhoExpressOperation &what, long operand)
			: SinkWhoOperationRawInteger(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoTimesRawFloat
		: public SinkWhoOperationRawFloat
	{
	public:
		SinkWhoTimesRawFloat(const WhoExpressOperation &what, double operand)
			: SinkWhoOperationRawFloat(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoTimesUncountedInteger
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoTimesUncountedInteger(const CallWho &what, const Integer &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoTimesUncountedFloat
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoTimesUncountedFloat(const CallWho &what, const Float &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoTimesUncountedDuration
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoTimesUncountedDuration(const CallWho &what, const Duration &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoTimesInteger
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoTimesInteger(const WhoExpressOperation &what, const Integer *operand)
			: SinkWhoOperationAny(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoTimesFloat
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoTimesFloat(const WhoExpressOperation &what, const Float *operand)
			: SinkWhoOperationAny(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoTimesDuration
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoTimesDuration(const WhoExpressOperation &what, const Duration *operand)
			: SinkWhoOperationAny(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class OperationDivideInteger
		: public NodeConstantTiny
	{
	public:
		OperationDivideInteger(const Constant *&link, const Integer *value)
			: NodeConstantTiny(link, BuiltinClicheOperationDivide::singleton, value)
		{}
        const CallWho* callWho(const Any *who) const override;
	};

	class OperationDivideFloat
		: public NodeConstantTiny
	{
	public:
		OperationDivideFloat(const Constant *&link, const Float *value)
			: NodeConstantTiny(link, BuiltinClicheOperationDivide::singleton, value)
		{}
        const CallWho* callWho(const Any *who) const override;
	};

	class OperationDivideDuration
		: public NodeConstantTiny
	{
	public:
		OperationDivideDuration(const Constant *&link, const Duration *value)
			: NodeConstantTiny(link, BuiltinClicheOperationDivide::singleton, value)
		{}
        const CallWho* callWho(const Any *who) const override;
	};

	class WhoDivideInteger
		: public CallWho
	{
	public:
		WhoDivideInteger(const OperationDivideInteger *value, const Any *who)
			:  CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoDivideFloat
		: public CallWho
	{
	public:
		WhoDivideFloat(const OperationDivideFloat *value, const Any *who)
			:  CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoDivideDuration
		: public CallWho
	{
	public:
		WhoDivideDuration(const OperationDivideDuration *value, const Any *who)
			: CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoExpressDivide
		: public WhoExpressOperation
	{
	public:
		WhoExpressDivide(const NodeExpressShort *call, const Any *who)
			: WhoExpressOperation(call, who)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoDivideRawInteger
		: public SinkWhoOperationRawInteger
	{
	public:
		SinkWhoDivideRawInteger(const WhoExpressOperation &what, long operand)
			: SinkWhoOperationRawInteger(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoDivideRawFloat
		: public SinkWhoOperationRawFloat
	{
	public:
		SinkWhoDivideRawFloat(const WhoExpressOperation &what, double operand)
			: SinkWhoOperationRawFloat(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoDivideUncountedInteger
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoDivideUncountedInteger(const CallWho &what, const Integer &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoDivideUncountedFloat
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoDivideUncountedFloat(const CallWho &what, const Float &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoDivideUncountedDuration
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoDivideUncountedDuration(const CallWho &what, const Duration &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoDivideInteger
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoDivideInteger(const WhoExpressOperation &what, const Integer *operand)
			: SinkWhoOperationAny(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoDivideFloat
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoDivideFloat(const WhoExpressOperation &what, const Float *operand)
			: SinkWhoOperationAny(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoDivideDuration
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoDivideDuration(const WhoExpressOperation &what, const Duration *operand)
			: SinkWhoOperationAny(what, operand)
		{}
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class OperationIntegerDivideInteger
		: public NodeConstantTiny
	{
	public:
		OperationIntegerDivideInteger(const Constant *&link, const Integer *value)
			: NodeConstantTiny(link, BuiltinClicheOperationIntegerDivide::singleton, value)
		{}
        const CallWho* callWho(const Any *who) const override;
	};

	class OperationIntegerDivideFloat
		: public NodeConstantTiny
	{
	public:
		OperationIntegerDivideFloat(const Constant *&link, const Float *value)
			: NodeConstantTiny(link, BuiltinClicheOperationIntegerDivide::singleton, value)
		{}
        const CallWho* callWho(const Any *who) const override;
	};

	class OperationIntegerDivideDuration
		: public NodeConstantTiny
	{
	public:
		OperationIntegerDivideDuration(const Constant *&link, const Duration *value)
			: NodeConstantTiny(link, BuiltinClicheOperationIntegerDivide::singleton, value)
		{}
        const CallWho* callWho(const Any *who) const override;
	};

	class WhoIntegerDivideInteger
		: public CallWho
	{
	public:
		WhoIntegerDivideInteger(const OperationIntegerDivideInteger *value, const Any *who)
			:  CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoIntegerDivideFloat
		: public CallWho
	{
	public:
		WhoIntegerDivideFloat(const OperationIntegerDivideFloat *value, const Any *who)
			:  CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoIntegerDivideDuration
		: public CallWho
	{
	public:
		WhoIntegerDivideDuration(const OperationIntegerDivideDuration *value, const Any *who)
			: CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoExpressIntegerDivide
		: public WhoExpressOperation
	{
	public:
		WhoExpressIntegerDivide(const NodeExpressShort *call, const Any *who)
			: WhoExpressOperation(call, who)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoIntegerDivideRawInteger
		: public SinkWhoOperationRawInteger
	{
	public:
		SinkWhoIntegerDivideRawInteger(const WhoExpressOperation &what, long operand)
			: SinkWhoOperationRawInteger(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoIntegerDivideRawFloat
		: public SinkWhoOperationRawFloat
	{
	public:
		SinkWhoIntegerDivideRawFloat(const WhoExpressOperation &what, double operand)
			: SinkWhoOperationRawFloat(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoIntegerDivideUncountedInteger
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoIntegerDivideUncountedInteger(const CallWho &what, const Integer &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoIntegerDivideUncountedFloat
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoIntegerDivideUncountedFloat(const CallWho &what, const Float &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoIntegerDivideUncountedDuration
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoIntegerDivideUncountedDuration(const CallWho &what, const Duration &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkWhoIntegerDivideInteger
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoIntegerDivideInteger(const WhoExpressOperation &what, const Integer *operand)
			: SinkWhoOperationAny(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoIntegerDivideFloat
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoIntegerDivideFloat(const WhoExpressOperation &what, const Float *operand)
			: SinkWhoOperationAny(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoIntegerDivideDuration
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoIntegerDivideDuration(const WhoExpressOperation &what, const Duration *operand)
			: SinkWhoOperationAny(what, operand)
		{}
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class OperationModuloInteger
		: public NodeConstantTiny
	{
	public:
		OperationModuloInteger(const Constant *&link, const Integer *value)
			: NodeConstantTiny(link, BuiltinClicheOperationModulo::singleton, value)
		{}
        const CallWho* callWho(const Any *who) const override;
	};

	class OperationModuloFloat
		: public NodeConstantTiny
	{
	public:
		OperationModuloFloat(const Constant *&link, const Float *value)
			: NodeConstantTiny(link, BuiltinClicheOperationModulo::singleton, value)
		{}
        const CallWho* callWho(const Any *who) const override;
	};

	class WhoModuloInteger
		: public CallWho
	{
	public:
		WhoModuloInteger(const OperationModuloInteger *value, const Any *who)
			:  CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoModuloFloat
		: public CallWho
	{
	public:
		WhoModuloFloat(const OperationModuloFloat *value, const Any *who)
			:  CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoExpressModulo
		: public WhoExpressOperation
	{
	public:
		WhoExpressModulo(const NodeExpressShort *call, const Any *who)
			: WhoExpressOperation(call, who)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoModuloRawInteger
		: public SinkWhoOperationRawInteger
	{
	public:
		SinkWhoModuloRawInteger(const WhoExpressOperation &what, long operand)
			: SinkWhoOperationRawInteger(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoModuloRawFloat
		: public SinkWhoOperationRawFloat
	{
	public:
		SinkWhoModuloRawFloat(const WhoExpressOperation &what, double operand)
			: SinkWhoOperationRawFloat(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoModuloUncountedInteger
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoModuloUncountedInteger(const CallWho &what, const Integer &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoModuloUncountedFloat
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoModuloUncountedFloat(const CallWho &what, const Float &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoModuloInteger
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoModuloInteger(const WhoExpressOperation &what, const Integer *operand)
			: SinkWhoOperationAny(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkWhoModuloFloat
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoModuloFloat(const WhoExpressOperation &what, const Float *operand)
			: SinkWhoOperationAny(what, operand)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
	};

	class SinkTimescale
		: public SinkProperty
	{
        SinkTimescale *as_SinkTimescale() const;
	protected:
        SinkTimescale(const CallWho &what)
            : SinkProperty(what)
        {}
	};

	class WhoPropertyHexadecimal
		: public CallWho
	{
	public:
		WhoPropertyHexadecimal(const PropertyHexadecimal *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class SinkPropertyHexadecimal
		: public SinkProperty
	{
	public:
		SinkPropertyHexadecimal(const WhoPropertyHexadecimal &what)
			: SinkProperty(what)
		{}
        const Step *pass(Runner &run, const Integer *value) override;
	};

	class SinkRound
		: public SinkUntypedConstantOperation
	{
		using SinkUntypedConstantOperation::pass;
	public:
		SinkRound(const WhoUntypedOperation &what, const Constant *operand)
			: SinkUntypedConstantOperation(what, operand)
		{}
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const Timestamp *value) override;
        const Step *pass(Runner &run, const PilsDate *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};

	class SinkTruncate
		: public SinkUntypedConstantOperation
	{
		using SinkUntypedConstantOperation::pass;
	public:
		SinkTruncate(const WhoUntypedOperation &what, const Constant *operand)
			: SinkUntypedConstantOperation(what, operand)
		{}
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const Timestamp *value) override;
        const Step *pass(Runner &run, const PilsDate *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
	};


	class WhoPropertyLocalTime
		: public CallWho
	{
	public:
		WhoPropertyLocalTime(const PropertyLocalTime *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class SinkPropertyLocalTime
		: public SinkProperty
	{
	public:
		SinkPropertyLocalTime(const WhoPropertyLocalTime &what)
			: SinkProperty(what)
		{}
        const Step *pass(Runner &run, const Timestamp *value) override;
        const Step *pass(Runner &run, const PilsDate *value) override;
	};

	class WhoPropertyGreenwichMeanTime
		: public CallWho
	{
	public:
		WhoPropertyGreenwichMeanTime(const PropertyGreenwichMeanTime *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class SinkPropertyGreenwichMeanTime
		: public SinkProperty
	{
	public:
		SinkPropertyGreenwichMeanTime(const WhoPropertyGreenwichMeanTime &what)
			: SinkProperty(what)
		{}
        const Step *pass(Runner &run, const Timestamp *value) override;
        const Step *pass(Runner &run, const PilsDate *value) override;
	};
}
#endif
