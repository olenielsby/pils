#pragma once
#include "compile.h"
namespace PILS
{
	class Ruleset
		: public PokerShort
	{
	public:
		Ruleset(const Any* rulelist, const Rule *const *rules, size_t count)
			: PokerShort(BuiltinClicheRuleset::singleton, rulelist), compiled(rules, count)
		{}
        const Ruleset *as_Ruleset() const override;
        const Step *step_(Runner &run) const override;
        bool compileBuild(CompilingBuild &compiling) const override;
        bool write(Writing &writing, WriteState state, long level, const Constant *dot) const override;
        ~Ruleset();
		class Compilation
		{
		public:
			Compilation(const Rule *const *rules, size_t count);
			void releaseFrom(Ruleset &ruleset);
			const QuickCalling *calling;
			const QuickCalling *assigning;
		private:
			size_t count;
			size_t size;
			const Cliche **cliche;
		};
		Compilation compiled;
	};
}
