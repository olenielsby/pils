/* This file is public domain */
#ifndef DEFINE_PILS_STATEMENT_H
#define DEFINE_PILS_STATEMENT_H
#include "pipe.h"
#include "language.h"
namespace PILS
{
	class StatementAssignConstant
		: public PokerShort
	{
	public:
		StatementAssignConstant(const PokerClicheShort &cliche, const Constant *expression)
			: PokerShort(cliche, expression)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class StatementAssignExpress
		: public PokerShort
	{
	public:
		StatementAssignExpress(const PokerClicheShort &cliche, const Express *expression)
			: PokerShort(cliche, expression)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class StatementAssignConstantContinue
		: public PokerTrailer
	{
	public:
		StatementAssignConstantContinue(const PokerClicheTrailer &cliche, const Any *const *element)
			: PokerTrailer(cliche, element)
		{}
        const CallWho *callWho(const Any *who) const override;
	private:
		const Constant *source;
	};

	class StatementAssignExpressContinue
		: public PokerTrailer
	{
	public:
        const CallWho *callWho(const Any *who) const override;
		StatementAssignExpressContinue(const PokerClicheTrailer &cliche, const Any *const *element)
			: PokerTrailer(cliche, element)
		{}
	private:
		const Express *source;
	};

	class WhoAssignConstant
		: public WhoAssignShort
	{
	public:
		WhoAssignConstant(const StatementAssignConstant *call, const Any *who)
			: WhoAssignShort(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoAssignExpress
		: public WhoAssignShort
	{
	public:
		WhoAssignExpress(const StatementAssignExpress *call, const Any *who)
			: WhoAssignShort(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoAssignConstantContinue
		: public WhoAssignContinue
	{
	public:
		WhoAssignConstantContinue(const StatementAssignConstantContinue *call, const Any *who)
			: WhoAssignContinue(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoAssignExpressContinue
		: public WhoAssignContinue
	{
	public:
		WhoAssignExpressContinue(const StatementAssignExpressContinue *call, const Any *who)
			: WhoAssignContinue(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class SinkAssign
		: public Sink
	{
	public:
        Sink *kick(Runner &run) override;
		SinkAssign(const WhoAssign &what)
			: what(what)
		{}
        const Step *pass(Runner &run, const Any *thing) override;
		const WhoAssign &what;
	};

	class SinkAssigning
		: public Sink
	{
	public:
		SinkAssigning(const WhoAssign &what, const Any *assignValue)
			: what(what), assignValue(assignValue)
		{}
        Sink *kick(Runner &run) override;
		const WhoAssign &what;
		const Any *assignValue;
	};

	class SinkAssigningCall
		: public SinkAssigning
	{
	public:
		SinkAssigningCall(const WhoAssign &what, const Any *assignValue)
			: SinkAssigning(what, assignValue)
		{}
        const Step *pass(Runner &run, const Any *thing) override;
	};

	class SinkAssigningArgument
		: public SinkAssigning
	{
	public:
		SinkAssigningArgument(const WhoAssign &what, const Any *assignValue)
			: SinkAssigning(what, assignValue)
		{}
        const Step *pass(Runner &run, const Any *thing) override;
	};

	class SinkAssigningWho
		: public SinkAssigning
	{
	public:
		SinkAssigningWho(const WhoAssign &what, const Any *assignValue, const Any *argument)
			: SinkAssigning(what, assignValue), argument(argument)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *thing) override;
        const Step *pass(Runner &run, SinkTaggedNodeBuilding &nodeBuilding) override;
        const Step *pass(Runner &run, PassingMind *mind, const Express *what) override;
		const Any *argument;
	};

	class SinkBind
		: public Sink
	{
	public:
		SinkBind(const Bind &what, const Any **done)
			: what(what), done(done)
		{}
        const Step *pass(Runner &run, const Any *thing) override;
        Sink *kick(Runner &run) override;
		const Bind &what;
		const Any **done;
	};

	class WhoEval
		: public CallWho
	{
	public:
        const Step *step_(Runner &run) const override;
		WhoEval(const OperatorEval *call, const Any *who)
			:  CallWho(call, who)
		{}
	};

	class OperationEvalConstant
		: public NodeConstantTiny
	{
	public:
        const CallWho *callWho(const Any *who) const override;
		OperationEvalConstant(const Constant *&link, const BuiltinClicheEval &cliche, const Constant *value)
			: NodeConstantTiny(link, cliche, value)
		{}
	};

	class OperationEvalExpress
		:public NodeExpressTiny
	{
	public:
        const CallWho *callWho(const Any *who) const override;
		OperationEvalExpress(const BuiltinClicheEval &cliche, const Express *value)
			: NodeExpressTiny(cliche, value)
		{}
	};

	class WhoEvalConstant
		: public CallWho
	{
	public:
        const Step *step_(Runner &run) const override;
		WhoEvalConstant(const NodeConstantTiny *call, const Any *who)
			:  CallWho(call, who)
		{}
	};

	class WhoEvalExpress
		: public CallWho
	{
	public:
        const Step *step_(Runner &run) const override;
		WhoEvalExpress(const NodeExpressTiny *call, const Any *who)
			:  CallWho(call, who)
		{}
	};

	class SinkEval
		: public Sink
	{
	public:
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
	};

	class SinkEvalOperand
		: public Sink
	{
	public:
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
		SinkEvalOperand(const Any &who)
			: who(who)
		{}
	private:
		const Any &who;
	};

	class SinkUntypedOperand
		: public Sink
	{
	public:
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
	private:
		friend class WhoUntypedOperationExpress;
		SinkUntypedOperand(const WhoUntypedOperationExpress &what)
			: what(what)
		{}
		const WhoUntypedOperationExpress &what;
	};

	class SinkUntypedOperandAssign
		: public Sink
	{
	public:
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
	private:
		friend class WhoUntypedOperationExpress;
		SinkUntypedOperandAssign(const WhoAssign &what, const Any *assignValue)
			: what(what), assignValue(assignValue)
		{}
		const WhoAssign &what;
		const Any *assignValue;
	};

	class Quote
		: public PokerShort
	{
	public:
		Quote(const BuiltinClicheQuote &cliche, const Any *element)
			: PokerShort(cliche, element)
		{}
        const Step *step_(Runner &run) const override;
        bool compileBuild(CompilingBuild &compiling) const override;
	};

	class Use
		: public PokerTrailer
	{
	public:
		Use(const BuiltinClicheUse &cliche, const Any *const *element)
			: PokerTrailer(cliche, element)
		{}
        const Step *step_(Runner &run) const override;
	private:
		const Any *dummy;
	};

	class UseRuleset
		: public Use
	{
	public:
		UseRuleset(const BuiltinClicheUse &cliche, const Any *const *element)
			: Use(cliche, element)
		{}
        const Step *step_(Runner &run) const override;
	};

	class UselineConstant
		: public NodeConstantTiny
	{
	public:
		UselineConstant(const Constant *&link, const BuiltinClicheUseline &cliche, const Constant *value)
			: NodeConstantTiny(link, cliche, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class UselineExpress
		: public NodeExpressTiny
	{
	public:
		UselineExpress(const BuiltinClicheUseline &cliche, const Express *value)
			: NodeExpressTiny(cliche, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class WhoUselineConstant
		: public CallWho
	{
	public:
		WhoUselineConstant(const UselineConstant *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoUselineExpress
		: public CallWho
	{
	public:
		WhoUselineExpress(const UselineExpress *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoUselineRuleset
		: public CallWho
	{
	public:
		WhoUselineRuleset(const UselineExpress *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class SinkUse
		: public Sink
	{
	public:
		SinkUse(const Any &statement)
			: statement(statement)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
	private:
		const Any &statement;
	};

	class SinkBut
		: public Sink
	{
	public:
		SinkBut(const Any *but)
			: but(but)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
	protected:
		const Any *but;
	};

	class SinkThrough
		: public SinkBut
	{
	public:
		SinkThrough(const Any *through)
			: SinkBut(through)
		{}
        const Step *pass(Runner &run, const Any *value) override;
	};

	class SinkAround
		: public SinkThrough
	{
	public:
		SinkAround(const Any *around)
			: SinkThrough(around)
		{}
        const Step *pass(Runner &run, const Any *value) override;
	};

	class SinkRepeat
		: public Sink
	{
	public:
		SinkRepeat(const Any *who, const WhoUntypedOperation &what)
			: who(who), what(what)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
	protected:
		const Any *who;
		const WhoUntypedOperation &what;
	};

	class SinkAgain
		: public SinkConstant
	{
	public:
        using SinkConstant::pass;
		SinkAgain(const Any *who, const WhoUntypedOperation &what)
			: who(who), what(what), old(nullptr), antique(nullptr), antiqueNumber(0x40), antiqueCountdown(0x40)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Constant *value) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *called(Runner &run, const Constant &call) override;
        const Step *called(Runner &run, const Integer &call) override;
        const Step *called(Runner &run, const ListConstant &call) override;
        const Step *called(Runner &run, const NodeConstant &call) override;
        const Step *called(Runner &run, const Empty &call) override;
        const Step *miss(Runner &run) override;
	private:
		const Any *who;
		const WhoUntypedOperation &what;
		const Constant *old;
		const Constant *antique;
		size_t antiqueNumber;
		size_t antiqueCountdown;
	};

	class SinkTrial
		: public SinkRepeat
	{
	public:
		SinkTrial(const Any *who, const WhoUntypedOperation &what)
			: SinkRepeat(who, what)
		{}
        const Step *pass(Runner &run, const Any *value) override;
	};

	class SinkRepeating
		: public Sink
	{
	public:
		SinkRepeating(const Any *item, const Any *who, const WhoUntypedOperation &what)
			: item(item), who(who), what(what)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *item) override;
        const Step *called(Runner &run, const Constant &call) override;
        const Step *called(Runner &run, const Integer &call) override;
        const Step *called(Runner &run, const ListConstant &call) override;
        const Step *called(Runner &run, const NodeConstant &call) override;
        const Step *called(Runner &run, const Empty &call) override;
        const Step *called(Runner &run, const ListExpress &call) override;
        const Step *called(Runner &run, const NodeExpress &call) override;
	protected:
		const Any *item;
		const Any *who;
		const WhoUntypedOperation &what;
	};

	class SinkTrialing
		: public SinkRepeating
	{
	public:
		SinkTrialing(const Any *item, const Any *who, const WhoUntypedOperation &what)
			: SinkRepeating(item, who, what)
		{}
        const Step *pass(Runner &run, const Any *item) override;
        virtual const Step *tailStep(Runner &run, const Any *thing, const Any *where_) override;
        virtual const Step *tailStep(Runner &run, const Any *thing) override;
	};

	class If
		: public PokerTrailer
	{
	public:
		If(const BuiltinClicheIf &cliche, const Any *const *element)
			: PokerTrailer(cliche, element)
		{}
        const Step *step_(Runner &run) const override;
	private:
		const Any *dummy;
	};

	class IfElse
		: public PokerTrailer
	{
	public:
		IfElse(const BuiltinClicheIfElse &cliche, const Any *const *element)
			: PokerTrailer(cliche, element)
		{}
        const Step *step_(Runner &run) const override;
	private:
		const Any *dummy[2];
	};

	class SinkIf
		: public SinkCondition
	{
	public:
        const Step *fail(Runner &run) override;
        const Step *succeed(Runner &run) override;
        Sink *kick(Runner &run) override;
		SinkIf(const Any &where_, const Any &clause)
			: where_(where_), clause(clause), elseClause(Empty::singleton)
		{}
		SinkIf(const Any &where_, const Any &clause, const Any &elseClause)
			: where_(where_), clause(clause), elseClause(elseClause)
		{}
	protected:
		const Any &where_;
		const Any &clause;
		const Any &elseClause;
	};

	class SinkWhoWorkaround
		: public SinkWhoCalling
	{
	public:
		SinkWhoWorkaround(const WhoUntypedOperation &what, const Any *who)
			: SinkWhoCalling(what, who)
		{}
        const Step *pass(Runner &run, const Any *value) override;
	};

	class SinkTransformSave
		: public Sink
	{
	public:
		SinkTransformSave(const WhoUntypedOperation &what, const Any *who, const Any *original)
			: what(what), who(who), original(original)
		{}
		using Sink::pass;
		virtual const Step *pass(Runner &run, const Any &value) = 0;
        const Step *called(Runner &run, const Constant &call) override;
        const Step *called(Runner &run, const Integer &call) override;
        const Step *called(Runner &run, const ListConstant &call) override;
        const Step *called(Runner &run, const NodeConstant &call) override;
        const Step *called(Runner &run, const Empty &call) override;
        const Step *called(Runner &run, const ListExpress &call) override;
        const Step *called(Runner &run, const NodeExpress &call) override;
        const Step *called(Runner &run, const Any &call, const Any *assignValue) override;
	protected:
		const WhoUntypedOperation &what;
		const Any *who;
		const Any *original;
	};

	class SinkTransformSaveBase
		: public SinkTransformSave
	{
	public:
		SinkTransformSaveBase(const WhoUntypedOperation &what, const Any *who, const Any *original)
			: SinkTransformSave(what, who, original)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *pass(Runner &run, const Any &value) override;
        const Step *tailStep(Runner &run, const Any *thing, const Any *where_) override;
        const Step *tailStep(Runner &run, const Any *thing) override;
	private:
	};

	/* This class us used both for node and list elements, both express
	   and constant. They only differ in the relatively rare case where
	   elements are changed by workouts, so there is little gain in splitting
	   the class.

	   Note: who and original fields are uncounted, as the constructor
	   declaration tells (const Any&), though SinkTransformSave declares them
	   as counted (const Any*). This is because they are used by the called(...)
	   methods common to the classes.

	   The first time an element of the node or list is changed by the
	   workout, the  'altered'  pointer is set to a temporary buffer which
	   holds the elements processed so far. The pointer follows the
	   insertions and must be reset to the start before it is copied
	   and deleted.
	*/

	class SinkTransformSaveElement
		: public SinkTransformSave
	{
        const Step *pass(Runner &run, const Any *value) override;
        const Step *pass(Runner &run, const Any &value) override;
	protected:
		SinkTransformSaveElement(const WhoUntypedOperation &what, const Any &who, const Any &original, const Any *const *element, const Any *const *end)
			: SinkTransformSave(what, &who, &original), element(element), end(end), altered(nullptr)
		{}
		const Any *const *element;
		const Any *const *end;
		const Any **altered;
	};

	class SinkTransformSaveListElement
		: public SinkTransformSaveElement
	{
	public:
		SinkTransformSaveListElement(const WhoUntypedOperation &what, const Any &who, const Any &original, const Any *const *element, const Any *const *end)
			: SinkTransformSaveElement(what, who, original, element, end), counting(Integer::get(0))
		{}
        Sink *kick(Runner &run) override;
        const Step *step_(Runner &run) const override;
		const Step *step_(Runner &run);
	private:
		const Integer *counting;
	};

	class SinkTransformSaveLeg
		: public SinkTransformSaveElement
	{
	public:
		SinkTransformSaveLeg(const WhoUntypedOperation &what, const Any &who, const Any &original, const Any *const *element, const Any *const *end, const Constant *const *name)
			: SinkTransformSaveElement(what, who, original, element, end), nameOffset((char *)name - (char *)element)
		{}
        Sink *kick(Runner &run) override;
        const Step *step_(Runner &run) const override;
		const Step *step_(Runner &run);
	private:
		const size_t nameOffset;
	};

	class SinkTransformForget
		: public SinkForget
	{
	public:
		SinkTransformForget(const WhoUntypedOperation &what, const Any *who)
			: what(what), who(who)
		{}
        const Step *called(Runner &run, const Constant &call) override;
        const Step *called(Runner &run, const Integer &call) override;
        const Step *called(Runner &run, const ListConstant &call) override;
        const Step *called(Runner &run, const NodeConstant &call) override;
        const Step *called(Runner &run, const Empty &call) override;
        const Step *called(Runner &run, const ListExpress &call) override;
        const Step *called(Runner &run, const NodeExpress &call) override;
        const Step *called(Runner &run, const Any &call, const Any *assignValue) override;
	protected:
		const WhoUntypedOperation &what;
		const Any *who;
	};

	class SinkTransformForgetBase
		: public SinkTransformForget
	{
	public:
        using SinkTransformForget::pass;
		SinkTransformForgetBase(const WhoUntypedOperation &what, const Any *who, const Any *original)
			: SinkTransformForget(what, who), original(original)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, long dummy) override;
        const Step *tailStep(Runner &run, const Any *thing, const Any *where_) override;
        const Step *tailStep(Runner &run, const Any *thing) override;
	private:
		const Any *original;
	};

	class SinkTransformForgetElement
		: public SinkTransformForget
	{
	public:
        using SinkTransformForget::pass;
        const Step *pass(Runner &run, long dummy) override;
	protected:
		SinkTransformForgetElement(const WhoUntypedOperation &what, const Any &who, const Any *const *element, const Any *const *end)
			: SinkTransformForget(what, &who), element(element), end(end)
		{}
		const Any *const *element;
		const Any *const *const end;
	};

	class SinkTransformForgetListElement
		: public SinkTransformForgetElement
	{
	public:
		SinkTransformForgetListElement(const WhoUntypedOperation &what, const Any &who, const Any *const *element, const Any *const *end)
			: SinkTransformForgetElement(what, who, element, end), counting(Integer::get(0))
		{}
        Sink *kick(Runner &run) override;
        const Step *step_(Runner &run) const override;
        const Step *step_(Runner &run);
	private:
		const Integer *counting;
	};

	class SinkTransformForgetLeg
		: public SinkTransformForgetElement
	{
	public:
		SinkTransformForgetLeg(const WhoUntypedOperation &what, const Any &who, const Any *const *element, const Any *const *end, const Constant *const *name)
			: SinkTransformForgetElement(what, who, element, end), nameOffset((char *)name - (char*)element)
		{}
        Sink *kick(Runner &run) override;
        const Step *step_(Runner &run) const override;
        const Step *step_(Runner &run);
	private:
		const size_t nameOffset;
	};

	class OrConstant
		: public NodeConstantTiny
	{
	public:
		OrConstant(const Constant *&link, const BuiltinClicheOr &cliche, const Constant *value)
			: NodeConstantTiny(link, cliche, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class OrExpress
		: public NodeExpressTiny
	{
	public:
		OrExpress(const BuiltinClicheOr &cliche, const Express *value)
			: NodeExpressTiny(cliche, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class WhoOrConstant
		: public CallWho
	{
	public:
		WhoOrConstant(const OrConstant *call, const Any *who)
			: CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoOrExpress
		: public CallWho
	{
	public:
		WhoOrExpress(const OrExpress *call, const Any *who)
			: CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class AndConstant
		: public NodeConstantTiny
	{
	public:
		AndConstant(const Constant *&link, const BuiltinClicheTiny &cliche, const Constant *value)
			: NodeConstantTiny(link, cliche, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class AndExpress
		: public NodeExpressTiny
	{
	public:
		AndExpress(const BuiltinClicheTiny &cliche, const Express *value)
			: NodeExpressTiny(cliche, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class WhoAndConstant
		: public CallWho
	{
	public:
		WhoAndConstant(const AndConstant *call, const Any *who)
			: CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoAndExpress
		: public CallWho
	{
	public:
		WhoAndExpress(const AndExpress *call, const Any *who)
			: CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class AnywayConstant
		: public AndConstant
	{
	public:
		AnywayConstant(const Constant *&link, const BuiltinClicheAnyway &cliche, const Constant *value)
			: AndConstant(link, cliche, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class AnywayExpress
		: public AndExpress
	{
	public:
		AnywayExpress(const BuiltinClicheAnyway &cliche, const Express *value)
			: AndExpress(cliche, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class WhoAnywayConstant
		: public WhoAndConstant
	{
	public:
		WhoAnywayConstant(const AnywayConstant *call, const Any *who)
			: WhoAndConstant(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoAnywayExpress
		: public WhoAndExpress
	{
	public:
		WhoAnywayExpress(const AnywayExpress *call, const Any *who)
			: WhoAndExpress(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class SinkWhoOr
		: public Sink
	{
	public:
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Any *const *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *tailStep(Runner &run, const Any *thing, const Any *where_) override;
        const Step *tailStep(Runner &run, const Any *thing) override;
        bool needsResult() override;
	protected:
		SinkWhoOr(const CallWho &what)
			: what(what)
		{}
		const CallWho &what;
	};

	class SinkWhoOrConstant
		: public SinkWhoOr
	{
	public:
		SinkWhoOrConstant(const WhoOrConstant &what)
			: SinkWhoOr(what)
		{}
        const Step *error(Runner &run, const Any *error, const Express *what, const Any *who) override;
        const Step *miss(Runner &run) override;
	};

	class SinkWhoOrExpress
		: public SinkWhoOr
	{
	public:
		SinkWhoOrExpress(const WhoOrExpress &what)
			: SinkWhoOr(what)
		{}
        const Step *error(Runner &run, const Any *error, const Express *what, const Any *who) override;
        const Step *miss(Runner &run) override;
	};

	class SinkWhoAnd
		: public SinkForget
	{
	public:
        Sink *kick(Runner &run) override;
        const Step *error(Runner &run, const Any *error, const Express *what, const Any *who) override;
        const Step *miss(Runner &run) override;
	protected:
		SinkWhoAnd(const CallWho &what)
			: what(what)
		{}
		const CallWho &what;
	};

	class SinkWhoAndConstant
		: public SinkWhoAnd
	{
	public:
        using SinkWhoAnd::pass;
		SinkWhoAndConstant(const WhoAndConstant &what)
			: SinkWhoAnd(what)
		{}
        const Step *pass(Runner &run, long value) override;
	};

	class SinkWhoAndExpress
		: public SinkWhoAnd
	{
	public:
        using SinkWhoAnd::pass;
		SinkWhoAndExpress(const WhoAndExpress &what)
			: SinkWhoAnd(what)
		{}
        const Step *pass(Runner &run, long value) override;
	};

	class SinkWhoAnywayConstant
		: public SinkWhoAndConstant
	{
	public:
		SinkWhoAnywayConstant(const WhoAnywayConstant &what)
			: SinkWhoAndConstant(what)
		{}
        const Step *error(Runner &run, const Any *error, const Express *what, const Any *who) override;
        const Step *miss(Runner &run) override;
	};

	class SinkWhoAnywayExpress
		: public SinkWhoAndExpress
	{
	public:
		SinkWhoAnywayExpress(const WhoAnywayExpress &what)
			: SinkWhoAndExpress(what)
		{}
        const Step *error(Runner &run, const Any *error, const Express *what, const Any *who) override;
        const Step *miss(Runner &run) override;
	};

	class PipeToGroups
		: public PipeToNowhere
	{
	public:
		PipeToGroups(const WhoUntypedOperation &what, const Any *filter)
			: what(what), filter(filter)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *item) override;
        const Step *pipeItem(Runner &run, const Any *item) override;
        const Step *pipeEnd(Runner &run) override;
        const Step *miss(Runner &run) override;
        void refer(Runner &run, const Express &what) override;
	private:
		friend class PipingToGroups;
		const WhoUntypedOperation &what;
		const Any *const filter;
		std::multimap<const Constant *, const Any *> multimap;
	};

	class PipingToGroups
		: public SinkConstant
	{
	public:
        using SinkConstant::pass;
		PipingToGroups(PipeToGroups &pipe, const Any *item)
			: pipe(pipe), item(item)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Constant *value) override;
        const Step *pass(Runner &run, const NodeExpressLong *value) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *miss(Runner &run) override;
	private:
		PipeToGroups &pipe;
		const Any * item;
	};

	class PipeToFirsts
		: public PipeToNowhere
	{
	public:
		PipeToFirsts(const WhoUntypedOperation &what, const Any *filter)
			: what(what), filter(filter)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *item) override;
        const Step *pipeItem(Runner &run, const Any *item) override;
        const Step *pipeEnd(Runner &run) override;
        const Step *miss(Runner &run) override;
        void refer(Runner &run, const Express &what) override;
		const WhoUntypedOperation &what;
		const Any *const filter;
		std::map<const Constant *, const Any *> map;
	};

	class PipingToFirsts
		: public SinkConstant
	{
	public:
        using SinkConstant::pass;
		PipingToFirsts(PipeToFirsts &pipe, const Any *item)
			: pipe(pipe), item(item)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Constant *value) override;
        const Step *pass(Runner &run, const NodeExpressLong *value) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *miss(Runner &run) override;
	protected:
		PipeToFirsts &pipe;
		const Any * item;
	};

	class PipeToLasts
		: public PipeToFirsts
	{
	public:
		PipeToLasts(const WhoUntypedOperation &what, const Any *filter)
			: PipeToFirsts(what, filter)
		{}
        const Step *pipeItem(Runner &run, const Any *item) override;
	};

	class PipingToLasts
		: public PipingToFirsts
	{
	public:
		PipingToLasts(PipeToLasts &pipe, const Any *item)
			: PipingToFirsts(pipe, item)
		{}
        const Step *pass(Runner &run, const Constant *value) override;
	};

	class PipeToSingles
		: public PipeToFirsts
	{
	public:
		PipeToSingles(const WhoUntypedOperation &what, const Any *filter)
			: PipeToFirsts(what, filter)
		{}
        const Step *pipeItem(Runner &run, const Any *item) override;
	};

	class PipingToSingles
		: public PipingToFirsts
	{
	public:
		PipingToSingles(PipeToSingles &pipe, const Any *item)
			: PipingToFirsts(pipe, item)
		{}
        const Step *pass(Runner &run, const Constant *value) override;
	};

	class PipeToFolds
		: public PipeToFirsts
	{
	public:
		PipeToFolds(const WhoUntypedOperation &what, const Any *filter)
			: PipeToFirsts(what, filter)
		{}
        const Step *pipeItem(Runner &run, const Any *item) override;
	};

	class PipingToFolds
		: public PipingToFirsts
	{
	public:
		PipingToFolds(PipeToFolds &pipe, const Any *item)
			: PipingToFirsts(pipe, item)
		{}
        const Step *pass(Runner &run, const Constant *value) override;
	};

	class FoldingToFolds
		: public Sink
	{
	public:
		FoldingToFolds(PipeToFolds &pipe, const Constant &key, const Any *oldValue)
			: pipe(pipe), key(key), oldValue(oldValue)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *miss(Runner &run) override;
	protected:
		PipeToFolds &pipe;
		const Constant &key;
		const Any *oldValue;
	};

	class SinkBug
		: public Sink
	{
	public:
		SinkBug(const Language *language)
			: language(language)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *pass(Runner &run, const PilsString *value) override;
	private:
		const Language *language;
		static void bug(Runner &run, const PilsString &bug);
	};

	class Comment
		: public PokerTrailer
	{
	public:
		Comment(const BuiltinClicheComment &cliche, const Any *const *element)
			: PokerTrailer(cliche, element)
		{}
        virtual const Step *step_(Runner &run) const override;
        virtual void compileRulePattern(Compiling &compiling, const Rule &rule) const override;
        virtual void compilePattern(Compiling &compiling) const override;
        virtual void compilePattern(Compiling &compiling, size_t offset) const override;
        virtual void compileAction(Compiling &compiling) const override;
        virtual const void *compilePatternIndex() const override;
        bool compileBuild(CompilingBuild &compiling) const override;
	private:
		const Any *comment;
	};

	class Combined
		: public PokerTrailer
	{
	public:
		Combined(const BuiltinClicheCombined &cliche, const Any *const *element)
			: PokerTrailer(cliche, element)
		{}
		Combined(const BuiltinClicheCombined &cliche, const Any *v1, const Any *v2)
			: PokerTrailer(cliche, v1, v2)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        const Step *calling(Runner &run, const ListExpress &call) const override;
        const Step *calling(Runner &run, const NodeExpress &call) const override;
	private:
		const Any *dummy;
	};

	class SinkCombine
		: public SinkHolding
	{
	public:
		SinkCombine(const Any *thing)
			: SinkHolding(thing)
		{}
        const Step *pass(Runner &run, const Any *value) override;
	};

	template <typename T> class SinkCallingCombined
		: public Sink
	{
	public:
		SinkCallingCombined(const T &call)
			: call(call)
		{}
        Sink *kick(Runner &run)
		{
			return this + 1;
		}

		const Step *called(Runner &run, const Empty &dummyCall)
		{
			const T &call = this->call;
			return (run.sink = this + 1)->called(run, call);
		}

		const Step *error(Runner &run, const Any *error, const Express *what, const Any *who)
		{
			return (run.sink = this + 1)->error(run, error, what, who);
		}

		bool needsResult()
		{
			return ((Sink *)(this + 1))->needsResult();
		}

		const Step *miss(Runner &run)
		{
			return ((Sink *)(this + 1))->miss(run);
		}

		const Step *pass(Runner &run, const Any *value)
		{
			run.sink = this + 1;
			return value->passCounted(run);
		}
	private:
		const T &call;
	};

	class SinkCallingCombinedHead
		: public Sink
	{
	public:
		SinkCallingCombinedHead(const Any &tail, const Any &who, const Express &what)
			: tail(tail), who(who), what(what)
		{}
        Sink *kick(Runner &run) override;
        const Step *called(Runner &run, const Constant &call) override;
        const Step *called(Runner &run, const Integer &call) override;
        const Step *called(Runner &run, const ListConstant &call) override;
        const Step *called(Runner &run, const NodeConstant &call) override;
        const Step *called(Runner &run, const Empty &call) override;
        const Step *called(Runner &run, const ListExpress &call) override;
        const Step *called(Runner &run, const NodeExpress &call) override;
        const Step *pass(Runner &run, const Any *value) override;
	private:
		const Any &tail;
		const Any &who;
		const Express &what;
	};

	class SinkCallingCombinedTail
		: public SinkHold
	{
	public:
		SinkCallingCombinedTail(const Any *thing)
			: SinkHold(thing)
		{}
        const Step *called(Runner &run, const Constant &call) override;
        const Step *called(Runner &run, const Integer &call) override;
        const Step *called(Runner &run, const ListConstant &call) override;
        const Step *called(Runner &run, const NodeConstant &call) override;
        const Step *called(Runner &run, const Empty &call) override;
        const Step *called(Runner &run, const ListExpress &call) override;
        const Step *called(Runner &run, const NodeExpress &call) override;
	};

	class SwitchClicheShort
		: public ClicheShort
	{
	public:
		SwitchClicheShort(const Constant *&link, const Constant *h, const Constant *a)
			: ClicheShort(link, h, a)
		{}
        const NodeConstantShort *newNode(const Constant *&link, const Integer *value) const override;
        const NodeConstantShort *newNode(const Constant *&link, const Float *value) const override;
        const NodeConstantShort *newNode(const Constant *&link, const PilsColor *value) const override;
        const NodeConstantShort *newNode(const Constant *&link, const PilsDate *value) const override;
        const NodeConstantShort *newNode(const Constant *&link, const Timestamp *value) const override;
        const NodeConstantShort *newNode(const Constant *&link, const Duration *value) const override;
        const NodeConstantShort *newNode(const Constant *&link, const PilsString *value) const override;
        const NodeConstantShort *newNode(const Constant *&link, const Cliche *value) const override;
        const NodeConstantShort *newNode(const Constant *&link, const NodeConstant *value) const override;
        const NodeConstantShort *newNode(const Constant *&link, const ListConstant *value) const override;
        const NodeConstantShort *newNode(const Constant *&link, const Special *value) const override;
        virtual const CallWho *whoOperation(const NodeExpressShort *operation, const Any *who) const override;
	};

	class SwitchConstantShort
		: public NodeConstantShort
	{
	public:
		SwitchConstantShort(const Constant *&link, const ClicheShort &cliche, const Constant *value)
			: NodeConstantShort(link, cliche, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class SwitchClicheLong
		: public ClicheLong
	{
	public:
		SwitchClicheLong(const Constant *&link, const Constant *h, const Constant *const *a, size_t c)
			: ClicheLong(link, h, a, c)
		{}
        const NodeConstantLong *newNodeConstant(const Constant *&link, const Constant *const *value) const override;
        const Any *node(const Any *const *element) const override;
	};

	class SwitchClicheTrailer
		: public ClicheTrailer
	{
	public:
		SwitchClicheTrailer(const Constant *&link, const Constant *h, const Constant *const *a, size_t c)
			: ClicheTrailer(link, h, a, c)
		{}
        const NodeConstantLong *newNodeConstant(const Constant *&link, const Constant *const *value) const override;
        const Any *node(const Any *const *element) const override;
	};

	class SwitchConstantLong
		: public NodeConstantLong
	{
	public:
		SwitchConstantLong(const Constant *&link, const ClicheLong &cliche, const Constant *const *value)
			: NodeConstantLong(link, cliche, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class SwitchConstantTrailer
		: public NodeConstantTrailer
	{
	public:
		SwitchConstantTrailer(const Constant *&link, const ClicheLong &cliche, const Constant *const *value)
			: NodeConstantTrailer(link, cliche, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class SwitchExpressLong
		: public NodeExpressLong
	{
	public:
		SwitchExpressLong(const SwitchClicheLong &cliche, const Any *const *value)
			: NodeExpressLong(cliche, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class SwitchExpressTrailer
		: public NodeExpressTrailer
	{
	public:
		SwitchExpressTrailer(const SwitchClicheTrailer &cliche, const Any *const *value)
			: NodeExpressTrailer(cliche, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class WhoSwitch
		: public CallWho
	{
	public:
        const Step *step_(Runner &run) const override;
		virtual const Step *miss(Runner &run, const Any *value) const = 0;
	protected:
		WhoSwitch(const Any *call, const Any *who)
			: CallWho(call, who)
		{}
	};

	class WhoSwitchCall
		: public WhoSwitch
	{
	public:
        const Step *miss(Runner &run, const Any *value) const override;
		WhoSwitchCall(const Any *call, const Any *who)
			: WhoSwitch(call, who)
		{}
	};

	class WhoSwitchTry
		: public WhoSwitch
	{
	public:
        const Step *miss(Runner &run, const Any *value) const override;
		WhoSwitchTry(const Any *call, const Any *who)
			: WhoSwitch(call, who)
		{}
	};

	class SinkSwitch
		: public Sink
	{
	public:
		SinkSwitch(const WhoSwitch &what)
			: what(what)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
	private:
		const WhoSwitch &what;
	};

	class WhoPropertyDistinct
		: public CallWho
	{
	public:
		WhoPropertyDistinct(const PropertyDistinct *call, const Any *who)
			: CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class PipeDistinct
		: public Pipe
	{
	public:
        using Pipe::pass;
		PipeDistinct(const WhoPropertyDistinct &what)
			: what(what)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *pipeBegin(Runner &run) override;
        const Step *pipeItem(Runner &run, const Any *item) override;
        const Step *pipeEnd(Runner &run) override;
	private:
		const WhoPropertyDistinct &what;
		std::set<const Any *> set;
	};

	class PipeDistinctFilter
		: public Pipe
	{
	public:
        using Pipe::pass;
		PipeDistinctFilter(const WhoUntypedOperation &what, const Any *filter)
			: what(what), filter(filter)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *pipeBegin(Runner &run) override;
        const Step *pipeItem(Runner &run, const Any *item) override;
        const Step *pipeEnd(Runner &run) override;
	private:
		friend class PipingDistinctFilter;
		const WhoUntypedOperation &what;
		std::set<const Constant *> set;
		const Any *const filter;
	};

	class PipingDistinctFilter
		: public SinkConstant
	{
	public:
        using SinkConstant::pass;
		PipingDistinctFilter(PipeDistinctFilter &pipe, const Any *item)
			: pipe(pipe), item(item)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Constant *value) override;
        const Step *pass(Runner &run, const NodeExpressLong *value) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *miss(Runner &run) override;
	private:
		PipeDistinctFilter &pipe;
		const Any * item;
	};

	class WhoPropertyCounts
		: public CallWho
	{
	public:
		WhoPropertyCounts(const PropertyCounts *call, const Any *who)
			: CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class PipeToCounts
		: public Pipe
	{
	public:
        using Pipe::pass;
		PipeToCounts(const WhoPropertyCounts &what)
			: what(what)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *pipeBegin(Runner &run) override;
        const Step *pipeItem(Runner &run, const Any *item) override;
        const Step *pipeEnd(Runner &run) override;
	private:
		const WhoPropertyCounts &what;
		std::map<const Constant *, double> map;
	};
}
#endif
