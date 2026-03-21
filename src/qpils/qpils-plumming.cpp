/* This file is public domain */
// #include "qpils-standard-specials.h"
#include "qpils-plumming.h"
namespace PILS
{
    const Namespace_Qt *Namespace_Qt::singleton;
    const Namespace_QtClass *Namespace_QtClass::singleton;

    const HashedConstant *SingletonSpecial::dummyHashLink = nullptr;
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
        Namespace_Qt::initialize();
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

    const Any *ReallySpecial::specialCalling(Runner &run, const QtName &method) const
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

    const Any *QtCliche::specialOperation(Runner &run, const ReallySpecial &special, const Any &argument) const
	{
        return special.specialCalling(run, (QtName &)*head, argument);
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

    bool ReallySpecial::converting(QtSpecialConverter &converter) const
	{
		return false; //TODO
	}

    const Any *ReallySpecial::specialCalling(Runner &run, const QtName &method, const Any &arg) const
	{
        return nullptr;
	}

	const Any *TypecheckLanguage::get(Runner &run) const
	{
		return PilsString::get("english"); //TODO
	}

    void Namespace_Qt::initialize()
	{
        const PILS_CHAR* uri = _PS("pils.org/ns/qt");
        size_t c = std::char_traits<PILS_CHAR>::length(uri);
        singleton = new (c * sizeof(PILS_CHAR)) Namespace_Qt(uri, c);
	}

    void Namespace_QtClass::initialize()
    {
        const PILS_CHAR* uri = _PS("pils.org/ns/qtclass");
        size_t c = std::char_traits<PILS_CHAR>::length(uri);
        singleton = new (c * sizeof(PILS_CHAR)) Namespace_QtClass(uri, c);
    }

    const ClicheShort *Namespace_Qt::newCliche(const HashedConstant *&link, const Constant *a) const
	{
		const PilsString *name = a->as_String();
        if (name) return new const QtName(link, this, name);
        else return PilsString::newCliche(link, a);
	}

    const ClicheShort *Namespace_QtClass::newCliche(
        const HashedConstant *&link,
        const Constant *a) const
    {
        if (const PilsString *name = a->as_String())
        {
            QByteArray qtname("Q");
            qtname.append(name->value, name->count->value);

            int id = QMetaType::fromName(qtname.constData()).id();

            if (id != QMetaType::UnknownType)
                return new const QtClassName(link, this, name, id);
        }
        return PilsString::newCliche(link, a);
    }

    bool QtSpecialConverter::convert(const ReallySpecial &argument)
	{
		return argument.converting(*this);
	}

    bool QtSpecialConverter::converting(const FileName &argument)
	{
		return false;
	}

    bool QtSpecialConverter::converting(const Timestamp &argument)
	{
		return false;
	}

    bool QtSpecialConverter::converting(const QtReference &argument)
	{
		return false;
	}

    const Any *QtName::specialCall(Runner &run, const ReallySpecial &special) const
	{
		return special.specialCalling(run, *this);
	}

    const QtName *QtName::get(const char *name)
	{
        return Namespace_Qt::singleton->get(name);
	}

    const QtName *Namespace_Qt::get(const char *name) const
	{
		addReference();
        return (const QtName *)clichefy(PilsString::get(name));
	}

    size_t QtName::unlinkAndGetSize()
	{
		unhash();
		head->unduplicateReference();
		attributes[0]->releaseFrom(*this);
        return sizeof(QtName);
    }

    size_t QtClassName::unlinkAndGetSize()
    {
        unhash();
        head->unduplicateReference();
        attributes[0]->releaseFrom(*this);
        return sizeof(QtClassName);
    }

    const ClicheTiny *QtName::newCliche() const
	{
        return new const QtCliche(this);
	}

    const QtCliche *QtCliche::get(const char *name)
	{
        return (const QtCliche*) QtName::get(name)->clichefy();
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

    bool QtClassNameQPoint::construct(const Any **args, int argc, QVariant &value)
    {
        if (argc != 2)
            return false;

        int x, y;

        if (!fill(args[0], x)) return false;
        if (!fill(args[1], y)) return false;

        value = QVariant::fromValue(QPoint(x, y));
        return true;
    }

    bool QtClassNameQSize::construct(const Any **args, int argc, QVariant &value)
    {
        if (argc != 2)
            return false;

        int w, h;

        if (!fill(args[0], w)) return false;
        if (!fill(args[1], h)) return false;

        value = QVariant::fromValue(QSize(w, h));
        return true;
    }

    bool QtClassNameQRect::construct(const Any **args, int argc, QVariant &value)
    {
        if (argc != 4)
            return false;

        int x, y, w, h;

        if (!fill(args[0], x)) return false;
        if (!fill(args[1], y)) return false;
        if (!fill(args[2], w)) return false;
        if (!fill(args[3], h)) return false;

        value = QVariant::fromValue(QRect(x, y, w, h));
        return true;
    }

    bool QtClassNameQColor::construct(const Any **args, int argc, QVariant &value)
    {
        if (argc == 1)
        {
            QString s;
            if (!fill(args[0], s))
                return false;

            QColor c(s);
            if (!c.isValid())
                return false;

            value = QVariant::fromValue(c);
            return true;
        }

        if (argc == 3 || argc == 4)
        {
            int r,g,b,a = 255;

            if (!fill(args[0], r)) return false;
            if (!fill(args[1], g)) return false;
            if (!fill(args[2], b)) return false;

            if (argc == 4 && !fill(args[3], a))
                return false;

            value = QVariant::fromValue(QColor(r,g,b,a));
            return true;
        }

        return false;
    }

    bool QtClassNameQDateTime::construct(const Any **args, int argc, QVariant &value)
    {
        // TODO:
        // Mulige konstruktioner:
        // DateTime timestamp
        // DateTime "2025-03-12T12:30:00"

        (void)args;
        (void)argc;
        (void)value;
        return false;
    }

    bool QtClassNameQTransform::construct(const Any **args, int argc, QVariant &value)
    {
        // TODO:
        // sandsynlig konstruktion:
        // Transform m11 m12 m13 m21 m22 m23 m31 m32 m33

        (void)args;
        (void)argc;
        (void)value;
        return false;
    }

    bool QtValueClassName::fill(const Any *a, int &out)
    {
        if (const Integer *i = a->as_Integer())
        {
            out = (int)i->value;
            return true;
        }

        // if (const Float *f = a->as_Float())
        // {
        //     out = (int)f->value;
        //     return true;
        // }

        return false;
    }

    bool QtValueClassName::fill(const Any *a, double &out)
    {
        // if (const Float *f = a->as_Float())
        // {
        //     out = f->value;
        //     return true;
        // }

        if (const Integer *i = a->as_Integer())
        {
            out = (double)i->value;
            return true;
        }

        return false;
    }

    bool QtValueClassName::fill(const Any *a, QString &out)
    {
        if (const PilsString *s = a->as_String())
        {
            out = QString::fromUtf8(s->value, s->count->value);
            return true;
        }

        // if (const QtValueWrapper *w = a->as_QtValue())
        // {
        //     if (w->variant.metaType().id() == QMetaType::QString)
        //     {
        //         out = w->variant.toString();
        //         return true;
        //     }
        // }

        return false;
    }

    bool QtValueClassName::fill(const Any *a, QByteArray &out)
    {
        if (const PilsString *s = a->as_String())
        {
            out = QByteArray(s->value, s->count->value);
            return true;
        }

        // if (const QtValueWrapper *w = a->as_QtValue())
        // {
        //     if (w->variant.metaType().id() == QMetaType::QByteArray)
        //     {
        //         out = w->variant.toByteArray();
        //         return true;
        //     }
        // }

        return false;
    }

    bool QtValueClassName::fill(const Any *a, QColor &out)
    {
        // if (const QtValueWrapper *w = a->as_QtValue())
        // {
        //     if (w->variant.metaType().id() == QMetaType::QColor)
        //     {
        //         out = w->variant.value<QColor>();
        //         return true;
        //     }
        // }

        // string farvenavn (#ff00ff, "red" osv.)
        if (const PilsString *s = a->as_String())
        {
            QString name = QString::fromUtf8(s->value, s->count->value);
            QColor c(name);

            if (c.isValid())
            {
                out = c;
                return true;
            }
        }

        return false;
    }

    bool QtValueClassName::fill(const Any *a, QImage &out)
    {
        // if (const QtValueWrapper *w = a->as_QtValue())
        // {
        //     if (w->variant.metaType().id() == QMetaType::QImage)
        //     {
        //         out = w->variant.value<QImage>();
        //         return true;
        //     }
        // }

        if (const PilsString *s = a->as_String())
        {
            QImage img;
            if (img.loadFromData((const uchar*)s->value, s->count->value))
            {
                out = img;
                return true;
            }
        }

        return false;
    }

    bool QtValueClassName::fill(const Any *a, QObject* &out)
    {
        // if (const QtObjectWrapper *w = a->as_QtObject())
        // {
        //     out = w->object;
        //     return true;
        // }

        return false;
    }
}

