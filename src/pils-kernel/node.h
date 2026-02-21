/* This file is public domain */
#ifndef DEFINE_PILS_NODE_H
#define DEFINE_PILS_NODE_H
#include "pipe.h"
namespace PILS
{
	class WhoPropertyCliche
		: public CallWho
	{
	public:
		WhoPropertyCliche(const TypecheckPropertyCliche *call, const Any *who)
			:  CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class SinkPropertyCliche
		: public SinkProperty
	{
	public:
		SinkPropertyCliche(const WhoPropertyCliche &what)
			: SinkProperty(what)
		{}
		const Step *pass(Runner &run, const NodeConstantShort &node);
		const Step *pass(Runner &run, const NodeConstantLong &node);
		const Step *pass(Runner &run, const NodeExpressShort &node);
		const Step *pass(Runner &run, const NodeExpressLong &node);
		const Step *pass(Runner &run, const NodeConstantShort *node);
		const Step *pass(Runner &run, const NodeConstantLong *node);
		const Step *pass(Runner &run, const NodeExpressShort *node);
		const Step *pass(Runner &run, const NodeExpressLong *node);
	};

	class WhoPropertyHead
		: public CallWho
	{
	public:
		WhoPropertyHead(const PropertyHead *call, const Any *who)
			:  CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class SinkPropertyHead
		: public SinkProperty
	{
	public:
		SinkPropertyHead(const WhoPropertyHead &what)
			: SinkProperty(what)
		{}
		const Step *pass(Runner &run, const Cliche &cliche);
		const Step *pass(Runner &run, const NodeConstantShort &node);
		const Step *pass(Runner &run, const NodeConstantLong &node);
		const Step *pass(Runner &run, const NodeExpressShort &node);
		const Step *pass(Runner &run, const NodeExpressLong &node);
		const Step *pass(Runner &run, const Cliche *cliche);
		const Step *pass(Runner &run, const NodeConstantShort *node);
		const Step *pass(Runner &run, const NodeConstantLong *node);
		const Step *pass(Runner &run, const NodeExpressShort *node);
		const Step *pass(Runner &run, const NodeExpressLong *node);
	};

	class WhoPropertyLegs
		: public CallWho
	{
	public:
		WhoPropertyLegs(const TypecheckPropertyLegs *call, const Any *who)
			:  CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
	};

	class SinkPropertyLegs
		: public SinkProperty
	{
	public:
		SinkPropertyLegs(const WhoPropertyLegs &what)
			: SinkProperty(what)
		{}
		const Step *pass(Runner &run, const Cliche *cliche);
	};

	class SinkHeadset
		: public Sink
	{
	public:
		SinkHeadset(const WhoUntypedOperation &what, const Constant *name)
			: what(what), name(name)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Cliche *cliche);
		const Step *pass(Runner &run, const NodeConstantShort *node);
		const Step *pass(Runner &run, const NodeConstantLong *node);
		const Step *pass(Runner &run, const NodeExpressShort *node);
		const Step *pass(Runner &run, const NodeExpressLong *node);
		const Step *pass(Runner &run, const Any *thing);
	private:
		const WhoUntypedOperation &what;
		const Constant *name;
	};

	class PipesourceLegs
		: public Pipesource
	{
	public:
		PipesourceLegs(const WhoUntypedOperation &what, const Any *who, const NodeConstant *node)
			: what(what),
			  who(who),
			  node(node),
			  name(node->cliche->attributes),
			  nameEnd(&node->cliche->attributes[node->cliche->count]),
			  value((const Any *const *)node->element)
		{}
		PipesourceLegs(const WhoUntypedOperation &what, const Any *who, const NodeExpress *node)
			: what(what),
			  who(who),
			  node(node),
			  name(node->cliche->attributes),
			  nameEnd(&node->cliche->attributes[node->cliche->count]),
			  value(node->element)
		{}
		Sink *kick(Runner &run);
		const Step *step_(Runner &run) const;
	private:
		const WhoUntypedOperation &what;
		const Any *who;
		const Any *node;
		const Constant *const *name;
		const Constant *const *const nameEnd;
		const Any *const *value;
	};

	class PipingLegs
		: public Piping
	{
	public:
		PipingLegs(Pipe &pipe)
			: Piping(pipe)
		{}
		const Step *called(Runner &run, const Any &call, const Any *assignValue);
	};

	class SinkBindMerge
		: public Sink
	{
	public:
		SinkBindMerge(const WhoUntypedOperation &what, const Any *operand)
			: what(what), operand(operand)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const NodeExpressLong *node);
		const Step *pass(Runner &run, const Any *value);
	protected:
		const WhoUntypedOperation &what;
		const Any *operand;
	};

	class SinkMerge
		: public SinkBindMerge
	{
	public:
		SinkMerge(const WhoUntypedOperation &what, const Any *operand)
			: SinkBindMerge(what, operand)
		{}
		const Step *pass(Runner &run, const Cliche *cliche);
		const Step *pass(Runner &run, const NodeConstantShort *node);
		const Step *pass(Runner &run, const NodeConstantLong *node);
		const Step *pass(Runner &run, const NodeExpressShort *node);
		const Step *pass(Runner &run, const NodeExpressLong *node);
		const Step *pass(Runner &run, const ListConstant *node);
		const Step *pass(Runner &run, const Any *value);
	private:
		const Step *passNode(Runner &run, const Any *node, const Cliche &cliche, const Any *const *element);
		class Round
		{
		protected:
			Round(const Cliche *a, const Cliche *b)
				: aAttribute(a->attributes),
				  aEnd(&a->attributes[a->count]),
				  bAttribute(b->attributes),
				  bEnd(&b->attributes[b->count])
			{}
			void round();
			const Constant *const *aAttribute;
			const Constant *const *const aEnd;
			const Constant *const *bAttribute;
			const Constant *const *const bEnd;
			virtual void a() = 0;
			virtual void b() = 0;
			virtual void ab() = 0;
		};

		class CountRound
			: public Round
		{
		public:
			size_t count;
			CountRound(const Cliche *a, const Cliche *b)
				: Round(a, b), count(0)
			{
				round();
			}
		protected:
			void a();
			void b();
			void ab();
		};

		class NameRound
			: public Round
		{
		public:
			NameRound(const Cliche *a, const Cliche *b, const Constant **destination)
				: Round(a, b), destination(destination)
			{
				round();
			}
		protected:
			void a();
			void b();
			void ab();
		private:
			const Constant **destination;
		};

		class ValueRound
			: public Round
		{
		public:
			ValueRound(const Cliche *a, const Cliche *b, const Any **destination, const Any *const *aSource, const Any *const *bSource)
				: Round(a, b), destination(destination), aSource(aSource), bSource(bSource)
			{
				round();
			}
		protected:
			void a();
			void b();
			void ab();
		private:
			const Any **destination;
			const Any *const *aSource;
			const Any *const *bSource;
		};
	};

	class SinkUntypedConstantOperation
		: public Sink
	{
	public:
		SinkUntypedConstantOperation(const WhoUntypedOperation &what, const Constant *operand)
			: what(what), operand(operand)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
	private:
		const WhoUntypedOperation &what;
	protected:
		const Constant *operand;
	};

	class SinkWithout
		: public SinkUntypedConstantOperation
	{
		using SinkUntypedConstantOperation::pass;
	public:
		SinkWithout(const WhoUntypedOperation &what, const Constant *operand)
			: SinkUntypedConstantOperation(what, operand)
		{}
		const Step *pass(Runner &run, const Cliche *cliche);
		const Step *pass(Runner &run, const NodeConstantShort *node);
		const Step *pass(Runner &run, const NodeConstantLong *node);
		const Step *pass(Runner &run, const NodeExpressShort *node);
		const Step *pass(Runner &run, const NodeExpressLong *node);
	private:
		const Step *passNode(Runner &run, const Any *node, const Cliche &cliche, const Any *const *element);
	};

	class SinkMakeCliche
		: public SinkUntypedConstantOperation
	{
		using SinkUntypedConstantOperation::pass;
	public:
		SinkMakeCliche(const WhoUntypedOperation &what, const Constant *operand)
			: SinkUntypedConstantOperation(what, operand)
		{}
		const Step *pass(Runner &run, const ListConstant *value);
	};

	class SinkMakeName
		: public SinkUntypedConstantOperation
	{
	public:
		SinkMakeName(const WhoUntypedOperation &what, const Constant *operand)
			: SinkUntypedConstantOperation(what, operand)
		{}
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const Duration *value);
		const Step *pass(Runner &run, const PilsString *value);
		const Step *pass(Runner &run, const Cliche *value);
		const Step *pass(Runner &run, const ListConstant *value);
		const Step *pass(Runner &run, const NodeConstantLong *value);
		const Step *pass(Runner &run, const NodeConstantShort *value);
		const Step *pass(Runner &run, const Special *value);
	private:
		const Step *passConstant(Runner &run, const Constant *head);
	};
}
#endif
