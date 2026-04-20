/* This file is public domain */
#pragma once
#include "pipe.h"
namespace PILS
{
	class PipesourceListBuilderBegin
		: public Pipesource
	{
	public:
		PipesourceListBuilderBegin(const Any &thing)
			: thing(thing)
		{}
        const Step *step_(Runner &run) const override;
        Sink *kick(Runner &run) override;
	private:
		const Any &thing;
	};

	class PipesourceHold
		: public Pipesource
	{
	public:
		PipesourceHold(const Any *hold)
			: hold(hold)
		{}
        const Step *step_ (Runner &run) const override;
        Sink *kick(Runner &run) override;
	private:
		const Any *hold;
	};

	class SinkExit
		: public Sink
	{
	public:
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
	};

	class BuilderShort
		: public PokerShort
	{
	public:
		BuilderShort(const PokerClicheShort &cliche, const Any* value)
			: PokerShort(cliche, value)
		{}
        const Step *step_(Runner &run) const override;
	};

	class BuilderTrailer
		: public PokerTrailer
	{
	public:
		BuilderTrailer(const BuiltinClicheBuilderTrailer &cliche, const Any *tail, const Constant *tag)
			: PokerTrailer(cliche, tail, tag)
		{
			const Constant *kind = cliche.attributes[1];
			kind->retain();
			const ClicheTiny *nameCliche = kind->clichefy();
			name = (const NodeConstantTiny *)nameCliche->nodeConstant(tag);
			tag->retain();
			nameCliche->release();
		}
        void unlink() override;
        const Step *step_(Runner &run) const override;
	private:
		const Any *dummy;
		const NodeConstantTiny *name;
	};
}
