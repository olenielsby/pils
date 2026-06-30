#pragma once
#include "qpils_plumming.h"
#include "qpils_converter.h"
namespace PILS {

class PlatformSpecializedNodeConstantTiny : public NodeConstantTiny
{
public:
    PlatformSpecializedNodeConstantTiny(const Constant *&link, const ClicheTiny &cliche, const Constant *value)
        : NodeConstantTiny(link, cliche, value)
    {}
    bool convert(Converter &converter) const override;
    virtual bool converting(PlatformSpecificConverter &converter) const = 0;
};

class QtClassNameQPoint : public QtValueClassName
{
public:
    QtClassNameQPoint() : QtValueClassName("Point") {};
    const PlatformSpecializedNodeConstantTiny *newSpecializedNode(const Constant *&link, const ClicheTiny &cliche, const ListConstant *value) const override;
};

class QtClassNameQSize : public QtValueClassName
{
public:
    QtClassNameQSize() : QtValueClassName("Size") {};
    const PlatformSpecializedNodeConstantTiny *newSpecializedNode(const Constant *&link, const ClicheTiny &cliche, const ListConstant *value) const override;
};

class QtClassNameQRect : public QtValueClassName
{
public:
    QtClassNameQRect() : QtValueClassName("Rect") {};
    const PlatformSpecializedNodeConstantTiny *newSpecializedNode(const Constant *&link, const ClicheTiny &cliche, const ListConstant *value) const override;
};

class QtClassNameQColor : public QtValueClassName
{
public:
    QtClassNameQColor() : QtValueClassName("Color") {};
    // bool construct(const Any *const *args, int argc, QVariant &value) const override;
};

class QtClassNameQImage : public QtValueClassName
{
public:
    QtClassNameQImage() : QtValueClassName("Image") {};
    const PlatformSpecializedNodeConstantTiny *newSpecializedNode(const Constant *&link, const ClicheTiny &cliche, const PilsString *value) const override;
};

class QtClassNameQTransform : public QtValueClassName
{
public:
    QtClassNameQTransform() : QtValueClassName("Transform") {};
    const PlatformSpecializedNodeConstantTiny *newSpecializedNode(const Constant *&link, const ClicheTiny &cliche, const ListConstant *value) const override;
};

class QtClassNameQByteArray : public QtValueClassName
{
public:
    QtClassNameQByteArray() : QtValueClassName("ByteArray") {};
    const PlatformSpecializedNodeConstantTiny *newSpecializedNode(const Constant *&link, const ClicheTiny &cliche, const PilsString *value) const override;
};

class QtClassNameQDateTime : public QtValueClassName
{
public:
    QtClassNameQDateTime() : QtValueClassName("DateTime") {};
    // bool construct(const Any *const *args, int argc, QVariant &value) const override;
};

class QtValueClassCliche
    : public ClicheTiny
{
public:
    QtValueClassCliche(const QtValueClassName *head)
        : ClicheTiny(head)
    {}
    const NodeConstantShort *newNode(const Constant *&link, const PilsString *value) const override
    {
        auto className = static_cast<const QtValueClassName*>(head);
        if (auto specialized = className->newSpecializedNode(link, *this, value))
            return specialized;
        else return ClicheTiny::newNode(link, value);
    }
    const NodeConstantShort *newNode(const Constant *&link, const ListConstant *value) const override
    {
        auto className = static_cast<const QtValueClassName*>(head);
        if (auto specialized = className->newSpecializedNode(link, *this, value))
            return specialized;
        else return ClicheTiny::newNode(link, value);
    }
    // const Any *specialOperation(Runner &run, const ReallySpecial &special, const Any &argument) const override;
    // const NodeConstantShort *newNode(const Constant *&link, const Integer *value) const override;
    // const NodeConstantShort *newNode(const Constant *&link, const Float *value) const override;
    // const NodeConstantShort *newNode(const Constant *&link, const PilsDate *value) const override;
    // const NodeConstantShort *newNode(const Constant *&link, const Duration *value) const override;
    // const NodeConstantShort *newNode(const Constant *&link, const Cliche *value) const override;
    // const NodeConstantShort *newNode(const Constant *&link, const NodeConstant *value) const override;
    // const NodeConstantShort *newNode(const Constant *&link, const Special *value) const override;
};


class NodeEmbeddedQValueType : public PlatformSpecializedNodeConstantTiny
{
public:
    NodeEmbeddedQValueType(const Constant *&link, const ClicheTiny &cliche, const Constant *value)
        : PlatformSpecializedNodeConstantTiny(link, cliche, value)
    {}
};

class NeQPoint : public NodeEmbeddedQValueType
{
public:
    NeQPoint(const Constant *&link, const ClicheTiny &cliche, const Constant *value, QPoint qValue)
        : NodeEmbeddedQValueType(link, cliche, value), qValue(qValue)
    {}
    bool converting(PlatformSpecificConverter &converter) const override {return converter.converting(*this);}
    QPoint qValue;
};

class NeQSize : public NodeEmbeddedQValueType
{
public:
    NeQSize(const Constant *&link, const ClicheTiny &cliche, const Constant *value, QSize qValue)
        : NodeEmbeddedQValueType(link, cliche, value), qValue(qValue)
    {}
    bool converting(PlatformSpecificConverter &converter) const override {return converter.converting(*this);}
    QSize qValue;
};

class NeQRect : public NodeEmbeddedQValueType
{
public:
    NeQRect(const Constant *&link, const ClicheTiny &cliche, const Constant *value, QRect qValue)
        : NodeEmbeddedQValueType(link, cliche, value), qValue(qValue)
    {}
    bool converting(PlatformSpecificConverter &converter) const override {return converter.converting(*this);}
    QRect qValue;
};

class NeQImage : public NodeEmbeddedQValueType
{
public:
    NeQImage(const Constant *&link, const ClicheTiny &cliche, const PilsString *value)
        : NodeEmbeddedQValueType(link, cliche, value), ready(false)
    {}
    bool converting(PlatformSpecificConverter &converter) const override {return converter.converting(*this);}
    const QImage &qValue() const;
private:
    mutable QImage lazyQValue;
    mutable bool ready;
};

class NeQByteArray : public NodeEmbeddedQValueType
{
public:
    NeQByteArray(const Constant *&link, const ClicheTiny &cliche, const Constant *value, QByteArray qValue)
        : NodeEmbeddedQValueType(link, cliche, value), qValue(qValue)
    {}
    bool converting(PlatformSpecificConverter &converter) const override {return converter.converting(*this);}
    QByteArray qValue;
};

class NeQTransform : public NodeEmbeddedQValueType
{
public:
    NeQTransform(const Constant *&link, const ClicheTiny &cliche, const Constant *value, QTransform qValue)
        : NodeEmbeddedQValueType(link, cliche, value), qValue(qValue)
    {}
    bool converting(PlatformSpecificConverter &converter) const override {return converter.converting(*this);}
    QTransform qValue;
};

}