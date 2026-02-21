/* This file is public domain */
#include "pils-kernel/sink.h"

#ifdef _MSC_VER

#include <windows.h>

const PILS::PilsString *pils_configuration_get_user_language()
{
	char lang[100];
	GetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_SENGLANGUAGE, lang, 100);
	for (int i = 0; lang[i]; i++)
		lang[i] = tolower(lang[i]);
	return PILS::PilsString::get(lang);
}

#elif defined(JUCE_LINUX)

const PILS::PilsString *pils_configuration_get_user_language()
{
	return PILS::PilsString::get("english");
}

#else

#include <juce.h>
#include "pils-kernel/language-switch.h"

const PILS::PilsString *pils_configuration_get_user_language()
{
	const char *language_name = NULL;
	CFArrayRef array = CFLocaleCopyPreferredLanguages();
	CFIndex count = CFArrayGetCount(array);
	for (CFIndex i = 0; i < count; i++)
	{
		CFStringRef languageID = (CFStringRef)CFArrayGetValueAtIndex(array, 0);
		char lc[32];
		CFStringGetCString(languageID, lc, sizeof(lc), kCFStringEncodingUTF8);
		if (language_name = language_code_to_english_language_name(lc[0], lc[1], lc[2])) break;
	}
	CFRelease(array);
	if (!language_name) language_name = "english";
	return PILS::PilsString::get(language_name);
}

#endif
