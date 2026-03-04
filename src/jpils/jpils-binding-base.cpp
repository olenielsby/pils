/* This file is public domain */
//#include <src/juce_WithoutMacros.h>
#include "jpils-binding-base.h"
#include "jpils-thread.h"
#include "jpils-graph.h"
#include "pilsatomic.h"

namespace PILS
{
	size_t TypedPtr::hash() const
	{
		return reinterpret_cast<size_t>(ptr);
	}

	const Any *Plumcake::specialCalling(Runner &run, const JuceName &name, const Any &arg) const
	{
		if (name.staticAccessor)
			return JuceMethod::invokeChain(name.methods, run, *name.staticAccessor, &arg);
		else return NULL;
	}

	const Any *JuceReference::specialCalling(Runner &run, const JuceName &method, const Any &arg) const
	{
		return JuceMethod::invokeChain(method.methods, run, *this, &arg);
	}

	const Any *JuceReference::specialCalling(Runner &run, const JuceName &method) const
	{
		return JuceMethod::invokeChain(method.methods, run, *this, NULL);
	}

	bool JuceReference::specialComparing(const JuceLookup &lookup) const
	{
		if (lookup.object.ptr != lookup.object.class_.cast(*this)) return false;
		if (class_.level < lookup.object.class_.level && lookup.object.ptr == ptr)
		{
			lookup.owner = this;
			return false;
		}
		return true;
	}

	JuceStaticClass::JuceStaticClass(const char *namestring)
		: name(*JuceName::get(namestring))
	{
		TypedPtr staticAccessor = {*this, this};
		((JuceName &)name).staticAccessor = new (Heap::allocate(sizeof(JuceReference))) JuceReference(staticAccessor);
	}

	JuceStaticClass::JuceStaticClass(const JuceName *name)
		: name(*name)
	{
		TypedPtr staticAccessor = {*this, this};
		((JuceName &)this->name).staticAccessor = new (Heap::allocate(sizeof(JuceReference))) JuceReference(staticAccessor);
	}

	void *JuceStaticClass::cast(const TypedPtr &ptr) const
	{
		if (&ptr.class_ == this) return ptr.ptr;
		else return NULL;
	}

	void *JuceDummyClass::cast(const TypedPtr &ptr) const
	{
		return ptr.ptr;
	}

	void *JuceClass::cast(const TypedPtr &ptr) const
	{
		if (ptr.class_.lineage[level] == this) return ptr.ptr;
		for (int i = 0; i < this->mixinCount; i++)
		{
			void *v = mixinOf[i].of.cast(ptr);
			if (v) return ((char *)v) + mixinOf[i].offset;
		}
		return NULL;
	}

	bool JuceClassBase::recognizing(const void *instance, PILS::Recognizer &recognizer) const
	{
		return false;
	}

	void JuceName::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.check_(*typecheck);
		pattern.whoAttribute()->compilePattern(compiling);
	}

	bool JuceClass::converting(const JuceReference &argument)
	{
		return cast(argument) != NULL;
	}

	const Any *Plumcake::specialCalling(Runner &run, const JuceName &method) const
	{
		const Any *accessor = method.staticAccessor;
		if (accessor) accessor->addReference();
		return accessor;
	}

	const ReallySpecial *JuceLookup::newSpecial(const HashedConstant *&link)
	{
		return object.class_.newSpecial(link, object, owner);
	}

	bool JuceLookup::compare(const ReallySpecial &special) const
	{
		return special.specialComparing(*this);
	}

	void JuceLookup::unduplicate()
	{}

	size_t JuceLookup::hash() const
	{
		return reinterpret_cast<size_t>(object.ptr);
	}

	const JuceReference *JuceClassBase::newSpecial(const HashedConstant *&link, TypedPtr &object, const JuceReference *owner) const
	{
		if (owner) owner->addReference();
		return new (Heap::allocate(sizeof(JuceReference))) JuceReference(link, object, owner);
	}

	void JuceReference::write(Writing &writing) const
	{
		class_.getName().write(writing, WRITING_NAME, 10, NULL);
		writing.write('?');
	}

	bool JuceReference::recognize(Recognizer &recognizer) const
	{
		return class_.recognizing(ptr, recognizer);
	}

	void JuceReference::alert()
	{}

	size_t JuceReference::unlinkAndGetSize()
	{
		unhash();
		if (when) when->releaseFrom(*this);
		if (owner) owner->releaseFrom(*this);
		return sizeof(JuceReference);
	}

	void JuceOwnedReference::write(Writing &writing) const
	{
		class_.getName().write(writing, WRITING_NAME, 10, NULL);
		writing.write('&');
	}

	size_t JuceOwnedReference::unlinkAndGetSize()
	{
		unhash();
		if (when) when->releaseFrom(*this);
		{
			Mutex::Unlock unlock(Heap::mutex);
			class_.release(ptr);
		}
		return sizeof(JuceReference);
	}

	JuceObject::JuceObject(const HashedConstant *&link, TypedPtr &typedPtr, CallbackHelperBase *helper)
		: JuceReference(link, typedPtr, NULL), helper(helper)
	{
		if (helper) helper->who = this;
	}

	void JuceObject::alert() {}

	void JuceObject::deleted()
	{
		ptr = NULL;
	}

	void JuceObject::write(Writing &writing) const
	{
		class_.getName().write(writing, WRITING_NAME, 10, NULL);
		writing.write('+');
	}

	size_t JuceObject::unlinkAndGetSize()
	{
		unhash();
		if (when) when->releaseFrom(*this);
		if (ptr) class_.release(ptr);
		return sizeof(JuceObject);
	}

	const JuceReference *JuceReferenceCountedClass::newSpecial(const HashedConstant *&link, TypedPtr &object, const JuceReference *owner) const
	{
		((ReferenceCountedObject *)object.ptr)->incReferenceCount();
		return new (Heap::allocate(sizeof(JuceOwnedReference))) JuceOwnedReference(link, object);
	}

	JuceComponent::JuceComponent(const HashedConstant *&link, TypedPtr &typedPtr, CallbackHelperBase *helper)
		: JuceObject(link, typedPtr, helper), desktop(false)
	{
        addReference(); // sikr mod sletning
		addReference();
	}

	size_t JuceComponent::unlinkAndGetSize()
	{
		unhash();
		if (when) when->releaseFrom(*this);
		return sizeof(JuceComponent);
	}

	bool JuceComponent::isMultipleReferenced() const
	{
		return !ptr || referenceCount != 1;
	}

	const Any *JuceComponent::mindError() const
	{
		addReference();
		return this;
	}

	const Step *JuceComponent::calling(Runner &run, const Constant &call) const
	{
		if (&call == &Builtin::name.mind && ptr)
		{
			const Express *what = run.calling.what;
			what->addReference();
			return run.sink->pass(run, (PassingMind*)this, what);
		}
		else return JuceObject::calling(run, call);
	}

	void CallbackHelperBase::helper__visibilityChanged()
	{
		who->alert();
	}

	void JuceComponent::alert()
	{
		class PendingDelete	: Pending
		{
		public:
			PendingDelete(juce::Component *gone_) : Pending(*MainThread::singleton), gone_(gone_) {}
			~PendingDelete()
			{
                delete gone_;
			}
		private:
			juce::Component *gone_;
		};

		Component *component = (Component *)ptr;
		if (!desktop && component && component->isOnDesktop())
		{
			desktop = true;
			PILS_INTERLOCKED_INCREMENT(desktopComponentCount);
		}
		else if (desktop && !(component->isOnDesktop()))
		{
			new PendingDelete(component);
		}
	}

	void JuceComponent::deleted()
	{
		JuceObject::deleted();
		this->PassingMindMap::~PassingMindMap();
		strapSticker.~Sticker();
		if (desktop)
		{
			desktop = false;
			PILS_INTERLOCKED_DECREMENT(desktopComponentCount);
		}
		releaseReference();
	}

	const Any *JuceComponent::specialCalling(Runner &run, const Strap &call) const
	{
		if (!ptr) return NULL;
		strapSticker.stick(call);
		call.addReference();
		return &call;
	}

	CallbackHelperBase::~CallbackHelperBase()
	{
		// Component *deleted = (Component *)who->ptr;
		if (thread)
		{
			thread->releaseReference();
		}
		who->deleted();
	}

	void JuceClass::release(void *ptr) const
	{
		releaseThunk(ptr);
	}

	void JuceStaticClass::release(void *ptr) const
	{}

	bool JuceImageClass::recognizing(const void *instance, Recognizer &recognizer) const
	{
		return recognizer.recognizing(*(const juce::Image*)instance);
	}

	bool JuceDrawableClass::recognizing(const void *instance, Recognizer &recognizer) const
	{
		return recognizer.recognizing(*(const juce::Drawable*)instance);
	}

	bool JuceColourClass::recognizing(const void *instance, Recognizer &recognizer) const
	{
		return recognizer.recognizing(*(const juce::Colour*)instance);
	}

	const Any *JuceMethod::invokeChain(const JuceMethod *method, Runner &run, const JuceReference &object, const Any *operand)
	{
		const Any *result = NULL;
		for (;result == NULL && method != NULL; method = method->next)
		{
			void *rawObject = method->class_.cast(object);
			if (rawObject)
				result = method->invoke(run, object, rawObject, operand);
		}
		return result;
	}
	bool ArgumentSource::fill(String &slot)
	{
		if (const Any *argument = getArgument())
		{
			if (const PilsString *string = argument->as_String())
			{
				slot = String::fromUTF8(string->value, string->count->value);
				return true;
			}
		}
		return false;
	}
	bool ArgumentSource::fill(float &slot)
	{
		double value;
		if (fill(value))
		{
			slot = (float)value;
			return true;
		}
		else return false;
	}
	bool ArgumentSource::fill(double &slot)
	{
		const Any *argument;
		return (argument = getArgument()) && argument->isNumber(slot);
	}
	bool ArgumentSource::fill(int &slot)
	{
		if (const Any *argument = getArgument())
		{
			if (const Integer *integer = argument->as_Integer())
			{
				slot = integer->value;
				return true;
			}
		}
		return false;
	}
	bool ArgumentSource::fill(unsigned int &slot)
	{
		double value;
		if (fill(value))
		{
			slot = (unsigned int)value;
			return true;
		}
		else return false;
	}
	bool ArgumentSource::fill(short &slot)
	{
		if (const Any *argument = getArgument())
		{
			if (const Integer *integer = argument->as_Integer())
			{
				slot = (short)integer->value;
				return true;
			}
		}
		return false;
	}
	bool ArgumentSource::fill(bool &slot)
	{
		if (const Any *argument = getArgument())
		{
			if (const Integer *integer = argument->as_Integer())
			{
				slot = integer->value > 0;
				return true;
			}
		}
		return false;
	}
	bool ArgumentSource::fill(juce::int64 &slot)
	{
		double value;
		if (fill(value))
		{
			slot = (juce::int64)value;
			return true;
		}
		else return false;
	}
	bool ArgumentSource::fill(juce::uint8 &slot)
	{
		if (const Any *argument = getArgument())
		{
			if (const Integer *integer = argument->as_Integer())
			{
				slot = (juce::uint8)integer->value;
				return true;
			}
		}
		return false;
	}
	bool ArgumentSource::fill(juce::Array<int> &slot)
	{
		if (const Any *argument = getArgument())
		{
			if (const Integer *integer = argument->as_Integer())
			{
				while (integer)
				{
					slot.add(integer->value);
					argument = getArgument();
					if (argument) integer = argument->as_Integer();
				}
				return !argument;
			}
			else if (const ListConstant *list = argument->as_ListConstant())
			{
				int count = list->count->value;
				slot.ensureStorageAllocated(count);
				for (int i = 0; i < count; i++)
				{
					if (const Integer *integer = list->element[i]->as_Integer())
						slot.add(integer->value);
					else return false;
				}
				return true;
			}
			else return false;
		}
		else return true; //no more arguments = empty list
	}
	bool ArgumentSource::fill(juce::BorderSize<int> &slot)
	{
		const Integer *integer;
		if (const Any *argument = getArgument())
		{
			if (integer = argument->as_Integer())
			{
				slot.setTop(integer->value);
				if ((argument = getArgument()) && (integer = argument->as_Integer()))
					slot.setLeft(integer->value);
				else return false;
				if ((argument = getArgument()) && (integer = argument->as_Integer()))
					slot.setBottom(integer->value);
				else return false;
				if ((argument = getArgument()) && (integer = argument->as_Integer()))
					slot.setRight(integer->value);
				else return false;
				return true;
			}
			else if (const ListConstant *list = argument->as_ListConstant())
			{
				int count = list->count->value;
				if (count != 4) return false;
				if (integer = list->element[0]->as_Integer())
					slot.setTop(integer->value);
				else return false;
				if (integer = list->element[1]->as_Integer())
					slot.setLeft(integer->value);
				else return false;
				if (integer = list->element[2]->as_Integer())
					slot.setBottom(integer->value);
				else return false;
				if (integer = list->element[3]->as_Integer())
					slot.setRight(integer->value);
				else return false;
				return true;
			}
			else return false;
		}
		else return true; //no more arguments = empty list
	}
	bool ArgumentSource::fill(StringPairArray &slot)
	{
		return false;
	}
	bool ArgumentSource::fill(StringArray &slot)
	{
		return false;
	}
	bool ArgumentSource::fill(const StringArray &slot)
	{
		return false;
	}
    // bool ArgumentSource::fill(BitArray &slot)
    // {
    // 	return false;
    // }
    // bool ArgumentSource::fill(const BitArray &slot)
    // {
    // 	return false;
    // }
	bool ArgumentSource::fill(char *&slot)
	{
		return false;
	}
	bool ArgumentSource::fill(char &slot)
	{
		if (const Any *argument = getArgument())
		{
			if (const Integer *integer = argument->as_Integer())
			{
				slot = (char)integer->value;
				return true;
			}
		}
		return false;
	}
	bool ArgumentSource::fill(const char *&slot)
	{
		return false;
	}
	bool ArgumentSource::fill(const void *&slot)
	{
		return false;
	}
	bool ArgumentSource::fill(juce_wchar *&slot)
	{
		return false;
	}
	bool ArgumentSource::fill(const juce_wchar *&slot)
	{
		return false;
	}
	bool ArgumentSource::fill(const tm *&slot)
	{
		return false;
	}
	bool ArgumentSource::fill(const OwnedArray<juce::File> &slot)
	{
		return false;
	}
	bool ArgumentSource::fill(const OwnedArray<juce::Font> &slot)
	{
		return false;
	}
	bool ArgumentSource::fill(const juce::ApplicationCommandTarget::InvocationInfo &slot)
	{
		return false;
	}
	bool ArgumentSource::fill(const juce::DirectoryContentsList::FileInfo &slot)
	{
		return false;
	}
	bool ArgumentSource::fill(const juce::DirectoryContentsList::FileInfo *&slot)
	{
		return false;
	}
	bool ArgumentSource::fill(const juce::File &slot)
	{
		return false;
	}
	bool ArgumentSource::fill(const juce::uint8 *&slot)
	{
		return false;
	}
	bool ArgumentSource::fill(const SparseSet<int> &slot)
	{
		return false;
	}
	bool ArgumentSource::fill(MessageCallbackFunction *&slot)
	{
		return false;
	}
	bool ArgumentSource::fill(Array <PropertyComponent *> &slot)
	{
		return false;
	}
	bool ArgumentSource::fill(Array <const UndoableAction *> &slot)
	{
		return false;
	}
	bool ArgumentSource::fill(Component **&slot)
	{
		return false;
	}
	bool ArgumentSource::fill(void *&slot)
	{
		return false;
	}
	bool ArgumentSource::fill(const File **&slot)
	{
		return false;
	}
	bool ArgumentSource::fill(float **&slot)
	{
		return false;
	}

    // bool ArgumentSource::fill(Image::SharedImage *&slot)
    // {
    // 	return false;
    // }

	bool ArgumentSource::fill(ModalComponentManager::Callback *&slot)
	{
		return false;
	}

	bool ArgumentSource::fill(const double *&slot)
	{
		return false;
	}

	bool ArgumentSource::fill(Rectangle<float> &slot)
	{
		float f;
		if (!fill(f)) return false;
		slot.setX(f);
		if (!fill(f)) return false;
		slot.setY(f);
		if (!fill(f)) return false;
		slot.setWidth(f);
		if (!fill(f)) return false;
		slot.setHeight(f);
		return true;
	}

	bool ArgumentSource::fill(Line<float> &slot)
	{
		juce::Point<float> f;
		if (!fill(f)) return false;
		slot.setStart(f);
		if (!fill(f)) return false;
		slot.setEnd(f);
		return true;
	}

	bool ArgumentSource::fill(Range<double> &slot)
	{
		double f;
		if (!fill(f)) return false;
		slot.setStart(f);
		if (!fill(f)) return false;
		slot.setEnd(f);
		return true;
	}

	bool ArgumentSource::fill(const Constant *&slot)
	{
		const Any *argument = getArgument();
		return argument && (slot = argument->as_Constant());
	}

	bool ArgumentSource::fill(const void *&slot, int &count)
	{
		const Any *argument = getArgument();
		if (!argument) return false;
		const PilsString *string = argument->as_String();
		if (!string) return false;
		slot = string->value;
		count = string->count->value;
		return true;
	}

	bool ArgumentSource::fill(const void *&slot, size_t &count)
	{
		const Any *argument = getArgument();
		if (!argument) return false;
		const PilsString *string = argument->as_String();
		if (!string) return false;
		slot = string->value;
		count = string->count->value;
		return true;
	}

	class ColorRecognizer : public Recognizer
	{
	public:
        bool recognizing(const PilsColor &color) override
		{
			value = (const juce::Colour *)&color.value;
			return true;
		}
        bool recognizing(const juce::Colour &thing) override
		{
			value = &thing;
			return true;
		}
		const juce::Colour *value;
	};

	bool ArgumentSource::fill(const juce::Colour *&slot, const JuceClass &class_)
	{
		if (const Any *argument = getArgument())
		{
			ColorRecognizer recognizer;
			if (argument->recognize(recognizer))
			{
				slot = recognizer.value;
				return true;
			}
		}
		return false;
	}

	bool ArgumentSource::fill(juce::Colour *&slot, const JuceClass &class_)
	{
		return fill((const juce::Colour *&)slot, class_);
	}

	bool ArgumentSource::fill(const juce::Path *&slot, const JuceClass &class_)
	{
		if (const Any *argument = getArgument())
		{
			class instance : public Recognizer
			{
			public:
                bool recognizing(const juce::Path &path) override
				{
					this->path = &path;
					return true;
				}
				const juce::Path *path;
			} recognizer;
			if (argument->recognize(recognizer))
			{
				slot = recognizer.path;
				return true;
			}
			else
			{
				JuceClassConverter converter(class_, false);
				if (argument->convert(converter))
				{
					slot = (Path *)converter.value;
					return true;
				}
			}
		}
		return false;
	}

	bool ArgumentSource::fill(Rectangle<int> &slot)
	{
		int x, y, w, h;
		if (fill(x) && fill (y) & fill(w) & fill(h))
		{
			slot = Rectangle<int>(x, y, w, h);
			return true;
		}
		else return false;
	}

	bool ArgumentSource::fill(juce::Point<int> &slot)
	{
		int x, y;
		if (fill(x) && fill (y))
		{
			slot = juce::Point<int>(x, y);
			return true;
		}
		else return false;
	}

	bool ArgumentSource::fill(juce::Point<float> &slot)
	{
		float x, y;
		if (fill(x) && fill (y))
		{
			slot = juce::Point<float>(x, y);
			return true;
		}
		else return false;
	}

	bool ArgumentSource::fill(Range<int> &slot)
	{
		int a, b;
		if (fill(a) && fill (b))
		{
			slot = Range<int>(a, b);
			return true;
		}
		else return false;
	}

	bool ArgumentSource::fill(juce::uint64 &slot)
	{
		double value;
		if (fill(value))
		{
			slot = (juce::uint64)value;
			return true;
		}
		else return false;
	}

	bool ArgumentSource::fill(unsigned long &slot)
	{
		double value;
		if (fill(value))
		{
			slot = (size_t)value;
			return true;
		}
		else return false;
	}
	
	bool ArgumentSource::fill(juce::uint16 &slot)
	{
		int value;
		if (fill(value) && value == (value & 0xffff))
		{
			slot = (juce::uint16)value;
			return true;
		}
		else return false;
	}

    // bool ArgumentSource::fill(juce::var::Identifier &slot)
    // {
    // 	juce::String value;
    // 	if (fill(value))
    // 	{
    // 		slot = juce::var::Identifier(value);
    // 		return true;
    // 	}
    // 	else return false;
    // }

	bool ArgumentSource::fill(juce::var &slot)
	{
		// todo: convert various arg types to var
		return false;
	}

    bool ArgumentSource::fill(juce::BigInteger &slot)
    {
        // todo: recognize and copy BigInteger
        return false;
    }

	bool ArgumentSource::fillClass(void *&slot, const JuceClass &class_, bool nullable)
	{
		if (const Any *argument = getArgument())
		{
			JuceClassConverter converter(class_, nullable);
			if (argument->convert(converter))
			{
				slot = converter.value;
				return true;
			}
		}
		return false;
	}
    //ChatGPTG genereret
    bool ArgumentSource::fill(juce_wchar &slot)
    {
        int temp;
        if (!fill(temp))
            return false;

        slot = static_cast<juce_wchar>(temp);
        return true;
    }

	bool JuceClassConverter::convert(const Cliche &className)
	{
		value = NULL;
		return nullable && &toClass.getName() == &className;
	}

	bool JuceClassConverter::converting(const JuceReference &argument)
	{
		return ((value = toClass.cast(argument)) != NULL);
	}

	bool JuceReference::converting(JuceSpecialConverter &converter) const
	{
		return converter.converting(*this);
	}

	const Any *UnimplementedMethod::invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
	{
		return NULL;
	}

	const Any *VarMethod::invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
	{
		return NULL;
	}

	const Any *VoidMethod::invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
	{
		ArgumentSource source(operand);
		if (this->argumentsThunk(rawObject, source, thunk, NULL))
		{
			object.addReference();
			return &object;
		}
		else return NULL;
	}

	const Any *ConstructorMethod::invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
	{
		ArgumentSource source(operand);
		CallbackHelperBase *helper = NULL;
		if (argumentsThunk(&helper, source, thunk, &rawObject))
			return resultClass.wrap(rawObject, helper);
		else return NULL;
	}

	const Any *ReferenceMethod::invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
	{
		void *result = NULL;
		ArgumentSource source(operand);
		if (this->argumentsThunk(rawObject, source, thunk, &result) && result)
			return resultClass.reference(result);
		else return NULL;
	}

	const Any *FactoryMethod::invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
	{
		void *result = NULL;
		ArgumentSource source(operand);
		if (this->argumentsThunk(rawObject, source, thunk, &result) && result)
			return resultClass.ownedReference(result);
		else return NULL;
	}

	const Any *PilsReferenceMethod::invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
	{
		const Any *result = NULL;
		ArgumentSource source(operand);
		if (this->argumentsThunk(rawObject, source, thunk, &result))
			return result;
		else return NULL;
	}

	const Any *IntMethod::invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
	{
		ArgumentSource source(operand);
		int result;
		if (this->argumentsThunk(rawObject, source, thunk, &result))
		{
			return Integer::get(result);
		}
		else return NULL;
	}

	const Any *Uint32Method::invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
	{
		ArgumentSource source(operand);
		juce::uint32 result;
		if (this->argumentsThunk(rawObject, source, thunk, &result))
		{
			return Number::get(result);
		}
		else return NULL;
	}

	const Any *ShortMethod::invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
	{
		ArgumentSource source(operand);
		short result;
		if (this->argumentsThunk(rawObject, source, thunk, &result))
		{
			return Integer::get(result);
		}
		else return NULL;
	}

	const Any *CharMethod::invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
	{
		ArgumentSource source(operand);
		char result;
		if (this->argumentsThunk(rawObject, source, thunk, &result))
		{
			return Integer::get(result);
		}
		else return NULL;
	}

	const Any *ConstCharPtrMethod::invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
	{
		ArgumentSource source(operand);
		const char *result;
		if (this->argumentsThunk(rawObject, source, thunk, &result))
		{
			if (result)
				return PilsString::get(result);
			else
			{
				Empty::singleton.addReference();
				return &Empty::singleton;
			}
		}
		else return NULL;
	}

	const Any *BoolMethod::invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
	{
		ArgumentSource source(operand);
		bool result;
		if (this->argumentsThunk(rawObject, source, thunk, &result))
		{
			return Integer::get(result);
		}
		else return NULL;
	}

	const Any *Juce_wcharMethod::invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
	{
		ArgumentSource source(operand);
		juce_wchar result;
		if (this->argumentsThunk(rawObject, source, thunk, &result))
		{
			return Integer::get(result);
		}
		else return NULL;
	}

	const Any *DoubleMethod::invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
	{
		ArgumentSource source(operand);
		double result;
		if (this->argumentsThunk(rawObject, source, thunk, &result))
		{
			return Number::get(result);
		}
		else return NULL;
	}

	const Any *FloatMethod::invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
	{
		ArgumentSource source(operand);
		float result;
		if (this->argumentsThunk(rawObject, source, thunk, &result))
		{
			return Number::get(result);
		}
		else return NULL;
	}

	const Any *Int64Method::invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
	{
		ArgumentSource source(operand);
		int64 result;
		if (this->argumentsThunk(rawObject, source, thunk, &result))
		{
			return Number::get((double)result);
		}
		else return NULL;
	}

	const Any *StringMethod::invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
	{
		ArgumentSource source(operand);
		juce::String result;
		if (this->argumentsThunk(rawObject, source, thunk, &result))
			return pils(result);
		else return NULL;
	}

	const Any *TimeMethod::invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
	{
		ArgumentSource source(operand);
		juce::Time result;
		if (this->argumentsThunk(rawObject, source, thunk, &result))
		{
			return pils(result);
		}
		else return NULL;
	}

	const Any *PilsColorMethod::invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
	{
		ArgumentSource source(operand);
		unsigned int result;
		if (this->argumentsThunk(rawObject, source, thunk, &result))
		{
			return PilsColor::get(result);
		}
		else return NULL;
	}

	const Any *ClassExtracterMethod::invoke(Runner &run, const JuceReference &object, void *rawObject, const Any *operand) const
	{
		if (object.ptr && !operand)
		{
			const JuceName &class_ = object.class_.getName();
			class_.addReference();
			return &class_;
		}
		else return NULL;
	}

	const Any *CallbackHelperBase::pilsCall(const Any *call) const
	{
		if (!who->when) return NULL;
		PilsThread *thread = PilsThread::RunLevel::getCurrent(this->thread);
		PilsThread::RunLevel running(thread);
		Runner &run = running.run();
		const Any *result = NULL;
		who->when->addReference();
		JuceObject *who = this->who;
		run.calling.who = who;
		who->addReference();
		run.calling.what = (const Express *)who;
		new (run.allocate(sizeof(SinkJuceCallback))) SinkJuceCallback(result, run.where_);
		run.where_ = who->when;
		run.run(call->caller(*thread, *who->when));
		call->releaseReference();
		if (result)
			who->alert();
		who->releaseReference();
		thread->releaseReference();
		return result;
	}

	Sink *SinkJuceCallback::kick(Runner &run)
	{
		run.where_->releaseReference();
		run.where_ = whence;
		return this + 1;
	}

	const Step *SinkJuceCallback::pass(Runner &run, const Any *value)
	{
		result = value;
		run.sink = kick(run);
		return NULL;
	}

	const Step *SinkJuceCallback::miss(Runner &run)
	{
		while (run.sink != this) run.sink = run.sink->kick(run);
		run.sink = kick(run);
		return NULL;
	}

	bool CallbackHelperBase::fromPils(const PILS::Any *pils)
	{
		if (pils)
		{
			pils->releaseReference();
			return true;
		}
		else return false;
	}

	bool CallbackHelperBase::fromPils(const Any *pils, bool &result)
	{
		bool ok = false;
		if (pils)
		{
			if (const Integer *integer = pils->as_Integer())
			{
				result = integer->value > 0;
				ok = true;
			}
			pils->releaseReference();
		}
		return ok;
	}

	bool CallbackHelperBase::fromPils(const Any *pils, int &result)
	{
		bool ok = false;
		if (pils)
		{
			if (const Integer *integer = pils->as_Integer())
			{
				result = integer->value;
				ok = true;
			}
			pils->releaseReference();
		}
		return ok;
	}

	bool CallbackHelperBase::fromPils(const Any *pils, int64 &result)
	{
		bool ok = false;
		if (pils)
		{
			double number;
			if (pils->isNumber(number))
			{
				result = (int64)number;
				ok = true;
			}
			pils->releaseReference();
		}
		return ok;
	}

	bool CallbackHelperBase::fromPils(const Any *pils, double &result)
	{
		bool ok = false;
		if (pils)
		{
			ok = pils->isNumber(result);
			pils->releaseReference();
		}
		return ok;
	}

	bool CallbackHelperBase::fromPils(const Any *pils, float &result)
	{
		double number;
		bool ok = false;
		if (pils)
		{
			ok = pils->isNumber(number);
			pils->releaseReference();
			if (ok) result = (float)number;
		}
		return ok;
	}

	bool CallbackHelperBase::fromPils(const Any *pils, juce::String &result)
	{
		bool ok = false;
		if (pils)
		{
			if (const PilsString *string = pils->as_String())
			{
				result = juce::String::fromUTF8(string->value, string->count->value);
				ok = true;
			}
			pils->releaseReference();
		}
		return ok;
	}

	bool CallbackHelperBase::fromPils(const Any *pils, juce::StringArray &result)
	{
		bool ok = false;
		if (pils)
		{
			if (const PilsString *string = pils->as_String())
			{
				result.add(juce::String::fromUTF8(string->value, string->count->value));
				ok = true;
			}
			else if (const ListConstant *list = pils->as_ListConstant())
			{
				ok = true;
				for (int i = 0; i < list->count->value; i++)
				{
					if (const PilsString *string = list->element[i]->as_String())
					{
						result.add(juce::String::fromUTF8(string->value, string->count->value));
					}
					else
					{
						ok = false;
						break;
					}
				}
			}
			pils->releaseReference();
		}
		return ok;
	}

	bool CallbackHelperBase::fromPils(const Any *pils, juce::ReferenceCountedObjectPtr<juce::ReferenceCountedObject> &result, JuceClass &class_, bool nullable)
	{
		if (!pils) return false;
		JuceClassConverter converter(class_, nullable);
		bool done = pils->convert(converter);
		if (done)
		{
			result = (juce::ReferenceCountedObject *)converter.value;
		}
		pils->releaseReference();
		return done;
	}

	const Any *CallbackHelperBase::fromPilsPtr(const Any *pils, void *&result, JuceClass &class_, bool nullable)
	{
		if (!pils) return NULL;
		JuceClassConverter converter(class_, nullable);
		if (pils->convert(converter))
		{
			result = converter.value;
			return pils;
		}
		else
		{
			pils->releaseReference();
			return NULL;
		}
	}

	const JuceReference *JuceClass::wrap(void *ptr, CallbackHelperBase *helper) const
	{
		TypedPtr typedPtr = {*this, ptr};
		const HashedConstant *&link = HashedConstant::hashChain(typedPtr.hash());
		Mutex::Lock lock(Heap::mutex);
		return new (Heap::allocate(sizeof(JuceObject))) JuceObject(link, typedPtr, helper);
	}

	const JuceReference *JuceReferenceCountedClass::wrap(void *ptr, CallbackHelperBase *helper) const
	{
		TypedPtr typedPtr = {*this, ptr};
		const HashedConstant *&link = HashedConstant::hashChain(typedPtr.hash());
		Mutex::Lock lock(Heap::mutex);
		return new (Heap::allocate(sizeof(JuceOwnedReference))) JuceOwnedReference(link, typedPtr);
	}

	const JuceReference *JuceComponentClass::wrap(void *ptr, CallbackHelperBase *helper) const
	{
		TypedPtr typedPtr = {*this, ptr};
		const HashedConstant *&link = HashedConstant::hashChain(typedPtr.hash());
		Mutex::Lock lock(Heap::mutex);
		return new (Heap::allocate(sizeof(PILS::JuceComponent))) JuceComponent(link, typedPtr, helper);
	}

	const Constant *JuceClass::reference(const void * ptr) const
	{
		if (!ptr)
		{
			Empty::singleton.addReference();
			return &Empty::singleton;
		}
		TypedPtr typedPtr = {*this, (void *)ptr};
		JuceLookup lookup(typedPtr);
		return lookup.lookup();
	}

	const Constant *JuceClass::ownedReference(void * ptr) const
	{
		if (!ptr)
		{
			Empty::singleton.addReference();
			return &Empty::singleton;
		}
		TypedPtr typedPtr = {*this, ptr};
		const HashedConstant *&link = HashedConstant::hashChain(typedPtr.hash());
		Mutex::Lock lock(Heap::mutex);
		return new (Heap::allocate(sizeof(PILS::JuceOwnedReference))) JuceOwnedReference(link, typedPtr);
	}

	const Constant *JuceComponentClass::ownedReference(void * ptr) const
	{
		return reference(ptr);
	}
}
