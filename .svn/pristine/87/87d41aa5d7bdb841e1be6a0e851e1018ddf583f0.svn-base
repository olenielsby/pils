/* This file is public domain */
#ifndef DEFINE_PILS_ORDER_H
#define DEFINE_PILS_ORDER_H
#include "pipe.h"
namespace PILS
{
	class PipeOrder
		: public Pipe
	{
	public:
		PipeOrder(const WhoUntypedOperation &what, const Any *keypicker)
			: what(what), keypicker(keypicker)
		{}
		const Step *pass(Runner &run, const Any *thing);
		Sink *kick(Runner &run);
		const Step *pipeItem(Runner &run, const Any *thing);
		const Step *pipeBegin(Runner &run);
		const Step *pipeEnd(Runner &run);
	private:
		typedef std::pair<const Constant*, const Any*> Pair;
		typedef std::vector<Pair> Bag;
		class Comparator
		{
		public:
			bool operator()(const Pair &p1, const Pair &p2) const;
		};
		class PipesourceSorted
			: public Pipesource
		{
		public:
			PipesourceSorted(Pipe &pipe, Bag &bag)
				: pipe(pipe), at(bag.begin()), end(bag.end())
			{}
			const Step *step_(Runner &run) const;
			Sink *kick(Runner &run);
		private:
			Pipe &pipe;
			Bag::iterator at;
			Bag::iterator end;
		};
		class SinkOrderKey
			: Sink
		{
		public:
			SinkOrderKey(Bag &bag, const Any *item)
				: bag(bag), item(item)
			{}
			Sink *kick(Runner &run);
			const Step *pass(Runner &run, const Integer *value);
			const Step *pass(Runner &run, const Float *value);
			const Step *pass(Runner &run, const Timestamp *value);
			const Step *pass(Runner &run, const Duration *value);
			const Step *pass(Runner &run, const PilsDate *value);
			const Step *pass(Runner &run, const PilsString *value);
			const Step *pass(Runner &run, const Cliche *value);
			const Step *pass(Runner &run, const ListConstant *value);
			const Step *pass(Runner &run, const NodeConstantLong *value);
			const Step *pass(Runner &run, const NodeConstantShort *value);
			const Step *pass(Runner &run, const Special *value);
			const Step *pass(Runner &run, const Any *value);
			// all constants go here
			const Step *pass(Runner &run, const Constant *value);
		private:
			Bag &bag;
			const Any *item;
		};
		const WhoUntypedOperation &what;
		const Any *keypicker;
		Bag bag;
	};
}
#endif
