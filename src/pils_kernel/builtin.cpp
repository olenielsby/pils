/* This file is public domain */
#include "numeric.h"
// #include "initializers.h"

namespace PILS
{
	const Call *Any::callHere() const
	{
        return new const Call(this);
	}

	const CallWho* Any::callWho(const Any* who) const
	{
        return new const CallWho(this, who);
	}

    const Call *Constant::callHere() const
	{
        return new const Slot(this);
	}

	const Call *Empty::callHere() const
	{
        return new const EmptySlot();
	}

	const CallWho *ClicheShort::whoOperation(const NodeExpressShort *operation, const Any *who) const
	{
        return new WhoExpressOperation(operation, who);
	}

	const Slot *Slot::as_Slot() const
	{
		return this;
	}

	const CallWho *PokerShort::callWho(const Any *who) const
	{
        return new const CallWho(this, who);
	}

	const Any *CallWho::whoAttribute() const
	{
		return element[1];
	}

	const Any *CallWho::callAttribute() const
	{
		return element[0];
	}

	const Special *Plum::cake()
	{
		const Special *cake = &singleton.plumcake;
		cake->retain();
		return cake;
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const Constant *&link, const Integer *value) const
	{
        return new const UntypedOperationConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const Constant *&link, const Float *value) const
	{
        return new const UntypedOperationConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const Constant *&link, const PilsColor *value) const
	{
        return new const UntypedOperationConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const Constant *&link, const Timestamp *value) const
	{
        return new const UntypedOperationConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const Constant *&link, const Duration *value) const
	{
        return new const UntypedOperationConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const Constant *&link, const PilsDate *value) const
	{
        return new const UntypedOperationConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const Constant *&link, const PilsString *value) const
	{
        return new const UntypedOperationConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const Constant *&link, const Cliche *value) const
	{
        return new const UntypedOperationConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const Constant *&link, const NodeConstant *value) const
	{
        return new const UntypedOperationConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const Constant *&link, const ListConstant *value) const
	{
        return new const UntypedOperationConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const Constant *&link, const Special *value) const
	{
        return new const UntypedOperationConstant(link, *this, value);
	}

	const NodeExpressShort *BuiltinClicheUntypedOperation::node(const Express *value) const
	{
        return new const UntypedOperationExpress(*this, value);
	}

	const CallWho *UntypedOperationConstant::callWho(const Any *who) const
	{
        return new const WhoUntypedOperationConstant(this, who);
	}

	const CallWho *UntypedOperationExpress::callWho(const Any *who) const
	{
        return new const WhoUntypedOperationExpress(this, who);
	}

	const Any *BuiltinClicheNameValue::node(const Any *const *element) const
	{
        return new const NameValue(element);
	}

	bool NameValue::isNameValuePair(const Constant *&name, const Any *&value) const
	{
        if ((name = element[1]->as_Constant()))
		{
			value = element[0];
			return true;
		}
		else return false;
	}

	const Any *SystemProperty::get(Runner &run) const
	{
		return nullptr;
	}

	const Any *SystemProperty::set(const Any &assignvalue) const
	{
		return nullptr;
	}

    void PredefinedName::writingToDebugOutput(int level) const
    {
        std::fputs(this->attributes[0]->as_String()->value, stderr);
    }
}
