#pragma once
#include "TypeIterator.h"
namespace PE
{
	// 层级结构为 TypeDirectory --> ResourceNameDirectory --> LanguageDirectory --> ResourceData
	// TODO: 未完成
	class ResourceDirectory:
		public DataDirectory<ResourceDirectory, PIMAGE_RESOURCE_DIRECTORY, IMAGE_DIRECTORY_ENTRY_RESOURCE>,
		public GetIterator<TypeIterator,ResourceDirectory>
	{
		static DWORD GetNumberOfEntries(PIMAGE_RESOURCE_DIRECTORY Directory);
		static PIMAGE_RESOURCE_DIR_STRING_U LocateEntryName(PIMAGE_RESOURCE_DIRECTORY directoryRoot, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry);
		static PIMAGE_RESOURCE_DIRECTORY_ENTRY LocateFirstEntry(PIMAGE_RESOURCE_DIRECTORY res);
		static PIMAGE_RESOURCE_DIRECTORY LocateResourceDirectory(PIMAGE_RESOURCE_DIRECTORY directoryRoot, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry);
		static PIMAGE_RESOURCE_DATA_ENTRY LocateResourceDataEntry(PIMAGE_RESOURCE_DIRECTORY directoryRoot, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry);
	public:
		friend GetIteratorBase::Iterator;
		explicit ResourceDirectory(PeDecoder& pe);

		~ResourceDirectory();
		

	};

}