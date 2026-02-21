#include <Windows.h>
#include "jpils_DynamicLibrary.h"

/* replacement class: jucepils version 0.4 is based on juce 1.53
   but the DynamicLibrary stuff got into the jpils interface
   from the juce tip, so to revert, emulate it here. Used for
   pilsplugs only.
*/

namespace juce
{
	DynamicLibrary::DynamicLibrary(juce::String string)
		: string(string)
	{
		wchar_t buffer[0x100];
		string.copyToUTF16(buffer, 0x200);
		handle = (void*)LoadLibraryW(buffer);
	}
	void *DynamicLibrary::getNativeHandle()
	{
		return handle;
	}
	void *DynamicLibrary::getFunction(juce::String name)
	{
		char buffer[0x100];
		name.copyToUTF8(buffer, 0x100);
		return GetProcAddress((HMODULE)handle, buffer);
	}
	DynamicLibrary::~DynamicLibrary()
	{
		FreeLibrary((HMODULE)handle);
	}
}
