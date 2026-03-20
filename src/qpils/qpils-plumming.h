/* This file is public domain */
#pragma once
#include <qstring.h>
#include <QDateTime>
#include <QColor>
#include <QRect>
#include <QSize>
#include <QImage>
#include "writing.h"
class PlugCompilable;
class PlugObject;

namespace PILS
{
    const PilsString *pils(const QString &string);
    const Constant *pils(const QDateTime &time);
    long long longlongtime(QDateTime time);

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
        // virtual bool recognizing(const juce::Path &thing){return false;}
        // virtual bool recognizing(const juce::Colour &thing){return false;}
        // virtual bool recognizing(const juce::ColourGradient &thing){return false;}
        // virtual bool recognizing(const juce::Image &thing){return false;}
        // virtual bool recognizing(const juce::Drawable &thing){return false;}
	};

	class QtName;
	class QtSpecialConverter;
	class QtReference;
	class QtLookup;
	class Identifier;
	class IdentifierLookup;
	class FileNameLookup;
	class FileName;
	class Timestamp;
	class ThreadLookup;

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
		// Simple file operations
        virtual bool specialComparing(const FileNameLookup &lookup) const;
		// PILS system properties
        virtual const Any *specialCalling(Runner &run, const SystemProperty &call) const;
		// Qt calls
        virtual const Any *specialCalling(Runner &run, const QtName &method, const Any &arg) const;
        virtual const Any *specialCalling(Runner &run, const QtName &method) const;
        virtual bool specialComparing(const QtLookup &lookup) const;
        virtual bool converting(QtSpecialConverter &converter) const;
		// Threads
        virtual bool specialComparing(const ThreadLookup &lookup) const;
		// Plugin loader
        // virtual void *loadPlugin(const PilsString &name) const;
        // virtual bool specialComparing(const PlugLibraryLookup &lookup) const;
        // virtual bool specialComparing(const PlugObjectLookup &lookup) const;
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
        // const Any *specialCalling(Runner &run, const QtName &method, const Any &args) const override;
        // const Any *specialCalling(Runner &run, const QtName &method) const override;
        const Any *specialCalling(Runner &run, const Strap &call) const override;
        // void *loadPlugin(const PilsString &name) const override;
	private:
        void write(Writing &writing) const override;
		Plumcake();
		friend class Plum;
	};

	/* namespace URIs */

    class Namespace_Qt
        : public PilsString
    {
    public:
        static const Namespace_Qt *singleton;
        const ClicheShort *newCliche(const HashedConstant *&link, const Constant *a) const override;
        const QtName *get(const char *name) const;
        static void initialize();
    private:
        friend class Plumcake;
        Namespace_Qt(const PILS_CHAR *text, size_t count)
            :  PilsString(text, count)
        {}
    };

    class Namespace_QtClass
        : public PilsString
    {
    public:
        static const Namespace_QtClass *singleton;
        const ClicheShort *newCliche(const HashedConstant *&link, const Constant *a) const override;
        const QtName *get(const char *name) const;
        static void initialize();
    private:
        // friend class Plumcake;
        Namespace_QtClass(const PILS_CHAR *text, size_t count)
            :  PilsString(text, count)
        {}
    };

	class QtClass;
	class QtMethod;

	class QtName
		: public ClicheShort
	{
	public:
		QtName(const HashedConstant *&link, const Namespace_Qt *h, const PilsString *a)
            : ClicheShort(link, h, a),
            // methods(NULL), staticAccessor(NULL),
            typecheck(&Converter::dummy)
		{}
        static const QtName *get(const char *name);
        // const QtMethod *methods;
        // const QtReference *staticAccessor;
        size_t unlinkAndGetSize() override;
        const ClicheTiny *newCliche() const override;
        const Any *specialCall(Runner &run, const ReallySpecial &special) const override;
        // void compileTypecheck(Compiling &compiling, const CallWho &pattern) const override;
	private:
        // friend class QtClass;
        Converter *typecheck;
	};

    class QtClassName
        : public ClicheShort
    {
    public:
        QtClassName(const HashedConstant *&link,
                    const Namespace_QtClass *h,
                    const PilsString *a,
                    int metaTypeId)
            : ClicheShort(link, h, a),
            typecheck(&Converter::dummy)
        {}
        // static const QtClassName *get(const char *name);

        size_t unlinkAndGetSize() override;
        // const ClicheTiny *newCliche() const override;
        // const Any *specialCall(Runner &run, const ReallySpecial &special) const override;
        // void compileTypecheck(Compiling &compiling, const CallWho &pattern) const override;

    protected:
        QtClassName(const char *name)
            : ClicheShort(Namespace_QtClass::singleton, PilsString::get(name))
        {}
        // friend class QtClass;
        int metaTypeId;   // cached Qt metatype id
        Converter *typecheck;
    };

    class QtWrapper
        : public ReallySpecial
    {
    public:
        const QtClassName *className;
        size_t unlinkAndGetSize() override;
    };

    class QtValueWrapper
        : public QtWrapper
    {
    public:
        QVariant variant;
        size_t unlinkAndGetSize() override;
    };

    class QtObjectWrapper
        : public QtWrapper
    {
    public:
        QObject *object;
        size_t unlinkAndGetSize() override;
    };

    class QtValueClassName
        : public QtClassName
    {
    protected:
        QtValueClassName(const char *name)
            : QtClassName(name)
        {}
        virtual bool construct(const Any **args, int argc, QVariant &value) = 0;
        const QtValueWrapper *constructAndWrap(const Any **args, int argc);
        static bool fill(const Any *a, int &out);
        static bool fill(const Any *a, double &out);
        static bool fill(const Any *a, QString &out);
        static bool fill(const Any *a, QByteArray &out);
        static bool fill(const Any *a, QColor &out);
        static bool fill(const Any *a, QImage &out);
        static bool fill(const Any *a, QObject* &out);
    };

    class QtClassNameQPoint : public QtValueClassName
    {
    public:
        QtClassNameQPoint() : QtValueClassName("Point") {};
        bool construct(const Any **args, int argc, QVariant &value) override;
    };

    class QtClassNameQSize : public QtValueClassName
    {
    public:
        QtClassNameQSize() : QtValueClassName("Size") {};
        bool construct(const Any **args, int argc, QVariant &value) override;
    };

    class QtClassNameQRect : public QtValueClassName
    {
    public:
        QtClassNameQRect() : QtValueClassName("Rect") {};
        bool construct(const Any **args, int argc, QVariant &value) override;
    };

    class QtClassNameQColor : public QtValueClassName
    {
    public:
        QtClassNameQColor() : QtValueClassName("Color") {};
        bool construct(const Any **args, int argc, QVariant &value) override;
    };

    class QtClassNameQImage : public QtValueClassName
    {
    public:
        QtClassNameQImage() : QtValueClassName("Image") {};
        bool construct(const Any **args, int argc, QVariant &value) override;
    };

    class QtClassNameQTransform : public QtValueClassName
    {
    public:
        QtClassNameQTransform() : QtValueClassName("Transform") {};
        bool construct(const Any **args, int argc, QVariant &value) override;
    };

    class QtClassNameQString : public QtValueClassName
    {
    public:
        QtClassNameQString() : QtValueClassName("String") {};
        bool construct(const Any **args, int argc, QVariant &value) override;
    };

    class QtClassNameQByteArray : public QtValueClassName
    {
    public:
        QtClassNameQByteArray() : QtValueClassName("ByteArray") {};
        bool construct(const Any **args, int argc, QVariant &value) override;
    };

    class QtClassNameQDateTime : public QtValueClassName
    {
    public:
        QtClassNameQDateTime() : QtValueClassName("DateTime") {};
        bool construct(const Any **args, int argc, QVariant &value) override;
    };

    class QtCliche
		: public ClicheTiny
	{
	public:
		QtCliche(const QtName *head)
			: ClicheTiny(head)
		{}
        const Any *specialOperation(Runner &run, const ReallySpecial &special, const Any &argument) const override;
		static const QtCliche *get(const char *jame);
	};

	/* converters */

	class QtSpecialConverter
		: public Converter
	{
	public:
        bool convert(const ReallySpecial &argument) override;
        virtual bool converting(const QtReference &argument);
        virtual bool converting(const Timestamp &argument);
        virtual bool converting(const FileName &argument);
	};
}

