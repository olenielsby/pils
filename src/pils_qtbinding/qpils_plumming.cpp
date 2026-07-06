/* This file is public domain */
// #include "qpils-standard-specials.h"
#include "qpils_plumming.h"
#include "qpils_event.h"
#include "qpils_qobject_wrapper.h"
#include <QIODevice>
namespace PILS
{
    const Namespace_QtMethod *Namespace_QtMethod::singleton;
    const Namespace_QtSignal *Namespace_QtSignal::singleton;
    const PilsString *QtEventCliche::namespace_;
    const Namespace_QtClass *Namespace_QtClass::singleton;

    const Constant *SingletonSpecial::dummyHashLink = nullptr;
	Plum::Plum()
		: plumcake(*new Plumcake())
	{}

    void Plumcake::unlink()
	{
        throw L"Plumcake::unlink Reference counter leak";
	}

	void Plumcake::write(Writing &writing) const
	{
		writing.write((PILS_CHAR)'*');
	}

	Plumcake::Plumcake()
	{
        Namespace_QtMethod::initialize();
        Namespace_QtSignal::initialize();
        Namespace_QtClass::initialize();
        QtEventCliche::initializeNamespace();
        QtValueClassName::initialize();
        QtObjectClassName::initialize();
        QtEventCliche::initialize();
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
        call.retain();
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

    const Any *ReallySpecial::specialCalling(Runner &run, const QtMethodName &method) const
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

    const Any *QtMethodCliche::specialOperation(Runner &run, const ReallySpecial &special, const Any &argument) const
	{
        return special.specialCalling(run, (const QtMethodName &)*head, argument);
	}

    const Any *QtObjectClassCliche::specialOperation(Runner &run, const ReallySpecial &special, const Any &argument) const
    {
        return special.specialCalling(run, (const QtObjectClassName &)*head, argument);
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

    bool ReallySpecial::specialComparing(const QtLookup &lookup) const
	{
		return false;
	}

    bool ReallySpecial::converting(PlatformSpecificConverter &converter) const
	{
        return false;
	}

    const Any *ReallySpecial::specialCalling(Runner &run, const QtMethodName &method, const Any &arg) const
	{
        return nullptr;
	}

	const Any *TypecheckLanguage::get(Runner &run) const
	{
		return PilsString::get("english"); //TODO
	}

    void Namespace_QtMethod::initialize()
	{
        const PILS_CHAR* uri = _PS("pils.org/ns/qtmethod");
        size_t c = std::char_traits<PILS_CHAR>::length(uri);
        singleton = new ((c + 1) * sizeof(PILS_CHAR)) Namespace_QtMethod(uri, c);
	}

    void Namespace_QtSignal::initialize()
    {
        const PILS_CHAR* uri = _PS("pils.org/ns/qtsignal");
        size_t c = std::char_traits<PILS_CHAR>::length(uri);
        singleton = new ((c + 1) * sizeof(PILS_CHAR)) Namespace_QtSignal(uri, c);
    }

    void Namespace_QtClass::initialize()
    {
        const PILS_CHAR* uri = _PS("pils.org/ns/qtclass");
        size_t c = std::char_traits<PILS_CHAR>::length(uri);
        singleton = new ((c + 1) * sizeof(PILS_CHAR)) Namespace_QtClass(uri, c);
    }

    void QtEventCliche::initializeNamespace()
    {
        namespace_ = PilsString::get("pils.org/ns/qtevent");
    }

    const ClicheShort *Namespace_QtMethod::newCliche(const Constant *&link, const Constant *a) const
	{
		const PilsString *name = a->as_String();
        if (name) return new const QtMethodName(link, this, name);
        else return PilsString::newCliche(link, a);
	}

    const ClicheShort *Namespace_QtSignal::newCliche(const Constant *&link, const Constant *a) const
    {
        const PilsString *name = a->as_String();
        if (name) return new const QtSignalName(link, this, name);
        else return PilsString::newCliche(link, a);
    }
    // QMetaType::fromName is not reliable
    // so this method is ditched favor of preregistering classes.

    const ClicheShort *Namespace_QtClass::newCliche(
        const Constant *&link,
        const Constant *a) const
    {
        if (const PilsString *name = a->as_String())
        {
            return new QtObjectClassName(link, this, name, nullptr);
        }
        return PilsString::newCliche(link, a);
    }


    const Any *QtMethodName::specialCall(Runner &run, const ReallySpecial &special) const
	{
		return special.specialCalling(run, *this);
	}

    const QtMethodName *QtMethodName::get(const char *name)
	{
        return Namespace_QtMethod::singleton->get(name);
	}

    const QtMethodName *Namespace_QtMethod::get(const char *name) const
	{
        retain();
        return (const QtMethodName *)clichefy(PilsString::get(name));
	}

    const ClicheTiny *QtMethodName::newCliche() const
	{
        return new const QtMethodCliche(this);
	}

    const QtMethodCliche *QtMethodCliche::get(const char *name)
	{
        return (const QtMethodCliche*) QtMethodName::get(name)->clichefy();
	}

    const ClicheTiny *QtObjectClassName::newCliche() const
    {
        return new const QtObjectClassCliche(this);
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

    const Any *ReallySpecial::specialCalling(Runner &run, const QtObjectClassName &className) const
    {
        return nullptr;
    }

    const Any *ReallySpecial::specialCalling(Runner &run, const QtObjectClassName &className, const Any &args) const
    {
        return nullptr;
    }

    bool ReallySpecial::specialComparing(const QtObjectLookup &twin) const
    {
        return false;
    }

    bool QtObjectWrapper::specialComparing(const QtObjectLookup &twin) const
    {
        return twin.object == object.data();
    }

    const Any *QtObjectClassName::specialCall(Runner &run, const ReallySpecial &special) const
    {
        return special.specialCalling(run, *this);
    }

    QObject* QtObjectClassName::createQObject(const Any *const  argv[], size_t argc) const
    {
        for (auto impl = constructors; impl; impl = impl->next)
        {
            if (QObject* obj = impl->construct(argv, argc))
                return obj;
        }
        return nullptr;
    }

    const Any *BuiltinClicheWhen::specialOperation(Runner &run, const ReallySpecial &special, const Any &argument) const
    {
        if (!run.isMainThread())
            return nullptr;
        return special.specialWhen(run, argument);
    }

    const Any *ReallySpecial::specialWhen(Runner &run, const Any &argument) const
    {
        return nullptr;
    }

}
