/* This file is public domain */
#ifndef DEFINE_PILS_CONCATENATE_H
#define DEFINE_PILS_CONCATENATE_H
#include "pipe.h"
#include "pilsstring.h"
namespace PILS
{
	class ConcatenateConstant
		: public NodeConstantTiny
	{
	public:
		ConcatenateConstant(const HashedConstant *&link, const BuiltinClicheConcatenate &cliche, const Constant *value)
			: NodeConstantTiny(link, cliche, value)
		{}
		const CallWho *callWho(const Any *who) const;
	};

	class ConcatenateExpress
		: public NodeExpressTiny
	{
	public:
		ConcatenateExpress(const BuiltinClicheConcatenate &cliche, const Express *value)
			: NodeExpressTiny(cliche, value)
		{}
		const CallWho *callWho(const Any *who) const;
	};

	class WhoConcatenateConstant
		: public CallWho
	{
	public:
		WhoConcatenateConstant(const ConcatenateConstant *call, const Any *who)
			: CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class WhoConcatenateExpress
		: public CallWho
	{
	public:
		WhoConcatenateExpress(const ConcatenateExpress *call, const Any *who)
			: CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class PipeConcatenate
		: public Pipe
	{
	public:
		PipeConcatenate(const Any &who)
			: who(&who)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
		const Step *pipeItem(Runner &run, const Any *item);
		const Step *pipeBegin(Runner &run);
		const Step *pipeEnd(Runner &run);
	private:
		const Any *who;
	};
}
#endif
