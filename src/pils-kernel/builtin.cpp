/* This file is public domain */
#include "numeric.h"

namespace PILS
{
	const Call *Any::callHere() const
	{
		return new (Heap::allocate(sizeof(Call))) const Call(this);
	}

	const CallWho* Any::callWho(const Any* who) const
	{
		return new
			(Heap::allocate(sizeof(CallWho)))
			const CallWho(this, who);
	}

	const Call *Constant::callHere() const
	{
		return
			new (Heap::allocate(sizeof(Slot)))
			const Slot(this);
	}

	const Call *Empty::callHere() const
	{
		return new (Heap::allocate(sizeof(EmptySlot))) EmptySlot();
	}

	const CallWho *ClicheShort::whoOperation(const NodeExpressShort *operation, const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(WhoExpressOperation)))
			WhoExpressOperation(operation, who);
	}

	const Slot *Slot::as_Slot() const
	{
		return this;
	}

	const CallWho *PokerShort::callWho(const Any *who) const
	{
		return new
			(Heap::allocate(sizeof(CallWho)))
			const CallWho(this, who);
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
		cake->addReference();
		return cake;
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const HashedConstant *&link, const Integer *value) const
	{
		return new (Heap::allocate(sizeof(UntypedOperationConstant))) const UntypedOperationConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const HashedConstant *&link, const Float *value) const
	{
		return new (Heap::allocate(sizeof(UntypedOperationConstant))) const UntypedOperationConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const HashedConstant *&link, const PilsColor *value) const
	{
		return new (Heap::allocate(sizeof(UntypedOperationConstant))) const UntypedOperationConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const HashedConstant *&link, const Timestamp *value) const
	{
		return new (Heap::allocate(sizeof(UntypedOperationConstant))) const UntypedOperationConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const HashedConstant *&link, const Duration *value) const
	{
		return new (Heap::allocate(sizeof(UntypedOperationConstant))) const UntypedOperationConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const HashedConstant *&link, const PilsDate *value) const
	{
		return new (Heap::allocate(sizeof(UntypedOperationConstant))) const UntypedOperationConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const HashedConstant *&link, const PilsString *value) const
	{
		return new (Heap::allocate(sizeof(UntypedOperationConstant))) const UntypedOperationConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const HashedConstant *&link, const Cliche *value) const
	{
		return new (Heap::allocate(sizeof(UntypedOperationConstant))) const UntypedOperationConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const HashedConstant *&link, const NodeConstant *value) const
	{
		return new (Heap::allocate(sizeof(UntypedOperationConstant))) const UntypedOperationConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const HashedConstant *&link, const ListConstant *value) const
	{
		return new (Heap::allocate(sizeof(UntypedOperationConstant))) const UntypedOperationConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const HashedConstant *&link, const Special *value) const
	{
		return new (Heap::allocate(sizeof(UntypedOperationConstant))) const UntypedOperationConstant(link, *this, value);
	}

	const NodeExpressShort *BuiltinClicheUntypedOperation::node(const Express *value) const
	{
		return new (Heap::allocate(sizeof(UntypedOperationExpress))) const UntypedOperationExpress(*this, value);
	}

	const CallWho *UntypedOperationConstant::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoUntypedOperationConstant))) const WhoUntypedOperationConstant(this, who);
	}

	const CallWho *UntypedOperationExpress::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoUntypedOperationExpress))) const WhoUntypedOperationExpress(this, who);
	}

	const Any *BuiltinClicheNameValue::node(const Any *const *element) const
	{
		return new (Heap::allocate(sizeof(NameValue))) const NameValue(element);
	}

	bool NameValue::isNameValuePair(const Constant *&name, const Any *&value) const
	{
		if (name = element[1]->as_Constant())
		{
			value = element[0];
			return true;
		}
		else return false;
	}

	const Any *SystemProperty::get(Runner &run) const
	{
		return NULL;
	}

	const Any *SystemProperty::set(const Any &assignvalue) const
	{
		return NULL;
	}
}
