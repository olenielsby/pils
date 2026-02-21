/* This file is public domain */
#ifndef DEFINE_PILS_ESCAPE_H
#define DEFINE_PILS_ESCAPE_H

#include "compile.h"
namespace PILS
{
	class Escape
		: public NodeExpressTiny
	{
	public:
		Escape(const Any *value)
			: NodeExpressTiny(EscapeCliche::singleton, value)
		{}
		const Step *step_(Runner &run) const;
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const void *compilePatternIndex() const;
		void compilePattern(Compiling &compiling) const;
		bool compileBuild(CompilingBuild &compiling) const;
		bool write (Writing &writing, WriteState state, long level, const Constant *dot) const;
	};

	class EscapeNodeConstantShort
		: public Escape
	{
	public:
		EscapeNodeConstantShort(const NodeConstantShort *value)
			: Escape(value)
		{}
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		void compileNodecheckPattern(Compiling &compiling) const;
	};

	class EscapeNodeConstantLong
		: public Escape
	{
	public:
		EscapeNodeConstantLong(const NodeConstantLong *value)
			: Escape(value)
		{}
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		void compileNodecheckPattern(Compiling &compiling) const;
	};

	class EscapeNodeConstantTrailer
		: public EscapeNodeConstantLong
	{
	public:
		EscapeNodeConstantTrailer(const NodeConstantLong *value)
			: EscapeNodeConstantLong(value)
		{}
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
	};

	class EscapeNodeExpressShort
		: public Escape
	{
	public:
		EscapeNodeExpressShort(const NodeExpressShort *value)
			: Escape(value)
		{}
		const Step *step_(Runner &run) const;
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		void compilePattern(Compiling &compiling) const;
		void compileNodecheckPattern(Compiling &compiling) const;
		bool compileBuild(CompilingBuild &compiling) const;
	};

	class EscapeNodeExpressLong
		: public Escape
	{
	public:
		EscapeNodeExpressLong(const NodeExpressLong *value)
			: Escape(value)
		{}
		const Step *step_(Runner &run) const;
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		void compilePattern(Compiling &compiling) const;
		void compileNodecheckPattern(Compiling &compiling) const;
		bool compileBuild(CompilingBuild &compiling) const;
	};

	class EscapeNodeExpressTrailer
		: public EscapeNodeExpressLong
	{
	public:
		EscapeNodeExpressTrailer(const NodeExpressLong *value)
			: EscapeNodeExpressLong(value)
		{}
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
	};
}
#endif
