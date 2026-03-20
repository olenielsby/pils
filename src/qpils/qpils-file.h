/* This file is public domain */
#pragma once
#include "qpils-plumming.h"
#include <QDir>
#include <QFileInfo>

namespace PILS
{
	class FileName
		: public ReallySpecial
	{
	public:
        FileName(const HashedConstant *&link, const PilsString *name, bool isFolder)
            :   ReallySpecial(link), file(new QFileInfo(QString::fromUtf8(name->value, name->count->value))), name(name)
		{}
        const Any *specialCalling(Runner &run, const Constant &name) const override;
        const Any *specialCalling(Runner &run, const Constant &name, const Any &arg) const override;
        bool specialComparing(const FileNameLookup &lookup) const override;
        bool converting(QtSpecialConverter &converter) const override;
        void write(Writing & writing) const override;
        size_t unlinkAndGetSize() override;
	private:
		friend class FileNameConverter;
		const PilsString *name;
        const QFileInfo *const file;
	};

	class FileNameLookup
		: public SpecialLookup
	{
	public:
		FileNameLookup(const PilsString &name)
            : name(name), isFolder(name.count->value > 0 && name.value[name.count->value-1] == '/')
		{}
        const ReallySpecial *newSpecial(const HashedConstant *&link) override;
        bool compare(const ReallySpecial &special) const override;
        void unduplicate() override;
        size_t hash() const override;
		const PilsString &name;
		const bool isFolder;
	};

	class FileNameConverter
        : public QtSpecialConverter
	{
	public:
		FileNameConverter()
			: name(NULL)
		{}
		const PilsString *name;
        bool converting(const FileName &argument) override;
	};

    // class PipesourceUnzip
    // 	: public Pipesource
    // {
    // public:
    // 	PipesourceUnzip(const juce::File &file);
 //        const Step *pass(Runner &run, const Any *thing) override;
 //        const Step *step_(Runner &run) const override;
 //        Sink *kick(Runner &run) override;
    // private:
    // 	juce::ZipFile zipFile;
    // 	int at, count;
    // };
}
