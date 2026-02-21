/* This file is public domain */
#include "../pils-kernel/pilserror.h"
#include "compile.h"

namespace pilsplug
{
	const PilsplugHost host;

	Generic::GenericMethod Generic::genericMethods[] =
	{
		&Generic::m0, &Generic::m1, &Generic::m2, &Generic::m3, &Generic::m4, &Generic::m5, &Generic::m6, &Generic::m7, &Generic::m8, &Generic::m9,
		&Generic::m10,&Generic::m11,&Generic::m12,&Generic::m13,&Generic::m14,&Generic::m15,&Generic::m16,&Generic::m17,&Generic::m18,&Generic::m19,
		&Generic::m20,&Generic::m21,&Generic::m22,&Generic::m23,&Generic::m24,&Generic::m25,&Generic::m26,&Generic::m27,&Generic::m28,&Generic::m29,
		&Generic::m30,&Generic::m31,&Generic::m32,&Generic::m33,&Generic::m34,&Generic::m35,&Generic::m36,&Generic::m37,&Generic::m38,&Generic::m39,
		&Generic::m40,&Generic::m41,&Generic::m42,&Generic::m43,&Generic::m44,&Generic::m45,&Generic::m46,&Generic::m47,&Generic::m48,&Generic::m49,
		&Generic::m50,&Generic::m51,&Generic::m52,&Generic::m53,&Generic::m54,&Generic::m55,&Generic::m56,&Generic::m57,&Generic::m58,&Generic::m59,
		&Generic::m60,&Generic::m61,&Generic::m62,&Generic::m63,&Generic::m64,&Generic::m65,&Generic::m66,&Generic::m67,&Generic::m68,&Generic::m69,
		&Generic::m70,&Generic::m71,&Generic::m72,&Generic::m73,&Generic::m74,&Generic::m75,&Generic::m76,&Generic::m77,&Generic::m78,&Generic::m79,
		&Generic::m80,&Generic::m81,&Generic::m82,&Generic::m83,&Generic::m84,&Generic::m85,&Generic::m86,&Generic::m87,&Generic::m88,&Generic::m89,
		&Generic::m90,&Generic::m91,&Generic::m92,&Generic::m93,&Generic::m94,&Generic::m95,&Generic::m96,&Generic::m97,&Generic::m98,&Generic::m99
	};

	Result Generic::mm(int m, void *result, va_list &vl)
	{
	    return NULL;
	}
}

namespace PILS
{
	const NodeConstantShort *PlugTypeCliche::newNode(const HashedConstant *&link, const NodeConstant *value) const
	{
		return ClicheTiny::newNode(link, value);
	}

	const NodeConstantLong *PlugCliche::newNodeConstant(const HashedConstant *&link, const Constant *const *value) const
	{
		if (value[0]->as_NodeConstant() && value[1]->as_String())
			return new (Heap::allocate(sizeof(PlugNode))) PlugNode(link, *this, value);
		else return ClicheTrailer::newNodeConstant(link, value);
	}

	bool PlugCompilable::compile(PlugCompiling &state) const
	{
		return false;
	}

	bool PlugName::compile(PlugCompiling &state) const
	{
		return false;
	}

	bool PlugNameInt::compile(PlugCompiling &state) const
	{
		return state.compile(*this);
	}

	bool PlugNameDouble::compile(PlugCompiling &state) const
	{
		return state.compile(*this);
	}

	bool PlugNameVoid::compile(PlugCompiling &state) const
	{
		return state.compile(*this);
	}

	bool PlugNameString::compile(PlugCompiling &state) const
	{
		return state.compile(*this);
	}

	bool PlugNameBlob::compile(PlugCompiling &state) const
	{
		return state.compile(*this);
	}

	const Any *PlugNode::specialCall(Runner &run, const ReallySpecial &special) const
	{
		const Any *result = NULL;
		if (!run.isMainThread()) return NULL;
		typedef pilsplug::Plug *(*PlugDoor) (const pilsplug::PilsplugHost &);
		if (void *handle = PlugTools::loadPlugin(special, (PilsString &)*element[1]))
		{
			const Special *libraryHandle = PlugLibrary::get(handle);
			if (PlugDoor plugDoor = (PlugDoor)(PlugTools::getProcAddress(handle, "plug")))
			{
				if (pilsplug::Plug *plug = plugDoor(pilsplug::host))
				{
					const NodeConstant *typenode = static_cast<const NodeConstant *>(element[0]);
					if (const NodeConstant *types = typenode->element[0]->as_NodeConstant())
					{
						const Constant *const *at
							= std::lower_bound(
							&types->cliche->attributes[types->cliche->attributes[0] == &Empty::singleton],
							&types->cliche->attributes[types->cliche->count],
							types->cliche->head);
						if (at != &types->cliche->attributes[types->cliche->count] && *at == types->cliche->head)
						{
							size_t type = at - types->cliche->attributes;
							pilsplug::interface::Object *object = plug->root();
							if (object)
							{
								result = (const Any *)(const void *)PlugObjectLookup(object, *types, type, *plug, *libraryHandle).lookup();
							}
						}
					}
				}
			}
			libraryHandle->releaseReference();
		}
		return result;
	}

	const Special *PlugLibrary::get(void *handle)
	{
		return (const Special*)(const void*)PlugLibraryLookup(handle).lookup();
	}

	size_t PlugLibraryLookup::hash() const
	{
		return reinterpret_cast<size_t>(handle);
	}

	size_t PlugObjectLookup::hash() const
	{
		return reinterpret_cast<size_t>(object);
	}

	void PlugObjectLookup::unduplicate()
	{
		pilsplug::host.decrement(*object);
	}

	PlugObject::~PlugObject()
	{
		if (pilsplug::host.decrement(*object) == 0)
			plug.delete_(object);
	}

	const Any *PlugObject::specialCalling(Runner &run, const Number &call) const
	{
		return specialCalling(run, Builtin::name.hash, call);
	}

	const Any *PlugObject::specialCalling(Runner &run, const PilsString &call) const
	{
		return specialCalling(run, Builtin::name.dollar, call);
	}

	const Any *PlugObject::specialCalling(Runner &run, const Constant &name, const Any &arg) const
	{
		const ListConstant *const methods = types->element[type]->as_ListConstant();
		if (methods == NULL) return NULL;
		int methodCount = methods->count->value;
		if (methodCount > PILSPLUG_MAX_METHOD_COUNT) methodCount = PILSPLUG_MAX_METHOD_COUNT;
		for (int methodIndex = 0; methodIndex < methodCount; methodIndex++)
		{
			if (const NodeConstantTiny *method = methods->element[methodIndex]->as_NodeConstantTiny())
			{
				if (method->cliche->head == &name)
				{
					if (const NodeConstantTiny *signature = method->element[0]->as_NodeConstantTiny())
					{
						if (const Any *result = dispatch(run, methodIndex, signature->cliche->head, signature->element[0], &arg))
							return result;
					}
				}
			}
		}
		return NULL;
	}

	class PlugMethodInvoker : private PlugCompiling
	{
	public:
		PlugMethodInvoker(const PlugObject &self) : error(NULL), self(self), count(1) {}
		bool setArgument(const Constant *typeSpecifier, const Any *argument)
		{
			if (const PlugCompilable *compilable = PlugCompilable::cast(typeSpecifier))
			{
				this->argument = argument;
				return compilable->compile(*this);
			}
			if (const PlugObject *other = PlugTools::as_PlugObject(argument))
			{
				if (other->types == self.types && typeSpecifier == other->types->cliche->attributes[other->type])
				{
					argumentRecord[count++].ptr = other->object;
					return true;
				}
			}
			return false;
		}
		const Any *invoke(int methodIndex, const Constant *returnTypeSpecifier);
		pilsplug::Result error;
	private:
		pilsplug::Result invoking(int methodIndex)
		{
			pilsplug::Generic::GenericMethod &method = pilsplug::Generic::genericMethods[methodIndex];

			return error =
				(((pilsplug::Generic*)self.object)->*method)(
				argumentRecord[0].ptr,
				argumentRecord[1].ptr,
				argumentRecord[2].ptr,
				argumentRecord[3].ptr,
				argumentRecord[4].ptr,
				argumentRecord[5].ptr,
				argumentRecord[6].ptr,
				argumentRecord[7].ptr,
				argumentRecord[8].ptr,
				argumentRecord[9].ptr);
		}
		const PlugObject &self;
		struct ArgumentRecord
		{
			void *ptr;
			union
			{
				double double_;
				float float_;
				int int_;
				const char *string;
				pilsplug::interface::Object *object;
				pilsplug::BlobReference blob;
			};
		};
		ArgumentRecord argumentRecord[PILSPLUG_MAX_PARAMETER_COUNT];
		size_t count;
		const Any *argument;
		bool compile(const PlugNameInt &spec)
		{
			if (const Integer *integer = argument->as_Integer())
			{
				ArgumentRecord &record = argumentRecord[count++];
				record.int_ = integer->value;
				record.ptr = &record.int_;
				return true;
			}
			else return false;
		}
		bool compile(const PlugNameDouble &spec)
		{
			ArgumentRecord &record = argumentRecord[count++];
			if (argument->isNumber(record.double_))
			{
				record.ptr = &record.double_;
				return true;
			}
			else return false;
		}
		bool compile(const PlugNameString &spec)
		{
			ArgumentRecord &record = argumentRecord[count++];
			const PilsString *string = argument->as_String();
			if (string)
			{
				record.ptr = (void*)&string->value;
				return true;
			}
			else return false;
		}
		bool compile(const PlugNameBlob &spec)
		{
			ArgumentRecord &record = argumentRecord[count++];
			const PilsString *string = argument->as_String();
			if (string)
			{
				record.ptr = &record.blob;
				record.blob.count = string->count->value;
				record.blob.data = &string->value;
				return true;
			}
			else if (argument == &Empty::singleton)
			{
				record.ptr = &record.blob;
				record.blob.count = 0;
				record.blob.data = NULL;
				return true;
			}
			else return false;
		}
	};

	const Any *PlugObject::dispatch(Runner &run, int methodIndex, const Constant *returnTypeSpecifier, const Constant *parametersSpecifier, const Any *argument) const
	{
		const Constant *const *parameters;
		const Any *const *arguments;
		size_t count;
		if (const ListConstant *parameterList = parametersSpecifier->as_ListConstant())
		{
			if (!argument->isList(arguments, count) || count != (size_t)parameterList->count->value || count > PILSPLUG_MAX_PARAMETER_COUNT)
				return NULL;
			parameters = parameterList->element;
		}
		else
		{
			count = 1;
			parameters = &parametersSpecifier;
			arguments = &argument;
		}
		PlugMethodInvoker invoker(*this);
		for (size_t i = 0; i < count; i++)
		{
			if (!invoker.setArgument(parameters[i], arguments[i]))
				return NULL;
		}
		const Any *value = invoker.invoke(methodIndex, returnTypeSpecifier);
		if (invoker.error)
		{
			pilsplug::interface::Object *errorObject = (pilsplug::interface::Object *)(void*)invoker.error;
			if (value) value->releaseReference();
			const Constant *const *at = std::lower_bound
				(&types->cliche->attributes[types->cliche->attributes[0] == &Empty::singleton],
				&types->cliche->attributes[types->cliche->count],
				&Builtin::name.error
				);
			if (at != &types->cliche->attributes[types->cliche->count] && *at == &Builtin::name.error)
			{
				size_t type = at - types->cliche->attributes;
				value = (const Special *)(const void *)PlugObjectLookup(errorObject, *types, type, plug, *handle).lookup();
			}
			else
			{
				value = &Builtin::name.error;
				value->addReference();
			}
			new (run.allocate(sizeof(SinkError))) SinkError();
		}
		return value;
	}

	bool PlugCompiling::compile(const PlugNameDouble &)
	{
		return false;
	}

	bool PlugCompiling::compile(const PlugNameInt &)
	{
		return false;
	}

	bool PlugCompiling::compile(const PlugNameString &)
	{
		return false;
	}

	bool PlugCompiling::compile(const PlugNameBlob &)
	{
		return false;
	}

	bool PlugCompiling::compile(const PlugNameVoid &)
	{
		return false;
	}

	const Any *PlugMethodInvoker::invoke(int methodIndex, const Constant *returnTypeSpecifier)
	{
		if (const PlugCompilable *compilable = PlugCompilable::cast(returnTypeSpecifier))
		{
			class TypedInvoking : public PlugCompiling
			{
			public:
				TypedInvoking(PlugMethodInvoker &this_PlugMethodInvoker, int methodIndex)
					: resultRecord(this_PlugMethodInvoker.argumentRecord[0]), this_PlugMethodInvoker(this_PlugMethodInvoker), methodIndex(methodIndex)
				{}
				const Any *result;
				ArgumentRecord &resultRecord;
				bool compile(const PlugNameDouble &)
				{
					resultRecord.ptr = &resultRecord.double_;
					if (!this_PlugMethodInvoker.invoking(methodIndex))
					{
						result = Number::get(resultRecord.double_);
						return true;
					}
					else return false;
				}
				bool compile(const PlugNameInt &)
				{
					resultRecord.ptr = &resultRecord.int_;
					if (!this_PlugMethodInvoker.invoking(methodIndex))
					{
						result = Integer::get(resultRecord.int_);
						return true;
					}
					else return false;
				}
				bool compile(const PlugNameString &)
				{
					resultRecord.ptr = &resultRecord.string;
					if (!this_PlugMethodInvoker.invoking(methodIndex))
					{
						if (resultRecord.string)
							result = PilsString::get((const char *)resultRecord.string);
						else
						{
							result = &Empty::singleton;
							result->addReference();
						}
						return true;
					}
					else return false;
				}
				bool compile(const PlugNameBlob &)
				{
					resultRecord.ptr = &resultRecord.blob;
					resultRecord.blob.count = -1;
					if (!this_PlugMethodInvoker.invoking(methodIndex))
					{
						if (resultRecord.blob.count >=0 && resultRecord.blob.data != NULL)
							result = PilsString::get((const char *)resultRecord.blob.data, resultRecord.blob.count);
						else
						{
							result = &Empty::singleton;
							result->addReference();
						}
						return true;
					}
					else return false;
				}
				bool compile(const PlugNameVoid &)
				{
					if (!this_PlugMethodInvoker.invoking(methodIndex))
					{
						result = this_PlugMethodInvoker.self.as_Special();
						result->addReference();
						return true;
					}
					else return false;
				}
			private:
				PlugMethodInvoker &this_PlugMethodInvoker;
				int methodIndex;
			} ;
			TypedInvoking typedInvoking(*this, methodIndex);
			if (compilable->compile(typedInvoking))
				return typedInvoking.result;
		}
		const Cliche *cliche = self.types->cliche;
		const Constant *const *at =
			std::lower_bound(&cliche->attributes[cliche->attributes[0] == &Empty::singleton], &cliche->attributes[cliche->count], returnTypeSpecifier);
		if (at != &cliche->attributes[cliche->count] && *at == returnTypeSpecifier)
		{
			ArgumentRecord &resultRecord = argumentRecord[0];
			resultRecord.ptr = &resultRecord.object;
			resultRecord.object = NULL;
			size_t type = at - cliche->attributes;
			if (invoking(methodIndex) == NULL)
			{
				if (resultRecord.object)
				{
					return (const Special *)(const void *)PlugObjectLookup(resultRecord.object, *self.types, type, self.plug, *self.handle).lookup();
				}
				else
				{
					Empty::singleton.addReference();
					return &Empty::singleton;
				}
			}
		}
		return NULL;
	}
}
