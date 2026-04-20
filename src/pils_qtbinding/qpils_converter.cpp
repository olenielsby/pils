#include "qpils_converter.h"
#include "qpils_qobject_wrapper.h"
#include "qpils_specialized_node.h"

namespace PILS {


bool PlatformSpecializedNodeConstantTiny::convert(Converter &converter) const
{
    return converter.convert(*this);
}

bool QtConverter::convert(const ReallySpecial &argument)
{
    return argument.converting(*this);
}

bool QtConverter::convert(const PlatformSpecializedNodeConstantTiny &argument)
{
    return argument.converting(*this);
}

// bool QtArgumentConverter::convert(const Integer &argument)
// {
//     switch (type.id())
//     {
//     case QMetaType::Double:
//         ga.double_ = argument.value;
//         ga.genericArgument = QGenericArgument("double", &ga.double_);
//         return true;
//     case QMetaType::Int:
//         ga.int_ = argument.value;
//         ga.genericArgument = QGenericArgument("int", &ga.int_);
//         return true;
//     default:
//         return false;
//     }
// }

QObject *QtConverter::getObject(const QtObjectWrapper &wrap)
{
    return wrap.object;
}

// bool QtArgumentConverter::convert(const Float &argument)
// {
//     if (type.id() == QMetaType::Double)
//     {
//         ga.genericArgument = QGenericArgument("double", &argument.value);
//         return true;
//     }
//     else return false;
// }

// bool QtArgumentConverter::convert(const Timestamp &argument)
// {
//     return false;
// }

// bool QtArgumentConverter::convert(const PilsString &argument)
// {
//     if (type.id() == QMetaType::QString)
//     {
//         if (const PlatformDependentString *twin = argument.getPlatformTwin())
//         {
//             ga.genericArgument = QGenericArgument("QString", &twin->qString);
//             return true;
//         }
//     }
//     return false;
// }

// bool QtArgumentConverter::converting(const NeQPoint &argument)
// {
//     if (type.id() == QMetaType::QPoint)
//     {
//         ga.genericArgument = QGenericArgument("QPoint", &argument.qValue);
//         return true;
//     }
//     return false;
// }

// bool QtArgumentConverter::converting(const NeQSize &argument)
// {
//     if (type.id() == QMetaType::QSize)
//     {
//         ga.genericArgument = QGenericArgument("QSize", &argument.qValue);
//         return true;
//     }
//     return false;
// }

// bool QtArgumentConverter::converting(const NeQRect &argument)
// {
//     if (type.id() == QMetaType::QRect)
//     {
//         ga.genericArgument = QGenericArgument("QRect", &argument.qValue);
//         return true;
//     }
//     return false;
// }

// bool QtArgumentConverter::converting(const NeQImage &argument)
// {
//     if (type.id() != QMetaType::QImage)
//         return false;
//     const QImage &img = argument.qValue();
//     if (img.isNull())
//         return false;
//     ga.genericArgument = QGenericArgument("QImage", &img);
//     return true;
// }

// bool QtArgumentConverter::converting(const NeQByteArray &argument)
// {
//     if (type.id() == QMetaType::QByteArray)
//     {
//         ga.genericArgument = QGenericArgument("QByteArray", &argument.qValue);
//         return true;
//     }
//     return false;
// }

// bool QtArgumentConverter::converting(const NeQTransform &argument)
// {
//     if (type.id() == QMetaType::QTransform)
//     {
//         ga.genericArgument = QGenericArgument("QTransform", &argument.qValue);
//         return true;
//     }
//     return false;
// }

bool QtFill::fill(const Any *a, bool &out)
{
    if (const Integer *i = a->as_Integer())
    {
        out = (i->value != 0);
        return true;
    }
    return false;
}

bool QtFill::fill(const Any *a, int &out)
{
    if (const Integer *i = a->as_Integer())
    {
        out = (int)i->value;
        return true;
    }
    double number;
    if (a->isNumber(number))
    {
        out = (int)number;
        return true;
    }
    return false;
}

bool QtFill::fill(const Any *a, double &out)
{
    return a->isNumber(out);
}

bool QtFill::fill(const Any *a, QString &out)
{
    if (const PilsString *s = a->as_String())
    {
        out = s->getPlatformTwin()->qString;
        return true;
    }
    return false;
}

bool QtFill::fill(const Any *a, QByteArray &out)
{
    if (const PilsString *s = a->as_String())
    {
        out = QByteArray(s->value, s->count->value);
        return true;
    }
    return false;
}

bool QtFill::fill(const Any *a, QColor &out)
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

bool QtFill::fill(const Any *a, QImage &out)
{
    QtImageConverter converter(out);
    return a->convert(converter);
}

bool QtFill::fill(const Any *a, QIcon &out)
{
    QImage img;
    if (fill(a, img)) {
        out = QIcon(QPixmap::fromImage(img));
        return true;
    }
    return false;
}

bool QtFill::fill(const Any *a, QPixmap &out)
{
    QImage img;
    if (fill(a, img)) {
        out = QPixmap::fromImage(img);
        return true;
    }
    return false;
}

bool QtFill::fill(const Any *a, QVariant &out)
{
    if (const Integer *i = a->as_Integer())
    {
        out = (qint64)i->value;
        return true;
    }
    QString s;
    if (fill(a, s))
    {
        out = s;
        return true;
    }
    double n;
    if (fill(a, n))
    {
        out = n;
        return true;
    }
    return false;
}

const Constant* QtWrap::wrap(int v)
{
    return Integer::get(v);
}

const Constant* QtWrap::wrap(double v)
{
    return Number::get(v);
}

const Constant* QtWrap::wrap(bool v)
{
    return Integer::get(v);
}

const Constant *QtWrap::wrap(const QString &s)
{
    return PilsString::get(s.toUtf8());
}

const Constant *QtWrap::wrap(const char *s)
{
    if (s)
        return PilsString::get(s);
    return Empty::get();
}

const Constant *QtWrap::wrap(QObject *obj)
{
    if (obj == nullptr)
    {
        return Empty::get();
    }
    QtObjectLookup lookup(obj);
    return lookup.lookup();
}

bool QtImageConverter::converting(const NeQImage &argument)
{
    out = argument.qValue();
    return (!out.isNull());
}

} // namespace PILS
