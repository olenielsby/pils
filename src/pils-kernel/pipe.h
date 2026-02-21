/* This file is public domain */
#ifndef DEFINE_PILS_PIPE_H
#define DEFINE_PILS_PIPE_H
#include "call.h"
namespace PILS
{
	class Pipe
		: public Sink
	{
	public:
		Pipe *connectPipe(Runner &run);
		virtual const Step *pipeItem(Runner &run, const Any *item) = 0;
		virtual	const Step *pipeBegin(Runner &run) = 0;
		virtual const Step *pipeEnd(Runner &run) = 0;
		virtual Pipe *splicing();
		virtual Sink *shortcut(Runner &run);
		const Step *pass(Runner &run, const ListConstant &value);
		const Step *pass(Runner &run, const ListExpress &value);
		const Step *pass(Runner &run, const ListConstant *value);
		const Step *pass(Runner &run, const ListExpress *value);
		const Step *pass(Runner &run, const Special *value);
		const Step *pass(Runner &run, const Any *anchor, const Any *const *range, size_t count);
		const Step *pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count);
	};

	class PipeToNowhere
		: public Pipe
	{
	public:
		const Step *pass(Runner &run, const Any *thing);
		Sink *kick(Runner &run);
		const Step *pipeItem(Runner &run, const Any *thing);
		const Step *pipeBegin(Runner &run);
		const Step *pipeEnd(Runner &run);
		Sink *shortcut(Runner &run);
		const Step *called(Runner &run, const Empty &call);
		const Step *error(Runner &run, const Any *error, const Express *what, const Any *who);
		const Step *miss(Runner &run);
		void refer(Runner &run, const Express &what);
	};

	class PipeHoldTail
		: public Pipe
	{
	public:
		PipeHoldTail(const Any *thing, const Any *whence)
			: thing(thing), whence(whence)
		{}
		const Step *pass(Runner &run, const Any *value);
		Sink *kick(Runner &run);
		const Step *tailStep(Runner &run, const Any *thing, const Any *where_);
		const Step *tailStep(Runner &run, const Any *thing);
		bool needsResult();
		const Step *pipeItem(Runner &run, const Any *item);
		const Step *pipeBegin(Runner &run);
		const Step *pipeEnd(Runner &run);
		Sink *pushWhere(Runner &run, const Any *where);
		const Any *thing;
		const Any *whence;
	};

	class PipeWhereabout
		: public Pipe
	{
	public:
		PipeWhereabout(const Any *where_)
			: where_(where_)
		{}
		const Step *pass(Runner &run, const Any *value);
		Sink *kick(Runner &run);
		const Step *tailStep(Runner &run, const Any *thing, const Any *where_);
		const Step *tailStep(Runner &run, const Any *thing);
		bool needsResult();
		const Step *pipeItem(Runner &run, const Any *item);
		const Step *pipeBegin(Runner &run);
		const Step *pipeEnd(Runner &run);
		Sink *pushWhere(Runner &run, const Any *where);
		const Any *where_;
	};

	class PipeToList
		: public PipeToNowhere
	{
	public:
		Sink *kick(Runner &run);
		const Step *pipeItem(Runner &run, const Any *thing);
		const Step *pipeEnd(Runner &run);
		const Step *miss(Runner &run);
		void refer(Runner &run, const Express &what);
	private:
		std::vector<const Any*> elements;
	};

	class Pipesource
		: public Sink
	{
	public:
		const Step *pass(Runner &run, const Any *thing); //dummy
	};

	class PipeHold
		: public Pipe
	{
	public:
		PipeHold(const Any *hold)
			: hold(hold)
		{}
		const Step *pass(Runner &run, const Any *thing);
		Sink *kick(Runner &run);
		const Step *pipeBegin(Runner &run);
		const Step *pipeItem(Runner &run, const Any *thing);
		const Step *pipeEnd(Runner &run);
		const Any *hold;
	};

	class PipesourceListRange
		: public Pipesource
	{
	public:
		PipesourceListRange(const Any *const *source, size_t count)
			: source(source), end(source + count)
		{}
		const Step *step_(Runner &run) const;
		Sink *kick(Runner &run);
	protected:
		PipesourceListRange(const Any *const *source, const Any *const *end)
			: source(source), end(end)
		{}
		const Any *const *source;
		const Any *const *const end;
	};

	class PipesourceListRangeReverse
		: public PipesourceListRange
	{
	public:
		PipesourceListRangeReverse(const Any *const *source, size_t count)
			: PipesourceListRange(source + count, source)
		{}
		const Step *step_(Runner &run) const;
	};

	class PipesourceListRangeEval
		: public PipesourceListRange
	{
	public:
		PipesourceListRangeEval(const Any *const *source, size_t count)
			: PipesourceListRange(source, count)
		{}
		const Step *step_(Runner &run) const;
	};

	class Piping
		: public Sink
	{
	public:
		Piping(Pipe &pipe)
			: pipe(pipe)
		{}
		const Step *pass(Runner &run, const Any *thing);
		Sink *kick(Runner &run);
	protected:
		Pipe &pipe;
	};

	class PipeEach
		: public Pipe
	{
	public:
		PipeEach(const WhoUntypedOperation &what, const Any *filter)
			: what(what), filter(filter)
		{}
		const Step *pass(Runner &run, const Any *thing);
		Sink *kick(Runner &run);
		const Step *pipeItem(Runner &run, const Any *thing);
		const Step *pipeBegin(Runner &run);
		const Step *pipeEnd(Runner &run);
	protected:
		const WhoUntypedOperation &what;
		const Any *filter;
	};

	class PipeFind
		: public PipeEach
	{
	public:
		PipeFind(const WhoUntypedOperation &what, const Any *filter)
			: PipeEach(what, filter)
		{}
		const Step *pipeItem(Runner &run, const Any *thing);
		const Step *pipeBegin(Runner &run);
		const Step *pipeEnd(Runner &run);
	};

	class PipeEvery
		: public PipeEach
	{
	public:
		PipeEvery(const WhoUntypedOperation &what, const Any *filter)
			: PipeEach(what, filter)
		{}
		const Step *pipeItem(Runner &run, const Any *thing);
	};

	class PipeWhile
		: public PipeEach
	{
	public:
		PipeWhile(const WhoUntypedOperation &what, const Any *filter)
			: PipeEach(what, filter)
		{}
		const Step *pipeItem(Runner &run, const Any *thing);
	};

	class PipeExcept
		: public PipeEach
	{
	public:
		PipeExcept(const WhoUntypedOperation &what, const Any *filter)
			: PipeEach(what, filter)
		{}
		const Step *pipeItem(Runner &run, const Any *thing);
	};

	class PipeFold
		: public Pipe
	{
	public:
		PipeFold(const WhoUntypedOperation &what, const Any *fold)
			: what(what), fold(fold), value(NULL)
		{}
		const Step *pass(Runner &run, const Any *thing);
		Sink *kick(Runner &run);
		const Step *pipeItem(Runner &run, const Any *thing);
		const Step *pipeBegin(Runner &run);
		const Step *pipeEnd(Runner &run);
	protected:
		const WhoUntypedOperation &what;
		const Any *fold;
		friend class PipingFold;
		const Any *value;
	};

	class PipingEvery
		: public Piping
	{
	public:
		PipingEvery(Pipe &pipe, const Any *item)
			: Piping(pipe), item(item)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *thing);
		const Step *tailStep(Runner &run, const Any *thing, const Any *where_);
		const Step *error(Runner &run, const Any *error, const Express *what, const Any *who);
		const Step *miss(Runner &run);
	private:
		const Any *item;
	};

	class PipeSplicingEvery
		: public Pipe
	{
	public:
		PipeSplicingEvery(Pipe &splicing)
			: splicing(splicing)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *thing);
		const Step *pipeItem(Runner &run, const Any *thing);
		const Step *pipeBegin(Runner &run);
		const Step *pipeEnd(Runner &run);
	private:
		Pipe &splicing;
	};

	class PipingExcept
		: public SinkForget
	{
	public:
		PipingExcept(Pipe &pipe, const Any *item)
			: pipe(pipe), item(item)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, long dummy);
		const Step *miss(Runner &run);
	private:
		Pipe &pipe;
		const Any *item;
	};

	class PipingEach
		: public PipingEvery
	{
	public:
		PipingEach(Pipe &pipe, const Any *item)
			: PipingEvery(pipe, item)
		{}
		const Step *called(Runner &run, const Constant &call);
		const Step *called(Runner &run, const Integer &call);
		const Step *called(Runner &run, const ListConstant &call);
		const Step *called(Runner &run, const NodeConstant &call);
		const Step *called(Runner &run, const Empty &call);
		const Step *called(Runner &run, const ListExpress &call);
		const Step *called(Runner &run, const NodeExpress &call);
		const Step *called(Runner &run, const Any &call, const Any *assignValue);
		const Step *miss(Runner &run);
	};

	class PipingWhile
		: public PipingEvery
	{
	public:
		PipingWhile(Pipe &pipe, const Any *item)
			: PipingEvery(pipe, item)
		{}
		const Step *called(Runner &run, const Constant &call);
		const Step *called(Runner &run, const Integer &call);
		const Step *called(Runner &run, const ListConstant &call);
		const Step *called(Runner &run, const NodeConstant &call);
		const Step *called(Runner &run, const Empty &call);
		const Step *called(Runner &run, const ListExpress &call);
		const Step *called(Runner &run, const NodeExpress &call);
		const Step *called(Runner &run, const Any &call, const Any *assignValue);
		const Step *miss(Runner &run);
	};

	class PipingEveryTail
		: public Piping
	{
	public:
		PipingEveryTail(Pipe &pipe, const Any *thing, const Any *whence)
			: Piping(pipe), thing(thing), whence(whence)
		{}
		const Step *pass(Runner &run, const Any *value);
		Sink *kick(Runner &run);
		const Step *tailStep(Runner &run, const Any *thing, const Any *where_);
		const Step *tailStep(Runner &run, const Any *thing);
		Pipe *connectPipe(Runner &run);
	private:
		const Any *thing;
		const Any *whence;
	};

	class PipingFind
		: public PipingEach
	{
	public:
		PipingFind(Pipe &pipe, const Any *item)
			: PipingEach(pipe, item)
		{}
		const Step *pass(Runner &run, const Any *thing);
		const Step *tailStep(Runner &run, const Any *thing, const Any *where_);
	};

	class PipingFold
		: public Piping
	{
	public:
		PipingFold(PipeFold &pipe)
			: Piping(pipe)
		{}
		const Step *pass(Runner &run, const Any *value);
		const Step *error(Runner &run, const Any *error, const Express *what, const Any *who);
		const Step *called(Runner &run, const Any &call, const Any *assignValue);
		const Step *miss(Runner &run);
	};

	class WhoCount
		: public CallWho
	{
	public:
		WhoCount(const TypecheckPropertyCount *call, const Any *who)
			: CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class PipeProperty
		: public Pipe
	{
	public:
		const Step *pass(Runner &run, SinkTaggedNodeBuilding &nodeBuilding);
		const Step *pass(Runner &run, const Any *value);
		const Step *pipeBegin(Runner &run);
	protected:
		PipeProperty(const CallWho &what)
			: what(what)
		{}
		const CallWho &what;
	};

	class PipeCount
		: public PipeProperty
	{
	public:
		PipeCount(const WhoCount &what)
			: PipeProperty(what), count(0)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const PilsString &value);
		const Step *pass(Runner &run, const PilsString *value);
		const Step *pass(Runner &run, const ListConstant &value);
		const Step *pass(Runner &run, const ListExpress &value);
		const Step *pass(Runner &run, const ListConstant *value);
		const Step *pass(Runner &run, const ListExpress *value);
		const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count);
		const Step *pass(Runner &run, const Any *anchor, const Any *const *range, size_t count);
		const Step *pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count);
		const Step *pipeItem(Runner &run, const Any *thing);
		const Step *pipeEnd(Runner &run);
	private:
		size_t count;
	};

	class WhoCharacterEncoding
		: public CallWho
	{
	public:
		WhoCharacterEncoding(const PropertyCharacterEncoding *call, const Any *who)
			: CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class PipeCharacterEncoder
		: public PipeProperty, private Converter
	{
	public:
		PipeCharacterEncoder(const WhoCharacterEncoding &whatever)
			: PipeProperty(whatever), state(0)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const PilsString *value);
		const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count);
		const Step *pipeItem(Runner &run, const Any *thing);
		const Step *pipeEnd(Runner &run);
		bool convert(const Integer &character);
	private:
		std::string string;
		int state;
	};

	class PipesourceCharacterDecoder
		: public Pipesource
	{
	public:
		PipesourceCharacterDecoder(const CallWho &what, const Any *anchor, const PILS_CHAR *at, const PILS_CHAR *end)
			: what(what), state(0), anchor(anchor), at(at), end(end)
		{
			state = ((PropertyCharacterEncoding *)what.callAttribute())->initialState(this->at, end);
		}
		Sink *kick(Runner &run);
		const Step *step_(Runner &run) const;
		const Step *step_(Runner &run);
	private:
		const CallWho &what;
		int state;
		const Any *anchor;
		const PILS_CHAR *at;
		const PILS_CHAR *end;
	};

	class WhoPropertyIncrementRange
		: public CallWho
	{
	public:
		WhoPropertyIncrementRange(const PropertyIncrementRange *call, const Any *who)
			:  CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class SinkPropertyIncrementRange
		: public Sink
	{
	public:
		SinkPropertyIncrementRange(const WhoPropertyIncrementRange &what)
			: what(what)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *who);
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Integer *value);
	private:
		const WhoPropertyIncrementRange &what;
	};

	class WhoPropertyDecrementRange
		: public WhoPropertyIncrementRange
	{
	public:
		WhoPropertyDecrementRange(const PropertyDecrementRange *call, const Any *who)
			: WhoPropertyIncrementRange(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class SinkPropertyDecrementRange
		: public SinkPropertyIncrementRange
	{
	public:
		SinkPropertyDecrementRange(const WhoPropertyIncrementRange &what)
			: SinkPropertyIncrementRange(what)
		{}
		const Step *pass(Runner &run, long value);
	};

	class PipesourceIntegerStep
		: public Pipesource
	{
	public:
		PipesourceIntegerStep(long next, long count, long delta)
			: next(next), count(count), delta(delta)
		{}
		const Step *step_(Runner &run) const;
		Sink *kick(Runner &run);
	private:
		long next;
		long count;
		long delta;
	};

	class UpDownInteger
		: public NodeConstantTiny
	{
	public:
		UpDownInteger(const HashedConstant *&link, const BuiltinClicheOperationUpDown &cliche, const Integer *value)
			: NodeConstantTiny(link, cliche, value)
		{}
		const CallWho *callWho(const Any *who) const;
	};

	class WhoUpInteger
		: public CallWho
	{
	public:
		WhoUpInteger(const UpDownInteger *call, const Any *who)
			:  CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoDownInteger
		: public CallWho
	{
	public:
		WhoDownInteger(const UpDownInteger *call, const Any *who)
			:  CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoUpExpress
		: public CallWho
	{
	public:
		WhoUpExpress(const NodeExpressShort *call, const Any *who)
			:  CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoDownExpress
		: public CallWho
	{
	public:
		WhoDownExpress(const NodeExpressShort *call, const Any *who)
			:  CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class SinkUpOperand
		: public Sink
	{
	public:
		SinkUpOperand(const CallWho &what)
			: what(what)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *operand);
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Integer *value);
		const CallWho &what;
	};

	class SinkDownOperand
		: public SinkUpOperand
	{
	public:
		SinkDownOperand(const CallWho &what)
			: SinkUpOperand(what)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Integer *value);
	};

	class SinkUp
		: public Sink
	{
	public:
		SinkUp(const CallWho &what, long end)
			: what(what), end(end)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *operand);
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Integer *value);
	private:
		const CallWho &what;
	protected:
		long end;
	};

	class SinkDown
		: public SinkUp
	{
	public:
		SinkDown(const CallWho &what, long end)
			: SinkUp(what, end)
		{}
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Integer *value);
	};

	class WhoReverse
		: public CallWho
	{
	public:
		WhoReverse(const PropertyReverse *call, const Any *who)
			:  CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class SinkReverse
		: public Sink
	{
	public:
		SinkReverse(const CallWho &what)
			: what(what)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *who);
		const Step *pass(Runner &run, const ListConstant *value);
		const Step *pass(Runner &run, const ListExpress *value);
		const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count);
		const Step *pass(Runner &run, const Any *anchor, const Any *const *range, size_t count);
		const Step *pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count);
	private:
		const CallWho &what;
		const Step *pass(Runner &run, const PilsString *value);
	};

	class WhoPropertySplice
		: public CallWho
	{
	public:
		WhoPropertySplice(const PropertySplice *call, const Any *who)
			:  CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class PipeSplice
		: public Pipe
	{
	public:
		PipeSplice(const CallWho &what)
			: what(what)
		{}
		const Step *pass(Runner &run, const Any *thing);
		Sink *kick(Runner &run);
		const Step *pipeItem(Runner &run, const Any *thing);
		const Step *pipeBegin(Runner &run);
		const Step *pipeEnd(Runner &run);
		Pipe *splicing();
	private:
		const CallWho &what;
	};

	class PipingSplice
		: public Pipe
	{
	public:
		PipingSplice(Pipe &pipe, const Any *anchor)
			: pipe(pipe), anchor(anchor)
		{}
		const Step *pass(Runner &run, const Any *thing);
		Sink *kick(Runner &run);
		const Step *pipeItem(Runner &run, const Any *thing);
		const Step *pipeBegin(Runner &run);
		const Step *pipeEnd(Runner &run);
	private:
		Pipe &pipe;
		const Any *anchor;
	};

	class PipeListSeparator
		: public Pipe
	{
	public:
		PipeListSeparator(const CallWho &what, const Any *separator)
			: what(what), separator(separator), insertSeparator(false)
		{}
		const Step *pass(Runner &run, const Any *thing);
		Sink *kick(Runner &run);
		const Step *pipeItem(Runner &run, const Any *thing);
		const Step *pipeBegin(Runner &run);
		const Step *pipeEnd(Runner &run);
		Pipe &next() {return this[1];}
	private:
		const CallWho &what;
		const Any *separator;
		bool insertSeparator;
	};

	class PipesourceInsert
		: public Pipesource
	{
	public:
		PipesourceInsert(Pipe &pipe, const Any *item)
			: pipe(pipe), item(item)
		{}
		Sink *kick(Runner &run);
		const Step *step_(Runner &run) const;
	private:
		Pipe &pipe;
		const Any *item;
	};

	class PipeCounting
		: public PipeEach
	{
	public:
		PipeCounting(const WhoUntypedOperation &what, const Any *filter)
			: PipeEach(what, filter), count(0)
		{}
		const Step *pipeItem(Runner &run, const Any *thing);
		/*size-dependent methods*/
		const Step *pass(Runner &run, const Any *thing);
		Sink *kick(Runner &run);
		const Step *pipeBegin(Runner &run);
		/*enumerate node legs*/
		const Step *pass(Runner &run, const NodeConstantShort *node);
		const Step *pass(Runner &run, const NodeConstantLong *node);
		const Step *pass(Runner &run, const NodeExpressShort *node);
		const Step *pass(Runner &run, const NodeExpressLong *node);
	private:
		double count;
	};

	class PipeFirst
		: public PipeEach
	{
	public:
		PipeFirst(const WhoUntypedOperation &what, const Any *filter)
			: PipeEach(what, filter)
		{}
		const Step *pipeItem(Runner &run, const Any *thing);
		const Step *pipeBegin(Runner &run);
	private:
		friend class PipesourceFirst;
		const Step *pipeMyItem(Runner &run);
	};

	class PipesourceFirst
		: public Pipesource
	{
	public:
		PipesourceFirst(PipeFirst &pipeFirst)
			: pipeFirst(pipeFirst)
		{}
		const Step *step_(Runner &run) const;
		Sink *kick(Runner &run);
	private:
		PipeFirst &pipeFirst;
	};

	class PipeMinMax
		: public PipeFind
	{
	public:
		PipeMinMax(const WhoUntypedOperation &what, const Any *filter)
			: PipeFind(what, filter), key(NULL), value(NULL)
		{}
		Sink *kick(Runner &run);
		const Step *pipeItem(Runner &run, const Any *thing);
		const Step *pipeEnd(Runner &run);
	protected:
		friend class PipingMinMax;
		virtual bool better(const Constant *key) = 0;
		const Constant *key;
		const Any *value;
	};

	class PipeMin
		: public PipeMinMax
	{
	public:
		PipeMin(const WhoUntypedOperation &what, const Any *filter)
			: PipeMinMax(what, filter)
		{}
	protected:
		virtual bool better(const Constant *key);
	};

	class PipeMax
		: public PipeMinMax
	{
	public:
		PipeMax(const WhoUntypedOperation &what, const Any *filter)
			: PipeMinMax(what, filter)
		{}
	protected:
		virtual bool better(const Constant *key);
	};

	class PipingMinMax
		: SinkConstant
	{
	public:
		PipingMinMax(PipeMinMax &pipe, const Any *item)
			: pipe(pipe), item(item)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Constant *value);
		const Step *pass(Runner &run, const Any *value);
		const Step *miss(Runner &run);
	private:
		PipeMinMax &pipe;
		const Any *const item;
	};

	class PipeSum
		: public PipeFind
	{
	public:
		PipeSum(const WhoUntypedOperation &what, const Any *filter)
			: PipeFind(what, filter), sum(0)
		{}
		Sink *kick(Runner &run);
		const Step *pipeItem(Runner &run, const Any *thing);
		const Step *pipeEnd(Runner &run);
	private:
		friend class PipingSum;
		double sum;
	};

	class PipingSum
		: Sink
	{
	public:
		PipingSum(PipeSum &pipe, const Any *item)
			: pipe(pipe), item(item)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const Any *value);
		const Step *miss(Runner &run);
	private:
		PipeSum &pipe;
		const Any *const item;
	};

	class AggregateCallWho : public CallWho
	{
	public:
		AggregateCallWho(const PredefinedAggregateFunctionName *call, const Any *who)
			: CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class PipeAggregate : public Pipe
	{
	public:
		const Step *pass(Runner &run, const Any *value);
		const Step *pipeBegin(Runner &run);
	protected:
		PipeAggregate(const AggregateCallWho &what)
			: what(what)
		{}
		const AggregateCallWho &what;
	};

	class PipeAggregateSum : public PipeAggregate
	{
	public:
		PipeAggregateSum(const AggregateCallWho &what)
			: PipeAggregate(what), sum(0)
		{}
		const Step *pipeItem(Runner &run, const Any *item);
		const Step *pipeEnd(Runner &run);
		Sink *kick(Runner &run);
	private:
		double sum;
	};

	class PipeAggregateMinMax : public PipeAggregate
	{
	public:
		const Step *pipeEnd(Runner &run);
		Sink *kick(Runner &run);
	protected:
		PipeAggregateMinMax(const AggregateCallWho &what)
			: PipeAggregate(what), item(NULL)
		{}
		const Constant *item;
	};

	class PipeAggregateMin : public PipeAggregateMinMax
	{
	public:
		PipeAggregateMin(const AggregateCallWho &what)
			: PipeAggregateMinMax(what)
		{}
		const Step *pipeItem(Runner &run, const Any *item);
	};

	class PipeAggregateMax : public PipeAggregateMinMax
	{
	public:
		PipeAggregateMax(const AggregateCallWho &what)
			: PipeAggregateMinMax(what)
		{}
		const Step *pipeItem(Runner &run, const Any *item);
	};
}
#endif
