/* This file is public domain */
#ifndef _JPILS_PLUMMING_H_
#define _JPILS_PLUMMING_H_

#include "writing.h"
#include <juce_gui_basics/juce_gui_basics.h>
class PlugCompilable;
class PlugObject;

namespace PILS
{
	const PilsString *pils(const juce::String &string);
	const Constant *pils(const juce::Time &time);
	long long longlongtime(::juce::Time time);

	class PilsGraph;
	class PilsFont;

	class Recognizer
	{
	public:
		virtual bool recognizing(const Any *const *elements, size_t count){return false;}
		virtual bool recognizing(const PilsString &text){return false;}
		virtual bool recognizing(const PilsColor &color){return false;}
		virtual bool recognizing(long number){return recognizing((double)number);}
		virtual bool recognizing(double number){return false;}
		virtual bool recognizing(const PlugCompilable &thing){return false;}
		virtual bool recognizing(const PilsGraph &thing){return false;}
		virtual bool recognizing(const PilsFont &thing){return false;}
		virtual bool recognizing(const juce::Path &thing){return false;}
		virtual bool recognizing(const juce::Colour &thing){return false;}
		virtual bool recognizing(const juce::ColourGradient &thing){return false;}
		virtual bool recognizing(const juce::Image &thing){return false;}
		virtual bool recognizing(const juce::Drawable &thing){return false;}
	};

	class JuceName;
	class JuceSpecialConverter;
	class JuceReference;
	class JuceLookup;
	class Identifier;
	class IdentifierLookup;
	class FileNameLookup;
	class FileName;
	class Timestamp;
	class ThreadLookup;
	class PlugLibraryLookup;
	class PlugObjectLookup;

	class ReallySpecial
		: public Special
	{
	public:
		using Special::specialCalling;
        virtual const Any *specialCalling(Runner &run, const Constant &name, const Any &args) const;
        const Any *specialCalling(Runner &run, const Constant &name) const override;
        virtual const Any *specialPlus(Runner &run, const Any &operand) const;
        virtual const Any *specialMinus(Runner &run, const Any &operand) const;
		// standard extended types: Timestamp, Identifier
        virtual bool specialComparing(const IdentifierLookup &lookup) const;
        virtual bool isIdentifier() const;
		// recognize Graphics for rendering
        virtual juce::Graphics *as_Graphics() const;
		// Simple file operations
        virtual bool specialComparing(const FileNameLookup &lookup) const;
		// PILS system properties
        virtual const Any *specialCalling(Runner &run, const SystemProperty &call) const;
		// JUCE calls
        virtual const Any *specialCalling(Runner &run, const JuceName &method, const Any &arg) const;
        virtual const Any *specialCalling(Runner &run, const JuceName &method) const;
        virtual bool specialComparing(const JuceLookup &lookup) const;
        virtual bool converting(JuceSpecialConverter &converter) const;
		// Threads
        virtual bool specialComparing(const ThreadLookup &lookup) const;
		// Plugin loader
        virtual void *loadPlugin(const PilsString &name) const;
        virtual bool specialComparing(const PlugLibraryLookup &lookup) const;
        virtual bool specialComparing(const PlugObjectLookup &lookup) const;
	protected:
		ReallySpecial(const HashedConstant *&link) : Special(link) {}
		ReallySpecial() : Special() {}
	};

	// Singleton specials are inserted in a dummy hash chain
	class SingletonSpecial
		: public ReallySpecial
	{
	protected:
		SingletonSpecial()
			: ReallySpecial(dummyHashLink)
		{}
	private:
		static const HashedConstant *dummyHashLink;
	};

	class Plumcake
		: public SingletonSpecial
	{
	public:
        size_t unlinkAndGetSize() override;
        size_t hash() const;
        bool specialCompare(const ReallySpecial *special) const;
        const Any *specialCalling(Runner &run, const Constant &name, const Any &args) const override;
        const Any *specialCalling(Runner &run, const Constant &name) const override;
        const Any *specialCalling(Runner &run, const SystemProperty &call) const override;
        const Any *specialCalling(Runner &run, const JuceName &method, const Any &args) const override;
        const Any *specialCalling(Runner &run, const JuceName &method) const override;
        const Any *specialCalling(Runner &run, const Strap &call) const override;
        void *loadPlugin(const PilsString &name) const override;
	private:
        void write(Writing &writing) const override;
		Plumcake();
		friend class Plum;
	};

	/* namespace URIs */

	class Namespace_Juce
		: public PilsString
	{
	public:
		static const Namespace_Juce *singleton;
		static const Namespace_Juce *opengl_singleton;
        const ClicheShort *newCliche(const HashedConstant *&link, const Constant *a) const override;
        const JuceName *get(const char *name) const;
		static void initialize();
	private:
		friend class Plumcake;
		Namespace_Juce(const PILS_CHAR *text, size_t count)
			:  PilsString(text, count)
		{}
	};

	class JuceClass;
	class JuceMethod;
	class JuceName
		: public ClicheShort
	{
	public:
		JuceName(const HashedConstant *&link, const Namespace_Juce *h, const PilsString *a)
			: ClicheShort(link, h, a), methods(NULL), staticAccessor(NULL), typecheck(&Converter::dummy)
		{}
		static const JuceName *get(const char *name);
		const JuceMethod *methods;
		const JuceReference *staticAccessor;
        size_t unlinkAndGetSize() override;
        const ClicheTiny *newCliche() const override;
        const Any *specialCall(Runner &run, const ReallySpecial &special) const override;
        void compileTypecheck(Compiling &compiling, const CallWho &pattern) const override;
	private:
		friend class JuceClass;
		Converter *typecheck;
	};

	class JuceCliche
		: public ClicheTiny
	{
	public:
		JuceCliche(const JuceName *head)
			: ClicheTiny(head)
		{}
        const Any *specialOperation(Runner &run, const ReallySpecial &special, const Any &argument) const override;
		static const JuceCliche *get(const char *jame);
	};

	/* converters */

	class JuceSpecialConverter
		: public Converter
	{
	public:
        bool convert(const ReallySpecial &argument) override;
        virtual bool converting(const JuceReference &argument);
        virtual bool converting(const Timestamp &argument);
        virtual bool converting(const FileName &argument);
	};
}
#endif
