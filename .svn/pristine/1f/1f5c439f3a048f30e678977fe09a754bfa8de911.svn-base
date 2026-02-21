#include <juce.h>

namespace juce
{
	class DynamicLibrary
	{
	public:
		DynamicLibrary(juce::String string);
		~DynamicLibrary();
		void *getFunction(juce::String name);
		void *getNativeHandle();
	private:
		juce::String string;
		void *handle;
	};
}
