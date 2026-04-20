/* This file is public domain */
#ifndef DEFINE_PILS_CHANNEL_H
#define DEFINE_PILS_CHANNEL_H
#include "sink.h"

namespace PILS
{
class Channel;
class Listener
    : public PokerTrailer
{
public:
    Listener(const Any *listener, const Channel *channel);
    friend class Channel;
    const Channel *const channel() const
    {
        assert(inner_channel);
        assert(element[1]->as_Channel() == inner_channel);
        return inner_channel;
    }
    const Any *const ear() const {return element[0];}
    const Channel *inner_channel;
    Listener *next;
private:
    Listener **previous;
    void unlink() override;
};

class Channel
    : public NodeConstantTiny
{
public:
    Channel(const Constant *&link, const BuiltinClicheChannel &cliche, const Constant *value)
        : NodeConstantTiny(link, cliche, value), listening(nullptr)
    {}
    const Channel *as_Channel() const override;
private:
    friend class Listener;
    const Step *calling(Runner &run, const Constant &call) const override;
    const Step *calling(Runner &run, const Integer &call) const override;
    const Step *calling(Runner &run, const ListConstant &call) const override;
    const Step *calling(Runner &run, const NodeConstant &call) const override;
    const Step *calling(Runner &run, const Empty &call) const override;
    const Step *calling(Runner &run, const ListExpress &call) const override;
    const Step *calling(Runner &run, const NodeExpress &call) const override;
    const Step *calling(Runner &run, const Any &call, const Any *assignValue) const override;
    mutable Listener *listening;
};

	template <typename T> class SinkChanneling : public Sink
	{
	public:
		SinkChanneling(Listener *listener, const Any &oldWho, const T &call)
			: listener(listener), oldWho(oldWho), call(call)
		{}
		const Step *step_(Runner &run) const
		{
			run.calling.who = listener;
            return listener->ear()->calling(run, call);
		}
		const Step *called(Runner &run, const T &call)
		{
			{
                Mutex::Lock lock(Mutex::singleMutex);
				for (Listener *next = listener->next; next; next = next->next)
				{
					if (next->duplicateReferenceNoChildren())
					{
						listener->releaseReferenceInsideLock();
						listener = next;
						return this;
					}
				}
			}
			return (run.sink = kick(run))->called(run, call);
		}
		Sink *kick(Runner &run)
		{
			listener->release();
			run.calling.who = &oldWho;
			return this + 1;
		}
		const Step *pass(Runner &run, const Any *thing)
		{
			run.sink = kick(run);
			return thing->passCounted(run);
		}
		const Step *tailStep(Runner &run, const Any *thing, const Any *where_)
		{
			return (run.sink = kick(run))->tailStep(run, thing, where_);
		}
		const Step *tailStep(Runner &run, const Any *thing)
		{
			return (run.sink = kick(run))->tailStep(run, thing);
		}
		const Step *error(Runner &run, const Any *error, const Express *what, const Any *who)
		{
			oldWho.retain();
			who->release();
			return (run.sink = kick(run))->error(run, error, what, &oldWho);
		}
		const Step *miss(Runner &run)
		{
			Sink &next = this[1];
			return next.miss(run);
		}
	private:
		Listener *listener;
		const Any &oldWho;
		const T &call;
	};

	class SinkChannelingAssign
		: public Sink
	{
	public:
		SinkChannelingAssign(Listener *listener, const Any &oldWho, const Any &call, const Any &assignValue)
			: listener(listener), oldWho(oldWho), call(call), assignValue(assignValue)
		{}
		Sink *kick(Runner &run)
		{
			listener->release();
			run.calling.who = &oldWho;
			return this + 1;
		}
		const Step *step_(Runner &run) const
		{
			run.calling.who = listener;
            return listener->ear()->calling(run, call, &assignValue);
		}
		const Step *called(Runner &run, const Any &call, const Any *assignValue)
		{
			{
                Mutex::Lock lock(Mutex::singleMutex);
				for (Listener *next = listener->next; next; next = next->next)
				{
					if (next->duplicateReferenceNoChildren())
					{
						listener->releaseReferenceInsideLock();
						listener = next;
						return this;
					}
				}
			}
			return (run.sink = kick(run))->called(run, call, assignValue);
		}
		const Step *pass(Runner &run, const Any *thing)
		{
			run.sink = kick(run);
			return thing->passCounted(run);
		}
		const Step *tailStep(Runner &run, const Any *thing, const Any *where_)
		{
			return (run.sink = kick(run))->tailStep(run, thing, where_);
		}
		const Step *tailStep(Runner &run, const Any *thing)
		{
			return (run.sink = kick(run))->tailStep(run, thing);
		}
		const Step *error(Runner &run, const Any *error, const Express *what, const Any *who)
		{
			return (run.sink = kick(run))->error(run, error, what, who);
		}
		const Step *miss(Runner &run)
		{
			Sink &next = this[1];
			return next.miss(run);
		}
	private:
		Listener *listener;
		const Any &oldWho;
		const Any &call;
		const Any &assignValue;
	};

	class SinkListen
		: public Sink
	{
	public:
		SinkListen(const WhoUntypedOperation &what, const Any *ear)
			: what(what), ear(ear)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const NodeConstantShort *node);
		const Step *pass(Runner &run, const Any *thing);
	private:
		const WhoUntypedOperation &what;
		const Any *ear;
	};
}
#endif
