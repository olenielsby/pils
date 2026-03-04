/* This file is public domain */
#ifndef _PILSPLUG__PLUGHOST_H_
#define _PILSPLUG__PLUGHOST_H_

#include "pilsplug.h"
#include "../pils-kernel/sink.h"

namespace PILS
{
	class PlugObject;

	class PlugTools
	{
	public:
		static void *loadPlugin(const ReallySpecial &cracker, const PilsString &name);
		static void *getProcAddress(void *handle, const char *name);
		static const PlugObject *as_PlugObject(const Any *thing);
	};

	class PlugMixinSpecial
	{
	public:
		virtual const Special *as_Special() const = 0;
	};

	class PlugObject : public PlugMixinSpecial
	{
	protected:
		friend class PlugMethodInvoker;
		PlugObject(pilsplug::interface::Object *const object, const NodeConstant *types, size_t type, pilsplug::Plug &plug, const Special *handle)
			: object(object), types(types), type(type), plug(plug), handle(handle)
		{}
		~PlugObject();
        const Any *specialCalling(Runner &run, const Constant &name, const Any &arg) const;
        const Any *specialCalling(Runner &run, const Number &call) const;
        const Any *specialCalling(Runner &run, const PilsString &call) const;

		pilsplug::interface::Object *const object;
		const NodeConstant *const types;
		const size_t type;
		pilsplug::Plug &plug;
		const Special *const handle;
	private:
        const Any *dispatch(Runner &run, int methodIndex, const Constant *returnTypeSpecifier, const Constant *parametersSpecifier, const Any *argument) const;
	};

	class PlugObjectLookup : public SpecialLookup
	{
	public:
		PlugObjectLookup(pilsplug::interface::Object *object, const NodeConstant &types, size_t type, pilsplug::Plug &plug, const Special &handle)
			: object(object), types(types), type(type), plug(plug), handle(handle)
		{}
        const ReallySpecial *newSpecial(const HashedConstant *&link) override;
        void unduplicate() override;
        bool compare(const ReallySpecial &other) const override;
        size_t hash() const override;
	private:
		friend class PlugObjectSpecial;
		pilsplug::interface::Object *const object;
		const NodeConstant &types;
		const size_t type;
		pilsplug::Plug &plug;
		const Special &handle;
	};

	class PlugLibrary : public PlugMixinSpecial
	{
	public:
		static const Special *get(void *handle);
	protected:
		PlugLibrary(void *handle) : handle(handle) {}
		~PlugLibrary();
		void *handle;
	};

	class PlugLibraryLookup : public SpecialLookup
	{
	public:
		PlugLibraryLookup(void *handle) : handle(handle) {}
        const ReallySpecial *newSpecial(const HashedConstant *&link) override;
        void unduplicate() override;
        bool compare(const ReallySpecial &other) const override;
        size_t hash() const override;
		void *handle;
	};

	class PlugCompiling;

	class PlugCompilable
	{
	public:
        virtual bool compile(PlugCompiling &state) const;
		static const PlugCompilable *cast(const Any *thing);
	};

	class PlugName
		: public ClicheShort, public PlugCompilable
	{
	protected:
		PlugName(const PILS_CHAR *name)
			: ClicheShort(namespace_, PilsString::get(name))
		{}
	public:
        bool recognize(Recognizer &recognizer) const override;
        bool compile(PlugCompiling &state) const override;
	private:
		static const PilsString *const namespace_;
	};

	class PlugNamePlug : public PlugName
	{
	private:
		PlugNamePlug(const PILS_CHAR *name) : PlugName(name) {}
		friend class PlugCliche;
		friend class PlugTypeCliche;
		static const PlugNamePlug singleton;
	};

	class PlugTypeCliche : public ClicheTiny
	{
	public:
        const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const override;
	private:
		PlugTypeCliche() : ClicheTiny(&PlugNamePlug::singleton) {}
		static const PlugTypeCliche singleton;
	};

	class PlugCliche : public ClicheTrailer
	{
	public:
        const NodeConstantLong *newNodeConstant(const HashedConstant *&link, const Constant *const *value) const override;
	private:
		PlugCliche() : ClicheTrailer(&PlugNamePlug::singleton, &Empty::singleton, &PlugNamePlug::singleton) {}
		static const PlugCliche singleton;
		const void *dummy;
	};

	class PlugNameInt : public PlugName
	{
	public:
        bool compile(PlugCompiling &state) const override;
	private:
		PlugNameInt(const PILS_CHAR *name) : PlugName(name) {}
		static const PlugNameInt singleton;
	};

	class PlugNameDouble : public PlugName
	{
	public:
        bool compile(PlugCompiling &state) const override;
	private:
		PlugNameDouble(const PILS_CHAR *name) : PlugName(name) {}
		static const PlugNameDouble singleton;
	};

	class PlugNameVoid : public PlugName
	{
	public:
        bool compile(PlugCompiling &state) const override;
	private:
		PlugNameVoid(const PILS_CHAR *name) : PlugName(name) {}
		static const PlugNameVoid singleton;
	};

	class PlugNameString : public PlugName
	{
	public:
        bool compile(PlugCompiling &state) const override;
	private:
		PlugNameString(const PILS_CHAR *name) : PlugName(name) {}
		static const PlugNameString singleton;
	};

	class PlugNameBlob : public PlugName
	{
	public:
        bool compile(PlugCompiling &state) const override;
	private:
		PlugNameBlob(const PILS_CHAR *name) : PlugName(name) {}
		static const PlugNameBlob singleton;
	};

	class PlugCompiling
	{
	public:
		virtual bool compile(const PlugNameInt &spec);
		virtual bool compile(const PlugNameDouble &spec);
		virtual bool compile(const PlugNameVoid &spec);
		virtual bool compile(const PlugNameString &spec);
		virtual bool compile(const PlugNameBlob &spec);
	};
}
#endif
