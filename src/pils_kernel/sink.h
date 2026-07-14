/* This file is public domain */
#pragma once
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
        explicit Runner(size_t stackSize);
		virtual ~Runner();
		void *allocate(size_t size);
		Sink *pushWhere(const Any *newWhere);
		void run(const Step *step_);
		const Step *pass(const Any *thing);
        virtual bool isMainThread() const;
        virtual const Constant *as_Thread() const;
		virtual const Step *callingKnot(const Any &who, const Any &call);
		virtual const Step *callingKnot(const Any &who, const Any &call, const Any *assignValue);
		virtual const Step *thread(const Any &what);
        void release(const Any *thing);
        Any *deletionQueue = nullptr;
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
            const Step *step_(Runner &run) const override;
		};
		Strap::Sticker threadStrapSticker;
		Strap::Sticker *temporaryStrapSticker;
        bool stackOverflow() const;
		const Step *callingStackOverflow();
		bool oldTimer;
        static Runner &main();
	};

    class PassingMind : public Strap::Sticker
	{
    public:
        PassingMind(Runner &run, const Any &owner) : owner(owner), Strap::Sticker (run) {}
        ~PassingMind();
        const Any *set(const Constant *key, const Any *value);
        const Any *get(const Constant &key) const;
        const Any &owner;
	private:
        std::unordered_map<const Constant*, const Any*> map;
    };

    /* Template for node constructor maps
     *
     * If present, the joker value is stored outside the map
     * and placed in front when attribute names and values
     * are extracted.
     */

    template<class Value> class NodeBuilder
    {
    public:
        typedef std::map<const Constant*, const Value*> map; // Value* won't compile
        bool aim(const Constant *key)
        {
            if (aimed) goto bad;
            if (key == (const Constant *)&Empty::singleton)
            {
                if (joker)
                    goto bad;
            }
            else
            {
                if (mapping.count(key))
                    goto bad;
            }
            aimed = key;
            return true;
        bad:
            key->unduplicateReference();
            return false;
        }

        void set(Value* value)
        {
            if (aimed == (const Constant *)&Empty::singleton) joker = value;
            else mapping[aimed] = value;
            aimed = nullptr;
        }

        size_t count()
        {
            return mapping.size() + (joker ? 1 : 0);
        }

        const Any *build();
        // {
        //     size_t count = this->count();
        //     const Any *node;
        //     switch (count)
        //     {
        //     case 0:
        //         return nullptr;
        //     case 1:
        //         if (joker)
        //         {
        //             const ClicheTiny *cliche = head->clichefy();
        //             node = cliche->ClicheShort::node(joker);
        //             cliche->unduplicateReference();
        //         }
        //         else
        //         {
        //             typename map::iterator r = mapping.begin();
        //             const ClicheShort *cliche = head->clichefy(r->first);
        //             node = cliche->node(r->second);
        //             cliche->unduplicateReference();
        //         }
        //         break;
        //     default:
        //     {
        //         const Constant** attributes = new const Constant*[count];
        //         const Constant** values = new const Constant*[count];
        //         const Constant** a = attributes;
        //         const Constant** v = values;
        //         if (joker)
        //         {
        //             *a++ = &Empty::singleton;
        //             *v++ = joker;
        //         }
        //         for (typename map::iterator r = mapping.begin(); r != mapping.end(); r++)
        //         {
        //             *a++ = r->first;
        //             *v++ = (const Constant*)r->second;
        //         }
        //         const Cliche *cliche = head->clichefy(attributes, count);
        //         delete[] attributes;
        //         node = cliche->node(values);
        //         delete[] values;
        //         cliche->unduplicateReference();
        //     }
        //     }
        //     alive = false;
        //     return node;
        // }
        NodeBuilder(Runner &run, const Constant *head)
            : run(run), head(head), aimed(nullptr), joker(nullptr), alive(true)
        {}

        ~NodeBuilder()
        {
            if (aimed) aimed->unduplicateReference();
            if (alive)
            {
                head->unduplicateReference();
                if (joker)
                {
                    joker->unduplicateReference();
                    Empty::singleton.unduplicateReference();
                }
                for (typename map::iterator r = mapping.begin();
                     r != mapping.end();
                     r++)
                {
                    run.release(r->first);
                    run.release(r->second);
                }
            }
        }
        const Constant *head;
    protected:
        Runner &run;
    private:
        map mapping;
        const Constant *aimed;
        Value* joker;
        bool alive;
    };

    template<>
    const Any *NodeBuilder<const Constant>::build();

    template<>
    const Any *NodeBuilder<const Any>::build();

    class ClicheBuilder
    {
    public:
        bool add(const Constant *key);
        bool add(const Constant &key);
        const Cliche *build();
        ClicheBuilder(const Constant *head)
            : head(head), joker(false), alive(true)
        {}
        ~ClicheBuilder();
    private:
        std::set<const Constant*> setting;
        const Constant *head;
        bool joker;
        bool alive;
    };

    template <class Element, class Result> class ListBuilder
    {
    public:
        typedef std::vector<Element*> vector;
        void add(Element* element)
        {
            listing.insert(listing.end(), element);
        }
        Result *build()
        {
            size_t count = listing.size();
            Element **element = new Element*[count];
            Element **e = element;
            for (typename vector::iterator r = listing.begin(); r != listing.end(); r++)
                *e++ = (Element*)*r;
            Result *list = building(element, count);
            alive = false;
            delete [] element;
            return list;
        }
        explicit ListBuilder(Runner &run) : run(run), alive(true)
        {
        }
        ~ListBuilder()
        {
            if (alive)
            {
                for (typename vector::iterator r = listing.begin(); r != listing.end(); r++)
                {
                    run.release(*r);
                }
            }
        }

    protected:
        Runner &run;
    private:
        static Result* building(Element *const *element, size_t count);
        vector listing;
        bool alive;
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
        const Step *step_(Runner &run) const override;
	};

	/* Lightweight failure - construction of error node is postponed */
	class Miss
		: public Sink
	{
	public:
		virtual const Step *missing(Runner &run, Sink *sink) = 0;
        const Step *pass(Runner &run, const Any *value) override; //dummy
	};

	class MissCall
		: public Miss
	{
	public:
		MissCall(const Any &call) : call(call) {}
        const Step *missing(Runner &run, Sink *sink) override;
        Sink *kick(Runner &run) override;
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
        const Step *missing(Runner &run, Sink *sink) override;
        Sink *kick(Runner &run) override;
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
        const Step *missing(Runner &run, Sink *sink) override;
        Sink *kick(Runner &run) override;
	private:
		PassingMind *mind;
		const Any *call;
		const Express *what;
	};

	class MissSpecial
		: public Miss
	{
	public:
        const Step *called(Runner &run, const Constant &call) override;
        const Step *called(Runner &run, const Integer &call) override;
        const Step *called(Runner &run, const ListConstant &call) override;
        const Step *called(Runner &run, const NodeConstant &call) override;
        const Step *called(Runner &run, const Empty &call) override;
        const Step *called(Runner &run, const ListExpress &call) override;
        const Step *called(Runner &run, const NodeExpress &call) override;
        const Step *called(Runner &run, const Any &call, const Any *assignValue) override;
        const Step *miss(Runner &run) override = 0;
        const Step *missing(Runner &run, Sink *sink) override;
        virtual const Any *errorData() = 0;
	};

	class SinkConstant
		: public Sink
	{
	public:
        using Sink::pass;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const PilsDate *value) override;
        const Step *pass(Runner &run, const Timestamp *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const Cliche *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const NodeConstantLong *value) override;
        const Step *pass(Runner &run, const NodeConstantShort *value) override;
        const Step *pass(Runner &run, const Special *value) override;
		virtual const Step *pass(Runner &run, const Constant *value) = 0;
	};

	class SinkForget
		: public Sink
	{
	public:
		using Sink::pass;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const PilsString &value) override;
        const Step *pass(Runner &run, const Cliche &value) override;
        const Step *pass(Runner &run, const ListConstant &value) override;
        const Step *pass(Runner &run, const NodeConstantLong &value) override;
        const Step *pass(Runner &run, const NodeConstantShort &value) override;
        const Step *pass(Runner &run, const ListExpress &value) override;
        const Step *pass(Runner &run, const NodeExpressLong &value) override;
        const Step *pass(Runner &run, const NodeExpressShort &value) override;
        const Step *pass(Runner &run, const Any *value) override;
        bool needsResult() override;
	};

	class SinkHolding
		: public Sink
	{
	public:
        Sink *kick(Runner &run) override;
		const Any *thing;
		SinkHolding(const Any *thing)
			: thing(thing)
		{}
        bool needsResult() override;
	};

	class SinkHoldCalling
		: public SinkHolding
	{
	public:
		SinkHoldCalling(const Any *thing)
			: SinkHolding(thing)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const PilsDate *value) override;
        const Step *pass(Runner &run, const Timestamp *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const Cliche *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const NodeConstantLong *value) override;
        const Step *pass(Runner &run, const NodeConstantShort *value) override;
        const Step *pass(Runner &run, const Special *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
        const Step *pass(Runner &run, const NodeExpressLong *value) override;
        const Step *pass(Runner &run, const NodeExpressShort *value) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *pass(Runner &run, PassingMind *mind, const Express *what) override;
        const Step *tailStep(Runner &run, const Any *thing, const Any *where_) override;
        const Step *tailStep(Runner &run, const Any *thing) override;
        Pipe *connectPipe(Runner &run) override;
        const Step *error(Runner &run, const Any *error, const Express *what, const Any *who) override;
        const Step *miss(Runner &run) override;
	};

	class SinkResultStep
		: public SinkHoldCalling
	{
	public:
		SinkResultStep(const Any *thing)
			: SinkHoldCalling(thing)
		{}
        const Step *step_(Runner &run) const override;
	};

	class SinkHold
		: public SinkHoldCalling
	{
	public:
		SinkHold(const Any *thing)
			: SinkHoldCalling(thing)
		{}
        const Step *called(Runner &run, const Constant &call) override;
        const Step *called(Runner &run, const Integer &call) override;
        const Step *called(Runner &run, const ListConstant &call) override;
        const Step *called(Runner &run, const NodeConstant &call) override;
        const Step *called(Runner &run, const Empty &call) override;
        const Step *called(Runner &run, const ListExpress &call) override;
        const Step *called(Runner &run, const NodeExpress &call) override;
        const Step *called(Runner &run, const Any &call, const Any *assignValue) override;
	};

	class SinkHoldTail
		: public Sink
	{
	public:
		SinkHoldTail(const Any *thing, const Any *whence)
			: thing(thing), whence(whence)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const PilsDate *value) override;
        const Step *pass(Runner &run, const Timestamp *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const Cliche *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const NodeConstantLong *value) override;
        const Step *pass(Runner &run, const NodeConstantShort *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
        const Step *pass(Runner &run, const NodeExpressLong *value) override;
        const Step *pass(Runner &run, const NodeExpressShort *value) override;
        const Step *pass(Runner &run, const Any *value) override;
        Sink *kick(Runner &run) override;
        const Step *tailStep(Runner &run, const Any *thing, const Any *where_) override;
        const Step *tailStep(Runner &run, const Any *thing) override;
        Pipe *connectPipe(Runner &run) override;
        bool needsResult() override;
        Sink *pushWhere(Runner &run, const Any *where) override;
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
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
	private:
		void *block;
	};

	class SinkConstantCall
		: public Sink
	{
	public:
        const Step *pass(Runner &run, const Any *value) override;
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
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const PilsString &value) override;
        const Step *pass(Runner &run, const Cliche &value) override;
        const Step *pass(Runner &run, const ListConstant &value) override;
        const Step *pass(Runner &run, const NodeConstantShort &value) override;
        const Step *pass(Runner &run, const NodeConstantLong &value) override;
        const Step *pass(Runner &run, const Special &value) override;
        const Step *pass(Runner &run, const ListExpress &value) override;
        const Step *pass(Runner &run, const NodeExpressShort &value) override;
        const Step *pass(Runner &run, const NodeExpressLong &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const PilsDate *value) override;
        const Step *pass(Runner &run, const Timestamp *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const Cliche *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const NodeConstantShort *value) override;
        const Step *pass(Runner &run, const NodeConstantLong *value) override;
        const Step *pass(Runner &run, const Special *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
        const Step *pass(Runner &run, const NodeExpressShort *value) override;
        const Step *pass(Runner &run, const NodeExpressLong *value) override;
        const Step *pass(Runner &run, const Any *value) override;
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
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count) override;
        const Step *pass(Runner &run, const Any *value) override;
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
        const Step *pass(Runner &run, const Any *value) override;
        const Step *pass(Runner &run, SinkTaggedNodeBuilding &nodeBuilding) override;
        const Step *pass(Runner &run, PassingMind *mind, const Express *what) override;
        Sink *kick(Runner &run) override;
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
        const Step *pass(Runner &run, const Any *value) override;
        const Step *pass(Runner &run, SinkTaggedNodeBuilding &nodeBuilding) override;
        Sink *kick(Runner &run) override;
	protected:
		const CallWho &what;
	};

	class SinkWhoOperationUncounted
		: public Sink
	{
	public:
        Sink *kick(Runner &run) override;
	protected:
        SinkWhoOperationUncounted(const CallWho &what, const Any &operand);
        const Step *pass(Runner &run, const Any *value) override;
		const CallWho &what;
		const Any &operand;
	};

	class SinkWhoOperationAny
		: public Sink
	{
	public:
        Sink *kick(Runner &run) override;
	protected:
		SinkWhoOperationAny(const WhoExpressOperation &what, const Any *operand)
			: what(what), operand(operand)
		{}
        const Step *pass(Runner &run, const Any *value) override;
		const WhoExpressOperation &what;
		const Any *operand;
	};

	class SinkWhoOperationRawInteger
		: public Sink
	{
	public:
        Sink *kick(Runner &run) override;
	protected:
		SinkWhoOperationRawInteger(const WhoExpressOperation &what, long operand)
				: what(what), operand(operand)
		{}
        const Step *pass(Runner &run, const Any *value) override;
		const WhoExpressOperation &what;
		long operand;
	};

	class SinkWhoOperationRawFloat
		: public Sink
	{
	public:
        Sink *kick(Runner &run) override;
	protected:
		SinkWhoOperationRawFloat(const WhoExpressOperation &what, double operand)
			: what(what), operand(operand)
		{}
        const Step *pass(Runner &run, const Any *value) override;
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
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *thing) override;
        const Step *tailStep(Runner &run, const Any *thing, const Any *where_) override;
        const Step *tailStep(Runner &run, const Any *thing) override;
        Sink *pushWhere(Runner &run, const Any *where) override;
        Pipe *connectPipe(Runner &run) override;
        bool needsResult() override;
	};

	class SinkWhereaboutUncounted
		: public SinkWhereabout
	{
	public:
		SinkWhereaboutUncounted(const Any *where_)
			: SinkWhereabout(where_)
		{}
        Sink *kick(Runner &run) override;
        Sink *pushWhere(Runner &run, const Any *where) override;
        const Step *tailStep(Runner &run, const Any *thing) override;
	};

	class SinkNodeShort
		: public Sink
	{
	public:
		const ClicheShort &cliche;
		SinkNodeShort(const ClicheShort& cliche) : cliche(cliche) {}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *thing) override;
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
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *thing) override;
	};

	class SinkContinue
		: public SinkForget
	{
	public:
        using SinkForget::pass;
		const Any &tail;
		SinkContinue(const Any &tail)
			: tail(tail)
		{}
        const Step *pass(Runner &run, long dummy) override;
        Sink *kick(Runner &run) override;
	};

	class SinkCondition
		: public SinkForget
	{
	public:
        using SinkForget::pass;
        const Step *miss(Runner &run) override;
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const PilsString &value) override;
        const Step *pass(Runner &run, const Cliche &value) override;
        const Step *pass(Runner &run, const ListConstant &value) override;
        const Step *pass(Runner &run, const NodeConstantLong &value) override;
        const Step *pass(Runner &run, const NodeConstantShort &value) override;
        const Step *pass(Runner &run, const ListExpress &value) override;
        const Step *pass(Runner &run, const NodeExpressLong &value) override;
        const Step *pass(Runner &run, const NodeExpressShort &value) override;
        const Step *pass(Runner &run, const Special &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Any *value) override;
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
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        const Step *calling(Runner &run, const ListExpress &call) const override;
        const Step *calling(Runner &run, const NodeExpress &call) const override;
        const Step *calling(Runner &run, const Any &call, const Any *assignValue) const override;
        const Express *findCatchTag() const override;
        const Express *findCatchTag(const Constant &tag) const override;
	private:
		const Any *dummy;
	};

	class SinkTaggedBuilding
		: public SinkTagged
	{
	public:
		virtual const Step *calling(Runner &run, const Building &tag) = 0;
		virtual const Step *calling(Runner &run, const Building &tag, const Any *assignValue) = 0;
        virtual const Step *skip(Runner &run) override; //dummy
	protected:
		SinkTaggedBuilding(const Building &tag, SinkTagged *chain)
			: SinkTagged(tag, chain)
		{}
	};

	class SinkTaggedListBuilding
		: public SinkTaggedBuilding
	{
	public:
        using SinkTaggedBuilding::pass;
		SinkTaggedListBuilding(Building &tag, SinkTagged *chain)
			: SinkTaggedBuilding(tag, chain)
		{}
        const Step *calling(Runner &run, const Building &tag) override;
        const Step *calling(Runner &run, const Building &tag, const Any *assignValue) override;
        const Step *pass(Runner &run, long value) override;
        Sink *kick(Runner &run) override;
	};

	class SinkTaggedNodeBuilding
		: public SinkTaggedBuilding
	{
	public:
        using SinkTaggedBuilding::pass;
		SinkTaggedNodeBuilding(Building &tag, SinkTagged *chain, const Express &what)
			: SinkTaggedBuilding(tag, chain), head(((const NodeConstant*)tag.element[1])->element[0]), joker(nullptr)
		{
			head->retain();
		}
		SinkTaggedNodeBuilding(Building &tag, SinkTagged *chain, const Constant &head)
            : SinkTaggedBuilding(tag, chain), head(&head), joker(nullptr)
		{
			head.retain();
		}
        const Step *calling(Runner &run, const Building &tag) override;
        const Step *calling(Runner &run, const Building &tag, const Any *assignValue) override;
        const Step *pass(Runner &run, long value) override;
        Sink *kick(Runner &run) override;
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
        const Step *calling(Runner &run, const Building &tag) override;
        const Step *calling(Runner &run, const Building &tag, const Any *assignValue) override;
        Sink *kick(Runner &run) override;
	};
}
