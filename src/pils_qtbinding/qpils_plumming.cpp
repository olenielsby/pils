/* This file is public domain */
// #include "qpils-standard-specials.h"
#include "qpils_plumming.h"
#include "qpils_event.h"
#include "qpils_qobject_wrapper.h"
#include <QIODevice>
#include "initializers.h"

namespace PILS
{
    std::unordered_map<const PilsString *,Namespace*> Namespace::map;
    const Namespace_QtMethod Namespace_QtMethod::singleton("pils.org/ns/qtmethod");
    const Namespace_QtSignal Namespace_QtSignal::singleton("pils.org/ns/qtsignal");
    const Namespace_QtClass Namespace_QtClass::singleton("pils.org/ns/qtclass");
    const PilsString *QtEventCliche::namespace_;
    void QtEventCliche::initializeNamespace()
    {
        namespace_ = PilsString::get("pils.org/ns/qtevent");
    }
    Plum Plum::singleton;

    Namespace::Namespace(const char *uriText): uri(PilsString::get(uriText))
    {
        map.emplace(uri, this);
    }

    const Constant *SingletonSpecial::dummyHashLink = nullptr;
	Plum::Plum()
		: plumcake(*new Plumcake())
	{}

	void Plumcake::write(Writing &writing) const
	{
		writing.write((PILS_CHAR)'*');
	}

	Plumcake::Plumcake()
	{
        QtEventCliche::initializeNamespace();
        QtValueClassName::initialize();
        QtObjectClassName::initialize();
        QtEventCliche::initialize();
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

    const ClicheShort *Namespace_QtMethod::newCliche(const Constant *&link, const PilsString *name) const
	{
        return new const QtMethodName(link, uri, name);
	}

    const ClicheShort *Namespace_QtSignal::newCliche(const Constant *&link, const PilsString *name) const
    {
        return new const QtSignalName(link, uri, name);
    }

    const ClicheShort *Namespace_QtClass::newCliche(const Constant *&link, const PilsString *name) const
    {
        return new QtObjectClassName(link, uri, name, nullptr);
    }

    const Any *QtMethodName::specialCall(Runner &run, const ReallySpecial &special) const
	{
		return special.specialCalling(run, *this);
	}

    const QtMethodName *QtMethodName::get(const char *name)
	{
        return Namespace_QtMethod::singleton.get(name);
	}

    const QtMethodName *Namespace_QtMethod::get(const char *name) const
	{
        uri->retain();
        return (const QtMethodName *)uri->clichefy(PilsString::get(name));
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
