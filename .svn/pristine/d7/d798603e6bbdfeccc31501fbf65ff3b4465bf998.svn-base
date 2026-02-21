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
		const CallWho *callWho(const Any *who) const;
	};

	class StatementAssignExpress
		: public PokerShort
	{
	public:
		StatementAssignExpress(const PokerClicheShort &cliche, const Express *expression)
			: PokerShort(cliche, expression)
		{}
		const CallWho *callWho(const Any *who) const;
	};

	class StatementAssignConstantContinue
		: public PokerTrailer
	{
	public:
		StatementAssignConstantContinue(const PokerClicheTrailer &cliche, const Any *const *element)
			: PokerTrailer(cliche, element)
		{}
		const CallWho *callWho(const Any *who) const;
	private:
		const Constant *source;
	};

	class StatementAssignExpressContinue
		: public PokerTrailer
	{
	public:
		const CallWho *callWho(const Any *who) const;
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
		const Step *step_(Runner &run) const;
	};

	class WhoAssignExpress
		: public WhoAssignShort
	{
	public:
		WhoAssignExpress(const StatementAssignExpress *call, const Any *who)
			: WhoAssignShort(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoAssignConstantContinue
		: public WhoAssignContinue
	{
	public:
		WhoAssignConstantContinue(const StatementAssignConstantContinue *call, const Any *who)
			: WhoAssignContinue(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoAssignExpressContinue
		: public WhoAssignContinue
	{
	public:
		WhoAssignExpressContinue(const StatementAssignExpressContinue *call, const Any *who)
			: WhoAssignContinue(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class SinkAssign
		: public Sink
	{
	public:
		Sink *kick(Runner &run);
		SinkAssign(const WhoAssign &what)
			: what(what)
		{}
		const Step *pass(Runner &run, const Any *thing);
		const WhoAssign &what;
	};

	class SinkAssigning
		: public Sink
	{
	public:
		SinkAssigning(const WhoAssign &what, const Any *assignValue)
			: what(what), assignValue(assignValue)
		{}
		Sink *kick(Runner &run);
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
		const Step *pass(Runner &run, const Any *thing);
	};

	class SinkAssigningArgument
		: public SinkAssigning
	{
	public:
		SinkAssigningArgument(const WhoAssign &what, const Any *assignValue)
			: SinkAssigning(what, assignValue)
		{}
		const Step *pass(Runner &run, const Any *thing);
	};

	class SinkAssigningWho
		: public SinkAssigning
	{
	public:
		SinkAssigningWho(const WhoAssign &what, const Any *assignValue, const Any *argument)
			: SinkAssigning(what, assignValue), argument(argument)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *thing);
		const Step *pass(Runner &run, SinkTaggedNodeBuilding &nodeBuilding);
		const Step *pass(Runner &run, PassingMind *mind, const Express *what);
		const Any *argument;
	};

	class SinkBind
		: public Sink
	{
	public:
		SinkBind(const Bind &what, const Any **done)
			: what(what), done(done)
		{}
		const Step *pass(Runner &run, const Any *thing);
		Sink *kick(Runner &run);
		const Bind &what;
		const Any **done;
	};

	class WhoEval
		: public CallWho
	{
	public:
		const Step *step_(Runner &run) const;
		WhoEval(const OperatorEval *call, const Any *who)
			:  CallWho(call, who)
		{}
	};

	class OperationEvalConstant
		: public NodeConstantTiny
	{
	public:
		const CallWho *callWho(const Any *who) const;
		OperationEvalConstant(const HashedConstant *&link, const BuiltinClicheEval &cliche, const Constant *value)
			: NodeConstantTiny(link, cliche, value)
		{}
	};

	class OperationEvalExpress
		:public NodeExpressTiny
	{
	public:
		const CallWho *callWho(const Any *who) const;
		OperationEvalExpress(const BuiltinClicheEval &cliche, const Express *value)
			: NodeExpressTiny(cliche, value)
		{}
	};

	class WhoEvalConstant
		: public CallWho
	{
	public:
		const Step *step_(Runner &run) const;
		WhoEvalConstant(const NodeConstantTiny *call, const Any *who)
			:  CallWho(call, who)
		{}
	};

	class WhoEvalExpress
		: public CallWho
	{
	public:
		const Step *step_(Runner &run) const;
		WhoEvalExpress(const NodeExpressTiny *call, const Any *who)
			:  CallWho(call, who)
		{}
	};

	class SinkEval
		: public Sink
	{
	public:
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
	};

	class SinkEvalOperand
		: public Sink
	{
	public:
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
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
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
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
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
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
		const Step *step_(Runner &run) const;
		bool compileBuild(CompilingBuild &compiling) const;
	};

	class Use
		: public PokerTrailer
	{
	public:
		Use(const BuiltinClicheUse &cliche, const Any *const *element)
			: PokerTrailer(cliche, element)
		{}
		const Step *step_(Runner &run) const;
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
		const Step *step_(Runner &run) const;
	};

	class UselineConstant
		: public NodeConstantTiny
	{
	public:
		UselineConstant(const HashedConstant *&link, const BuiltinClicheUseline &cliche, const Constant *value)
			: NodeConstantTiny(link, cliche, value)
		{}
		const CallWho *callWho(const Any *who) const;
	};

	class UselineExpress
		: public NodeExpressTiny
	{
	public:
		UselineExpress(const BuiltinClicheUseline &cliche, const Express *value)
			: NodeExpressTiny(cliche, value)
		{}
		const CallWho *callWho(const Any *who) const;
	};

	class WhoUselineConstant
		: public CallWho
	{
	public:
		WhoUselineConstant(const UselineConstant *call, const Any *who)
			:  CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoUselineExpress
		: public CallWho
	{
	public:
		WhoUselineExpress(const UselineExpress *call, const Any *who)
			:  CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoUselineRuleset
		: public CallWho
	{
	public:
		WhoUselineRuleset(const UselineExpress *call, const Any *who)
			:  CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class SinkUse
		: public Sink
	{
	public:
		SinkUse(const Any &statement)
			: statement(statement)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
		const Step *pass(Runner &run, const ListConstant *value);
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
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
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
		const Step *pass(Runner &run, const Any *value);
	};

	class SinkAround
		: public SinkThrough
	{
	public:
		SinkAround(const Any *around)
			: SinkThrough(around)
		{}
		const Step *pass(Runner &run, const Any *value);
	};

	class SinkRepeat
		: public Sink
	{
	public:
		SinkRepeat(const Any *who, const WhoUntypedOperation &what)
			: who(who), what(what)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
	protected:
		const Any *who;
		const WhoUntypedOperation &what;
	};

	class SinkAgain
		: public SinkConstant
	{
	public:
		SinkAgain(const Any *who, const WhoUntypedOperation &what)
			: who(who), what(what), old(NULL), antique(NULL), antiqueNumber(0x40), antiqueCountdown(0x40)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Constant *value);
		const Step *pass(Runner &run, const Any *value);
		const Step *called(Runner &run, const Constant &call);
		const Step *called(Runner &run, const Integer &call);
		const Step *called(Runner &run, const ListConstant &call);
		const Step *called(Runner &run, const NodeConstant &call);
		const Step *called(Runner &run, const Empty &call);
		const Step *miss(Runner &run);
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
		const Step *pass(Runner &run, const Any *value);
	};

	class SinkRepeating
		: public Sink
	{
	public:
		SinkRepeating(const Any *item, const Any *who, const WhoUntypedOperation &what)
			: item(item), who(who), what(what)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *item);
		const Step *called(Runner &run, const Constant &call);
		const Step *called(Runner &run, const Integer &call);
		const Step *called(Runner &run, const ListConstant &call);
		const Step *called(Runner &run, const NodeConstant &call);
		const Step *called(Runner &run, const Empty &call);
		const Step *called(Runner &run, const ListExpress &call);
		const Step *called(Runner &run, const NodeExpress &call);
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
		const Step *pass(Runner &run, const Any *item);
		virtual const Step *tailStep(Runner &run, const Any *thing, const Any *where_);
		virtual const Step *tailStep(Runner &run, const Any *thing);
	};

	class If
		: public PokerTrailer
	{
	public:
		If(const BuiltinClicheIf &cliche, const Any *const *element)
			: PokerTrailer(cliche, element)
		{}
		const Step *step_(Runner &run) const;
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
		const Step *step_(Runner &run) const;
	private:
		const Any *dummy[2];
	};

	class SinkIf
		: public SinkCondition
	{
	public:
		const Step *fail(Runner &run);
		const Step *succeed(Runner &run);
		Sink *kick(Runner &run);
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
		const Step *pass(Runner &run, const Any *value);
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
		const Step *called(Runner &run, const Constant &call);
		const Step *called(Runner &run, const Integer &call);
		const Step *called(Runner &run, const ListConstant &call);
		const Step *called(Runner &run, const NodeConstant &call);
		const Step *called(Runner &run, const Empty &call);
		const Step *called(Runner &run, const ListExpress &call);
		const Step *called(Runner &run, const NodeExpress &call);
		const Step *called(Runner &run, const Any &call, const Any *assignValue);
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
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
		const Step *pass(Runner &run, const Any &value);
		const Step *tailStep(Runner &run, const Any *thing, const Any *where_);
		const Step *tailStep(Runner &run, const Any *thing);
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
		const Step *pass(Runner &run, const Any *value);
		const Step *pass(Runner &run, const Any &value);
	protected:
		SinkTransformSaveElement(const WhoUntypedOperation &what, const Any &who, const Any &original, const Any *const *element, const Any *const *end)
			: SinkTransformSave(what, &who, &original), element(element), end(end), altered(NULL)
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
		Sink *kick(Runner &run);
		const Step *step_(Runner &run) const;
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
		Sink *kick(Runner &run);
		const Step *step_(Runner &run) const;
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
		const Step *called(Runner &run, const Constant &call);
		const Step *called(Runner &run, const Integer &call);
		const Step *called(Runner &run, const ListConstant &call);
		const Step *called(Runner &run, const NodeConstant &call);
		const Step *called(Runner &run, const Empty &call);
		const Step *called(Runner &run, const ListExpress &call);
		const Step *called(Runner &run, const NodeExpress &call);
		const Step *called(Runner &run, const Any &call, const Any *assignValue);
	protected:
		const WhoUntypedOperation &what;
		const Any *who;
	};

	class SinkTransformForgetBase
		: public SinkTransformForget
	{
	public:
		SinkTransformForgetBase(const WhoUntypedOperation &what, const Any *who, const Any *original)
			: SinkTransformForget(what, who), original(original)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, long dummy);
		const Step *tailStep(Runner &run, const Any *thing, const Any *where_);
		const Step *tailStep(Runner &run, const Any *thing);
	private:
		const Any *original;
	};

	class SinkTransformForgetElement
		: public SinkTransformForget
	{
	public:
		const Step *pass(Runner &run, long dummy);
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
		Sink *kick(Runner &run);
		const Step *step_(Runner &run) const;
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
		Sink *kick(Runner &run);
		const Step *step_(Runner &run) const;
		const Step *step_(Runner &run);
	private:
		const size_t nameOffset;
	};

	class OrConstant
		: public NodeConstantTiny
	{
	public:
		OrConstant(const HashedConstant *&link, const BuiltinClicheOr &cliche, const Constant *value)
			: NodeConstantTiny(link, cliche, value)
		{}
		const CallWho *callWho(const Any *who) const;
	};

	class OrExpress
		: public NodeExpressTiny
	{
	public:
		OrExpress(const BuiltinClicheOr &cliche, const Express *value)
			: NodeExpressTiny(cliche, value)
		{}
		const CallWho *callWho(const Any *who) const;
	};

	class WhoOrConstant
		: public CallWho
	{
	public:
		WhoOrConstant(const OrConstant *call, const Any *who)
			: CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoOrExpress
		: public CallWho
	{
	public:
		WhoOrExpress(const OrExpress *call, const Any *who)
			: CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class AndConstant
		: public NodeConstantTiny
	{
	public:
		AndConstant(const HashedConstant *&link, const BuiltinClicheTiny &cliche, const Constant *value)
			: NodeConstantTiny(link, cliche, value)
		{}
		const CallWho *callWho(const Any *who) const;
	};

	class AndExpress
		: public NodeExpressTiny
	{
	public:
		AndExpress(const BuiltinClicheTiny &cliche, const Express *value)
			: NodeExpressTiny(cliche, value)
		{}
		const CallWho *callWho(const Any *who) const;
	};

	class WhoAndConstant
		: public CallWho
	{
	public:
		WhoAndConstant(const AndConstant *call, const Any *who)
			: CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoAndExpress
		: public CallWho
	{
	public:
		WhoAndExpress(const AndExpress *call, const Any *who)
			: CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class AnywayConstant
		: public AndConstant
	{
	public:
		AnywayConstant(const HashedConstant *&link, const BuiltinClicheAnyway &cliche, const Constant *value)
			: AndConstant(link, cliche, value)
		{}
		const CallWho *callWho(const Any *who) const;
	};

	class AnywayExpress
		: public AndExpress
	{
	public:
		AnywayExpress(const BuiltinClicheAnyway &cliche, const Express *value)
			: AndExpress(cliche, value)
		{}
		const CallWho *callWho(const Any *who) const;
	};

	class WhoAnywayConstant
		: public WhoAndConstant
	{
	public:
		WhoAnywayConstant(const AnywayConstant *call, const Any *who)
			: WhoAndConstant(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoAnywayExpress
		: public WhoAndExpress
	{
	public:
		WhoAnywayExpress(const AnywayExpress *call, const Any *who)
			: WhoAndExpress(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class SinkWhoOr
		: public Sink
	{
	public:
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count);
		const Step *pass(Runner &run, const Any *anchor, const Any *const *range, size_t count);
		const Step *pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count);
		const Step *pass(Runner &run, const Any *value);
		const Step *tailStep(Runner &run, const Any *thing, const Any *where_);
		const Step *tailStep(Runner &run, const Any *thing);
		bool needsResult();
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
		const Step *error(Runner &run, const Any *error, const Express *what, const Any *who);
		const Step *miss(Runner &run);
	};

	class SinkWhoOrExpress
		: public SinkWhoOr
	{
	public:
		SinkWhoOrExpress(const WhoOrExpress &what)
			: SinkWhoOr(what)
		{}
		const Step *error(Runner &run, const Any *error, const Express *what, const Any *who);
		const Step *miss(Runner &run);
	};

	class SinkWhoAnd
		: public SinkForget
	{
	public:
		Sink *kick(Runner &run);
		const Step *error(Runner &run, const Any *error, const Express *what, const Any *who);
		const Step *miss(Runner &run);
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
		SinkWhoAndConstant(const WhoAndConstant &what)
			: SinkWhoAnd(what)
		{}
		const Step *pass(Runner &run, long value);
	};

	class SinkWhoAndExpress
		: public SinkWhoAnd
	{
	public:
		SinkWhoAndExpress(const WhoAndExpress &what)
			: SinkWhoAnd(what)
		{}
		const Step *pass(Runner &run, long value);
	};

	class SinkWhoAnywayConstant
		: public SinkWhoAndConstant
	{
	public:
		SinkWhoAnywayConstant(const WhoAnywayConstant &what)
			: SinkWhoAndConstant(what)
		{}
		const Step *error(Runner &run, const Any *error, const Express *what, const Any *who);
		const Step *miss(Runner &run);
	};

	class SinkWhoAnywayExpress
		: public SinkWhoAndExpress
	{
	public:
		SinkWhoAnywayExpress(const WhoAnywayExpress &what)
			: SinkWhoAndExpress(what)
		{}
		const Step *error(Runner &run, const Any *error, const Express *what, const Any *who);
		const Step *miss(Runner &run);
	};

	class PipeToGroups
		: public PipeToNowhere
	{
	public:
		PipeToGroups(const WhoUntypedOperation &what, const Any *filter)
			: what(what), filter(filter)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *item);
		const Step *pipeItem(Runner &run, const Any *item);
		const Step *pipeEnd(Runner &run);
		const Step *miss(Runner &run);
		void refer(Runner &run, const Express &what);
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
		PipingToGroups(PipeToGroups &pipe, const Any *item)
			: pipe(pipe), item(item)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Constant *value);
		const Step *pass(Runner &run, const NodeExpressLong *value);
		const Step *pass(Runner &run, const Any *value);
		const Step *miss(Runner &run);
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
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *item);
		const Step *pipeItem(Runner &run, const Any *item);
		const Step *pipeEnd(Runner &run);
		const Step *miss(Runner &run);
		void refer(Runner &run, const Express &what);
		const WhoUntypedOperation &what;
		const Any *const filter;
		std::map<const Constant *, const Any *> map;
	};

	class PipingToFirsts
		: public SinkConstant
	{
	public:
		PipingToFirsts(PipeToFirsts &pipe, const Any *item)
			: pipe(pipe), item(item)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Constant *value);
		const Step *pass(Runner &run, const NodeExpressLong *value);
		const Step *pass(Runner &run, const Any *value);
		const Step *miss(Runner &run);
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
		const Step *pipeItem(Runner &run, const Any *item);
	};

	class PipingToLasts
		: public PipingToFirsts
	{
	public:
		PipingToLasts(PipeToLasts &pipe, const Any *item)
			: PipingToFirsts(pipe, item)
		{}
		const Step *pass(Runner &run, const Constant *value);
	};

	class PipeToSingles
		: public PipeToFirsts
	{
	public:
		PipeToSingles(const WhoUntypedOperation &what, const Any *filter)
			: PipeToFirsts(what, filter)
		{}
		const Step *pipeItem(Runner &run, const Any *item);
	};

	class PipingToSingles
		: public PipingToFirsts
	{
	public:
		PipingToSingles(PipeToSingles &pipe, const Any *item)
			: PipingToFirsts(pipe, item)
		{}
		const Step *pass(Runner &run, const Constant *value);
	};

	class PipeToFolds
		: public PipeToFirsts
	{
	public:
		PipeToFolds(const WhoUntypedOperation &what, const Any *filter)
			: PipeToFirsts(what, filter)
		{}
		const Step *pipeItem(Runner &run, const Any *item);
	};

	class PipingToFolds
		: public PipingToFirsts
	{
	public:
		PipingToFolds(PipeToFolds &pipe, const Any *item)
			: PipingToFirsts(pipe, item)
		{}
		const Step *pass(Runner &run, const Constant *value);
	};

	class FoldingToFolds
		: public Sink
	{
	public:
		FoldingToFolds(PipeToFolds &pipe, const Constant &key, const Any *oldValue)
			: pipe(pipe), key(key), oldValue(oldValue)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
		const Step *miss(Runner &run);
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
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
		const Step *pass(Runner &run, const PilsString *value);
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
		virtual const Step *step_(Runner &run) const;
		virtual void compileRulePattern(Compiling &compiling, const Rule &rule) const;
		virtual void compilePattern(Compiling &compiling) const;
		virtual void compilePattern(Compiling &compiling, size_t offset) const;
		virtual void compileAction(Compiling &compiling) const;
		virtual const void *compilePatternIndex() const;
		bool compileBuild(CompilingBuild &compiling) const;
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
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const Step *calling(Runner &run, const ListExpress &call) const;
		const Step *calling(Runner &run, const NodeExpress &call) const;
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
		const Step *pass(Runner &run, const Any *value);
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
		Sink *kick(Runner &run);
		const Step *called(Runner &run, const Constant &call);
		const Step *called(Runner &run, const Integer &call);
		const Step *called(Runner &run, const ListConstant &call);
		const Step *called(Runner &run, const NodeConstant &call);
		const Step *called(Runner &run, const Empty &call);
		const Step *called(Runner &run, const ListExpress &call);
		const Step *called(Runner &run, const NodeExpress &call);
		const Step *pass(Runner &run, const Any *value);
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
		const Step *called(Runner &run, const Constant &call);
		const Step *called(Runner &run, const Integer &call);
		const Step *called(Runner &run, const ListConstant &call);
		const Step *called(Runner &run, const NodeConstant &call);
		const Step *called(Runner &run, const Empty &call);
		const Step *called(Runner &run, const ListExpress &call);
		const Step *called(Runner &run, const NodeExpress &call);
	};

	class SwitchClicheShort
		: public ClicheShort
	{
	public:
		SwitchClicheShort(const HashedConstant *&link, const Constant *h, const Constant *a)
			: ClicheShort(link, h, a)
		{}
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsColor *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsDate *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Timestamp *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Cliche *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Special *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Listener *value) const;
		virtual const CallWho *whoOperation(const NodeExpressShort *operation, const Any *who) const;
	};

	class SwitchConstantShort
		: public NodeConstantShort
	{
	public:
		SwitchConstantShort(const HashedConstant *&link, const ClicheShort &cliche, const Constant *value)
			: NodeConstantShort(link, cliche, value)
		{}
		const CallWho *callWho(const Any *who) const;
	};

	class SwitchClicheLong
		: public ClicheLong
	{
	public:
		SwitchClicheLong(const HashedConstant *&link, const Constant *h, const Constant *const *a, size_t c)
			: ClicheLong(link, h, a, c)
		{}
		const NodeConstantLong *newNodeConstant(const HashedConstant *&link, const Constant *const *value) const;
		const Any *node(const Any *const *element) const;
	};

	class SwitchClicheTrailer
		: public ClicheTrailer
	{
	public:
		SwitchClicheTrailer(const HashedConstant *&link, const Constant *h, const Constant *const *a, size_t c)
			: ClicheTrailer(link, h, a, c)
		{}
		const NodeConstantLong *newNodeConstant(const HashedConstant *&link, const Constant *const *value) const;
		const Any *node(const Any *const *element) const;
	};

	class SwitchConstantLong
		: public NodeConstantLong
	{
	public:
		SwitchConstantLong(const HashedConstant *&link, const ClicheLong &cliche, const Constant *const *value)
			: NodeConstantLong(link, cliche, value)
		{}
		const CallWho *callWho(const Any *who) const;
	};

	class SwitchConstantTrailer
		: public NodeConstantTrailer
	{
	public:
		SwitchConstantTrailer(const HashedConstant *&link, const ClicheLong &cliche, const Constant *const *value)
			: NodeConstantTrailer(link, cliche, value)
		{}
		const CallWho *callWho(const Any *who) const;
	};

	class SwitchExpressLong
		: public NodeExpressLong
	{
	public:
		SwitchExpressLong(const SwitchClicheLong &cliche, const Any *const *value)
			: NodeExpressLong(cliche, value)
		{}
		const CallWho *callWho(const Any *who) const;
	};

	class SwitchExpressTrailer
		: public NodeExpressTrailer
	{
	public:
		SwitchExpressTrailer(const SwitchClicheTrailer &cliche, const Any *const *value)
			: NodeExpressTrailer(cliche, value)
		{}
		const CallWho *callWho(const Any *who) const;
	};

	class WhoSwitch
		: public CallWho
	{
	public:
		const Step *step_(Runner &run) const;
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
		const Step *miss(Runner &run, const Any *value) const;
		WhoSwitchCall(const Any *call, const Any *who)
			: WhoSwitch(call, who)
		{}
	};

	class WhoSwitchTry
		: public WhoSwitch
	{
	public:
		const Step *miss(Runner &run, const Any *value) const;
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
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
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
		const Step *step_(Runner &run) const;
	};

	class PipeDistinct
		: public Pipe
	{
	public:
		PipeDistinct(const WhoPropertyDistinct &what)
			: what(what)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
		const Step *pipeBegin(Runner &run);
		const Step *pipeItem(Runner &run, const Any *item);
		const Step *pipeEnd(Runner &run);
	private:
		const WhoPropertyDistinct &what;
		std::set<const Any *> set;
	};

	class PipeDistinctFilter
		: public Pipe
	{
	public:
		PipeDistinctFilter(const WhoUntypedOperation &what, const Any *filter)
			: what(what), filter(filter)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
		const Step *pipeBegin(Runner &run);
		const Step *pipeItem(Runner &run, const Any *item);
		const Step *pipeEnd(Runner &run);
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
		PipingDistinctFilter(PipeDistinctFilter &pipe, const Any *item)
			: pipe(pipe), item(item)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Constant *value);
		const Step *pass(Runner &run, const NodeExpressLong *value);
		const Step *pass(Runner &run, const Any *value);
		const Step *miss(Runner &run);
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
		const Step *step_(Runner &run) const;
	};

	class PipeToCounts
		: public Pipe
	{
	public:
		PipeToCounts(const WhoPropertyCounts &what)
			: what(what)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
		const Step *pipeBegin(Runner &run);
		const Step *pipeItem(Runner &run, const Any *item);
		const Step *pipeEnd(Runner &run);
	private:
		const WhoPropertyCounts &what;
		std::map<const Constant *, double> map;
	};
}
#endif
