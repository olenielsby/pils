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
		const Step *step_(Runner &run) const;
	};

	class SinkPropertyMinus
		: public SinkProperty
	{
	public:
		SinkPropertyMinus(const WhoPropertyMinus &what)
			: SinkProperty(what)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class WhoFloatProperty
		: public CallWho
	{
	public:
		WhoFloatProperty(const FloatProperty *call, const Any *who)
			:  CallWho(call, who), function(call->function)
		{}
		const Step *step_(Runner &run) const;
		double (*function)(double);
		size_t unlinkAndGetSize();
	};

	class SinkFloatProperty
		: public SinkProperty
	{
	public:
		SinkFloatProperty(const WhoFloatProperty &what)
			: SinkProperty(what)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class OperationPlusInteger
		: public NodeConstantTiny
	{
	public:
		OperationPlusInteger(const HashedConstant *&link, const Integer *value)
			: NodeConstantTiny(link, BuiltinClicheOperationPlus::singleton, value)
		{}
		const CallWho* callWho(const Any *who) const;
	};

	class OperationPlusFloat
		: public NodeConstantTiny
	{
	public:
		OperationPlusFloat(const HashedConstant *&link, const Float *value)
			: NodeConstantTiny(link, BuiltinClicheOperationPlus::singleton, value)
		{}
		const CallWho* callWho(const Any *who) const;
	};

	class OperationPlusTimestamp
		: public NodeConstantTiny
	{
	public:
		OperationPlusTimestamp(const HashedConstant *&link, const Timestamp *value)
			: NodeConstantTiny(link, BuiltinClicheOperationPlus::singleton, value)
		{}
		const CallWho* callWho(const Any *who) const;
	};

	class OperationPlusDuration
		: public NodeConstantTiny
	{
	public:
		OperationPlusDuration(const HashedConstant *&link, const Duration *value)
			: NodeConstantTiny(link, BuiltinClicheOperationPlus::singleton, value)
		{}
		const CallWho* callWho(const Any *who) const;
	};

	class OperationPlusPilsDate
		: public NodeConstantTiny
	{
	public:
		OperationPlusPilsDate(const HashedConstant *&link, const PilsDate *value)
			: NodeConstantTiny(link, BuiltinClicheOperationPlus::singleton, value)
		{}
		const CallWho* callWho(const Any *who) const;
	};

	class WhoPlusInteger
		: public CallWho
	{
	public:
		WhoPlusInteger(const OperationPlusInteger *value, const Any *who)
			: CallWho(value, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoPlusFloat
		: public CallWho
	{
	public:
		WhoPlusFloat(const OperationPlusFloat *value, const Any *who)
			: CallWho(value, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoPlusTimestamp
		: public CallWho
	{
	public:
		WhoPlusTimestamp(const OperationPlusTimestamp *value, const Any *who)
			: CallWho(value, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoPlusDuration
		: public CallWho
	{
	public:
		WhoPlusDuration(const OperationPlusDuration *value, const Any *who)
			: CallWho(value, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoPlusPilsDate
		: public CallWho
	{
	public:
		WhoPlusPilsDate(const OperationPlusPilsDate *value, const Any *who)
			: CallWho(value, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoExpressPlus
		: public WhoExpressOperation
	{
	public:
		WhoExpressPlus(const NodeExpressShort *call, const Any *who)
			: WhoExpressOperation(call, who)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoPlusRawInteger
		: public SinkWhoOperationRawInteger
	{
	public:
		SinkWhoPlusRawInteger(const WhoExpressOperation &what, long operand)
			: SinkWhoOperationRawInteger(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoPlusRawFloat
		: public SinkWhoOperationRawFloat
	{
	public:
		SinkWhoPlusRawFloat(const WhoExpressOperation &what, double operand)
			: SinkWhoOperationRawFloat(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoPlusUncountedInteger
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoPlusUncountedInteger(const CallWho &what, const Integer &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoPlusUncountedFloat
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoPlusUncountedFloat(const CallWho &what, const Float &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
	const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoPlusUncountedTimestamp
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoPlusUncountedTimestamp(const CallWho &what, const Timestamp &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoPlusUncountedDuration
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoPlusUncountedDuration(const CallWho &what, const Duration &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoPlusUncountedPilsDate
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoPlusUncountedPilsDate(const CallWho &what, const PilsDate &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoPlusInteger
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoPlusInteger(WhoExpressOperation &what, const Integer *operand)
			: SinkWhoOperationAny(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoPlusFloat
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoPlusFloat(WhoExpressOperation &what, const Float *operand)
			: SinkWhoOperationAny(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoPlusTimestamp
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoPlusTimestamp(WhoExpressOperation &what, const Timestamp *operand)
			: SinkWhoOperationAny(what, operand)
		{}
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoPlusDuration
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoPlusDuration(WhoExpressOperation &what, const Duration *operand)
			: SinkWhoOperationAny(what, operand)
		{}
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoPlusPilsDate
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoPlusPilsDate(WhoExpressOperation &what, const PilsDate *operand)
			: SinkWhoOperationAny(what, operand)
		{}
		const Step *pass(Runner &run, const Duration *value);
	};

	class OperationMinusInteger
		: public NodeConstantTiny
	{
	public:
		OperationMinusInteger(const HashedConstant *&link, const Integer *value)
			: NodeConstantTiny(link, BuiltinClicheOperationMinus::singleton, value)
		{}
		const CallWho* callWho(const Any *who) const;
	};

	class OperationMinusFloat
		: public NodeConstantTiny
	{
	public:
		OperationMinusFloat(const HashedConstant *&link, const Float *value)
			: NodeConstantTiny(link, BuiltinClicheOperationMinus::singleton, value)
		{}
		const CallWho* callWho(const Any *who) const;
	};

	class OperationMinusTimestamp
		: public NodeConstantTiny
	{
	public:
		OperationMinusTimestamp(const HashedConstant *&link, const Timestamp *value)
			: NodeConstantTiny(link, BuiltinClicheOperationMinus::singleton, value)
		{}
		const CallWho* callWho(const Any *who) const;
	};

	class OperationMinusDuration
		: public NodeConstantTiny
	{
	public:
		OperationMinusDuration(const HashedConstant *&link, const Duration *value)
			: NodeConstantTiny(link, BuiltinClicheOperationMinus::singleton, value)
		{}
		const CallWho* callWho(const Any *who) const;
	};

	class OperationMinusPilsDate
		: public NodeConstantTiny
	{
	public:
		OperationMinusPilsDate(const HashedConstant *&link, const PilsDate *value)
			: NodeConstantTiny(link, BuiltinClicheOperationMinus::singleton, value)
		{}
		const CallWho* callWho(const Any *who) const;
	};

	class WhoMinusInteger
		: public CallWho
	{
	public:
		WhoMinusInteger(const OperationMinusInteger *value, const Any *who)
			:  CallWho(value, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoMinusFloat
		: public CallWho
	{
	public:
		WhoMinusFloat(const OperationMinusFloat *value, const Any *who)
			:  CallWho(value, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoMinusTimestamp
		: public CallWho
	{
	public:
		WhoMinusTimestamp(const OperationMinusTimestamp *value, const Any *who)
			: CallWho(value, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoMinusDuration
		: public CallWho
	{
	public:
		WhoMinusDuration(const OperationMinusDuration *value, const Any *who)
			: CallWho(value, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoMinusPilsDate
		: public CallWho
	{
	public:
		WhoMinusPilsDate(const OperationMinusPilsDate *value, const Any *who)
			: CallWho(value, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoExpressMinus
		: public WhoExpressOperation
	{
	public:
		WhoExpressMinus(const NodeExpressShort *call, const Any *who)
			: WhoExpressOperation(call, who)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoMinusRawInteger
		: public SinkWhoOperationRawInteger
	{
	public:
		SinkWhoMinusRawInteger(const WhoExpressOperation &what, long operand)
			: SinkWhoOperationRawInteger(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoMinusRawFloat
		: public SinkWhoOperationRawFloat
	{
	public:
		SinkWhoMinusRawFloat(const WhoExpressOperation &what, double operand)
			: SinkWhoOperationRawFloat(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoMinusUncountedInteger
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoMinusUncountedInteger(const CallWho &what, const Integer &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoMinusUncountedFloat
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoMinusUncountedFloat(const CallWho &what, const Float &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoMinusUncountedTimestamp
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoMinusUncountedTimestamp(const CallWho &what, const Timestamp &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
		const Step *pass(Runner &run, const Timestamp *value);
	};

	class SinkWhoMinusUncountedDuration
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoMinusUncountedDuration(const CallWho &what, const Duration &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoMinusUncountedPilsDate
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoMinusUncountedPilsDate(const CallWho &what, const PilsDate &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
		const Step *pass(Runner &run, const PilsDate *value);
	};

	class SinkWhoMinusInteger
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoMinusInteger(const WhoExpressOperation &what, const Integer *operand)
			: SinkWhoOperationAny(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoMinusFloat
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoMinusFloat(const WhoExpressOperation &what, const Float *operand)
			: SinkWhoOperationAny(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoMinusTimestamp
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoMinusTimestamp(const WhoExpressOperation &what, const Timestamp *operand)
			: SinkWhoOperationAny(what, operand)
		{}
		const Step *pass(Runner &run, const Timestamp *value);
	};

	class SinkWhoMinusDuration
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoMinusDuration(const WhoExpressOperation &what, const Duration *operand)
			: SinkWhoOperationAny(what, operand)
		{}
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoMinusPilsDate
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoMinusPilsDate(const WhoExpressOperation &what, const PilsDate *operand)
			: SinkWhoOperationAny(what, operand)
		{}
		const Step *pass(Runner &run, const PilsDate *value);
	};

	class OperationTimesInteger
		: public NodeConstantTiny
	{
	public:
		OperationTimesInteger(const HashedConstant *&link, const Integer *value)
			: NodeConstantTiny(link, BuiltinClicheOperationTimes::singleton, value)
		{}
		const CallWho* callWho(const Any *who) const;
	};

	class OperationTimesFloat
		: public NodeConstantTiny
	{
	public:
		OperationTimesFloat(const HashedConstant *&link, const Float *value)
			: NodeConstantTiny(link, BuiltinClicheOperationTimes::singleton, value)
		{}
		const CallWho* callWho(const Any *who) const;
	};

	class OperationTimesDuration
		: public NodeConstantTiny
	{
	public:
		OperationTimesDuration(const HashedConstant *&link, const Duration *value)
			: NodeConstantTiny(link, BuiltinClicheOperationTimes::singleton, value)
		{}
		const CallWho* callWho(const Any *who) const;
	};

	class WhoTimesInteger
		: public CallWho
	{
	public:
		WhoTimesInteger(const OperationTimesInteger *value, const Any *who)
			:  CallWho(value, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoTimesFloat
		: public CallWho
	{
	public:
		WhoTimesFloat(const OperationTimesFloat *value, const Any *who)
			:  CallWho(value, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoTimesDuration
		: public CallWho
	{
	public:
		WhoTimesDuration(const OperationTimesDuration *value, const Any *who)
			: CallWho(value, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoExpressTimes
		: public WhoExpressOperation
	{
	public:
		WhoExpressTimes(const NodeExpressShort *call, const Any *who)
			: WhoExpressOperation(call, who)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoTimesRawInteger
		: public SinkWhoOperationRawInteger
	{
	public:
		SinkWhoTimesRawInteger(const WhoExpressOperation &what, long operand)
			: SinkWhoOperationRawInteger(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoTimesRawFloat
		: public SinkWhoOperationRawFloat
	{
	public:
		SinkWhoTimesRawFloat(const WhoExpressOperation &what, double operand)
			: SinkWhoOperationRawFloat(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoTimesUncountedInteger
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoTimesUncountedInteger(const CallWho &what, const Integer &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoTimesUncountedFloat
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoTimesUncountedFloat(const CallWho &what, const Float &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoTimesUncountedDuration
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoTimesUncountedDuration(const CallWho &what, const Duration &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoTimesInteger
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoTimesInteger(const WhoExpressOperation &what, const Integer *operand)
			: SinkWhoOperationAny(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoTimesFloat
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoTimesFloat(const WhoExpressOperation &what, const Float *operand)
			: SinkWhoOperationAny(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoTimesDuration
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoTimesDuration(const WhoExpressOperation &what, const Duration *operand)
			: SinkWhoOperationAny(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class OperationDivideInteger
		: public NodeConstantTiny
	{
	public:
		OperationDivideInteger(const HashedConstant *&link, const Integer *value)
			: NodeConstantTiny(link, BuiltinClicheOperationDivide::singleton, value)
		{}
		const CallWho* callWho(const Any *who) const;
	};

	class OperationDivideFloat
		: public NodeConstantTiny
	{
	public:
		OperationDivideFloat(const HashedConstant *&link, const Float *value)
			: NodeConstantTiny(link, BuiltinClicheOperationDivide::singleton, value)
		{}
		const CallWho* callWho(const Any *who) const;
	};

	class OperationDivideDuration
		: public NodeConstantTiny
	{
	public:
		OperationDivideDuration(const HashedConstant *&link, const Duration *value)
			: NodeConstantTiny(link, BuiltinClicheOperationDivide::singleton, value)
		{}
		const CallWho* callWho(const Any *who) const;
	};

	class WhoDivideInteger
		: public CallWho
	{
	public:
		WhoDivideInteger(const OperationDivideInteger *value, const Any *who)
			:  CallWho(value, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoDivideFloat
		: public CallWho
	{
	public:
		WhoDivideFloat(const OperationDivideFloat *value, const Any *who)
			:  CallWho(value, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoDivideDuration
		: public CallWho
	{
	public:
		WhoDivideDuration(const OperationDivideDuration *value, const Any *who)
			: CallWho(value, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoExpressDivide
		: public WhoExpressOperation
	{
	public:
		WhoExpressDivide(const NodeExpressShort *call, const Any *who)
			: WhoExpressOperation(call, who)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoDivideRawInteger
		: public SinkWhoOperationRawInteger
	{
	public:
		SinkWhoDivideRawInteger(const WhoExpressOperation &what, long operand)
			: SinkWhoOperationRawInteger(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoDivideRawFloat
		: public SinkWhoOperationRawFloat
	{
	public:
		SinkWhoDivideRawFloat(const WhoExpressOperation &what, double operand)
			: SinkWhoOperationRawFloat(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoDivideUncountedInteger
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoDivideUncountedInteger(const CallWho &what, const Integer &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoDivideUncountedFloat
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoDivideUncountedFloat(const CallWho &what, const Float &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoDivideUncountedDuration
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoDivideUncountedDuration(const CallWho &what, const Duration &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoDivideInteger
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoDivideInteger(const WhoExpressOperation &what, const Integer *operand)
			: SinkWhoOperationAny(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoDivideFloat
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoDivideFloat(const WhoExpressOperation &what, const Float *operand)
			: SinkWhoOperationAny(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoDivideDuration
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoDivideDuration(const WhoExpressOperation &what, const Duration *operand)
			: SinkWhoOperationAny(what, operand)
		{}
		const Step *pass(Runner &run, const Duration *value);
	};

	class OperationIntegerDivideInteger
		: public NodeConstantTiny
	{
	public:
		OperationIntegerDivideInteger(const HashedConstant *&link, const Integer *value)
			: NodeConstantTiny(link, BuiltinClicheOperationIntegerDivide::singleton, value)
		{}
		const CallWho* callWho(const Any *who) const;
	};

	class OperationIntegerDivideFloat
		: public NodeConstantTiny
	{
	public:
		OperationIntegerDivideFloat(const HashedConstant *&link, const Float *value)
			: NodeConstantTiny(link, BuiltinClicheOperationIntegerDivide::singleton, value)
		{}
		const CallWho* callWho(const Any *who) const;
	};

	class OperationIntegerDivideDuration
		: public NodeConstantTiny
	{
	public:
		OperationIntegerDivideDuration(const HashedConstant *&link, const Duration *value)
			: NodeConstantTiny(link, BuiltinClicheOperationIntegerDivide::singleton, value)
		{}
		const CallWho* callWho(const Any *who) const;
	};

	class WhoIntegerDivideInteger
		: public CallWho
	{
	public:
		WhoIntegerDivideInteger(const OperationIntegerDivideInteger *value, const Any *who)
			:  CallWho(value, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoIntegerDivideFloat
		: public CallWho
	{
	public:
		WhoIntegerDivideFloat(const OperationIntegerDivideFloat *value, const Any *who)
			:  CallWho(value, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoIntegerDivideDuration
		: public CallWho
	{
	public:
		WhoIntegerDivideDuration(const OperationIntegerDivideDuration *value, const Any *who)
			: CallWho(value, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoExpressIntegerDivide
		: public WhoExpressOperation
	{
	public:
		WhoExpressIntegerDivide(const NodeExpressShort *call, const Any *who)
			: WhoExpressOperation(call, who)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoIntegerDivideRawInteger
		: public SinkWhoOperationRawInteger
	{
	public:
		SinkWhoIntegerDivideRawInteger(const WhoExpressOperation &what, long operand)
			: SinkWhoOperationRawInteger(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoIntegerDivideRawFloat
		: public SinkWhoOperationRawFloat
	{
	public:
		SinkWhoIntegerDivideRawFloat(const WhoExpressOperation &what, double operand)
			: SinkWhoOperationRawFloat(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoIntegerDivideUncountedInteger
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoIntegerDivideUncountedInteger(const CallWho &what, const Integer &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoIntegerDivideUncountedFloat
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoIntegerDivideUncountedFloat(const CallWho &what, const Float &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoIntegerDivideUncountedDuration
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoIntegerDivideUncountedDuration(const CallWho &what, const Duration &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkWhoIntegerDivideInteger
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoIntegerDivideInteger(const WhoExpressOperation &what, const Integer *operand)
			: SinkWhoOperationAny(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoIntegerDivideFloat
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoIntegerDivideFloat(const WhoExpressOperation &what, const Float *operand)
			: SinkWhoOperationAny(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoIntegerDivideDuration
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoIntegerDivideDuration(const WhoExpressOperation &what, const Duration *operand)
			: SinkWhoOperationAny(what, operand)
		{}
		const Step *pass(Runner &run, const Duration *value);
	};

	class OperationModuloInteger
		: public NodeConstantTiny
	{
	public:
		OperationModuloInteger(const HashedConstant *&link, const Integer *value)
			: NodeConstantTiny(link, BuiltinClicheOperationModulo::singleton, value)
		{}
		const CallWho* callWho(const Any *who) const;
	};

	class OperationModuloFloat
		: public NodeConstantTiny
	{
	public:
		OperationModuloFloat(const HashedConstant *&link, const Float *value)
			: NodeConstantTiny(link, BuiltinClicheOperationModulo::singleton, value)
		{}
		const CallWho* callWho(const Any *who) const;
	};

	class WhoModuloInteger
		: public CallWho
	{
	public:
		WhoModuloInteger(const OperationModuloInteger *value, const Any *who)
			:  CallWho(value, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoModuloFloat
		: public CallWho
	{
	public:
		WhoModuloFloat(const OperationModuloFloat *value, const Any *who)
			:  CallWho(value, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoExpressModulo
		: public WhoExpressOperation
	{
	public:
		WhoExpressModulo(const NodeExpressShort *call, const Any *who)
			: WhoExpressOperation(call, who)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoModuloRawInteger
		: public SinkWhoOperationRawInteger
	{
	public:
		SinkWhoModuloRawInteger(const WhoExpressOperation &what, long operand)
			: SinkWhoOperationRawInteger(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoModuloRawFloat
		: public SinkWhoOperationRawFloat
	{
	public:
		SinkWhoModuloRawFloat(const WhoExpressOperation &what, double operand)
			: SinkWhoOperationRawFloat(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoModuloUncountedInteger
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoModuloUncountedInteger(const CallWho &what, const Integer &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoModuloUncountedFloat
		: public SinkWhoOperationUncounted
	{
	public:
		SinkWhoModuloUncountedFloat(const CallWho &what, const Float &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoModuloInteger
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoModuloInteger(const WhoExpressOperation &what, const Integer *operand)
			: SinkWhoOperationAny(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoModuloFloat
		: public SinkWhoOperationAny
	{
	public:
		SinkWhoModuloFloat(const WhoExpressOperation &what, const Float *operand)
			: SinkWhoOperationAny(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
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
		const Step *step_(Runner &run) const;
	};

	class SinkPropertyHexadecimal
		: public SinkProperty
	{
	public:
		SinkPropertyHexadecimal(const WhoPropertyHexadecimal &what)
			: SinkProperty(what)
		{}
		const Step *pass(Runner &run, const Integer *value);
	};

	class SinkRound
		: public SinkUntypedConstantOperation
	{
		using SinkUntypedConstantOperation::pass;
	public:
		SinkRound(const WhoUntypedOperation &what, const Constant *operand)
			: SinkUntypedConstantOperation(what, operand)
		{}
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkTruncate
		: public SinkUntypedConstantOperation
	{
		using SinkUntypedConstantOperation::pass;
	public:
		SinkTruncate(const WhoUntypedOperation &what, const Constant *operand)
			: SinkUntypedConstantOperation(what, operand)
		{}
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Duration *value);
	};


	class WhoPropertyLocalTime
		: public CallWho
	{
	public:
		WhoPropertyLocalTime(const PropertyLocalTime *call, const Any *who)
			:  CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class SinkPropertyLocalTime
		: public SinkProperty
	{
	public:
		SinkPropertyLocalTime(const WhoPropertyLocalTime &what)
			: SinkProperty(what)
		{}
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const PilsDate *value);
	};

	class WhoPropertyGreenwichMeanTime
		: public CallWho
	{
	public:
		WhoPropertyGreenwichMeanTime(const PropertyGreenwichMeanTime *call, const Any *who)
			:  CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class SinkPropertyGreenwichMeanTime
		: public SinkProperty
	{
	public:
		SinkPropertyGreenwichMeanTime(const WhoPropertyGreenwichMeanTime &what)
			: SinkProperty(what)
		{}
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const PilsDate *value);
	};
}
#endif
