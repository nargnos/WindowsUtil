#pragma once
#include "ImportDescriptorIterator.h"
namespace PE
{
	
	class ImportDirectory:
		public DataDirectory<ImportDirectory, PIMAGE_IMPORT_DESCRIPTOR, IMAGE_DIRECTORY_ENTRY_IMPORT>,
		public GetIterator<ImportDescriptorIterator, ImportDirectory>
	{
	public:
		friend GetIteratorBase::Iterator;
		explicit ImportDirectory(PeDecoder& pe);
		~ImportDirectory();
	};

}