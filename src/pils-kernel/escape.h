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
        const Step *step_(Runner &run) const override;
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        const void *compilePatternIndex() const override;
        void compilePattern(Compiling &compiling) const override;
        bool compileBuild(CompilingBuild &compiling) const override;
        bool write (Writing &writing, WriteState state, long level, const Constant *dot) const override;
	};

	class EscapeNodeConstantShort
		: public Escape
	{
	public:
		EscapeNodeConstantShort(const NodeConstantShort *value)
			: Escape(value)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        void compileNodecheckPattern(Compiling &compiling) const override;
	};

	class EscapeNodeConstantLong
		: public Escape
	{
	public:
		EscapeNodeConstantLong(const NodeConstantLong *value)
			: Escape(value)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        void compileNodecheckPattern(Compiling &compiling) const override;
	};

	class EscapeNodeConstantTrailer
		: public EscapeNodeConstantLong
	{
	public:
		EscapeNodeConstantTrailer(const NodeConstantLong *value)
			: EscapeNodeConstantLong(value)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
	};

	class EscapeNodeExpressShort
		: public Escape
	{
	public:
		EscapeNodeExpressShort(const NodeExpressShort *value)
			: Escape(value)
		{}
        const Step *step_(Runner &run) const override;
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        void compilePattern(Compiling &compiling) const override;
        void compileNodecheckPattern(Compiling &compiling) const override;
        bool compileBuild(CompilingBuild &compiling) const override;
	};

	class EscapeNodeExpressLong
		: public Escape
	{
	public:
		EscapeNodeExpressLong(const NodeExpressLong *value)
			: Escape(value)
		{}
        const Step *step_(Runner &run) const override;
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        void compilePattern(Compiling &compiling) const override;
        void compileNodecheckPattern(Compiling &compiling) const override;
        bool compileBuild(CompilingBuild &compiling) const override;
	};

	class EscapeNodeExpressTrailer
		: public EscapeNodeExpressLong
	{
	public:
		EscapeNodeExpressTrailer(const NodeExpressLong *value)
			: EscapeNodeExpressLong(value)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
	};
}
#endif
