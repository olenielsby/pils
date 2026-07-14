/* This file is public domain */
#pragma once
#include <qstring.h>
#include <QDateTime>
#include <QColor>
#include <QRect>
#include <QSize>
#include <QImage>
#include <QPushButton>
#include <QWidget>
#include <QWindow>
#include <QMainWindow>
#include <QPointer>
#include <QMetaMethod>

#include "writing.h"
class PlugCompilable;
class PlugObject;
namespace PILS
{
    class QtObjectWrapper;
    class QtSignalCliche;
    class QtEventCliche;

    const PilsString *pils(const QString &string);
    const Constant *pils(const QDateTime &time);
    long long longlongtime(QDateTime time);

	class PilsGraph;
	class PilsFont;
    class NodeEmbeddedQValueType;

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

    class QtClassName;
    class QtMethodName;
    class QtSignalName;
    class QtValueClassName;
    class QtObjectClassName;
    class PlatformSpecificConverter;
	class QtLookup;
	class Identifier;
	class IdentifierLookup;
	class FileNameLookup;
	class FileName;
	class Timestamp;
	class ThreadLookup;
    class QtObjectLookup;

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
        virtual bool specialComparing(const QtObjectLookup &lookup) const;
        // PILS system properties
        virtual const Any *specialCalling(Runner &run, const SystemProperty &call) const;
		// Qt calls
        virtual const Any *specialCalling(Runner &run, const QtMethodName &method, const Any &arg) const;
        virtual const Any *specialCalling(Runner &run, const QtMethodName &method) const;
        virtual const Any *specialCalling(Runner &run, const QtObjectClassName &objectClass, const Any &args) const;
        virtual const Any *specialCalling(Runner &run, const QtObjectClassName &objectClass) const;

        virtual bool specialComparing(const QtLookup &lookup) const;
        virtual bool converting(PlatformSpecificConverter &converter) const;
		// Threads
        virtual bool specialComparing(const ThreadLookup &lookup) const;
        virtual const Any *specialWhen(Runner &run, const Any &argument) const;
		// Plugin loader
        // virtual void *loadPlugin(const PilsString &name) const;
        // virtual bool specialComparing(const PlugLibraryLookup &lookup) const;
        // virtual bool specialComparing(const PlugObjectLookup &lookup) const;
	protected:
        ReallySpecial(const Constant *&link) : Special(link) {}
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
        static const Constant *dummyHashLink;
	};

    class Plumcake
		: public SingletonSpecial
	{
	public:
        using SingletonSpecial::specialCalling;
        const Any *specialCalling(Runner &run, const Constant &name, const Any &args) const override;
        const Any *specialCalling(Runner &run, const Constant &name) const override;
        const Any *specialCalling(Runner &run, const SystemProperty &call) const override;
        const Any *specialCalling(Runner &run, const Strap &call) const override;
        const Any *specialCalling(Runner &run, const QtObjectClassName &objectClass) const override;
        const Any *specialCalling(Runner &run, const QtObjectClassName &objectClass, const Any &args) const override;
        // void *loadPlugin(const PilsString &name) const override;
	private:
        void write(Writing &writing) const override;
		Plumcake();
		friend class Plum;
	};

	/* namespace URIs */

    class Namespace_QtMethod
        : public PilsString
    {
    public:
        using PilsString::newCliche;
        static const Namespace_QtMethod *singleton;
        const ClicheShort *newCliche(const Constant *&link, const Constant *a) const override;
        const QtMethodName *get(const char *name) const;
        static void initialize();
    private:
        friend class Plumcake;
        Namespace_QtMethod(const PILS_CHAR *text, size_t count)
            :  PilsString(text, count)
        {}
    };

    class Namespace_QtSignal
        : public PilsString
    {
    public:
        using PilsString::newCliche;
        static const Namespace_QtSignal *singleton;
        const ClicheShort *newCliche(const Constant *&link, const Constant *a) const override;
        static void initialize();
    private:
        friend class Plumcake;
        Namespace_QtSignal(const PILS_CHAR *text, size_t count)
            :  PilsString(text, count)
        {}
    };

    class Namespace_QtClass
        : public PilsString
    {
    public:
        using PilsString::newCliche;
        static const Namespace_QtClass *singleton;
        const ClicheShort *newCliche(const Constant *&link, const Constant *a) const override;
        static void initialize();
    private:
        // friend class Plumcake;
        Namespace_QtClass(const PILS_CHAR *text, size_t count)
            :  PilsString(text, count)
        {}
    };

    class QtClassName
        : public ClicheShort
    {
    public:
    static const char *withoutLeadingQ(const char *name)
        {
            return name+(name[0]=='Q');
        }
    protected:
        QtClassName(const Constant *&link,
                    const Namespace_QtClass *h,
                    const PilsString *a)
            : ClicheShort(link, h, a)
        {}
        QtClassName(const char *name)
            : ClicheShort(Namespace_QtClass::singleton, PilsString::get(name))
        {}
    };

    struct QtConstructorImplementation;

    class QtObjectClassName
        : public QtClassName
    {
    public:
        QtObjectClassName(
            const Constant *&link,
            const Namespace_QtClass *h,
            const PilsString *a,
            const QMetaObject *meta):
            QtClassName(link, h, a),
            meta(meta),
            constructors(nullptr)
        {
        }
        const Any *specialCall(Runner &run, const ReallySpecial &special) const override;
        const ClicheTiny *newCliche() const override;
        mutable const QMetaObject *meta;
        mutable const QtConstructorImplementation *constructors;
    private:
        friend class Plumcake;
        static void initialize();
        static const QtObjectClassName *registerQtClass(const char *name, const QMetaObject &meta);
        QObject* createQObject(const Any *const argv[], size_t argc) const;
    };

    class QtMethodName
		: public ClicheShort
	{
    public:
        QtMethodName(const Constant *&link, const Namespace_QtMethod *h, const PilsString *a)
            : ClicheShort(link, h, a)
		{}
        static const QtMethodName *get(const char *name);
        const ClicheTiny *newCliche() const override;
        const Any *specialCall(Runner &run, const ReallySpecial &special) const override;
        using Invoker = std::function<bool(QObject*, const Any *const *, size_t, const Any*&)>;
        struct Implementation {
            const QMetaObject * meta;
            const ClicheShort * exactClassName;
            Invoker invoker;
            Implementation * next;
        };
        // void compileTypecheck(Compiling &compiling, const CallWho &pattern) const override;
        mutable Implementation *implementationChain = nullptr;
        const QtMethodName *implement(const QMetaObject *meta, Invoker invoker, const char *className) const
        {
            const ClicheShort *pilsClassName = nullptr;
            if (className != nullptr)
            {
                pilsClassName = Namespace_QtClass::singleton->clichefy(PilsString::get(QtClassName::withoutLeadingQ(className)));
            }
            implementationChain =
                new Implementation{meta, pilsClassName, std::move(invoker), implementationChain};
            return this;
        }
	};

    class QtSignalName
        : public ClicheShort
    {
    public:
        QtSignalName(const Constant *&link, const Namespace_QtSignal *h, const PilsString *a)
            : ClicheShort(link, h, a)
        {}
        static const QtSignalName *get(const char *name);
        const ClicheTiny *newCliche() const override;
    };

    class QtValueClassName
        : public QtClassName
    {
    public:
        static void initialize();
        virtual const PlatformSpecializedNodeConstantTiny *newSpecializedNode(const Constant *&link, const ClicheTiny &cliche, const PilsString *value) const
        {return nullptr;}
        virtual const PlatformSpecializedNodeConstantTiny *newSpecializedNode(const Constant *&link, const ClicheTiny &cliche, const ListConstant *value) const
        {return nullptr;}
    protected:
        QtValueClassName(const char *name)
            : QtClassName(name)
        {}
        const ClicheTiny *newCliche() const override;
    };

    struct QtGenericArgumentWithStorage
    {
        QGenericArgument genericArgument;
        union
        {
            int int_;
            double double_;
            QObject* obj;
        };
    };

    class QtMethodCliche
		: public ClicheTiny
	{
	public:
        QtMethodCliche(const QtMethodName *head)
			: ClicheTiny(head)
		{}
        const Any *specialOperation(Runner &run, const ReallySpecial &special, const Any &argument) const override;
        static const QtMethodCliche *get(const char *name);
    };

    class QtObjectClassCliche
        : public ClicheTiny
    {
    public:
        QtObjectClassCliche(const QtObjectClassName *head)
            : ClicheTiny(head)
        {}
        const Any *specialOperation(Runner &run, const ReallySpecial &special, const Any &argument) const override;
    };

    class QtObjectLookup
        : public SpecialLookup
    {
    public:
        QtObjectLookup(Runner &run, QObject *object, const QtObjectClassName *className = nullptr)
            : object(object), className(className), run(run)
        {}
        const ReallySpecial *newSpecial(const Constant *&link) override;
        bool compare(const ReallySpecial &special) const override;
        size_t hash() const override;
        QObject *object;
        const QtObjectClassName *className;
        Runner &run;
    private:
        const QtObjectClassName *getClassNameFromQObjectInsideLock(QObject *object);
    };
}
