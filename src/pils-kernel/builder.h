/* This file is public domain */
#ifndef DEFINE_PILS_BUILDER_H
#define DEFINE_PILS_BUILDER_H
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
		const Step *step_(Runner &run) const;
		Sink *kick(Runner &run);
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
		const Step *step_ (Runner &run) const;
		Sink *kick(Runner &run);
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
		const Step *step_(Runner &run) const;
	};

	class BuilderTrailer
		: public PokerTrailer
	{
	public:
		BuilderTrailer(const BuiltinClicheBuilderTrailer &cliche, const Any *tail, const Constant *tag)
			: PokerTrailer(cliche, tail, tag)
		{
			const Constant *kind = cliche.attributes[1];
			kind->addReference();
			const ClicheTiny *nameCliche = kind->clichefy();
			name = (const NodeConstantTiny *)nameCliche->nodeConstant(tag);
			tag->addReference();
			nameCliche->releaseReference();
		}
		size_t unlinkAndGetSize();
		const Step *step_(Runner &run) const;
	private:
		const Any *dummy;
		const NodeConstantTiny *name;
	};
}
#endif
