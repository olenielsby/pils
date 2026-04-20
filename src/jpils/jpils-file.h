/* This file is public domain */
#ifndef _JPILS_FILE_H_
#define _JPILS_FILE_H_
#include "jpils-plumming.h"

namespace PILS
{
	class FileName
		: public ReallySpecial
	{
	public:
		FileName(const Constant *&link, const PilsString *name, bool isFolder)
			:  ReallySpecial(link), file(new juce::File (juce::String::fromUTF8 (name->value, name->count->value - isFolder))), name(name)
		{}
        const Any *specialCalling(Runner &run, const Constant &name) const override;
        const Any *specialCalling(Runner &run, const Constant &name, const Any &arg) const override;
        bool specialComparing(const FileNameLookup &lookup) const override;
        bool converting(JuceSpecialConverter &converter) const override;
        void write(Writing & writing) const override;
        size_t unlinkAndGetSize() override;
	private:
		friend class FileNameConverter;
		const PilsString *name;
		const juce::File *const file;
	};

	class FileNameLookup
		: public SpecialLookup
	{
	public:
		FileNameLookup(const PilsString &name)
			: name(name), isFolder(name.value[name.count->value-1] == '/')
		{}
        const ReallySpecial *newSpecial(const Constant *&link) override;
        bool compare(const ReallySpecial &special) const override;
        void unduplicate() override;
        size_t hash() const override;
		const PilsString &name;
		const bool isFolder;
	};

	class FileNameConverter
		: public JuceSpecialConverter
	{
	public:
		FileNameConverter()
			: name(nullptr)
		{}
		const PilsString *name;
        bool converting(const FileName &argument) override;
	};

	class PipesourceUnzip
		: public Pipesource
	{
	public:
		PipesourceUnzip(const juce::File &file);
        const Step *pass(Runner &run, const Any *thing) override;
        const Step *step_(Runner &run) const override;
        Sink *kick(Runner &run) override;
	private:
		juce::ZipFile zipFile;
		int at, count;
	};
}
#endif
