/* This file is public domain */
#include "jpils-standard-specials.h"
#include "plughost.h"
namespace PILS
{
	const Namespace_Juce *Namespace_Juce::singleton;
	const Namespace_Juce *Namespace_Juce::opengl_singleton;

	const PilsString *pils(const juce::String &string)
	{
		int count = string.copyToUTF8(nullptr, 0x7fffffff);
		return PilsString::get(string.toUTF8(), count - 1);
	}

	void *ReallySpecial::loadPlugin(const PilsString &name) const
	{
		return nullptr;
	}

	const Constant *SingletonSpecial::dummyHashLink = nullptr;
	Plum::Plum()
		: plumcake(*new Plumcake())
	{}

	size_t Plumcake::unlinkAndGetSize()
	{
		throw L"Reference counter leak";
	}

	void Plumcake::write(Writing &writing) const
	{
		writing.write((PILS_CHAR)'*');
	}

	Plumcake::Plumcake()
	{
		Namespace_Juce::initialize();
	}

	size_t Plumcake::hash() const
	{
		throw L"Bad plumcake";
	}

	bool Plumcake::specialCompare(const ReallySpecial *special) const
	{
		throw L"Bad plumcake";
	}

	const Any *Plumcake::specialCalling(Runner &run, const SystemProperty &call) const
	{
		return call.get(run);
	}

	const Any *Plumcake::specialCalling(Runner &run, const Strap &call) const
	{
		if (!run.isMainThread()) return nullptr;
		run.temporaryStrapSticker->stick(call);
		call.addReference();
		return &call;
	}

	const Any *SystemProperty::specialCall(Runner &run, const ReallySpecial &special) const
	{
		return special.specialCalling(run, *this);
	}

	const Any *SystemProperty::specialCall(Runner &run, const ReallySpecial &special, const Any &assignValue) const
	{
		return special.specialCalling(run, *this, assignValue);
	}

	const Any *SystemPropertyNew::get(Runner &run) const
	{
		return nullptr;
	}

	const Any *SystemPropertyPlumcake::get(Runner &run) const
	{
		return Plum::cake();
	}

	const Any *ReallySpecial::specialCalling(Runner &run, const SystemProperty &call) const
	{
		return specialCalling(run, (const Constant &)(call));
	}

	const Any *ReallySpecial::specialCalling(Runner &run, const JuceName &method) const
	{
		return nullptr;
	}

	const Any *ReallySpecial::specialPlus(Runner &run, const Any &argument) const
	{
		return nullptr;
	}

	const Any *ReallySpecial::specialMinus(Runner &run, const Any &argument) const
	{
		return nullptr;
	}

	juce::Graphics *ReallySpecial::as_Graphics() const
	{
		return nullptr;
	}

	const Any *BuiltinClicheOperationPlus::specialOperation(Runner &run, const ReallySpecial &special, const Any &operand) const
	{
		return special.specialPlus(run, operand);
	}

	const Any *BuiltinClicheOperationMinus::specialOperation(Runner &run, const ReallySpecial &special, const Any &operand) const
	{
		return special.specialMinus(run, operand);
	}

	const Any *ClicheTiny::specialOperation(Runner &run, const ReallySpecial &special, const Any &argument) const
	{
		return special.specialCalling(run, *head, argument);
	}

	const Any *ClicheTiny::specialOperation(Runner &run, const ReallySpecial &special, const Any &argument, const Any &assignValue) const
	{
		return nullptr;
	}

	const Any *JuceCliche::specialOperation(Runner &run, const ReallySpecial &special, const Any &argument) const
	{
		return special.specialCalling(run, (JuceName &)*head, argument);
	}

	const Any *ClicheShort::specialCall(Runner &run, const ReallySpecial &special) const
	{
		return special.specialCalling(run, *this);
	}

	const Any *ClicheShort::specialCall(Runner &run, const ReallySpecial &special, const Any &assignValue) const
	{
		return special.specialCalling(run, *this, assignValue);
	}

	const Any *ReallySpecial::specialCalling(Runner &run, const Constant &name, const Any &arg) const
	{
		return nullptr;
	}

	const Any *ReallySpecial::specialCalling(Runner &run, const Constant &name) const
	{
		return nullptr;
	}

	bool ReallySpecial::specialComparing(const IdentifierLookup &lookup) const
	{
		return false;
	}

	bool ReallySpecial::isIdentifier() const
	{
		return false;
	}

	bool ReallySpecial::specialComparing(const FileNameLookup &lookup) const
	{
		return false;
	}

	bool ReallySpecial::specialComparing(const JuceLookup &lookup) const
	{
		return false;
	}

	bool ReallySpecial::converting(JuceSpecialConverter &converter) const
	{
		return false; //TODO
	}

	const Any *ReallySpecial::specialCalling(Runner &run, const JuceName &method, const Any &arg) const
	{
		return nullptr;
	}

	const Any *TypecheckLanguage::get(Runner &run) const
	{
		return PilsString::get("english"); //TODO
	}

	void Namespace_Juce::initialize()
	{
		singleton =
			new (Heap::allocate(sizeof(PilsString) + 16 * sizeof(PILS_CHAR)))
			Namespace_Juce(_PS("pils.org/ns/juce"), 16);
		opengl_singleton =
			new (Heap::allocate(sizeof(PilsString) + 18 * sizeof(PILS_CHAR)))
			Namespace_Juce(_PS("pils.org/ns/opengl"), 18);
	}

	const ClicheShort *Namespace_Juce::newCliche(const Constant *&link, const Constant *a) const
	{
		const PilsString *name = a->as_String();
		if (name) return new (Heap::allocate(sizeof(JuceName))) JuceName(link, this, name);
		else return new (Heap::allocate(sizeof(ClicheShort))) ClicheShort(link, this, a);
	}

	bool JuceSpecialConverter::convert(const ReallySpecial &argument)
	{
		return argument.converting(*this);
	}

	bool JuceSpecialConverter::converting(const FileName &argument)
	{
		return false;
	}

	bool JuceSpecialConverter::converting(const Timestamp &argument)
	{
		return false;
	}

	bool JuceSpecialConverter::converting(const JuceReference &argument)
	{
		return false;
	}

	const Any *JuceName::specialCall(Runner &run, const ReallySpecial &special) const
	{
		return special.specialCalling(run, *this);
	}

	const JuceName *JuceName::get(const char *name)
	{
		return Namespace_Juce::singleton->get(name);
	}

	const JuceName *Namespace_Juce::get(const char *name) const
	{
		addReference();
		return (const JuceName *)clichefy(PilsString::get(name));
	}

	size_t JuceName::unlinkAndGetSize()
	{
		unhash();
		head->unduplicateReference();
		attributes[0]->releaseFrom(*this);
		return sizeof(JuceName);
	}

	const ClicheTiny *JuceName::newCliche() const
	{
		return new (Heap::allocate(sizeof(JuceCliche))) JuceCliche(this);
	}

	const JuceCliche *JuceCliche::get(const char *name)
	{
		return (const JuceCliche*) JuceName::get(name)->clichefy();
	}

	bool ListConstant::recognize(Recognizer &recognizer) const
	{
		return recognizer.recognizing((const Any *const *)element, count->value);
	}

	bool ListExpress::recognize(Recognizer &recognizer) const
	{
		return recognizer.recognizing(element, count->value);
	}

	bool PilsString::recognize(Recognizer &recognizer) const
	{
		return recognizer.recognizing(*this);
	}

	bool PilsColor::recognize(Recognizer &recognizer) const
	{
		return recognizer.recognizing(*this);
	}

	bool Integer::recognize(Recognizer &recognizer) const
	{
		return recognizer.recognizing(value);
	}

	bool Float::recognize(Recognizer &recognizer) const
	{
		return recognizer.recognizing(value);
	}


    bool ReallySpecial::specialComparing(const PlugLibraryLookup&) const
    {
        return false;
    }

    bool ReallySpecial::specialComparing(const PlugObjectLookup&) const
    {
        return false;
    }

    void* Plumcake::loadPlugin(const PilsString&) const
    {
        return nullptr;
    }
}
