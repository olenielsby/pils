/* This file is public domain */
/* PILS plugin object model */

#ifndef _INCLUDE_PILSPLUG_H_
#define _INCLUDE_PILSPLUG_H_

#define PILSPLUG_MAX_METHOD_COUNT 100
#define PILSPLUG_MAX_PARAMETER_COUNT 10

namespace pilsplug {

	// A Plug is exported by the dynamic library's plug() function.
	// 
	// The root() method is used to get the main object of the plug.
	// Other objects can be created by methods of the root object.

	namespace interface
	{
		class Object;
		class Error; // Must be derived from Object
	}

	typedef interface::Error *Result;

	class PilsplugHost;

	class Plug
	{
	public:
        virtual interface::Object *root() const;
        virtual void delete_(::pilsplug::interface::Object *object) const;
	};

	struct BlobReference
	{
		int count;
		const void *data;
	};

	namespace interface
	{
		class VirtualBaseObject
		{
		public:
			virtual ~VirtualBaseObject() {}
            void acquire() const;
            void release() const;
		protected:
			VirtualBaseObject() : count(1) {}
		private:
			friend class ::pilsplug::PilsplugHost;
			mutable volatile long count;
		};

		class Object : public virtual VirtualBaseObject {virtual void this_method_is_needed_to_prevent_VC_from_offsetting_derived_interface_types_from_Object() {}};
	}

	// The host (PILS or some bridge) provides service functions
	// needed by the plug.
	//
	// Reference counter helpers are mandatory.
	//
	// Optional functionality (logging etc.) can be added by
	// named services.

	class PilsplugHost
	{
	public:
        virtual void increment(const interface::VirtualBaseObject &object) const;
        virtual int decrement(const interface::VirtualBaseObject &object) const;
        virtual void *service(const char *name) const;
	};
}
#endif
