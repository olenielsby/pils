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
        Pipe *connectPipe(Runner &run) override;
		virtual const Step *pipeItem(Runner &run, const Any *item) = 0;
		virtual	const Step *pipeBegin(Runner &run) = 0;
		virtual const Step *pipeEnd(Runner &run) = 0;
		virtual Pipe *splicing();
		virtual Sink *shortcut(Runner &run);
        const Step *pass(Runner &run, const ListConstant &value) override;
        const Step *pass(Runner &run, const ListExpress &value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
        const Step *pass(Runner &run, const Special *value) override;
        const Step *pass(Runner &run, const Any *anchor, const Any *const *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count) override;
	};

	class PipeToNowhere
		: public Pipe
	{
	public:
        using Pipe::pass;
        const Step *pass(Runner &run, const Any *thing) override;
        Sink *kick(Runner &run) override;
        const Step *pipeItem(Runner &run, const Any *thing) override;
        const Step *pipeBegin(Runner &run) override;
        const Step *pipeEnd(Runner &run) override;
        Sink *shortcut(Runner &run) override;
        const Step *called(Runner &run, const Empty &call) override;
        const Step *error(Runner &run, const Any *error, const Express *what, const Any *who) override;
        const Step *miss(Runner &run) override;
        void refer(Runner &run, const Express &what) override;
	};

	class PipeHoldTail
		: public Pipe
	{
	public:
        using Pipe::pass;
		PipeHoldTail(const Any *thing, const Any *whence)
			: thing(thing), whence(whence)
		{}
        const Step *pass(Runner &run, const Any *value) override;
        Sink *kick(Runner &run) override;
        const Step *tailStep(Runner &run, const Any *thing, const Any *where_) override;
        const Step *tailStep(Runner &run, const Any *thing) override;
        bool needsResult() override;
        const Step *pipeItem(Runner &run, const Any *item) override;
        const Step *pipeBegin(Runner &run) override;
        const Step *pipeEnd(Runner &run) override;
        Sink *pushWhere(Runner &run, const Any *where) override;
		const Any *thing;
		const Any *whence;
	};

	class PipeWhereabout
		: public Pipe
	{
	public:
        using Pipe::pass;
		PipeWhereabout(const Any *where_)
			: where_(where_)
		{}
        const Step *pass(Runner &run, const Any *value) override;
        Sink *kick(Runner &run) override;
        const Step *tailStep(Runner &run, const Any *thing, const Any *where_) override;
        const Step *tailStep(Runner &run, const Any *thing) override;
        bool needsResult() override;
        const Step *pipeItem(Runner &run, const Any *item) override;
        const Step *pipeBegin(Runner &run) override;
        const Step *pipeEnd(Runner &run) override;
        Sink *pushWhere(Runner &run, const Any *where) override;
		const Any *where_;
	};

	class PipeToList
		: public PipeToNowhere
	{
	public:
        Sink *kick(Runner &run) override;
        const Step *pipeItem(Runner &run, const Any *thing) override;
        const Step *pipeEnd(Runner &run) override;
        const Step *miss(Runner &run) override;
        void refer(Runner &run, const Express &what) override;
	private:
		std::vector<const Any*> elements;
	};

	class Pipesource
		: public Sink
	{
	public:
        using Sink::pass;
        const Step *pass(Runner &run, const Any *thing) override; //dummy
	};

	class PipeHold
		: public Pipe
	{
	public:
        using Pipe::pass;
		PipeHold(const Any *hold)
			: hold(hold)
		{}
        const Step *pass(Runner &run, const Any *thing) override;
        Sink *kick(Runner &run) override;
        const Step *pipeBegin(Runner &run) override;
        const Step *pipeItem(Runner &run, const Any *thing) override;
        const Step *pipeEnd(Runner &run) override;
		const Any *hold;
	};

	class PipesourceListRange
		: public Pipesource
	{
	public:
		PipesourceListRange(const Any *const *source, size_t count)
			: source(source), end(source + count)
		{}
        const Step *step_(Runner &run) const override;
        Sink *kick(Runner &run) override;
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
        const Step *step_(Runner &run) const override;
	};

	class PipesourceListRangeEval
		: public PipesourceListRange
	{
	public:
		PipesourceListRangeEval(const Any *const *source, size_t count)
			: PipesourceListRange(source, count)
		{}
        const Step *step_(Runner &run) const override;
	};

	class Piping
		: public Sink
	{
	public:
		Piping(Pipe &pipe)
			: pipe(pipe)
		{}
        const Step *pass(Runner &run, const Any *thing) override;
        Sink *kick(Runner &run) override;
	protected:
		Pipe &pipe;
	};

	class PipeEach
		: public Pipe
	{
	public:
        using Pipe::pass;
		PipeEach(const WhoUntypedOperation &what, const Any *filter)
			: what(what), filter(filter)
		{}
        const Step *pass(Runner &run, const Any *thing) override;
        Sink *kick(Runner &run) override;
        const Step *pipeItem(Runner &run, const Any *thing) override;
        const Step *pipeBegin(Runner &run) override;
        const Step *pipeEnd(Runner &run) override;
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
        const Step *pipeItem(Runner &run, const Any *thing) override;
        const Step *pipeBegin(Runner &run) override;
        const Step *pipeEnd(Runner &run) override;
	};

	class PipeEvery
		: public PipeEach
	{
	public:
		PipeEvery(const WhoUntypedOperation &what, const Any *filter)
			: PipeEach(what, filter)
		{}
        const Step *pipeItem(Runner &run, const Any *thing) override;
	};

	class PipeWhile
		: public PipeEach
	{
	public:
		PipeWhile(const WhoUntypedOperation &what, const Any *filter)
			: PipeEach(what, filter)
		{}
        const Step *pipeItem(Runner &run, const Any *thing) override;
	};

	class PipeExcept
		: public PipeEach
	{
	public:
		PipeExcept(const WhoUntypedOperation &what, const Any *filter)
			: PipeEach(what, filter)
		{}
        const Step *pipeItem(Runner &run, const Any *thing) override;
	};

	class PipeFold
		: public Pipe
	{
	public:
        using Pipe::pass;
        PipeFold(const WhoUntypedOperation &what, const Any *fold)
			: what(what), fold(fold), value(nullptr)
		{}
        const Step *pass(Runner &run, const Any *thing) override;
        Sink *kick(Runner &run) override;
        const Step *pipeItem(Runner &run, const Any *thing) override;
        const Step *pipeBegin(Runner &run) override;
        const Step *pipeEnd(Runner &run) override;
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
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *thing) override;
        const Step *tailStep(Runner &run, const Any *thing, const Any *where_) override;
        const Step *error(Runner &run, const Any *error, const Express *what, const Any *who) override;
        const Step *miss(Runner &run) override;
	private:
		const Any *item;
	};

	class PipeSplicingEvery
		: public Pipe
	{
	public:
        using Pipe::pass;
		PipeSplicingEvery(Pipe &splicing)
			: splicing(splicing)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *thing) override;
        const Step *pipeItem(Runner &run, const Any *thing) override;
        const Step *pipeBegin(Runner &run) override;
        const Step *pipeEnd(Runner &run) override;
	private:
		Pipe &splicing;
	};

	class PipingExcept
		: public SinkForget
	{
	public:
        using SinkForget::pass;
        PipingExcept(Pipe &pipe, const Any *item)
			: pipe(pipe), item(item)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, long dummy) override;
        const Step *miss(Runner &run) override;
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
        const Step *called(Runner &run, const Constant &call) override;
        const Step *called(Runner &run, const Integer &call) override;
        const Step *called(Runner &run, const ListConstant &call) override;
        const Step *called(Runner &run, const NodeConstant &call) override;
        const Step *called(Runner &run, const Empty &call) override;
        const Step *called(Runner &run, const ListExpress &call) override;
        const Step *called(Runner &run, const NodeExpress &call) override;
        const Step *called(Runner &run, const Any &call, const Any *assignValue) override;
        const Step *miss(Runner &run) override;
	};

	class PipingWhile
		: public PipingEvery
	{
	public:
		PipingWhile(Pipe &pipe, const Any *item)
			: PipingEvery(pipe, item)
		{}
        const Step *called(Runner &run, const Constant &call) override;
        const Step *called(Runner &run, const Integer &call) override;
        const Step *called(Runner &run, const ListConstant &call) override;
        const Step *called(Runner &run, const NodeConstant &call) override;
        const Step *called(Runner &run, const Empty &call) override;
        const Step *called(Runner &run, const ListExpress &call) override;
        const Step *called(Runner &run, const NodeExpress &call) override;
        const Step *called(Runner &run, const Any &call, const Any *assignValue) override;
        const Step *miss(Runner &run) override;
	};

	class PipingEveryTail
		: public Piping
	{
	public:
		PipingEveryTail(Pipe &pipe, const Any *thing, const Any *whence)
			: Piping(pipe), thing(thing), whence(whence)
		{}
        const Step *pass(Runner &run, const Any *value) override;
        Sink *kick(Runner &run) override;
        const Step *tailStep(Runner &run, const Any *thing, const Any *where_) override;
        const Step *tailStep(Runner &run, const Any *thing) override;
        Pipe *connectPipe(Runner &run) override;
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
        const Step *pass(Runner &run, const Any *thing) override;
        const Step *tailStep(Runner &run, const Any *thing, const Any *where_) override;
	};

	class PipingFold
		: public Piping
	{
	public:
		PipingFold(PipeFold &pipe)
			: Piping(pipe)
		{}
        const Step *pass(Runner &run, const Any *value) override;
        const Step *error(Runner &run, const Any *error, const Express *what, const Any *who) override;
        const Step *called(Runner &run, const Any &call, const Any *assignValue) override;
        const Step *miss(Runner &run) override;
	};

	class WhoCount
		: public CallWho
	{
	public:
		WhoCount(const TypecheckPropertyCount *call, const Any *who)
			: CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class PipeProperty
		: public Pipe
	{
	public:
        using Pipe::pass;
        const Step *pass(Runner &run, SinkTaggedNodeBuilding &nodeBuilding) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *pipeBegin(Runner &run) override;
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
        using PipeProperty::pass;
		PipeCount(const WhoCount &what)
			: PipeProperty(what), count(0)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const PilsString &value) override;
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const ListConstant &value) override;
        const Step *pass(Runner &run, const ListExpress &value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
        const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Any *const *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count) override;
        const Step *pipeItem(Runner &run, const Any *thing) override;
        const Step *pipeEnd(Runner &run) override;
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
        const Step *step_(Runner &run) const override;
	};

	class PipeCharacterEncoder
		: public PipeProperty, private Converter
	{
	public:
        using PipeProperty::pass;
		PipeCharacterEncoder(const WhoCharacterEncoding &whatever)
			: PipeProperty(whatever), state(0)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count) override;
        const Step *pipeItem(Runner &run, const Any *thing) override;
        const Step *pipeEnd(Runner &run) override;
        bool convert(const Integer &character) override;
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
        Sink *kick(Runner &run) override;
        const Step *step_(Runner &run) const override;
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
        const Step *step_(Runner &run) const override;
	};

	class SinkPropertyIncrementRange
		: public Sink
	{
	public:
		SinkPropertyIncrementRange(const WhoPropertyIncrementRange &what)
			: what(what)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *who) override;
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
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
        const Step *step_(Runner &run) const override;
	};

	class SinkPropertyDecrementRange
		: public SinkPropertyIncrementRange
	{
	public:
		SinkPropertyDecrementRange(const WhoPropertyIncrementRange &what)
			: SinkPropertyIncrementRange(what)
		{}
        const Step *pass(Runner &run, long value) override;
	};

	class PipesourceIntegerStep
		: public Pipesource
	{
	public:
		PipesourceIntegerStep(long next, long count, long delta)
			: next(next), count(count), delta(delta)
		{}
        const Step *step_(Runner &run) const override;
        Sink *kick(Runner &run) override;
	private:
		long next;
		long count;
		long delta;
	};

	class UpDownInteger
		: public NodeConstantTiny
	{
	public:
		UpDownInteger(const Constant *&link, const BuiltinClicheOperationUpDown &cliche, const Integer *value)
			: NodeConstantTiny(link, cliche, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class WhoUpInteger
		: public CallWho
	{
	public:
		WhoUpInteger(const UpDownInteger *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoDownInteger
		: public CallWho
	{
	public:
		WhoDownInteger(const UpDownInteger *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoUpExpress
		: public CallWho
	{
	public:
		WhoUpExpress(const NodeExpressShort *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoDownExpress
		: public CallWho
	{
	public:
		WhoDownExpress(const NodeExpressShort *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class SinkUpOperand
		: public Sink
	{
	public:
		SinkUpOperand(const CallWho &what)
			: what(what)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *operand) override;
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
		const CallWho &what;
	};

	class SinkDownOperand
		: public SinkUpOperand
	{
	public:
		SinkDownOperand(const CallWho &what)
			: SinkUpOperand(what)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
	};

	class SinkUp
		: public Sink
	{
	public:
		SinkUp(const CallWho &what, long end)
			: what(what), end(end)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *operand) override;
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
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
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
	};

	class WhoReverse
		: public CallWho
	{
	public:
		WhoReverse(const PropertyReverse *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class SinkReverse
		: public Sink
	{
	public:
		SinkReverse(const CallWho &what)
			: what(what)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *who) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
        const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Any *const *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count) override;
	private:
		const CallWho &what;
        const Step *pass(Runner &run, const PilsString *value) override;
	};

	class WhoPropertySplice
		: public CallWho
	{
	public:
		WhoPropertySplice(const PropertySplice *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class PipeSplice
		: public Pipe
	{
	public:
        using Pipe::pass;
		PipeSplice(const CallWho &what)
			: what(what)
		{}
        const Step *pass(Runner &run, const Any *thing) override;
        Sink *kick(Runner &run) override;
        const Step *pipeItem(Runner &run, const Any *thing) override;
        const Step *pipeBegin(Runner &run) override;
        const Step *pipeEnd(Runner &run) override;
        Pipe *splicing() override;
	private:
		const CallWho &what;
	};

	class PipingSplice
		: public Pipe
	{
	public:
        using Pipe::pass;
        PipingSplice(Pipe &pipe, const Any *anchor)
			: pipe(pipe), anchor(anchor)
		{}
        const Step *pass(Runner &run, const Any *thing) override;
        Sink *kick(Runner &run) override;
        const Step *pipeItem(Runner &run, const Any *thing) override;
        const Step *pipeBegin(Runner &run) override;
        const Step *pipeEnd(Runner &run) override;
	private:
		Pipe &pipe;
		const Any *anchor;
	};

	class PipeListSeparator
		: public Pipe
	{
	public:
        using Pipe::pass;
        PipeListSeparator(const CallWho &what, const Any *separator)
			: what(what), separator(separator), insertSeparator(false)
		{}
        const Step *pass(Runner &run, const Any *thing) override;
        Sink *kick(Runner &run) override;
        const Step *pipeItem(Runner &run, const Any *thing) override;
        const Step *pipeBegin(Runner &run) override;
        const Step *pipeEnd(Runner &run) override;
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
        Sink *kick(Runner &run) override;
        const Step *step_(Runner &run) const override;
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
        const Step *pipeItem(Runner &run, const Any *thing) override;
		/*size-dependent methods*/
        const Step *pass(Runner &run, const Any *thing) override;
        Sink *kick(Runner &run) override;
        const Step *pipeBegin(Runner &run) override;
		/*enumerate node legs*/
        const Step *pass(Runner &run, const NodeConstantShort *node) override;
        const Step *pass(Runner &run, const NodeConstantLong *node) override;
        const Step *pass(Runner &run, const NodeExpressShort *node) override;
        const Step *pass(Runner &run, const NodeExpressLong *node) override;
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
        const Step *pipeItem(Runner &run, const Any *thing) override;
        const Step *pipeBegin(Runner &run) override;
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
        const Step *step_(Runner &run) const override;
        Sink *kick(Runner &run) override;
	private:
		PipeFirst &pipeFirst;
	};

	class PipeMinMax
		: public PipeFind
	{
	public:
		PipeMinMax(const WhoUntypedOperation &what, const Any *filter)
			: PipeFind(what, filter), key(nullptr), value(nullptr)
		{}
        Sink *kick(Runner &run) override;
        const Step *pipeItem(Runner &run, const Any *thing) override;
        const Step *pipeEnd(Runner &run) override;
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
        virtual bool better(const Constant *key) override;
	};

	class PipeMax
		: public PipeMinMax
	{
	public:
		PipeMax(const WhoUntypedOperation &what, const Any *filter)
			: PipeMinMax(what, filter)
		{}
	protected:
        virtual bool better(const Constant *key) override;
	};

	class PipingMinMax
		: SinkConstant
	{
	public:
        using SinkConstant::pass;
        PipingMinMax(PipeMinMax &pipe, const Any *item)
			: pipe(pipe), item(item)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Constant *value) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *miss(Runner &run) override;
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
        Sink *kick(Runner &run) override;
        const Step *pipeItem(Runner &run, const Any *thing) override;
        const Step *pipeEnd(Runner &run) override;
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
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *miss(Runner &run) override;
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
        const Step *step_(Runner &run) const override;
	};

	class PipeAggregate : public Pipe
	{
	public:
        using Pipe::pass;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *pipeBegin(Runner &run) override;
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
        const Step *pipeItem(Runner &run, const Any *item) override;
        const Step *pipeEnd(Runner &run) override;
        Sink *kick(Runner &run) override;
	private:
		double sum;
	};

	class PipeAggregateMinMax : public PipeAggregate
	{
	public:
        const Step *pipeEnd(Runner &run) override;
        Sink *kick(Runner &run) override;
	protected:
		PipeAggregateMinMax(const AggregateCallWho &what)
			: PipeAggregate(what), item(nullptr)
		{}
		const Constant *item;
	};

	class PipeAggregateMin : public PipeAggregateMinMax
	{
	public:
		PipeAggregateMin(const AggregateCallWho &what)
			: PipeAggregateMinMax(what)
		{}
        const Step *pipeItem(Runner &run, const Any *item) override;
	};

	class PipeAggregateMax : public PipeAggregateMinMax
	{
	public:
		PipeAggregateMax(const AggregateCallWho &what)
			: PipeAggregateMinMax(what)
		{}
        const Step *pipeItem(Runner &run, const Any *item) override;
	};
}
#endif
