#pragma once
#include <cassert>
#include "..\PeDecoder.h"
namespace PE
{
	namespace Resource
	{
		// 层级结构为 TypeDirectory --> ResourceNameDirectory --> LanguageDirectory --> ResourceData
		// 需要按这个层级遍历
		class ResourceDirectoryReader
		{
		public:
			ResourceDirectoryReader(PIMAGE_RESOURCE_DIRECTORY root);
			ResourceDirectoryReader();			
			void Reset();

			void ResetCurrentTypeDirectoryEntry();
			void ResetCurrentResourceNameDirectoryEntry();
			void ResetCurrentLanguageDirectoryEntry();

			bool NextTypeDirectoryEntry();
			bool NextResourceNameDirectoryEntry();
			bool NextLanguageDirectoryEntry();

			PIMAGE_RESOURCE_DIRECTORY_ENTRY CurrentTypeDirectoryEntry();
			PIMAGE_RESOURCE_DIRECTORY_ENTRY CurrentResourceNameDirectoryEntry();
			PIMAGE_RESOURCE_DIRECTORY_ENTRY CurrentLanguageDirectoryEntry();

			PIMAGE_RESOURCE_DIRECTORY CurrentTypeDirectory();
			PIMAGE_RESOURCE_DIRECTORY CurrentResourceNameDirectory();
			PIMAGE_RESOURCE_DATA_ENTRY CurrentResourceDataEntry();

			~ResourceDirectoryReader();
		private:
			void SetEntryArrayRange(PIMAGE_RESOURCE_DIRECTORY Directory, PIMAGE_RESOURCE_DIRECTORY_ENTRY& begin, PIMAGE_RESOURCE_DIRECTORY_ENTRY& end);
			PIMAGE_RESOURCE_DIRECTORY root;

			PIMAGE_RESOURCE_DIRECTORY_ENTRY firstTypeDirectoryEntry;
			PIMAGE_RESOURCE_DIRECTORY_ENTRY lastTypeDirectoryEntry;
			PIMAGE_RESOURCE_DIRECTORY_ENTRY currentTypeDirectoryEntry;

			PIMAGE_RESOURCE_DIRECTORY_ENTRY firstResourceNameDirectoryEntry;
			PIMAGE_RESOURCE_DIRECTORY_ENTRY lastResourceNameDirectoryEntry;
			PIMAGE_RESOURCE_DIRECTORY_ENTRY currentResourceNameDirectoryEntry;

			PIMAGE_RESOURCE_DIRECTORY_ENTRY firstLanguageDirectoryEntry;
			PIMAGE_RESOURCE_DIRECTORY_ENTRY lastLanguageDirectoryEntry;
			PIMAGE_RESOURCE_DIRECTORY_ENTRY currentLanguageDirectoryEntry;

		};
		DWORD GetNumberOfEntries(PIMAGE_RESOURCE_DIRECTORY Directory);
		PIMAGE_RESOURCE_DIR_STRING_U LocateEntryName(PIMAGE_RESOURCE_DIRECTORY directoryRoot, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry);
		PIMAGE_RESOURCE_DIRECTORY_ENTRY LocateFirstEntry(PIMAGE_RESOURCE_DIRECTORY res);
		PIMAGE_RESOURCE_DIRECTORY LocateResourceDirectory(PIMAGE_RESOURCE_DIRECTORY directoryRoot, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry);
		PIMAGE_RESOURCE_DATA_ENTRY LocateResourceDataEntry(PIMAGE_RESOURCE_DIRECTORY directoryRoot, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry);
	}
}