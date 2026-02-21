/* This file is public domain */
#include "plughost.h"
namespace PILS
{
	const PilsString *const PlugName::namespace_ = PilsString::get("pils.org/ns/pilsplug");

	const PlugNamePlug PlugNamePlug::singleton = "plug";
	const PlugTypeCliche PlugTypeCliche::singleton;
	const PlugCliche PlugCliche::singleton;

	const PlugNameInt PlugNameInt::singleton = "int";
	const PlugNameDouble PlugNameDouble::singleton = "double";
	const PlugNameVoid PlugNameVoid::singleton = "void";
	const PlugNameString PlugNameString::singleton = "string";
	const PlugNameBlob PlugNameBlob::singleton = "blob";
}
