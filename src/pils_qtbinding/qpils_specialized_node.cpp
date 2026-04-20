#include "qpils_specialized_node.h"
namespace PILS {

void QtValueClassName::initialize()
{
    new QtClassNameQPoint();
    new QtClassNameQSize();
    new QtClassNameQRect();
    new QtClassNameQColor();
    new QtClassNameQImage();
    new QtClassNameQTransform();
    new QtClassNameQByteArray();
    new QtClassNameQDateTime();
}

const ClicheTiny *QtValueClassName::newCliche() const
{
    return new const QtValueClassCliche(this);
}

const PlatformSpecializedNodeConstantTiny *QtClassNameQPoint::newSpecializedNode(const Constant *&link, const ClicheTiny &cliche, const ListConstant *value) const
{
    if (value->count->value != 2) return nullptr;
    int x, y;
    if (!QtFill::fill(value->element[0], x)) return nullptr;
    if (!QtFill::fill(value->element[1], y)) return nullptr;
    return new NeQPoint(link, cliche, value, QPoint(x, y));
}

const PlatformSpecializedNodeConstantTiny *QtClassNameQSize::newSpecializedNode(const Constant *&link, const ClicheTiny &cliche, const ListConstant *value) const
{
    if (value->count->value != 2) return nullptr;
    int w, h;
    if (!QtFill::fill(value->element[0], w)) return nullptr;
    if (!QtFill::fill(value->element[1], h)) return nullptr;
    return new NeQSize(link, cliche, value, QSize(w, h));
}

const PlatformSpecializedNodeConstantTiny *QtClassNameQRect::newSpecializedNode(const Constant *&link, const ClicheTiny &cliche, const ListConstant *value) const
{
    if (value->count->value != 4) return nullptr;
    int x, y, w, h;
    if (!QtFill::fill(value->element[0], x)) return nullptr;
    if (!QtFill::fill(value->element[1], y)) return nullptr;
    if (!QtFill::fill(value->element[2], w)) return nullptr;
    if (!QtFill::fill(value->element[3], h)) return nullptr;
    return new NeQRect(link, cliche, value, QRect(x, y, w, h));
}

const PlatformSpecializedNodeConstantTiny *QtClassNameQImage::newSpecializedNode(const Constant *&link, const ClicheTiny &cliche, const PilsString *value) const
{
    return new NeQImage(link, cliche, value);
}

const QImage &NeQImage::qValue() const
{
    if (!ready)
    {
        const PilsString &value = static_cast<const PilsString &>(*element[0]);
        const QByteArrayView data(value.value, value.count->value);
        lazyQValue = QImage::fromData(data);
        ready = true;
    }
    return lazyQValue;
}

const PlatformSpecializedNodeConstantTiny *QtClassNameQByteArray::newSpecializedNode(const Constant *&link, const ClicheTiny &cliche, const PilsString *value) const
{
    return new NeQByteArray(link, cliche, value, QByteArray(value->value, value->count->value));
}

// bool QtClassNameQDateTime::construct(const Any *const *args, int argc, QVariant &value) const
// {
//     if (argc != 1)
//         return false;
//     const Timestamp *timeStamp = args[0]->as_Timestamp();
//     if (timeStamp == nullptr)
//         return false;
//     qint64 ms = timeStamp->stamp;
//     QDateTime dt = QDateTime::fromMSecsSinceEpoch(ms);
//     value = QVariant::fromValue(dt);
//     return true;
// }

const PlatformSpecializedNodeConstantTiny *QtClassNameQTransform::newSpecializedNode(const Constant *&link, const ClicheTiny &cliche, const ListConstant *value) const
{
    // 6 args → affine transform
    if (value->count->value != 6) return nullptr;
    qreal m11, m12, m21, m22, dx, dy;
    if (!QtFill::fill(value->element[0], m11) ||
        !QtFill::fill(value->element[1], m12) ||
        !QtFill::fill(value->element[2], m21) ||
        !QtFill::fill(value->element[3], m22) ||
        !QtFill::fill(value->element[4], dx)  ||
        !QtFill::fill(value->element[5], dy))
        return nullptr;
    return new NeQTransform(link, cliche, value, QTransform(m11, m12, m21, m22, dx, dy));
}

}