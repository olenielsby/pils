#ifndef DEFINE_PILS_RELATIONAL_H
#define DEFINE_PILS_RELATIONAL_H
#include "sink.h"
namespace PILS
{
	class OperationEqualConstant
		: public NodeConstantTiny
	{
	public:
		OperationEqualConstant(const HashedConstant *&link, const Constant *value)
			: NodeConstantTiny(link, BuiltinClicheOperationEqual::singleton, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class OperationEqualInteger
		: public OperationEqualConstant
	{
	public:
		OperationEqualInteger(const HashedConstant *&link, const Integer *value)
			: OperationEqualConstant(link, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class OperationEqualFloat
		: public OperationEqualConstant
	{
	public:
		OperationEqualFloat(const HashedConstant *&link, const Float *value)
			: OperationEqualConstant(link, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class OperationEqualString
		: public OperationEqualConstant
	{
	public:
		OperationEqualString(const HashedConstant *&link, const PilsString *value)
			: OperationEqualConstant(link, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class WhoEqualConstant
		: public CallWho
	{
	public:
		WhoEqualConstant(const OperationEqualConstant *value, const Any *who)
			:  CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
        void compilePattern(Compiling &compiling) const override;
	};

	class WhoEqualInteger
		: public WhoEqualConstant
	{
	public:
		WhoEqualInteger(const OperationEqualInteger *value, const Any *who)
			:  WhoEqualConstant(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoEqualFloat
		: public WhoEqualConstant
	{
	public:
		WhoEqualFloat(const OperationEqualFloat *value, const Any *who)
			:  WhoEqualConstant(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoEqualString
		: public WhoEqualConstant
	{
	public:
		WhoEqualString(const OperationEqualString *value, const Any *who)
			:  WhoEqualConstant(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoExpressEqual
		: public WhoExpressOperation
	{
	public:
		WhoExpressEqual(const NodeExpressShort *call, const Any *who)
			: WhoExpressOperation(call, who)
		{}
        const Step *step_(Runner &run) const override;
        void compilePattern(Compiling &compiling) const override;
	};

	class SinkEqualOperand
		: public SinkOperand
	{
	public:
		SinkEqualOperand(const WhoExpressEqual &what)
			: SinkOperand(what)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const PilsString &value);
		const Step *pass(Runner &run, const Cliche &value);
		const Step *pass(Runner &run, const ListConstant &value);
		const Step *pass(Runner &run, const NodeConstantShort &value);
		const Step *pass(Runner &run, const NodeConstantLong &value);
		const Step *pass(Runner &run, const Special &value);
		const Step *pass(Runner &run, const ListExpress &value);
		const Step *pass(Runner &run, const NodeExpressShort &value);
		const Step *pass(Runner &run, const NodeExpressLong &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const Duration *value);
		const Step *pass(Runner &run, const PilsString *value);
		const Step *pass(Runner &run, const Cliche *value);
		const Step *pass(Runner &run, const ListConstant *value);
		const Step *pass(Runner &run, const NodeConstantShort *value);
		const Step *pass(Runner &run, const NodeConstantLong *value);
		const Step *pass(Runner &run, const Special *value);
		const Step *pass(Runner &run, const ListExpress *value);
		const Step *pass(Runner &run, const NodeExpressShort *value);
		const Step *pass(Runner &run, const NodeExpressLong *value);
	};

	class SinkWhoCompareRawInteger
		: public SinkWhoOperationRawInteger
	{
	public:
		const Step *miss(Runner &run);
	protected:
		SinkWhoCompareRawInteger(const WhoExpressOperation &what, long operand)
			: SinkWhoOperationRawInteger(what, operand)
		{}
	};

	class SinkWhoEqualRawInteger
		: public SinkWhoCompareRawInteger
	{
	public:
		SinkWhoEqualRawInteger(const WhoExpressOperation &what, long operand)
			: SinkWhoCompareRawInteger(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const PilsString &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const PilsString *value);
		const Step *pass(Runner &run, const Any *value);
	};

	class SinkWhoCompareRawFloat
		: public SinkWhoOperationRawFloat
	{
	public:
		const Step *miss(Runner &run);
	protected:
		SinkWhoCompareRawFloat(const WhoExpressOperation &what, double operand)
			: SinkWhoOperationRawFloat(what, operand)
		{}
	};

	class SinkWhoEqualRawFloat
		: public SinkWhoCompareRawFloat
	{
	public:
		SinkWhoEqualRawFloat(const WhoExpressOperation &what, double operand)
			: SinkWhoCompareRawFloat(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const PilsString &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const PilsString *value);
		const Step *pass(Runner &run, const Any *value);
	};

	class SinkWhoCompareUncounted
		: public SinkWhoOperationUncounted
	{
	public:
		const Step *miss(Runner &run);
	protected:
		SinkWhoCompareUncounted(const CallWho &what, const Any &operand)
			: SinkWhoOperationUncounted(what, operand)
		{}
	};

	class SinkWhoEqualUncountedBad
		: public SinkWhoCompareUncounted
	{
	public:
		SinkWhoEqualUncountedBad(const CallWho &what, const Any &operand)
			: SinkWhoCompareUncounted(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const PilsString &value);
		const Step *pass(Runner &run, const Cliche &value);
		const Step *pass(Runner &run, const ListConstant &value);
		const Step *pass(Runner &run, const NodeConstantLong &value);
		const Step *pass(Runner &run, const NodeConstantShort &value);
		const Step *pass(Runner &run, const ListExpress &value);
		const Step *pass(Runner &run, const NodeExpressLong &value);
		const Step *pass(Runner &run, const NodeExpressShort &value);
		const Step *pass(Runner &run, const Special &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const Duration *value);
		const Step *pass(Runner &run, const PilsString *value);
		const Step *pass(Runner &run, const Cliche *value);
		const Step *pass(Runner &run, const ListConstant *value);
		const Step *pass(Runner &run, const NodeConstantLong *value);
		const Step *pass(Runner &run, const NodeConstantShort *value);
		const Step *pass(Runner &run, const ListExpress *value);
		const Step *pass(Runner &run, const NodeExpressLong *value);
		const Step *pass(Runner &run, const NodeExpressShort *value);
		const Step *pass(Runner &run, const Special *value);
		const Step *pass(Runner &run, const Any *value);
	};

	class SinkWhoCompareAny
		: public SinkWhoOperationAny
	{
	public:
		const Step *miss(Runner &run);
	protected:
		SinkWhoCompareAny(const WhoExpressOperation &what, const Any *operand)
			: SinkWhoOperationAny(what, operand)
		{}
	};

	class SinkWhoEqualBad
		: public SinkWhoCompareAny
	{
	public:
		SinkWhoEqualBad(const WhoExpressOperation &what, const Any *operand)
			: SinkWhoCompareAny(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const PilsString &value);
		const Step *pass(Runner &run, const Cliche &value);
		const Step *pass(Runner &run, const ListConstant &value);
		const Step *pass(Runner &run, const NodeConstantLong &value);
		const Step *pass(Runner &run, const NodeConstantShort &value);
		const Step *pass(Runner &run, const ListExpress &value);
		const Step *pass(Runner &run, const NodeExpressLong &value);
		const Step *pass(Runner &run, const NodeExpressShort &value);
		const Step *pass(Runner &run, const Special &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const Duration *value);
		const Step *pass(Runner &run, const PilsString *value);
		const Step *pass(Runner &run, const Cliche *value);
		const Step *pass(Runner &run, const ListConstant *value);
		const Step *pass(Runner &run, const NodeConstantLong *value);
		const Step *pass(Runner &run, const NodeConstantShort *value);
		const Step *pass(Runner &run, const ListExpress *value);
		const Step *pass(Runner &run, const NodeExpressLong *value);
		const Step *pass(Runner &run, const NodeExpressShort *value);
		const Step *pass(Runner &run, const Special *value);
		const Step *pass(Runner &run, const Any *value);
	};

	class SinkWhoEqualUncountedConstant
		: public SinkWhoEqualUncountedBad
	{
	public:
		SinkWhoEqualUncountedConstant(const CallWho &what, const Constant &operand)
			: SinkWhoEqualUncountedBad(what,operand)
		{}
		const Step *pass(Runner &run, const Cliche &value);
		const Step *pass(Runner &run, const ListConstant &value);
		const Step *pass(Runner &run, const NodeConstantLong &value);
		const Step *pass(Runner &run, const NodeConstantShort &value);
		const Step *pass(Runner &run, const Special &value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const Duration *value);
		const Step *pass(Runner &run, const Cliche *value);
		const Step *pass(Runner &run, const ListConstant *value);
		const Step *pass(Runner &run, const NodeConstantLong *value);
		const Step *pass(Runner &run, const NodeConstantShort *value);
		const Step *pass(Runner &run, const Special *value);
	};

	class SinkWhoEqualUncountedInteger
		: public SinkWhoEqualUncountedBad
	{
	public:
		SinkWhoEqualUncountedInteger(const CallWho &what, const Integer &operand)
			: SinkWhoEqualUncountedBad(what,operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Integer *value);
	};

	class SinkWhoEqualUncountedFloat
		: public SinkWhoEqualUncountedBad
	{
	public:
		SinkWhoEqualUncountedFloat(const CallWho &what, const Float &operand)
			: SinkWhoEqualUncountedBad(what,operand)
		{}
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoEqualUncountedString
		: public SinkWhoEqualUncountedBad
	{
	public:
		SinkWhoEqualUncountedString(const CallWho &what, const PilsString &operand)
			: SinkWhoEqualUncountedBad(what,operand)
		{}
		const Step *pass(Runner &run, const PilsString &value);
		const Step *pass(Runner &run, const PilsString *value);
	};

	class SinkWhoEqualUncountedExpress
		: public SinkWhoEqualUncountedBad
	{
	public:
		SinkWhoEqualUncountedExpress(const WhoExpressOperation &what, const Express &operand)
			: SinkWhoEqualUncountedBad(what, operand)
		{}
		const Step *pass(Runner &run, const ListExpress &value);
		const Step *pass(Runner &run, const NodeExpressLong &value);
		const Step *pass(Runner &run, const NodeExpressShort &value);
		const Step *pass(Runner &run, const ListExpress *value);
		const Step *pass(Runner &run, const NodeExpressLong *value);
		const Step *pass(Runner &run, const NodeExpressShort *value);
	};

	class SinkWhoEqualConstant
		: public SinkWhoEqualBad
	{
	public:
		SinkWhoEqualConstant(const WhoExpressOperation &what, const Constant *operand)
			: SinkWhoEqualBad(what, operand)
		{}
		const Step *pass(Runner &run, const Cliche &value);
		const Step *pass(Runner &run, const ListConstant &value);
		const Step *pass(Runner &run, const NodeConstantLong &value);
		const Step *pass(Runner &run, const NodeConstantShort &value);
		const Step *pass(Runner &run, const Special &value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const Duration *value);
		const Step *pass(Runner &run, const Cliche *value);
		const Step *pass(Runner &run, const ListConstant *value);
		const Step *pass(Runner &run, const NodeConstantLong *value);
		const Step *pass(Runner &run, const NodeConstantShort *value);
		const Step *pass(Runner &run, const Special *value);
	};

	class SinkWhoEqualInteger
		: public SinkWhoEqualBad
	{
	public:
		SinkWhoEqualInteger(const WhoExpressOperation &what, const Integer *operand)
			: SinkWhoEqualBad(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Integer *value);
	};

	class SinkWhoEqualFloat
		: public SinkWhoEqualBad
	{
	public:
		SinkWhoEqualFloat(const WhoExpressOperation &what, const Float *operand)
			: SinkWhoEqualBad(what, operand)
		{}
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoEqualString
		: public SinkWhoEqualBad
	{
	public:
		SinkWhoEqualString(const WhoExpressOperation &what, const PilsString *operand)
			: SinkWhoEqualBad(what, operand)
		{}
		const Step *pass(Runner &run, const PilsString &value);
		const Step *pass(Runner &run, const PilsString *value);
	};

	class SinkWhoEqualExpress
		: public SinkWhoEqualBad
	{
	public:
		SinkWhoEqualExpress(const WhoExpressOperation &what, const Express *operand)
			: SinkWhoEqualBad(what, operand)
		{}
		const Step *pass(Runner &run, const ListExpress &value);
		const Step *pass(Runner &run, const NodeExpressLong &value);
		const Step *pass(Runner &run, const NodeExpressShort &value);
		const Step *pass(Runner &run, const ListExpress *value);
		const Step *pass(Runner &run, const NodeExpressLong *value);
		const Step *pass(Runner &run, const NodeExpressShort *value);
	};

	class OperationNotEqualConstant
		: public NodeConstantTiny
	{
	public:
		OperationNotEqualConstant(const HashedConstant *&link, const Constant *value)
			: NodeConstantTiny(link, BuiltinClicheOperationNotEqual::singleton, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class OperationNotEqualInteger
		: public NodeConstantTiny
	{
	public:
		OperationNotEqualInteger(const HashedConstant *&link, const Integer *value)
			: NodeConstantTiny(link, BuiltinClicheOperationNotEqual::singleton, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class OperationNotEqualFloat
		: public NodeConstantTiny
	{
	public:
		OperationNotEqualFloat(const HashedConstant *&link, const Float *value)
			: NodeConstantTiny(link, BuiltinClicheOperationNotEqual::singleton, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class OperationNotEqualString
		: public NodeConstantTiny
	{
	public:
		OperationNotEqualString(const HashedConstant *&link, const PilsString *value)
			: NodeConstantTiny(link, BuiltinClicheOperationNotEqual::singleton, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class WhoNotEqualConstant
		: public CallWho
	{
	public:
		WhoNotEqualConstant(const OperationNotEqualConstant *value, const Any *who)
			:  CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoNotEqualInteger
		: public CallWho
	{
	public:
		WhoNotEqualInteger(const OperationNotEqualInteger *value, const Any *who)
			:  CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoNotEqualFloat
		: public CallWho
	{
	public:
		WhoNotEqualFloat(const OperationNotEqualFloat *value, const Any *who)
			:  CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoNotEqualString
		: public CallWho
	{
	public:
		WhoNotEqualString(const OperationNotEqualString *value, const Any *who)
			:  CallWho(value, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoExpressNotEqual
		: public WhoExpressOperation
	{
	public:
		WhoExpressNotEqual(const NodeExpressShort *call, const Any *who)
			: WhoExpressOperation(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class SinkNotEqualOperand
		: public SinkOperand
	{
	public:
		SinkNotEqualOperand(const WhoExpressNotEqual &what)
			: SinkOperand(what)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const PilsString &value);
		const Step *pass(Runner &run, const Cliche &value);
		const Step *pass(Runner &run, const ListConstant &value);
		const Step *pass(Runner &run, const NodeConstantShort &value);
		const Step *pass(Runner &run, const NodeConstantLong &value);
		const Step *pass(Runner &run, const Special &value);
		const Step *pass(Runner &run, const ListExpress &value);
		const Step *pass(Runner &run, const NodeExpressShort &value);
		const Step *pass(Runner &run, const NodeExpressLong &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const Duration *value);
		const Step *pass(Runner &run, const PilsString *value);
		const Step *pass(Runner &run, const Cliche *value);
		const Step *pass(Runner &run, const ListConstant *value);
		const Step *pass(Runner &run, const NodeConstantShort *value);
		const Step *pass(Runner &run, const NodeConstantLong *value);
		const Step *pass(Runner &run, const Special *value);
		const Step *pass(Runner &run, const ListExpress *value);
		const Step *pass(Runner &run, const NodeExpressShort *value);
		const Step *pass(Runner &run, const NodeExpressLong *value);
	};

	class SinkWhoNotEqualRawInteger
		: public SinkWhoCompareRawInteger
	{
	public:
		SinkWhoNotEqualRawInteger(const WhoExpressOperation &what, long operand)
			: SinkWhoCompareRawInteger(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const PilsString &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const PilsString *value);
		const Step *pass(Runner &run, const Any *value);
	};

	class SinkWhoNotEqualRawFloat
		: public SinkWhoCompareRawFloat
	{
	public:
		SinkWhoNotEqualRawFloat(const WhoExpressOperation &what, double operand)
			: SinkWhoCompareRawFloat(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const PilsString &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const PilsString *value);
		const Step *pass(Runner &run, const Any *value);
	};

	class SinkWhoNotEqualUncountedBad
		: public SinkWhoCompareUncounted
	{
	public:
		SinkWhoNotEqualUncountedBad(const CallWho &what, const Any &operand)
			: SinkWhoCompareUncounted(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const PilsString &value);
		const Step *pass(Runner &run, const Cliche &value);
		const Step *pass(Runner &run, const ListConstant &value);
		const Step *pass(Runner &run, const NodeConstantLong &value);
		const Step *pass(Runner &run, const NodeConstantShort &value);
		const Step *pass(Runner &run, const ListExpress &value);
		const Step *pass(Runner &run, const NodeExpressLong &value);
		const Step *pass(Runner &run, const NodeExpressShort &value);
		const Step *pass(Runner &run, const Special &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const Duration *value);
		const Step *pass(Runner &run, const PilsString *value);
		const Step *pass(Runner &run, const Cliche *value);
		const Step *pass(Runner &run, const ListConstant *value);
		const Step *pass(Runner &run, const NodeConstantLong *value);
		const Step *pass(Runner &run, const NodeConstantShort *value);
		const Step *pass(Runner &run, const ListExpress *value);
		const Step *pass(Runner &run, const NodeExpressLong *value);
		const Step *pass(Runner &run, const NodeExpressShort *value);
		const Step *pass(Runner &run, const Special *value);
		const Step *pass(Runner &run, const Any *value);
	};

	class SinkWhoNotEqualBad
		: public SinkWhoCompareAny
	{
	public:
		SinkWhoNotEqualBad(const WhoExpressOperation &what, const Any *operand)
			: SinkWhoCompareAny(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const PilsString &value);
		const Step *pass(Runner &run, const Cliche &value);
		const Step *pass(Runner &run, const ListConstant &value);
		const Step *pass(Runner &run, const NodeConstantLong &value);
		const Step *pass(Runner &run, const NodeConstantShort &value);
		const Step *pass(Runner &run, const ListExpress &value);
		const Step *pass(Runner &run, const NodeExpressLong &value);
		const Step *pass(Runner &run, const NodeExpressShort &value);
		const Step *pass(Runner &run, const Special &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const Duration *value);
		const Step *pass(Runner &run, const PilsString *value);
		const Step *pass(Runner &run, const Cliche *value);
		const Step *pass(Runner &run, const ListConstant *value);
		const Step *pass(Runner &run, const NodeConstantLong *value);
		const Step *pass(Runner &run, const NodeConstantShort *value);
		const Step *pass(Runner &run, const ListExpress *value);
		const Step *pass(Runner &run, const NodeExpressLong *value);
		const Step *pass(Runner &run, const NodeExpressShort *value);
		const Step *pass(Runner &run, const Special *value);
		const Step *pass(Runner &run, const Any *value);
	};

	class SinkWhoNotEqualUncountedConstant
		: public SinkWhoNotEqualUncountedBad
	{
	public:
		SinkWhoNotEqualUncountedConstant(const CallWho &what, const Constant &operand)
			: SinkWhoNotEqualUncountedBad(what,operand)
		{}
		const Step *pass(Runner &run, const Cliche &value);
		const Step *pass(Runner &run, const ListConstant &value);
		const Step *pass(Runner &run, const NodeConstantLong &value);
		const Step *pass(Runner &run, const NodeConstantShort &value);
		const Step *pass(Runner &run, const Special &value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const Duration *value);
		const Step *pass(Runner &run, const Cliche *value);
		const Step *pass(Runner &run, const ListConstant *value);
		const Step *pass(Runner &run, const NodeConstantLong *value);
		const Step *pass(Runner &run, const NodeConstantShort *value);
		const Step *pass(Runner &run, const Special *value);
	};

	class SinkWhoNotEqualUncountedInteger
		: public SinkWhoNotEqualUncountedBad
	{
	public:
		SinkWhoNotEqualUncountedInteger(const CallWho &what, const Integer &operand)
			: SinkWhoNotEqualUncountedBad(what,operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Integer *value);
	};

	class SinkWhoNotEqualUncountedFloat
		: public SinkWhoNotEqualUncountedBad
	{
	public:
		SinkWhoNotEqualUncountedFloat(const CallWho &what, const Float &operand)
			: SinkWhoNotEqualUncountedBad(what,operand)
		{}
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoNotEqualUncountedString
		: public SinkWhoNotEqualUncountedBad
	{
	public:
		SinkWhoNotEqualUncountedString(const CallWho &what, const PilsString &operand)
			: SinkWhoNotEqualUncountedBad(what,operand)
		{}
		const Step *pass(Runner &run, const PilsString &value);
		const Step *pass(Runner &run, const PilsString *value);
	};

	class SinkWhoNotEqualUncountedExpress
		: public SinkWhoNotEqualUncountedBad
	{
	public:
		SinkWhoNotEqualUncountedExpress(const WhoExpressOperation &what, const Express &operand)
			: SinkWhoNotEqualUncountedBad(what, operand)
		{}
		const Step *pass(Runner &run, const ListExpress &value);
		const Step *pass(Runner &run, const NodeExpressLong &value);
		const Step *pass(Runner &run, const NodeExpressShort &value);
		const Step *pass(Runner &run, const ListExpress *value);
		const Step *pass(Runner &run, const NodeExpressLong *value);
		const Step *pass(Runner &run, const NodeExpressShort *value);
	};

	class SinkWhoNotEqualConstant
		: public SinkWhoNotEqualBad
	{
	public:
		SinkWhoNotEqualConstant(const WhoExpressOperation &what, const Constant *operand)
			: SinkWhoNotEqualBad(what, operand)
		{}
		const Step *pass(Runner &run, const Cliche &value);
		const Step *pass(Runner &run, const ListConstant &value);
		const Step *pass(Runner &run, const NodeConstantLong &value);
		const Step *pass(Runner &run, const NodeConstantShort &value);
		const Step *pass(Runner &run, const Special &value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const Duration *value);
		const Step *pass(Runner &run, const Cliche *value);
		const Step *pass(Runner &run, const ListConstant *value);
		const Step *pass(Runner &run, const NodeConstantLong *value);
		const Step *pass(Runner &run, const NodeConstantShort *value);
		const Step *pass(Runner &run, const Special *value);
	};

	class SinkWhoNotEqualInteger
		: public SinkWhoNotEqualBad
	{
	public:
		SinkWhoNotEqualInteger(const WhoExpressOperation &what, const Integer *operand)
			: SinkWhoNotEqualBad(what, operand)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Integer *value);
	};

	class SinkWhoNotEqualFloat
		: public SinkWhoNotEqualBad
	{
	public:
		SinkWhoNotEqualFloat(const WhoExpressOperation &what, const Float *operand)
			: SinkWhoNotEqualBad(what, operand)
		{}
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkWhoNotEqualString
		: public SinkWhoNotEqualBad
	{
	public:
		SinkWhoNotEqualString(const WhoExpressOperation &what, const PilsString *operand)
			: SinkWhoNotEqualBad(what, operand)
		{}
		const Step *pass(Runner &run, const PilsString &value);
		const Step *pass(Runner &run, const PilsString *value);
	};

	class SinkWhoNotEqualExpress
		: public SinkWhoNotEqualBad
	{
	public:
		SinkWhoNotEqualExpress(const WhoExpressOperation &what, const Express *operand)
			: SinkWhoNotEqualBad(what, operand)
		{}
		const Step *pass(Runner &run, const ListExpress &value);
		const Step *pass(Runner &run, const NodeExpressLong &value);
		const Step *pass(Runner &run, const NodeExpressShort &value);
		const Step *pass(Runner &run, const ListExpress *value);
		const Step *pass(Runner &run, const NodeExpressLong *value);
		const Step *pass(Runner &run, const NodeExpressShort *value);
	};

	class OperationLessInteger
		: public NodeConstantTiny
	{
	public:
		OperationLessInteger(const HashedConstant *&link, const Integer *value)
			: NodeConstantTiny(link, BuiltinClicheOperationLess::singleton, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class OperationLessFloat
		: public NodeConstantTiny
	{
	public:
		OperationLessFloat(const HashedConstant *&link, const Float *value)
			: NodeConstantTiny(link, BuiltinClicheOperationLess::singleton, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class OperationLessString
		: public NodeConstantTiny
	{
	public:
		OperationLessString(const HashedConstant *&link, const PilsString *value)
			: NodeConstantTiny(link, BuiltinClicheOperationLess::singleton, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class OperationLessEqualInteger
		: public NodeConstantTiny
	{
	public:
		OperationLessEqualInteger(const HashedConstant *&link, const Integer *value)
			: NodeConstantTiny(link, BuiltinClicheOperationLessEqual::singleton, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class OperationLessEqualFloat
		: public NodeConstantTiny
	{
	public:
		OperationLessEqualFloat(const HashedConstant *&link, const Float *value)
			: NodeConstantTiny(link, BuiltinClicheOperationLessEqual::singleton, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class OperationLessEqualString
		: public NodeConstantTiny
	{
	public:
		OperationLessEqualString(const HashedConstant *&link, const PilsString *value)
			: NodeConstantTiny(link, BuiltinClicheOperationLessEqual::singleton, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class OperationGreaterInteger
		: public NodeConstantTiny
	{
	public:
		OperationGreaterInteger(const HashedConstant *&link, const Integer *value)
			: NodeConstantTiny(link, BuiltinClicheOperationGreater::singleton, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class OperationGreaterFloat
		: public NodeConstantTiny
	{
	public:
		OperationGreaterFloat(const HashedConstant *&link, const Float *value)
			: NodeConstantTiny(link, BuiltinClicheOperationGreater::singleton, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class OperationGreaterString
		: public NodeConstantTiny
	{
	public:
		OperationGreaterString(const HashedConstant *&link, const PilsString *value)
			: NodeConstantTiny(link, BuiltinClicheOperationGreater::singleton, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class OperationGreaterEqualInteger
		: public NodeConstantTiny
	{
	public:
		OperationGreaterEqualInteger(const HashedConstant *&link, const Integer *value)
			: NodeConstantTiny(link, BuiltinClicheOperationGreaterEqual::singleton, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class OperationGreaterEqualFloat
		: public NodeConstantTiny
	{
	public:
		OperationGreaterEqualFloat(const HashedConstant *&link, const Float *value)
			: NodeConstantTiny(link,  BuiltinClicheOperationGreaterEqual::singleton, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class OperationGreaterEqualString
		: public NodeConstantTiny
	{
	public:
		OperationGreaterEqualString(const HashedConstant *&link, const PilsString *value)
			: NodeConstantTiny(link,  BuiltinClicheOperationGreaterEqual::singleton, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class WhoLessInteger
		: public CallWho
	{
	public:
		WhoLessInteger(const OperationLessInteger *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoLessFloat
		: public CallWho
	{
	public:
		WhoLessFloat(const OperationLessFloat *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoLessString
		: public CallWho
	{
	public:
		WhoLessString(const OperationLessString *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoLessExpress
		: public CallWho
	{
	public:
		WhoLessExpress(const NodeExpressTiny *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoLessEqualInteger
		: public CallWho
	{
	public:
		WhoLessEqualInteger(const OperationLessEqualInteger *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoLessEqualFloat
		: public CallWho
	{
	public:
		WhoLessEqualFloat(const OperationLessEqualFloat *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoLessEqualString
		: public CallWho
	{
	public:
		WhoLessEqualString(const OperationLessEqualString *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoLessEqualExpress
		: public CallWho
	{
	public:
		WhoLessEqualExpress(const NodeExpressTiny *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoGreaterInteger
		: public CallWho
	{
	public:
		WhoGreaterInteger(const OperationGreaterInteger *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoGreaterFloat
		: public CallWho
	{
	public:
		WhoGreaterFloat(const OperationGreaterFloat *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoGreaterString
		: public CallWho
	{
	public:
		WhoGreaterString(const OperationGreaterString *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoGreaterExpress
		: public CallWho
	{
	public:
		WhoGreaterExpress(const NodeExpressTiny *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoGreaterEqualInteger
		: public CallWho
	{
	public:
		WhoGreaterEqualInteger(const OperationGreaterEqualInteger *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoGreaterEqualFloat
		: public CallWho
	{
	public:
		WhoGreaterEqualFloat(const OperationGreaterEqualFloat *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoGreaterEqualString
		: public CallWho
	{
	public:
		WhoGreaterEqualString(const OperationGreaterEqualString *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoGreaterEqualExpress
		: public CallWho
	{
	public:
		WhoGreaterEqualExpress(const NodeExpressTiny *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class SinkCompare
		: public Sink
	{
	protected:
		SinkCompare(const CallWho &what)
			: what(what)
		{}
		const CallWho &what;
	};

	class SinkCompareIntegerRaw
		: public SinkCompare
	{
	public:
		const Step *pass(Runner &run, const Any *who);
		Sink *kick(Runner &run);
		const Step *miss(Runner &run);
	protected:
		SinkCompareIntegerRaw(const CallWho &what, long value)
			: SinkCompare(what), value(value)
		{}
		long value;
	};

	class SinkCompareFloatRaw
		: public SinkCompare
	{
	public:
		const Step *pass(Runner &run, const Any *who);
		Sink *kick(Runner &run);
		const Step *miss(Runner &run);
	protected:
		SinkCompareFloatRaw(const CallWho &what, double value)
			: SinkCompare(what), value(value)
		{}
		double value;
	};

	class SinkCompareConstant
		: public SinkCompare
	{
	public:
		const Step *pass(Runner &run, const Any *who);
		Sink *kick(Runner &run);
		const Step *miss(Runner &run);
	protected:
		SinkCompareConstant(const CallWho &what, const Constant *value)
			: SinkCompare(what), value(value)
		{}
		const Constant *value;
	};

	class SinkCompareString
		: public SinkCompareConstant
	{
	protected:
		SinkCompareString(const CallWho &what, const PilsString *value)
			: SinkCompareConstant(what, value)
		{}
	};

	class SinkCompareTimestamp
		: public SinkCompareConstant
	{
	protected:
		SinkCompareTimestamp(const CallWho &what, const Timestamp *value)
			: SinkCompareConstant(what, value)
		{}
	};

	class SinkCompareDuration
		: public SinkCompareConstant
	{
	protected:
		SinkCompareDuration(const CallWho &what, const Duration *value)
			: SinkCompareConstant(what, value)
		{}
	};

	class SinkComparePilsDate
		: public SinkCompareConstant
	{
	protected:
		SinkComparePilsDate(const CallWho &what, const PilsDate *value)
			: SinkCompareConstant(what, value)
		{}
	};

	class SinkCompareOperand
		: public Sink
	{
		using Sink::pass;
	public:
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	protected:
		SinkCompareOperand(const CallWho &what)
			: what(what)
		{}
		const CallWho &what;
	};

	class SinkLessOperand
		: public SinkCompareOperand
	{
	public:
		SinkLessOperand(const WhoLessExpress &what)
			: SinkCompareOperand(what)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const PilsString *value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkLessIntegerRaw
		: public SinkCompareIntegerRaw
	{
	public:
		SinkLessIntegerRaw(const CallWho &what, long value)
			: SinkCompareIntegerRaw(what, value)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkLessFloatRaw
		: public SinkCompareFloatRaw
	{
	public:
		SinkLessFloatRaw(const CallWho &what, double value)
			: SinkCompareFloatRaw(what, value)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkLessString
		: public SinkCompareString
	{
	public:
		SinkLessString(const CallWho &what, const PilsString *value)
			: SinkCompareString(what, value)
		{}
		const Step *pass(Runner &run, const PilsString *value);
	};

	class SinkLessTimestamp
		: public SinkCompareTimestamp
	{
	public:
		SinkLessTimestamp(const CallWho &what, const Timestamp *value)
			: SinkCompareTimestamp(what, value)
		{}
		const Step *pass(Runner &run, const Timestamp *value);
	};

	class SinkLessDuration
		: public SinkCompareDuration
	{
	public:
		SinkLessDuration(const CallWho &what, const Duration *value)
			: SinkCompareDuration(what, value)
		{}
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkLessPilsDate
		: public SinkComparePilsDate
	{
	public:
		SinkLessPilsDate(const CallWho &what, const PilsDate *value)
			: SinkComparePilsDate(what, value)
		{}
		const Step *pass(Runner &run, const PilsDate *value);
	};

	class SinkLessEqualOperand
		: public SinkCompareOperand
	{
	public:
		SinkLessEqualOperand(const WhoLessEqualExpress &what)
			: SinkCompareOperand(what)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const PilsString *value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkLessEqualIntegerRaw
		: public SinkCompareIntegerRaw
	{
	public:
		SinkLessEqualIntegerRaw(const CallWho &what, long value)
			: SinkCompareIntegerRaw(what, value)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkLessEqualFloatRaw
		: public SinkCompareFloatRaw
	{
	public:
		SinkLessEqualFloatRaw(const CallWho &what, double value)
			: SinkCompareFloatRaw(what, value)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkLessEqualString
		: public SinkCompareString
	{
	public:
		SinkLessEqualString(const CallWho &what, const PilsString *value)
			: SinkCompareString(what, value)
		{}
		const Step *pass(Runner &run, const PilsString *value);
	};

	class SinkLessEqualTimestamp
		: public SinkCompareTimestamp
	{
	public:
		SinkLessEqualTimestamp(const CallWho &what, const Timestamp *value)
			: SinkCompareTimestamp(what, value)
		{}
		const Step *pass(Runner &run, const Timestamp *value);
	};

	class SinkLessEqualDuration
		: public SinkCompareDuration
	{
	public:
		SinkLessEqualDuration(const CallWho &what, const Duration *value)
			: SinkCompareDuration(what, value)
		{}
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkLessEqualPilsDate
		: public SinkComparePilsDate
	{
	public:
		SinkLessEqualPilsDate(const CallWho &what, const PilsDate *value)
			: SinkComparePilsDate(what, value)
		{}
		const Step *pass(Runner &run, const PilsDate *value);
	};

	class SinkGreaterOperand
		: public SinkCompareOperand
	{
	public:
		SinkGreaterOperand(const WhoGreaterExpress &what)
			: SinkCompareOperand(what)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const PilsString *value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkGreaterIntegerRaw
		: public SinkCompareIntegerRaw
	{
	public:
		SinkGreaterIntegerRaw(const CallWho &what, long value)
			: SinkCompareIntegerRaw(what, value)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkGreaterFloatRaw
		: public SinkCompareFloatRaw
	{
	public:
		SinkGreaterFloatRaw(const CallWho &what, double value)
			: SinkCompareFloatRaw(what, value)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkGreaterString
		: public SinkCompareString
	{
	public:
		SinkGreaterString(const CallWho &what, const PilsString *value)
			: SinkCompareString(what, value)
		{}
		const Step *pass(Runner &run, const PilsString *value);
	};

	class SinkGreaterTimestamp
		: public SinkCompareTimestamp
	{
	public:
		SinkGreaterTimestamp(const CallWho &what, const Timestamp *value)
			: SinkCompareTimestamp(what, value)
		{}
		const Step *pass(Runner &run, const Timestamp *value);
	};

	class SinkGreaterDuration
		: public SinkCompareDuration
	{
	public:
		SinkGreaterDuration(const CallWho &what, const Duration *value)
			: SinkCompareDuration(what, value)
		{}
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkGreaterPilsDate
		: public SinkComparePilsDate
	{
	public:
		SinkGreaterPilsDate(const CallWho &what, const PilsDate *value)
			: SinkComparePilsDate(what, value)
		{}
		const Step *pass(Runner &run, const PilsDate *value);
	};

	class SinkGreaterEqualOperand
		: public SinkCompareOperand
	{
	public:
		SinkGreaterEqualOperand(const WhoGreaterEqualExpress &what)
			: SinkCompareOperand(what)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const PilsString *value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkGreaterEqualIntegerRaw
		: public SinkCompareIntegerRaw
	{
	public:
		SinkGreaterEqualIntegerRaw(const CallWho &what, long value)
			: SinkCompareIntegerRaw(what, value)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkGreaterEqualFloatRaw
		: public SinkCompareFloatRaw
	{
	public:
		SinkGreaterEqualFloatRaw(const CallWho &what, double value)
			: SinkCompareFloatRaw(what, value)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
	};

	class SinkGreaterEqualString
		: public SinkCompareString
	{
	public:
		SinkGreaterEqualString(const CallWho &what, const PilsString *value)
			: SinkCompareString(what, value)
		{}
		const Step *pass(Runner &run, const PilsString *value);
	};

	class SinkGreaterEqualTimestamp
		: public SinkCompareTimestamp
	{
	public:
		SinkGreaterEqualTimestamp(const CallWho &what, const Timestamp *value)
			: SinkCompareTimestamp(what, value)
		{}
		const Step *pass(Runner &run, const Timestamp *value);
	};

	class SinkGreaterEqualDuration
		: public SinkCompareDuration
	{
	public:
		SinkGreaterEqualDuration(const CallWho &what, const Duration *value)
			: SinkCompareDuration(what, value)
		{}
		const Step *pass(Runner &run, const Duration *value);
	};

	class SinkGreaterEqualPilsDate
		: public SinkComparePilsDate
	{
	public:
		SinkGreaterEqualPilsDate(const CallWho &what, const PilsDate *value)
			: SinkComparePilsDate(what, value)
		{}
		const Step *pass(Runner &run, const PilsDate *value);
	};
}
#endif
