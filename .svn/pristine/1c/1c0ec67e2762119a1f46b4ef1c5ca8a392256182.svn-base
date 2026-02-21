/* This file is public domain */
#include "jpils-plughost.h"
#include "pils-kernel/pilsatomic.h"
#include "pils-kernel/pilsatomic.h"
#include "jpils_DynamicLibrary.h"
namespace pilsplug
{
	void PilsplugHost::increment(const interface::VirtualBaseObject &object) const
	{
		PILS_INTERLOCKED_INCREMENT(object.count);
	}

	int PilsplugHost::decrement(const interface::VirtualBaseObject &object) const
	{
		return PILS_INTERLOCKED_DECREMENT_RETURN(object.count);
	}

	void *PilsplugHost::service(const char *) const
	{
		return NULL;
	}
}

namespace PILS
{
	bool ReallySpecial::specialComparing(const PILS::PlugLibraryLookup &lookup) const
	{
		return false;
	}

	bool ReallySpecial::specialComparing(const PILS::PlugObjectLookup &lookup) const
	{
		return false;
	}

	void *PlugTools::loadPlugin(const ReallySpecial &cracker, const PilsString &name)
	{
		return cracker.loadPlugin(name);
	}

	void *Plumcake::loadPlugin(const PilsString &name) const
	{
		const juce::String string = juce::String::fromUTF8(name.value, name.count->value);
		return new juce::DynamicLibrary(string);
	}

	void *PlugTools::getProcAddress(void *handle, const char *name)
	{
		juce::DynamicLibrary *h = static_cast<juce::DynamicLibrary *>(handle);
		return h->getFunction(juce::String::fromUTF8(name));
	}

	const ReallySpecial *PlugLibraryLookup::newSpecial(const HashedConstant *&link)
	{
		return new (Heap::allocate(sizeof(PlugLibrarySpecial))) PlugLibrarySpecial(link, handle);
	}

	bool PlugLibraryLookup::compare(const ReallySpecial &other) const
	{
		return other.specialComparing(*this);
	}

	void PlugLibraryLookup::unduplicate()
	{
		juce::DynamicLibrary *h = static_cast<juce::DynamicLibrary *>(handle);
		delete handle;
	}

	size_t PlugLibrarySpecial::unlinkAndGetSize()
	{
		unhash();
		if (when) when->releaseFrom(*this);
		this->PlugLibrary::~PlugLibrary();
		return sizeof(PlugLibrarySpecial);
	}

	PlugLibrary::~PlugLibrary()
	{
		juce::DynamicLibrary *h = static_cast<juce::DynamicLibrary *>(handle);
		delete h;
	}

	void PlugLibrarySpecial::write(Writing &writing) const
	{
		writing.write("-internal library handle-");
	}

	const Special *PlugLibrarySpecial::as_Special() const
	{
		return this;
	}

	bool PlugLibrarySpecial::specialComparing(const PlugLibraryLookup &lookup) const
	{
		juce::DynamicLibrary *h1 = static_cast<juce::DynamicLibrary *>(handle);
		juce::DynamicLibrary *h2 = static_cast<juce::DynamicLibrary *>(lookup.handle);
		return h1->getNativeHandle() == h2->getNativeHandle();
	}

	bool PlugObjectLookup::compare(const PILS::ReallySpecial &other) const
	{
		return other.specialComparing(*this);
	}

	const ReallySpecial *PlugObjectLookup::newSpecial(const HashedConstant *&link)
	{
		types.addReference();
		handle.addReference();
		return new (Heap::allocate(sizeof(PlugObjectSpecial))) PlugObjectSpecial(link, object, &types, type, plug, &handle);
	}

	bool PlugObjectSpecial::specialComparing(const PlugObjectLookup &lookup) const
	{
		return object == lookup.object && types == &lookup.types && PlugObject::type == lookup.type && handle == &lookup.handle;
	}

	void PlugObjectSpecial::write(Writing &writing) const
	{
		types->cliche->attributes[PlugObject::type]->write(writing, WRITING_CONSTANT, 10, NULL);
	}

	const Special *PlugObjectSpecial::as_Special() const
	{
		return this;
	}

	size_t PlugObjectSpecial::unlinkAndGetSize()
	{
		unhash();
		if (when) when->releaseFrom(*this);
		this->PlugObject::~PlugObject();
		types->releaseFrom(*this);
		handle->releaseFrom(*this);
		return sizeof(PlugObjectSpecial);
	}

	const PlugCompilable *PlugCompilable::cast(const Any *thing)
	{
		class PlugCompilableRecognizer : public Recognizer
		{
		public:
			bool recognizing(const PlugCompilable &thing)
			{
				plugCompilable = &thing;
				return true;
			}
			const PlugCompilable *plugCompilable;
		};
		PlugCompilableRecognizer recognizer;
		if (thing->recognize(recognizer))
			return recognizer.plugCompilable;
		else return NULL;
	}

	bool PlugName::recognize(Recognizer &recognizer) const
	{
		return recognizer.recognizing(*this);
	}

	const PlugObject *PlugTools::as_PlugObject(const Any *thing)
	{
		class PlugObjectRecognizer : public Recognizer
		{
		public:
			bool recognizing(const PlugObjectSpecial &thing)
			{
				object = &thing;
				return true;
			}
			const PlugObject *object;
		};
		PlugObjectRecognizer recognizer;
		if (thing->recognize(recognizer))
			return recognizer.object;
		else return NULL;
	}
}
