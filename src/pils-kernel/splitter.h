/* This file is public domain */
#ifndef DEFINE_PILS_SPLITTER_H
#define DEFINE_PILS_SPLITTER_H
#include "pipe.h"
namespace PILS
{
	class ClicheSplitter
		: public ClicheTrailer
	{
//		using ClicheTrailer::node;
	public:
		ClicheSplitter(const HashedConstant *&link, const Constant *h, const Constant *const *a, size_t c)
			: ClicheTrailer(link, h, a, c)
		{}
		const NodeConstantLong *newNodeConstant(const HashedConstant *&link, const Constant *const *value) const;
	};

	class Splitter
		: public NodeConstantTrailer
	{
	public:
		Splitter(const HashedConstant *&link, const ClicheSplitter &cliche, const Constant *const *element)
			: NodeConstantTrailer(link, cliche, element)
		{}
		const CallWho *callWho(const Any *who) const;
	};

	class WhoSplitter
		: public CallWho
	{
	public:
		WhoSplitter(const Splitter *call, const Any *who)
			: CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class SinkWhoSplitter
		: public SinkWho
	{
	public:
		SinkWhoSplitter(const WhoSplitter &what, const Any *argument)
			: SinkWho(what, argument)
		{}
		const Step *pass(Runner &run, const PilsString *value);
		const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count);
	};

	class PipesourceSplitter
		: public Pipesource
	{
	public:
		PipesourceSplitter(const Splitter *splitter, const Any *anchor, const PILS_CHAR *at, const PILS_CHAR *end)
			: splitter(splitter), anchor(anchor), at(at), end(end), last(&Builtin::name.dollar)
		{}
		Sink *kick(Runner &run);
		const Step *step_(Runner &run) const;
		const Splitter *splitter;
	private:
		const Any *const anchor;
    public:
		const PILS_CHAR *at;
		const PILS_CHAR *end;
		const Constant *last;
		Pipe &pipe() {return (Pipe&)(this [1]);}
	};

	class Splitsink
		: public Sink
	{
	public:
		Sink *kick(Runner &run);
		virtual const Step *back(Runner &run) = 0;
		virtual const Step *done(Runner &run, const PILS_CHAR *at) = 0;
		const Step *pass(Runner &run, const Cliche &name);
		const Step *pass(Runner &run, const Integer &name);
		const Step *pass(Runner &run, const PilsString &value);
		const Step *pass(Runner &run, const ListConstant &value);
		const Step *pass(Runner &run, const NodeConstantShort &value);
		const Step *pass(Runner &run, const Any *value);
	protected:
		Splitsink(PipesourceSplitter &splitting, const PILS_CHAR *at)
			: splitting(splitting), at(at)
		{}
		PipesourceSplitter &splitting;
		const PILS_CHAR *at;
	};

	class SplitsinkOptions
		: public Splitsink
	{
	public:
		SplitsinkOptions(PipesourceSplitter &splitting, const PILS_CHAR *at, const Constant *const &options)
			: Splitsink(splitting, at), optionAt(&options)
		{
			const Integer *count;
			if (options->isList((const Any *const *&)optionAt, count))
				optionEnd = optionAt + count->value;
			else optionEnd = optionAt + 1;
		}
		SplitsinkOptions(PipesourceSplitter &splitting, const PILS_CHAR *at, const ListConstant &options)
			: Splitsink(splitting, at), optionAt(&options.element[0]), optionEnd(&options.element[options.count->value])
		{}
		const Step *back(Runner &run);
		const Step *done(Runner &run, const PILS_CHAR *at);
	protected:
		SplitsinkOptions(PipesourceSplitter &splitting, const PILS_CHAR *at, const Constant *const *optionAt, const Constant *const *optionEnd)
			: Splitsink(splitting, at), optionAt(optionAt), optionEnd(optionEnd)
		{}
		const Constant *const *optionAt;
		const Constant *const *optionEnd;
	};

	class SplitsinkRoot
		: public SplitsinkOptions
	{
	public:
		SplitsinkRoot(PipesourceSplitter &splitting)
			: SplitsinkOptions(splitting, splitting.at, splitting.splitter->element[0])
		{}
		const Step *back(Runner &run);
		const Step *done(Runner &run, const PILS_CHAR *at);
	};

	class SplitsinkRepeat
		: public SplitsinkOptions
	{
	public:
		SplitsinkRepeat(PipesourceSplitter &splitting, const PILS_CHAR *at, const Constant *const &options, bool ok)
			: SplitsinkOptions(splitting, at, options), ok(ok)
		{
			optionBegin = optionAt;
		}
		const Step *back(Runner &run);
		const Step *done(Runner &run, const PILS_CHAR *at);
	protected:
		bool ok;
		const Constant *const *optionBegin;
	};

	class SplitsinkFind
		: public SplitsinkRepeat
	{
	public:
		SplitsinkFind(PipesourceSplitter &splitting, const PILS_CHAR *at, const Constant *const &options, bool ok)
			: SplitsinkRepeat(splitting, at, options, ok)
		{}
		const Step *back(Runner &run);
		const Step *done(Runner &run, const PILS_CHAR *at);
	};

	class SplitsinkCompound
		: public SplitsinkOptions
	{
	public:
		using SplitsinkOptions::pass;
		SplitsinkCompound(PipesourceSplitter &splitting, const PILS_CHAR *at, const ListConstant &compound)
			: SplitsinkOptions(splitting, at, &compound.element[0], &compound.element[compound.count->value])
		{}
		const Step *back(Runner &run);
		const Step *done(Runner &run, const PILS_CHAR *at);
		const Step *pass(Runner &run, const ListConstant &value);
	};

	class SplitsinkNot
		: public SplitsinkOptions
	{
	public:
		SplitsinkNot(PipesourceSplitter &splitting, const PILS_CHAR *at, const Constant *const &options)
			: SplitsinkOptions(splitting, at, options)
		{}
		const Step *back(Runner &run);
		const Step *done(Runner &run, const PILS_CHAR *at);
	};

	class SplitsinkLast
		: public SplitsinkOptions
	{
	public:
		SplitsinkLast(PipesourceSplitter &splitting, const PILS_CHAR *at, const Constant *const &options)
			: SplitsinkOptions(splitting, at, options)
		{}
		const Step *pass(Runner &run, const Cliche &name);
		const Step *pass(Runner &run, const PilsString &value);
		const Step *pass(Runner &run, const ListConstant &value);
		const Step *pass(Runner &run, const NodeConstantShort &value);
	};
}
#endif
