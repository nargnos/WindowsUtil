#pragma once
#include "..\PeDecoder.h"
namespace PE
{
	namespace Resource
	{
		class ResourceDirectoryReader
		{
		public:
			ResourceDirectoryReader(PIMAGE_RESOURCE_DIRECTORY res);
			ResourceDirectoryReader();
			void Init(PIMAGE_RESOURCE_DIRECTORY res);
			bool Next();
			PIMAGE_RESOURCE_DIRECTORY_ENTRY Current();
			void Reset();
			~ResourceDirectoryReader();
		private:
			PIMAGE_RESOURCE_DIRECTORY res;
			WORD numberOfEntries;
			WORD currentIndex;
			PIMAGE_RESOURCE_DIRECTORY_ENTRY firstEntry;
		};
		PIMAGE_RESOURCE_DIRECTORY LocateResourceDirectory(PIMAGE_RESOURCE_DIRECTORY_ENTRY entry);
		PIMAGE_RESOURCE_DATA_ENTRY LocateResourceDataEntry(PIMAGE_RESOURCE_DIRECTORY_ENTRY entry);
		PIMAGE_RESOURCE_DIRECTORY_ENTRY LocateFirstEntry(PIMAGE_RESOURCE_DIRECTORY res);
		PIMAGE_RESOURCE_DIRECTORY_STRING LocateEntryName(PIMAGE_RESOURCE_DIRECTORY_ENTRY entry);
	}
}