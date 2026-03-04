/* This file is public domain */
#include "jpils-file.h"
#include "jpils-standard-specials.h"

namespace PILS
{
	const Any *Plumcake::specialCalling(Runner &run, const Constant &name) const
	{
		return NULL;
	}

	const Any *Plumcake::specialCalling(Runner &run, const Constant &name, const Any &arg) const
	{
		if (run.isMainThread() && (&name == &Builtin::name.file || &name == &Builtin::name.folder))
		{
			const PilsString *fileName = arg.as_String();
			if (fileName && fileName->count->value && (fileName->value[fileName->count->value - 1] == '/') == (&name == &Builtin::name.folder))
			{
				return FileNameLookup(*fileName).lookup();
			}
		}
		return NULL;
	}

	bool FileNameLookup::compare(const ReallySpecial &special) const
	{
		return special.specialComparing(*this);
	}

	void FileNameLookup::unduplicate()
	{}

	size_t FileNameLookup::hash() const
	{
		return reinterpret_cast<size_t>(&name);
	}

	const ReallySpecial *FileNameLookup::newSpecial(const HashedConstant *&link)
	{
		name.addReference();
		return new (Heap::allocate(sizeof(FileName))) FileName(link, &name, isFolder);
	}

	void FileName::write(Writing & writing) const
	{
		writing.write(name->value, name->count->value);
	}

	size_t FileName::unlinkAndGetSize()
	{
		unhash();
		if (when) when->releaseFrom(*this);
		name->releaseFrom(*this);
        delete file;
		return sizeof(FileName);
	}

	const Any *FileName::specialCalling(Runner &run, const Constant &method) const
	{
        this->writeToDebugOutput(5);
        method.writeToDebugOutput(5);
        name->writeToDebugOutput(5);
        if (!run.isMainThread()) return NULL;
		else if (&method == &Builtin::name.name_)
		{
			name->addReference();
			return name;
		}
		else if (name->value[name->count->value - 1] == '/') //folder name
		{
			if ((&method == &Builtin::name.files || &method == &Builtin::name.folders) && file->isDirectory())
			{
				juce::Array<juce::File> results;
				int whatToLookFor = (&method == &Builtin::name.files?juce::File::findFiles:juce::File::findDirectories)+juce::File::ignoreHiddenFiles;
				int count = file->findChildFiles(results, whatToLookFor, false);
				if (!count)
				{
					Empty::singleton.addReference();
					return &Empty::singleton;
				}
				std::vector<const Constant *> items(count);
				for (int i = 0; i < count; i++)
				{
					juce::String name = results[i].getFullPathName().replaceCharacter('\\', '/');
					if (&method == &Builtin::name.folders) name += '/';
					const PilsString *pilsName = pils(name);
					items[i] = FileNameLookup(*pilsName).lookup();
					pilsName->unduplicateReference();
				}
				return ListConstant::get(&items[0], items.size());
			}
			else if(
				&method == &Builtin::name.ok && file->isDirectory()
				|| &method == &Builtin::name.delete_ && file->isDirectory() && file->deleteFile()
				|| &method == &Builtin::name.create && !file->isDirectory() && file->createDirectory())
			{
				addReference();
				return this;
			}
		}
		else if(&method == &Builtin::name.text)
		{
			if(!file->existsAsFile()) return NULL;
            juce::MemoryBlock data;
			if (file->loadFileAsData(data))
            {
                const PilsString* filedata = PilsString::get((const char *)data.getData(), data.getSize());
                filedata->writeToDebugOutput(5);
                return filedata;
            }
		}
		else if(&method == &Builtin::name.ok)
		{
			if(!file->existsAsFile()) return NULL;
			addReference();
			return this;
		}
		else if (&method == &Builtin::name.timestamp)
		{
			if(!file->existsAsFile()) return NULL;
			return pils(file->getLastModificationTime());
		}
		else if (&method == &Builtin::name.count_)
		{
			if(!file->existsAsFile()) return NULL;
			return Number::get((double)file->getSize());
		}
		else if (&method == &Builtin::name.readable)
		{
			if(!file->existsAsFile()) return NULL;
			return Integer::get(1); //TODO: test
		}
		else if (&method == &Builtin::name.writable)
		{
			if(!file->existsAsFile()) return NULL;
			return Integer::get(file->hasWriteAccess());
		}
		else if (&method == &Builtin::name.delete_)
		{
			if(!file->existsAsFile()) return NULL;
			return Integer::get(file->deleteFile());
		}
		else if (&method == &Builtin::name.zip)
		{
			addReference();
			run.sink->connectPipe(run);
			new (run.allocate(sizeof(PipesourceUnzip))) PipesourceUnzip(*file);
			return this;
		}
		return NULL;
	}

	const Any *FileName::specialCalling(Runner &run, const Constant &method, const Any &arg) const
	{
		if (!run.isMainThread()) return NULL;
		if (name->count->value == 0 || name->value[name->count->value - 1] == '/') return NULL;
		//Write text string to file
		if (&method == &Builtin::name.text)
		{
			const PilsString *string = arg.as_String();
			if (string && file->replaceWithData(string->value, string->count->value))
			{
				addReference();
				return this;
			}
		}
		else if (&method == &Builtin::name.move)
		{
			if(!file->existsAsFile()) return NULL;
			if (const PilsString *string = arg.as_String())
			{
				juce::String newName = juce::String::fromUTF8(string->value, string->count->value);
				juce::File newFile = juce::File(newName);
				if (file->moveFileTo(newFile))
				{
					return FileNameLookup(*string).lookup();
				}
			}
		}
		else if (&method == &Builtin::name.copy)
		{
			if(!file->existsAsFile()) return NULL;
			if (const PilsString *string = arg.as_String())
			{
				juce::String newName = juce::String::fromUTF8(string->value, string->count->value);
				juce::File newFile = juce::File(newName);
				if (file->copyFileTo(newFile))
				{
					return FileNameLookup(*string).lookup();
				}
			}
		}
		else if (&method == &Builtin::name.timestamp)
		{
			if (const Timestamp *timestamp = arg.as_Timestamp())
			{
				if(file->existsAsFile() && file->setLastModificationTime(::juce::Time(timestamp->value)))
				{
					addReference();
					return this;
				}
			}
		}
		else if (&method == &Builtin::name.zip)
		{
			// not supported in juce
		}
		return NULL;
	}

	bool FileName::specialComparing(const FileNameLookup &lookup) const
	{
		return name == &lookup.name;
	}

	bool FileName::converting(JuceSpecialConverter &converter) const
	{
		return converter.converting(*this);
	}

	const Any *QuickFetchFileName::specialAttribute(const Special &value) const
	{
		FileNameConverter converter;
		if (value.convert(converter) && converter.name->value[converter.name->count->value - 1] != '/')
			return converter.name;
		else return NULL;
	}

	const Any *QuickFetchFolderName::specialAttribute(const Special &value) const
	{
		FileNameConverter converter;
		if (value.convert(converter) && converter.name->value[converter.name->count->value - 1] == '/')
			return converter.name;
		else return NULL;
	}

	bool FileNameConverter::converting(const FileName &argument)
	{
		name = argument.name;
		return true;
	}

			/*
			juce::ZipFile zipFile(*file);
			ListBuilder<const Constant, const ListConstant> build;
			int count = zipFile.getNumEntries();
			for (int i = 0; i < count; i++)
			{
				const ZipFile::ZipEntry *entry = zipFile.getEntry(i);
				const Constant *elements[3];
				elements[0] = pils(entry->filename.replaceCharacter('\\', '/'));
				elements[2] = pils(entry->fileTime);
				MemoryBlock data;
				InputStream *stream = zipFile.createStreamForEntry(i);
				stream->readIntoMemoryBlock(data);
				delete stream;
				elements[1] = PilsString::get((char *)data.getData(), data.getSize());
				build.add(ListConstant::get(elements, 3));
			}
			return build.build();
			*/

	PipesourceUnzip::PipesourceUnzip(const juce::File &file)
		: zipFile(file), at(0)
	{
		count = zipFile.getNumEntries();
	}

	Sink *PipesourceUnzip::kick(Runner &run)
	{
		zipFile.~ZipFile();
		return this + 1;
	}

	const Step *PipesourceUnzip::pass(Runner &run, const PILS::Any *thing)
	{
		thing->releaseReference();
		return ((Pipe &)this[1]).pipeBegin(run);
	}

	const Step *PipesourceUnzip::step_(Runner &run) const
	{
		PipesourceUnzip *this_ = const_cast<PipesourceUnzip*>(this);
		Pipe &pipe = (Pipe &)this[1];
		if (count == at)
		{
			run.sink = this_->kick(run);
			return pipe.pipeEnd(run);
		}
		else
		{
            const juce::ZipFile::ZipEntry *entry = zipFile.getEntry(at);
			const Constant *elements[3];
			elements[0] = pils(entry->filename.replaceCharacter('\\', '/'));
			elements[2] = pils(entry->fileTime);
            juce::MemoryBlock data;
            juce::InputStream *stream = this_->zipFile.createStreamForEntry(this_->at++);
			stream->readIntoMemoryBlock(data);
			delete stream;
			elements[1] = PilsString::get((char *)data.getData(), data.getSize());
			return pipe.pipeItem(run, ListConstant::get(elements, 3));
		}
	}
}
