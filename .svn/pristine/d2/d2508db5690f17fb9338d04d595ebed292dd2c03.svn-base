/* This file is public domain */
// This file should be included in a single .cpp file of the plug

#include "pilsplug/pilsplug.h"

namespace pilsplug
{
	struct bridge
	{
		static const PilsplugHost *host;
		static const Plug plug;
	};

	const PilsplugHost *bridge::host = 0;
	const Plug bridge::plug;

	void interface::VirtualBaseObject::acquire() const
	{
		bridge::host->increment(*this);
	}

	void interface::VirtualBaseObject::release() const
	{
		if (bridge::host->decrement(*this) == 0)
		{
			delete this;
		}
	}
}

extern "C" const pilsplug::Plug *plug(const pilsplug::PilsplugHost &host)
{
	pilsplug::bridge::host = &host;
	return &pilsplug::bridge::plug;
}

void pilsplug::Plug::delete_(pilsplug::interface::Object *object) const
{
	delete object;
}
