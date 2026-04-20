/* This file is public domain */
#ifndef _JPILS_BINDING_BASE_H_
#define _JPILS_BINDING_BASE_H_
#include "jpils-plumming.h"
#include "jpils-thread.h"
#undef Point

using namespace juce;

typedef ::juce::Image::PixelFormat PixelFormat;

namespace PILS
{
	class JuceObject;
	class JuceClassBase;
	class CallbackHelperBase;
	class JuceClass;
	class JuceMethod;
	struct JuceClasses;
	class PilsThread;

	struct TypedPtr
	{
		const JuceClassBase &class_;
		void *ptr;
		size_t hash() const;
	};

	struct TypedResult : TypedPtr
	{
		const Any *pils;
		~TypedResult()
		{
			if (pils) pils->releaseReference();
		}
	};

	class JuceClassBase
	{
	public:
		JuceClassBase(int level = 0, const JuceClass *const *const lineage = &dummyLineage)
			: level(level), lineage(lineage)
		{}
		virtual const JuceName &getName() const = 0;
		virtual void* cast(const TypedPtr &ptr) const = 0;
		virtual const JuceReference *newSpecial(const Constant *&link, TypedPtr &object, const JuceReference *owner) const;
		virtual void release(void *ptr) const = 0;
		virtual bool recognizing(const void *instance, Recognizer &recognizer) const;
		const int level;
		const JuceClass *const *const lineage;
		static const JuceClass *const dummyLineage;
	};

	class JuceStaticClass
		: public JuceClassBase
	{
	public:
		JuceStaticClass(const char *namestring);
		JuceStaticClass(const JuceName *name);
        const JuceName &getName() const  override {return name;}
        void* cast(const TypedPtr &ptr) const override;
        void release(void *ptr) const override;
	private:
		friend class JuceClass;
		const JuceName &name;
	};

	class JuceDummyClass
		: public JuceStaticClass
	{
	public:
		JuceDummyClass() : JuceStaticClass("") {}
        void* cast(const TypedPtr &ptr) const override;
		static const JuceDummyClass singleton;
	};

	class JuceClass
		: public JuceClassBase, JuceSpecialConverter
	{
	public:
		struct Mixin;
		JuceClass(const char *name, int level, const JuceClass *const *lineage, void (*releaseThunk)(void *), int mixinCount, const Mixin *mixinOf)
			: JuceClassBase(level, lineage), staticClass(name), releaseThunk(releaseThunk), mixinCount(mixinCount), mixinOf(mixinOf)
		{
			(Converter *&)(getName().typecheck) = this;
		}
		JuceClass(const JuceName *name, int level, const JuceClass *const *lineage, void (*releaseThunk)(void *), int mixinCount, const Mixin *mixinOf)
			: JuceClassBase(level, lineage), staticClass(name), releaseThunk(releaseThunk), mixinCount(mixinCount), mixinOf(mixinOf)
		{
			(Converter *&)(getName().typecheck) = this;
		}
        const JuceName &getName() const  override {return staticClass.name;}
        void release(void *ptr) const override;
        void* cast(const TypedPtr &ptr) const override;
		virtual const JuceReference *wrap(void *object, CallbackHelperBase *helper) const;
		virtual const Constant *ownedReference(void *object) const;
		JuceStaticClass staticClass;
		static const JuceClasses classes;
		static const JuceClass *const lineages[];
		struct Mixin
		{
			Mixin(const JuceClass &of, size_t offset)
				: of(of), offset(offset)
			{}
			const JuceClass &of;
			const size_t offset;
		};
		static const Mixin mixins[];
        const Constant *reference(const void *) const;
        bool converting(const JuceReference &argument) override; // for typechecking
	private:
		void (* const releaseThunk)(void *);
		const int mixinCount;
		const Mixin *const mixinOf;
	};

	class JuceReferenceCountedClass
		: public JuceClass
	{
	public:
		JuceReferenceCountedClass(const char *name, int level, const JuceClass *const *lineage, void (* releaseThunk)(void *), int mixinCount, const JuceClass::Mixin *mixinOf)
			: JuceClass(name, level, lineage, releaseThunk, mixinCount, mixinOf)
		{}
        const JuceReference *newSpecial(const Constant *&link, TypedPtr &object, const JuceReference *owner) const override;
        const JuceReference *wrap(void *object, CallbackHelperBase *helper) const override;
	};

	class JuceComponentClass
		: public JuceClass
	{
	public:
		JuceComponentClass(const char *name, int level, const JuceClass *const *lineage, void (* releaseThunk)(void *), int mixinCount, const JuceClass::Mixin *mixinOf)
			: JuceClass(name, level, lineage, releaseThunk, mixinCount, mixinOf)
		{}
        const JuceReference *wrap(void *object, CallbackHelperBase *helper) const override;
        const Constant *ownedReference(void *object) const override;
	};

	class JuceImageClass
		: public JuceClass
	{
	public:
		JuceImageClass(const char *name, int level, const JuceClass *const *lineage, void (* releaseThunk)(void *), int mixinCount, const JuceClass::Mixin *mixinOf)
			: JuceClass(name, level, lineage, releaseThunk, mixinCount, mixinOf)
		{}
        bool recognizing(const void *instance, Recognizer &recognizer) const override;
	};

	class JuceDrawableClass
		: public JuceClass
	{
	public:
		JuceDrawableClass(const char *name, int level, const JuceClass *const *lineage, void (* releaseThunk)(void *), int mixinCount, const JuceClass::Mixin *mixinOf)
			: JuceClass(name, level, lineage, releaseThunk, mixinCount, mixinOf)
		{}
        bool recognizing(const void *instance, Recognizer &recognizer) const override;
	};

	class JuceColourClass
		: public JuceClass
	{
	public:
		JuceColourClass(const char *name, int level, const JuceClass *const *lineage, void (* releaseThunk)(void *), int mixinCount, const JuceClass::Mixin *mixinOf)
			: JuceClass(name, level, lineage, releaseThunk, mixinCount, mixinOf)
		{}
        bool recognizing(const void *instance, Recognizer &recognizer) const override;
	};

	class JuceReference
		: public ReallySpecial, public TypedPtr
	{
	public:
		virtual void alert();
		const JuceReference *const owner;
	protected:
		friend class JuceClassBase;
		friend class JuceStaticClass;
		JuceReference(const Constant *&link, TypedPtr &typedPtr, const JuceReference *const owner)
			: ReallySpecial(link), TypedPtr(typedPtr), owner(owner)
		{}
		JuceReference(TypedPtr &typedPtr)
			: TypedPtr(typedPtr), owner(nullptr)
		{}
        const Any *specialCalling(Runner &run, const JuceName &method, const Any &arg) const override;
        const Any *specialCalling(Runner &run, const JuceName &method) const override;
        bool specialComparing(const JuceLookup &lookup) const override;
        bool converting(JuceSpecialConverter &converter) const override;
        bool recognize(Recognizer &recognizer) const override;
        juce::Graphics *as_Graphics() const override;
		friend class CallbackHelper;
		friend class CallbackHelperBase;
	private:
        size_t unlinkAndGetSize() override;
        void write(Writing &writing) const override;
	};

	class JuceOwnedReference
		: public JuceReference
	{
	public:
		JuceOwnedReference(const Constant *&link, TypedPtr &typedPtr)
			: JuceReference(link, typedPtr, nullptr)
		{}
	private:
        size_t unlinkAndGetSize() override;
        void write(Writing &writing) const override;
	};

	class JuceObject
		: public JuceReference
	{
	public:
		JuceObject(const Constant *&link, TypedPtr &typedPtr, CallbackHelperBase *helper);
        void alert() override;
		virtual void deleted();
	protected:
		CallbackHelperBase *const helper;
	private:
        size_t unlinkAndGetSize() override;
        void write(Writing &writing) const override;
	};

	class JuceComponent
		: public JuceObject, PassingMindMap
	{
	public:
		JuceComponent(const Constant *&link, TypedPtr &typedPtr, CallbackHelperBase *helper);
        void alert() override;
        void deleted() override;
        const Any *mindError() const override;
        const Step *calling(Runner &run, const Constant &call) const override;
        const Any *specialCalling(Runner &run, const Strap &call) const override;
        bool isMultipleReferenced() const override;
		static volatile long desktopComponentCount;
	private:
        size_t unlinkAndGetSize() override;
		mutable Strap::Sticker strapSticker;
		bool desktop;
	};

	class JuceLookup
		: public SpecialLookup
	{
		friend class JuceClass;
		friend class JuceReference;
		JuceLookup(TypedPtr &object)
			: object(object), owner(nullptr)
		{}
        const ReallySpecial *newSpecial(const Constant *&link) override;
        bool compare(const ReallySpecial &special) const override;
        void unduplicate() override;
        size_t hash() const override;
		TypedPtr &object;
		mutable const JuceReference *owner;
	};

	class JuceClassConverter
		: public JuceSpecialConverter
	{
	public:
		JuceClassConverter(const JuceClass &toClass, bool nullable) : toClass(toClass), nullable(nullable) {}
        bool converting(const JuceReference &argument) override;
        bool convert(const Cliche &value) override;
		void *value;
	private:
		const JuceClass &toClass;
		bool nullable;
	};

	class ArgumentReader
	{
	public:
		bool done() {return at == end;}
	protected:
		ArgumentReader(const Any *argument)
			: argument(argument)
		{
			at = &this->argument;
			if (argument)
			{
				const Integer *count;
				if (argument->isList(at, count))
					end = at + count->value;
				else end = at + 1;
			}
			else end = at;
		}
		const Any *getArgument()
		{
			if (at == end) return nullptr;
			else return *at++;
		}
		int remainingArgumentCount()
		{
			return end - at;
		}
	private:
		const Any *argument;
		const Any *const *at;
		const Any *const *end;
	};

	template <typename T> struct ArrayArgument
	{
		ArrayArgument() : value(nullptr) {}
		~ArrayArgument() {if (value) delete [] value;}
		T *value;
		void size(int size)
		{
			if (size) value = new T[size];
		}
		operator T*() {return value;}
	};

	class ArgumentSource
		: public ArgumentReader
	{
	public:
		ArgumentSource(const Any *argument)
			: ArgumentReader(argument)
		{}
		template <typename T> bool fill(T *&slot, const JuceClass &class_, bool nullable = false)
		{
			return fillClass((void *&)slot, class_, nullable);
		}
		bool fill(juce::String &slot);
		bool fill(float &slot);
		bool fill(double &slot);
		bool fill(int &slot);
		bool fill(juce::uint32 &slot);
		bool fill(short &slot);
		bool fill(bool &slot);
		bool fill(juce::int64 &slot);
		bool fill(juce::uint64 &slot);
		bool fill(juce::uint16 &slot);
		bool fill(juce::uint8 &slot);
		bool fill(unsigned long &slot);

		bool fill(Array<int> &slot);
		bool fill(Rectangle<int> &slot);
		bool fill(juce::Point<int> &slot);
		bool fill(juce::Point<float> &slot);
		bool fill(Rectangle<float> &slot);
		bool fill(juce::Line<float> &slot);
		bool fill(Range<int> &slot);
		bool fill(Range<double> &slot);
		bool fill(var &slot);
        bool fill(Identifier &slot);
        bool fill(juce::Image *&slot);
		bool fill(StringPairArray &slot);
		bool fill(StringArray &slot);
		bool fill(const StringArray &slot);
        bool fill(BigInteger &slot);
        bool fill(const BigInteger &slot);
		bool fill(char *&slot);
		bool fill(char &slot);
		bool fill(signed char &slot);
		bool fill(const char *&slot);
        bool fill(const void *&slot);
		bool fill(juce_wchar *&slot);
		bool fill(const juce_wchar *&slot);
		bool fill(const tm *&slot);
		bool fill(const OwnedArray<File> &slot);
		bool fill(const OwnedArray<Font> &slot);
		bool fill(const ApplicationCommandTarget::InvocationInfo &slot);
		bool fill(const DirectoryContentsList::FileInfo &slot);
		bool fill(const DirectoryContentsList::FileInfo *&slot);
		bool fill(const File &slot);
		bool fill(const juce::uint8 *&slot);
        bool fill(void *&slot);
		bool fill(const SparseSet<int> &slot);
		bool fill(MessageCallbackFunction *&slot);
		bool fill(Array <PropertyComponent *> &slot);
		bool fill(Array <const UndoableAction *> &slot);
		bool fill(Component **&slot);
		bool fill(const File **&slot);
		bool fill(float **&slot);
		bool fill(const Constant *&slot);
		bool fill(const void *&slot, int &count);
		bool fill(const void *&slot, size_t &count);
		bool fill(const juce::Path *&slot, const JuceClass &class_);
		bool fill(const juce::Colour *&slot, const JuceClass &class_);
		bool fill(juce::Colour *&slot, const JuceClass &class_);
		bool fill(ModalComponentManager::Callback *&slot);
		bool fill(const double *&slot);
		bool fill(const RelativePoint &dummy);
		bool fill(const RelativeCoordinate &dummy);
		bool fill(const RelativeRectangle &dummy);
		bool fill(juce::BorderSize<int>&slot);

        bool fill(juce_wchar &slot);

		template <typename T> bool fill(ArrayArgument<T *>&slot, int &count, const JuceClass &class_)
		{
			const Any *argument = getArgument();
			if (!argument)
			{
				count = 0;
				return true;
			}
			JuceClassConverter converter(class_, true);
			const Any *const *element;
			size_t elementCount;
			if (argument->isList(element, elementCount))
			{
				count = elementCount;
				for (int i = 0; i < count; i++)
				{
					if (element[i]->convert(converter))
					{
						if (i == 0)
							slot.size(count);
						slot.value[i] = (T *)converter.value;
					}
					else return false;
				}
				return true;
			}
			else
			{
				slot.size(count = remainingArgumentCount() + 1);
				for (int i = 0; argument; i++, argument = getArgument())
				{
					if (argument->convert(converter))
						slot.value[i] = (T *)converter.value;
					else return false;
				}
				return true;
			}
		}
	private:
		bool fillClass(void *&slot, const JuceClass &class_, bool nullable);
	};

	typedef void (&Thunk)(void *object, void *arguments, void *result);
	typedef bool (&ArgumentsThunk)(void *object, ArgumentSource &source, Thunk thunk, void *result);

	class JuceMethod
	{
	public:
		static const Any *invokeChain(const JuceMethod *method, Runner &run, const JuceReference &object, const Any *operand);
	protected:
		JuceMethod(const JuceClassBase &class_, const JuceName *name)
			: class_(class_), next(name->methods)
		{
			(JuceMethod *&)name->methods = this;
		}
		virtual const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const = 0;
	private:
		const JuceClassBase &class_;
		const JuceMethod *const next;
	};

	template <typename Arguments> bool argsThunk(void *object, ArgumentSource &source, Thunk thunk, void *result)
	{
		Arguments arguments;
		if (arguments.fill(source))
		{
			thunk(object, &arguments, result);
			return true;
		}
		else return false;
	}

	class Method
		: public JuceMethod
	{
	protected:
		Method(const JuceClassBase &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: JuceMethod(class_, JuceName::get(name)), argumentsThunk(argumentsThunk), thunk(thunk)
		{}
		Method(const JuceClassBase &class_, const JuceName *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: JuceMethod(class_, name), argumentsThunk(argumentsThunk), thunk(thunk)
		{}
		ArgumentsThunk argumentsThunk;
		Thunk thunk;
	};

	class UnimplementedMethod
		: public Method
	{
	public:
		UnimplementedMethod(const JuceClassBase &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: Method(class_, name, argumentsThunk, thunk)
		{}
        const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const override;
	};

	class VoidMethod
		: public Method
	{
	public:
		VoidMethod(const JuceClassBase &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: Method(class_, name, argumentsThunk, thunk)
		{}
		VoidMethod(const JuceClassBase &class_, const JuceName *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: Method(class_, name, argumentsThunk, thunk)
		{}
        const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const override;
	};

	class PilsReferenceMethod
		: public Method
	{
	public:
		PilsReferenceMethod(const JuceClassBase &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: Method(class_, name, argumentsThunk, thunk)
		{}
        const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const override;
	};

	class ReferenceMethod /* creates references without ownership */
		: public Method
	{
	public:
		ReferenceMethod(const JuceClassBase &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk, const JuceClass &resultClass)
			: Method(class_, name, argumentsThunk, thunk), resultClass(resultClass)
		{}
		ReferenceMethod(const JuceClassBase &class_, const JuceName *name, ArgumentsThunk argumentsThunk, Thunk thunk, const JuceClass &resultClass)
			: Method(class_, name, argumentsThunk, thunk), resultClass(resultClass)
		{}
        const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const override;
	protected:
		const JuceClass &resultClass;
	};

	class FactoryMethod /* creates references, with ownership for non-components */
		: public ReferenceMethod
	{
	public:
		FactoryMethod(const JuceClassBase &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk, const JuceClass &resultClass)
			: ReferenceMethod(class_, name, argumentsThunk, thunk, resultClass)
		{}
		FactoryMethod(const JuceClassBase &class_, const JuceName *name, ArgumentsThunk argumentsThunk, Thunk thunk, const JuceClass &resultClass)
			: ReferenceMethod(class_, name, argumentsThunk, thunk, resultClass)
		{}
        const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const override;
	};

	/* this template doesn't compile when instantiated - CopyMethod classes are expanded by the plumming-generator
	template <typename T> class CopyMethod // copies result objects by new T(T&)
		: public ReferenceMethod
	{
	public:
		CopyMethod(const JuceClassBase &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk, const JuceClass &resultClass)
			: ReferenceMethod(class_, name, argumentsThunk, thunk, resultClass)
		{}
		const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
		{
			type result;
			ArgumentSource source(operand);
			if ( (*this->argumentsThunk)(rawObject, source, thunk, &result))
				return resultClass.ownedReference(new T(result));
			else return nullptr;
		}
    private:
        typedef T type;
	};
    */

	class ConstructorMethod /* creates PILS-extended objects, with ownership for non-components */
		: public FactoryMethod
	{
	public:
		ConstructorMethod(const JuceClass &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk, const JuceClass &resultClass)
			: FactoryMethod(class_.staticClass, name, argumentsThunk, thunk, resultClass)
		{}
		ConstructorMethod(const JuceClass &class_, const JuceName *name, ArgumentsThunk argumentsThunk, Thunk thunk, const JuceClass &resultClass)
			: FactoryMethod(class_.staticClass, name, argumentsThunk, thunk, resultClass)
		{}
        const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const override;
	};

	class IntMethod
		: public Method
	{
	public:
		IntMethod(const JuceClassBase &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: Method(class_, name, argumentsThunk, thunk)
		{}
		IntMethod(const JuceClassBase &class_, const JuceName *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: Method(class_, name, argumentsThunk, thunk)
		{}
        const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const override;
	};

	typedef IntMethod CommandIDMethod;

	class Uint32Method
		: public Method
	{
	public:
		Uint32Method(const JuceClassBase &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: Method(class_, name, argumentsThunk, thunk)
		{}
		Uint32Method(const JuceClassBase &class_, const JuceName *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: Method(class_, name, argumentsThunk, thunk)
		{}
        const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const override;
	};

	class ShortMethod
		: public Method
	{
	public:
		ShortMethod(const JuceClassBase &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: Method(class_, name, argumentsThunk, thunk)
		{}
        const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const override;
	};

	class Int64Method
		: public Method
	{
	public:
		Int64Method(const JuceClassBase &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: Method(class_, name, argumentsThunk, thunk)
		{}
        const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const override;
	};

	class CharMethod
		: public Method
	{
	public:
		CharMethod(const JuceClassBase &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: Method(class_, name, argumentsThunk, thunk)
		{}
        const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const override;
	};

	class ConstCharPtrMethod
		: public Method
	{
	public:
		ConstCharPtrMethod(const JuceClassBase &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: Method(class_, name, argumentsThunk, thunk)
		{}
		ConstCharPtrMethod(const JuceClassBase &class_, const JuceName *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: Method(class_, name, argumentsThunk, thunk)
		{}
        const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const override;
	};

	class BoolMethod
		: public Method
	{
	public:
		BoolMethod(const JuceClassBase &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: Method(class_, name, argumentsThunk, thunk)
		{}
		BoolMethod(const JuceClassBase &class_, const JuceName *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: Method(class_, name, argumentsThunk, thunk)
		{}
        const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const override;
	};

	typedef CharMethod Uint8Method;

	class Juce_wcharMethod
		: public Method
	{
	public:
		Juce_wcharMethod(const JuceClassBase &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: Method(class_, name, argumentsThunk, thunk)
		{}
        const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const override;
	};

	class DoubleMethod
		: public Method
	{
	public:
		DoubleMethod(const JuceClassBase &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: Method(class_, name, argumentsThunk, thunk)
		{}
        const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const override;
	};

	class FloatMethod
		: public Method
	{
	public:
		FloatMethod(const JuceClassBase &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: Method(class_, name, argumentsThunk, thunk)
		{}
        const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const override;
	};

	class StringMethod
		: public Method
	{
	public:
		StringMethod(const JuceClassBase &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: Method(class_, name, argumentsThunk, thunk)
		{}
		StringMethod(const JuceClassBase &class_, const JuceName *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: Method(class_, name, argumentsThunk, thunk)
		{}
        const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const override;
	};

	class TimeMethod
		: public Method
	{
	public:
		TimeMethod(const JuceClassBase &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk)
			: Method(class_, name, argumentsThunk, thunk)
		{}
        const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const override;
	};

    class PilsColorMethod
        : public Method
    {
    public:
        PilsColorMethod(const JuceClassBase &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk)
            : Method(class_, name, argumentsThunk, thunk)
        {}
        const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const override;
    };

    class VarMethod
        : public Method
    {
    public:
        VarMethod(const JuceClassBase &class_, const char *name, ArgumentsThunk argumentsThunk, Thunk thunk)
            : Method(class_, name, argumentsThunk, thunk)
        {}
        const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const override;
    };

	class IntrinsicMethod
		: public JuceMethod
	{
	public:
		IntrinsicMethod(const char *name)
			: JuceMethod(JuceDummyClass::singleton, JuceName::get(name))
		{}
	};

	class ClassExtracterMethod
		: public IntrinsicMethod
	{
	public:
		ClassExtracterMethod(const char *name)
			: IntrinsicMethod(name)
		{}
        const Any *invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const override;
	};

	class CallbackHelperBase
	{
	public:
		CallbackHelperBase() : thread(nullptr) {}
		~CallbackHelperBase();
		JuceObject *who;
		PilsThread *thread;
		void helper__visibilityChanged();
	protected:
		static const Constant *toPils(const juce::String &arg)
		{
			if(int count = arg.copyToUTF8(nullptr, 0x7fffffff))
			{
				std::vector<char> buffer(count);
				arg.copyToUTF8(&buffer[0], count);
				return PilsString::get(&buffer[0], count - 1);
			}
			else return PilsString::get((const char *)nullptr, 0);
		}

		static const Constant *toPils(int arg)
		{
			return Integer::get(arg);
		}

		static const Constant *toPils(juce::juce_wchar arg)
		{
			return Integer::get(arg);
		}

		static const Constant *toPils(float arg)
		{
			return Number::get(arg);
		}

		static const Constant *toPils(double arg)
		{
			return Number::get(arg);
		}

		static const Constant *toPils(int64 arg)
		{
			return Number::get((double)arg);
		}

		static const Constant *toPils(const ApplicationCommandTarget::InvocationInfo &arg);
		static const Constant *toPils(const DragAndDropTarget::SourceDetails &arg);

		static bool fromPils(const Any *pils);
		static bool fromPils(const Any *pils, bool &result);
		static bool fromPils(const Any *pils, int &result);
		static bool fromPils(const Any *pils, int64 &result);
		static bool fromPils(const Any *pils, double &result);
		static bool fromPils(const Any *pils, float &result);
		static bool fromPils(const Any *pils, juce::String &result);
		static bool fromPils(const Any *pils, juce::StringArray &result);
		static bool fromPils(const Any *pils, ReferenceCountedObjectPtr<ReferenceCountedObject> &result, JuceClass &class_, bool nullable = false);
		static bool fromPils(const Any *pils, var &result);

		static const Any *fromPilsPtr(const Any *pils, void *&result, JuceClass &class_, bool nullable = false);
        const Any *pilsCall(const Any *call) const;
	};

	class SinkJuceCallback
		: Sink
	{
	public:
		SinkJuceCallback(const Any *&result, const Any *whence)
			: result(result), whence(whence)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *thing) override;
        const Step *miss(Runner &run) override;
	private:
		const Any *&result;
		const Any *whence;
	};
}
#endif
