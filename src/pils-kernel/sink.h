/* This file is public domain */
#ifndef DEFINE_PILS_SINK_H
#define DEFINE_PILS_SINK_H
#include "builtin.h"
namespace PILS
{
/* The Runner class controls the execution of a PILS thread.

   NOTE:

   Often, the step_ parameter is an uncounted reference to a PILS object.
   In this case, a counted reference must be kept elsewhere.

   When evaluating a composite expression, the interpreter keeps a
   counted copy to the root, and work with uncounted references to
   sub-expressions, to save the overhead of counting operations.
*/

	class SinkTagged;
	class SinkTaggedNodeBuilding;
	class Closure;
	class Pipe;
	class WhoMatch;
	class SinkTimescale;
	class Miss;
	class Bridge;

	class Runner
	{
	public:
		Runner(Bridge &bridge, size_t stackSize);
		virtual ~Runner();
		void *allocate(size_t size);
		Sink *pushWhere(const Any *newWhere);
		void run(const Step *step_);
		const Step *pass(const Any *thing);
		virtual bool isMainThread() const;
		virtual const Constant *as_Thread() const = 0;
		virtual const Step *callingKnot(const Any &who, const Any &call);
		virtual const Step *callingKnot(const Any &who, const Any &call, const Any *assignValue);
		virtual const Step *thread(const Any &what);
		Bridge &bridge;
		char *stackLimit;
		char *pessimistStackLimit;
		Sink *sink;
		Sink *stackOverflowSink;
		SinkTagged *sinkTagChain;
		const Any *where_;
		struct
		{
			const Any *who;
			const Express *what;
			const NodeExpress *closure;
		}
		calling;
		class Done
			: public Step
		{
		public:
			static Done singleton;
			const Step *step_(Runner &run) const;
		};
		Strap::Sticker threadStrapSticker;
		Strap::Sticker *temporaryStrapSticker;
		bool stackOverflow() const;
		const Step *callingStackOverflow();
		bool oldTimer;
	};

	class PassingMind
	{
	public:
		virtual const Any *mindSet(const Constant *key, const Any *value) const = 0;
		virtual const Any *mindGet(const Constant &key) const = 0;
		virtual void mindRelease() const = 0;
		virtual const Any *mindError() const = 0;
	};

	class PassingMindMap
		: public PassingMind
	{
	public:
		const Any *mindSet(const Constant *key, const Any *value) const;
		const Any *mindGet(const Constant &key) const;
		void mindRelease() const;
	protected:
		PassingMindMap(){}
		~PassingMindMap();
	private:
		mutable std::map<const Constant*, const Any*> mind;
	};

	class Kickable
		: public Step
	{
	public:
		virtual Sink *kick(Runner &run) = 0;
	};

	class Sink
		: public Kickable
	{
	public:
		virtual const Step *miss(Runner &run);
		virtual const Step *pass(Runner &run, long value);
		virtual const Step *pass(Runner &run, double value);
		virtual const Step *pass(Runner &run, const Integer &value);
		virtual const Step *pass(Runner &run, const Float &value);
		virtual const Step *pass(Runner &run, const PilsString &value);
		virtual const Step *pass(Runner &run, const PilsColor &value);
		virtual const Step *pass(Runner &run, const Cliche &value);
		virtual const Step *pass(Runner &run, const ListConstant &value);
		virtual const Step *pass(Runner &run, const NodeConstantLong &value);
		virtual const Step *pass(Runner &run, const NodeConstantShort &value);
		virtual const Step *pass(Runner &run, const ListExpress &value);
		virtual const Step *pass(Runner &run, const NodeExpressLong &value);
		virtual const Step *pass(Runner &run, const NodeExpressShort &value);
		virtual const Step *pass(Runner &run, const Special &value);
		virtual const Step *pass(Runner &run, const Integer *value);
		virtual const Step *pass(Runner &run, const Float *value);
		virtual const Step *pass(Runner &run, const PilsDate *value);
		virtual const Step *pass(Runner &run, const Timestamp *value);
		virtual const Step *pass(Runner &run, const Duration *value);
		virtual const Step *pass(Runner &run, const PilsColor *value);
		virtual const Step *pass(Runner &run, const PilsString *value);
		virtual const Step *pass(Runner &run, const Cliche *value);
		virtual const Step *pass(Runner &run, const ListConstant *value);
		virtual const Step *pass(Runner &run, const NodeConstantLong *value);
		virtual const Step *pass(Runner &run, const NodeConstantShort *value);
		virtual const Step *pass(Runner &run, const ListExpress *value);
		virtual const Step *pass(Runner &run, const NodeExpressLong *value);
		virtual const Step *pass(Runner &run, const NodeExpressShort *value);
		virtual const Step *pass(Runner &run, const Special *value);
		virtual const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count);
		virtual const Step *pass(Runner &run, const Any *anchor, const Any *const *range, size_t count);
		virtual const Step *pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count);
		virtual const Step *pass(Runner &run, SinkTaggedNodeBuilding &nodeBuilding);
		virtual const Step *pass(Runner &run, const Any *value) = 0;
		virtual const Step *pass(Runner &run, PassingMind *mind, const Express *what);
		virtual Pipe *connectPipe(Runner &run);
		virtual void refer(Runner &run, const Express &what);
		virtual const Step *call(Runner &run, const Express &what, const Any *call);
		virtual const Step *call(Runner &run, const Express &what, const Any *call , const Any *who);
		virtual const Step *call(Runner &run, const Express &what, const Any &call);
		virtual const Step *call(Runner &run, const Express &what, const Any &call , const Any *who);
		virtual const Step *callaround(Runner &run, const Express &what, const Any *call, const Any *who);
		virtual const Step *assignCall(Runner &run, const Express &what, const Any *call, const Any *assignValue);
		virtual const Step *assignCall(Runner &run, const Express &what, const Any *call , const Any *who, const Any *assignValue);
		virtual const Step *assignCallaround(Runner &run, const Express &what, const Any *call, const Any *who, const Any *assignValue);
		virtual const Step *called(Runner &run, const Constant &call);
		virtual const Step *called(Runner &run, const Integer &call);
		virtual const Step *called(Runner &run, const ListConstant &call);
		virtual const Step *called(Runner &run, const NodeConstant &call);
		virtual const Step *called(Runner &run, const Empty &call);
		virtual const Step *called(Runner &run, const ListExpress &call);
		virtual const Step *called(Runner &run, const NodeExpress &call);
		virtual const Step *called(Runner &run, const Any &call, const Any *assignValue);
		virtual const Step *tailStep(Runner &run, const Any *thing, const Any *where_);
		virtual const Step *tailStep(Runner &run, const Any *thing);
		virtual const Step *error(Runner &run, const Any *error, const Express *what, const Any *who);
		void pushAssignTail(Runner &run, const Any &tail);
		virtual size_t concatenateCount();
		virtual const Step *concatenateBuild(Runner &run, PILS_CHAR *string, PILS_CHAR *at);
		virtual bool needsResult();
		virtual Sink *pushWhere(Runner &run, const Any *where);
		virtual SinkTimescale *as_SinkTimescale();
	protected:
		const Step *falseCompare(Runner &run, const Express &what, Sink &next);
	private:
		const Step *step_(Runner &run) const;
	};

	/* Lightweight failure - construction of error node is postponed */
	class Miss
		: public Sink
	{
	public:
		virtual const Step *missing(Runner &run, Sink *sink) = 0;
		const Step *pass(Runner &run, const Any *value); //dummy
	};

	class MissCall
		: public Miss
	{
	public:
		MissCall(const Any &call) : call(call) {}
		const Step *missing(Runner &run, Sink *sink);
		Sink *kick(Runner &run);
	protected:
		const Any &call;
	};

	class MissAssignCall
		: public MissCall
	{
	public:
		MissAssignCall(const Any &call, const Any *assignValue)
			: MissCall(call), assignValue(assignValue)
		{}
		const Step *missing(Runner &run, Sink *sink);
		Sink *kick(Runner &run);
	private:
		const Any *assignValue;
	};

	class MissPassingMindCall
		: public Miss
	{
	public:
		MissPassingMindCall(PassingMind *mind, const Any *call, const Express *what)
			: mind(mind), call(call), what(what)
		{}
		const Step *missing(Runner &run, Sink *sink);
		Sink *kick(Runner &run);
	private:
		PassingMind *mind;
		const Any *call;
		const Express *what;
	};

	class MissSpecial
		: public Miss
	{
	public:
		const Step *called(Runner &run, const Constant &call);
		const Step *called(Runner &run, const Integer &call);
		const Step *called(Runner &run, const ListConstant &call);
		const Step *called(Runner &run, const NodeConstant &call);
		const Step *called(Runner &run, const Empty &call);
		const Step *called(Runner &run, const ListExpress &call);
		const Step *called(Runner &run, const NodeExpress &call);
		const Step *called(Runner &run, const Any &call, const Any *assignValue);
		const Step *miss(Runner &run) = 0;
		const Step *missing(Runner &run, Sink *sink);
		virtual const Any *errorData() = 0;
	};

	class SinkConstant
		: public Sink
	{
	public:
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
		const Step *pass(Runner &run, const Special *value);
		virtual const Step *pass(Runner &run, const Constant *value) = 0;
	};

	class SinkForget
		: public Sink
	{
	public:
		using Sink::pass;
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
		const Step *pass(Runner &run, const Any *value);
		bool needsResult();
	};

	class SinkHolding
		: public Sink
	{
	public:
		Sink *kick(Runner &run);
		const Any *thing;
		SinkHolding(const Any *thing)
			: thing(thing)
		{}
		bool needsResult();
	};

	class SinkHoldCalling
		: public SinkHolding
	{
	public:
		SinkHoldCalling(const Any *thing)
			: SinkHolding(thing)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
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
		const Step *pass(Runner &run, const Special *value);
		const Step *pass(Runner &run, const ListExpress *value);
		const Step *pass(Runner &run, const NodeExpressLong *value);
		const Step *pass(Runner &run, const NodeExpressShort *value);
		const Step *pass(Runner &run, const Any *value);
		const Step *pass(Runner &run, PassingMind *mind, const Express *what);
		const Step *tailStep(Runner &run, const Any *thing, const Any *where_);
		const Step *tailStep(Runner &run, const Any *thing);
		Pipe *connectPipe(Runner &run);
		const Step *error(Runner &run, const Any *error, const Express *what, const Any *who);
		const Step *miss(Runner &run);
	};

	class SinkResultStep
		: public SinkHoldCalling
	{
	public:
		SinkResultStep(const Any *thing)
			: SinkHoldCalling(thing)
		{}
		const Step *step_(Runner &run) const;
	};

	class SinkHold
		: public SinkHoldCalling
	{
	public:
		SinkHold(const Any *thing)
			: SinkHoldCalling(thing)
		{}
		const Step *called(Runner &run, const Constant &call);
		const Step *called(Runner &run, const Integer &call);
		const Step *called(Runner &run, const ListConstant &call);
		const Step *called(Runner &run, const NodeConstant &call);
		const Step *called(Runner &run, const Empty &call);
		const Step *called(Runner &run, const ListExpress &call);
		const Step *called(Runner &run, const NodeExpress &call);
		const Step *called(Runner &run, const Any &call, const Any *assignValue);
	};

	class SinkHoldTail
		: public Sink
	{
	public:
		SinkHoldTail(const Any *thing, const Any *whence)
			: thing(thing), whence(whence)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
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
		const Step *pass(Runner &run, const Any *value);
		Sink *kick(Runner &run);
		const Step *tailStep(Runner &run, const Any *thing, const Any *where_);
		const Step *tailStep(Runner &run, const Any *thing);
		Pipe *connectPipe(Runner &run);
		bool needsResult();
		Sink *pushWhere(Runner &run, const Any *where);
		const Any *thing;
		const Any *whence;
	};

	class SinkFinal
		: public Sink
	{
	public:
		SinkFinal(void *block)
			: block(block)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
	private:
		void *block;
	};

	class SinkConstantCall
		: public Sink
	{
	public:
		const Step *pass(Runner &run, const Any *value);
		SinkConstantCall(const CallWho &what);
	protected:
		const CallWho &what;
	};

	class SinkOperand
		: public Sink
	{
	public:
		SinkOperand(const WhoExpressOperation &what)
			: what(what)
		{}
		Sink *kick(Runner &run);
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
		const Step *pass(Runner &run, const Any *value);
	protected:
		const WhoExpressOperation &what;
	};

	class SinkArgument
		: public Sink
	{
	public:
		SinkArgument(const CallWho &what)
			: what(what)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const PilsString *value);
		const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count);
		const Step *pass(Runner &run, const Any *value);
	private:
		const CallWho &what;
	};

	class SinkWho
		: public Sink
	{
	public:
		SinkWho(const CallWho &what, const Any *argument)
			: what(what), argument(argument)
		{}
		const Step *pass(Runner &run, const Any *value);
		const Step *pass(Runner &run, SinkTaggedNodeBuilding &nodeBuilding);
		const Step *pass(Runner &run, PassingMind *mind, const Express *what);
		Sink *kick(Runner &run);
	protected:
		const CallWho &what;
		const Any *argument;
	};

	class SinkProperty
		: public Sink
	{
	public:
		SinkProperty(const CallWho &what)
			: what(what)
		{}
		const Step *pass(Runner &run, const Any *value);
		const Step *pass(Runner &run, SinkTaggedNodeBuilding &nodeBuilding);
		Sink *kick(Runner &run);
	protected:
		const CallWho &what;
	};

	class SinkWhoOperationUncounted
		: public Sink
	{
	public:
		Sink *kick(Runner &run);
	protected:
		SinkWhoOperationUncounted(const CallWho &what, const Any &operand);
		const Step *pass(Runner &run, const Any *value);
		const CallWho &what;
		const Any &operand;
	};

	class SinkWhoOperationAny
		: public Sink
	{
	public:
		Sink *kick(Runner &run);
	protected:
		SinkWhoOperationAny(const WhoExpressOperation &what, const Any *operand)
			: what(what), operand(operand)
		{}
		const Step *pass(Runner &run, const Any *value);
		const WhoExpressOperation &what;
		const Any *operand;
	};

	class SinkWhoOperationRawInteger
		: public Sink
	{
	public:
		Sink *kick(Runner &run);
	protected:
		SinkWhoOperationRawInteger(const WhoExpressOperation &what, long operand)
				: what(what), operand(operand)
		{}
		const Step *pass(Runner &run, const Any *value);
		const WhoExpressOperation &what;
		long operand;
	};

	class SinkWhoOperationRawFloat
		: public Sink
	{
	public:
		Sink *kick(Runner &run);
	protected:
		SinkWhoOperationRawFloat(const WhoExpressOperation &what, double operand)
			: what(what), operand(operand)
		{}
		const Step *pass(Runner &run, const Any *value);
		const WhoExpressOperation &what;
		double operand;
	};

	class SinkWhereabout
		: public Sink
	{
	public:
		SinkWhereabout(const Any *where_)
			: where_(where_)
		{}
		const Any *where_;
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *thing);
		const Step *tailStep(Runner &run, const Any *thing, const Any *where_);
		const Step *tailStep(Runner &run, const Any *thing);
		Sink *pushWhere(Runner &run, const Any *where);
		Pipe *connectPipe(Runner &run);
		bool needsResult();
	};

	class SinkWhereaboutUncounted
		: public SinkWhereabout
	{
	public:
		SinkWhereaboutUncounted(const Any *where_)
			: SinkWhereabout(where_)
		{}
		Sink *kick(Runner &run);
		Sink *pushWhere(Runner &run, const Any *where);
		const Step *tailStep(Runner &run, const Any *thing);
	};

	class SinkNodeShort
		: public Sink
	{
	public:
		const ClicheShort &cliche;
		SinkNodeShort(const ClicheShort& cliche) : cliche(cliche) {}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *thing);
	};

	class SinkNodeLong
		: public Sink
	{
	public:
		const NodeExpressLong &node;
		const Any ** done;
		SinkNodeLong(const NodeExpressLong &node, const Any** done)
			: node(node), done(done)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *thing);
	};

	class SinkContinue
		: public SinkForget
	{
	public:
		const Any &tail;
		SinkContinue(const Any &tail)
			: tail(tail)
		{}
		const Step *pass(Runner &run, long dummy);
		Sink *kick(Runner &run);
	};

	class SinkCondition
		: public SinkForget
	{
	public:
		const Step *miss(Runner &run);
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
		const Step *pass(Runner &run, const Any *value);
		virtual const Step *fail(Runner &run) = 0;
		virtual const Step *succeed(Runner &run) = 0;
	};

	class SinkTagged
		: public SinkForget
	{
	public:
		SinkTagged(const NodeExpress &tag, SinkTagged *chain)
			: chain(chain), tag(tag)
		{}
		virtual const Step *skip(Runner &run) = 0;
		SinkTagged *chain;
		const NodeExpress &tag;
	};

	class Building
		: public PokerTrailer
	{
	public:
		Building(const BuiltinClicheBuilding &cliche, const Any *const *element)
			: PokerTrailer(cliche, element)
		{}
		Building(const Any *where_, const Constant *tag)
			: PokerTrailer(BuiltinClicheBuilding::singleton, where_, tag)
		{}
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const Step *calling(Runner &run, const ListExpress &call) const;
		const Step *calling(Runner &run, const NodeExpress &call) const;
		const Step *calling(Runner &run, const Any &call, const Any *assignValue) const;
		const Express *findCatchTag() const;
		const Express *findCatchTag(const Constant &tag) const;
	private:
		const Any *dummy;
	};

	class SinkTaggedBuilding
		: public SinkTagged
	{
	public:
		virtual const Step *calling(Runner &run, const Building &tag) = 0;
		virtual const Step *calling(Runner &run, const Building &tag, const Any *assignValue) = 0;
		virtual const Step *skip(Runner &run); //dummy
	protected:
		SinkTaggedBuilding(const Building &tag, SinkTagged *chain)
			: SinkTagged(tag, chain)
		{}
	};

	class SinkTaggedListBuilding
		: public SinkTaggedBuilding
	{
	public:
		SinkTaggedListBuilding(Building &tag, SinkTagged *chain)
			: SinkTaggedBuilding(tag, chain)
		{}
		const Step *calling(Runner &run, const Building &tag);
		const Step *calling(Runner &run, const Building &tag, const Any *assignValue);
		const Step *pass(Runner &run, long value);
		Sink *kick(Runner &run);
	};

	class SinkTaggedNodeBuilding
		: public SinkTaggedBuilding
	{
	public:
		SinkTaggedNodeBuilding(Building &tag, SinkTagged *chain, const Express &what)
			: SinkTaggedBuilding(tag, chain), head(((const NodeConstant*)tag.element[1])->element[0]), joker(NULL)
		{
			head->addReference();
		}
		SinkTaggedNodeBuilding(Building &tag, SinkTagged *chain, const Constant &head)
			: SinkTaggedBuilding(tag, chain), head(&head), joker(NULL)
		{
			head.addReference();
		}
		const Step *calling(Runner &run, const Building &tag);
		const Step *calling(Runner &run, const Building &tag, const Any *assignValue);
		const Step *pass(Runner &run, long value);
		Sink *kick(Runner &run);
		const Constant *head;
		const Any *joker;
		std::map<const Constant*, const Any*> building;
	};

	class SinkTaggedExit
		: public SinkTaggedBuilding
	{
	public:
		SinkTaggedExit(Building &tag, SinkTagged *chain)
			: SinkTaggedBuilding(tag, chain)
		{}
		const Step *calling(Runner &run, const Building &tag);
		const Step *calling(Runner &run, const Building &tag, const Any *assignValue);
		Sink *kick(Runner &run);
	};
}
#endif
