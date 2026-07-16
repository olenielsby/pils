#include "qpils_converter.h"
#include "qpils_qobject_wrapper.h"
#include "qpils_specialized_node.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QWheelEvent>
#include <QFocusEvent>

namespace PILS {

bool PlatformSpecializedNodeConstantTiny::convert(Converter &converter) const
{
    return converter.convert(*this);
}

bool PlatformSpecificConverter::convert(const ReallySpecial &argument)
{
    return argument.converting(*this);
}

bool PlatformSpecificConverter::convert(const PlatformSpecializedNodeConstantTiny &argument)
{
    return argument.converting(*this);
}


QObject *PlatformSpecificConverter::getObject(const QtObjectWrapper &wrap)
{
    return wrap.object;
}


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
        out = QString::fromUtf8(s->value, s->count->value);
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
        if (out.isNull())
            return false;
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

bool QtFill::fill(const Any* a, QKeySequence& out)
{
    QString s;
    if (!fill(a, s))
        return false;
    out = QKeySequence(s);
    return true;
}

bool QtFill::fill(const Any* a, QList<int>& out)
{
    auto list = a->as_ListConstant();
    if (list == nullptr) return false;
    int c = list->count->value;
    out.clear();
    for (int i = 0; i < c; i++)
    {
        int x;
        if (!fill(list->element[i], x)) return false;
        out.append(x);
    }
    return true;
}

bool QtFill::fill(const Any* a, QTextCursor& out)
{
    auto list = a->as_ListConstant();
    if (list == nullptr) return false;
    if (list->count->value != 2) return false;
    int start = 0;
    int end = 0;
    if (!fill(list->element[0], start)) return false;
    if (!fill(list->element[1], end)) return false;
    out.clearSelection();
    out.setPosition(start);
    out.setPosition(end, QTextCursor::KeepAnchor);
    return true;
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
    QtObjectLookup lookup(Runner::current(), obj); //Todo: is runner needed?
    return lookup.lookup();
}

const Constant *QtWrap::wrap(QPilsTreeNode *obj)
{
    if (obj == nullptr)
    {
        return Empty::get();
    }
    QtObjectLookup lookup(Runner::current(), obj, QPilsTreeNode::getClassName()); //Todo: make thread safe
    return lookup.lookup();
}

const Constant *QtWrap::wrap(const QMouseEvent &e)
{
    const Constant* argv[] = {
        wrap(e.position().x()),
        wrap(e.position().y()),
        wrap(e.button()),
        wrap(e.buttons()),
        wrap(e.modifiers())
    };

    return ListConstant::get(argv, 5);
}

const Constant *QtWrap::wrap(const QKeyEvent &e)
{
    const Constant* argv[] = {
        wrap(e.key()),
        wrap(e.text()),
        wrap(e.modifiers()),
        wrap(e.isAutoRepeat())
    };

    return ListConstant::get(argv, 4);
}

const Constant *QtWrap::wrap(const QResizeEvent &e)
{
    const Constant* argv[] = {
        wrap(e.size().width()),
        wrap(e.size().height()),
        wrap(e.oldSize().width()),
        wrap(e.oldSize().height())
    };

    return ListConstant::get(argv, 4);
}

const Constant *QtWrap::wrap(const QWheelEvent &e)
{
    const QPoint angle = e.angleDelta();

    const Constant* argv[] = {
        wrap(e.position().x()),
        wrap(e.position().y()),
        wrap(angle.x()),
        wrap(angle.y()),
        wrap(e.modifiers())
    };

    return ListConstant::get(argv, 5);
}

const Constant *QtWrap::wrap(const Qt::MouseButton &e)
{
    return wrap(static_cast<int>(e));
}
const Constant *QtWrap::wrap(const Qt::KeyboardModifier &e)
{
    return wrap(static_cast<int>(e));
}

const Constant *QtWrap::wrap(const QFocusEvent &e)
{
    return wrap(e.gotFocus());
}

const Constant *QtWrap::wrap(const QTextCursor &e)
{
    const Constant* argv[] = {
        wrap(e.anchor()),
        wrap(e.position())
    };
    return ListConstant::get(argv, 2);
}

const Constant *QtWrap::wrap(const QList<int> &e)
{
    QList<const Constant *> list;
    list.reserve(e.size());

    for (int value : e)
        list.append(wrap(value));

    return ListConstant::get(list.constData(), e.size());
}

bool QtImageConverter::converting(const NeQImage &argument)
{
    out = argument.qValue();
    return (!out.isNull());
}

} // namespace PILS
