#include "ResourceDirectoryReader.h"

namespace PE
{
	namespace Resource
	{
		ResourceDirectoryIterator::ResourceDirectoryIterator(PIMAGE_RESOURCE_DIRECTORY root) :root(root)
		{
			assert(root);
			SetEntryArrayRange(root, firstTypeDirectoryEntry, lastTypeDirectoryEntry);
			Reset();
		}
		void ResourceDirectoryIterator::SetEntryArrayRange(PIMAGE_RESOURCE_DIRECTORY Directory, PIMAGE_RESOURCE_DIRECTORY_ENTRY& begin, PIMAGE_RESOURCE_DIRECTORY_ENTRY& end)
		{
			begin = LocateFirstEntry(Directory);
			end = begin + GetNumberOfEntries(Directory);
		}
		bool ResourceDirectoryIterator::NextTypeDirectoryEntry()
		{
			if (currentTypeDirectoryEntry)
			{
				if (++currentTypeDirectoryEntry < lastTypeDirectoryEntry)
				{
					ResetCurrentResourceNameDirectoryEntry();
					ResetCurrentLanguageDirectoryEntry();
					return true;
				}
				
			}
			else
			{
				if (firstTypeDirectoryEntry)
				{
					currentTypeDirectoryEntry = firstTypeDirectoryEntry; 
					ResetCurrentResourceNameDirectoryEntry();
					ResetCurrentLanguageDirectoryEntry();
					return true;
				}
			}
			return false;
		}
		bool ResourceDirectoryIterator::NextResourceNameDirectoryEntry()
		{
			if (currentResourceNameDirectoryEntry)
			{
				if (++currentResourceNameDirectoryEntry < lastResourceNameDirectoryEntry)
				{
					ResetCurrentLanguageDirectoryEntry();
					return true;
				}
			}
			else
			{
				if (firstResourceNameDirectoryEntry)
				{
					currentResourceNameDirectoryEntry = firstResourceNameDirectoryEntry;
					ResetCurrentLanguageDirectoryEntry();
					return true;
				}
			}
			return false;
		}
		bool ResourceDirectoryIterator::NextLanguageDirectoryEntry()
		{
			if (currentLanguageDirectoryEntry)
			{
				if (++currentLanguageDirectoryEntry < lastLanguageDirectoryEntry)
				{
					return true;
				}
			}
			else
			{
				if (firstLanguageDirectoryEntry)
				{
					currentLanguageDirectoryEntry = firstLanguageDirectoryEntry;
					return true;
				}
			}
			return false;
		}

		void ResourceDirectoryIterator::Reset()
		{
			ResetCurrentTypeDirectoryEntry();
			ResetCurrentResourceNameDirectoryEntry();
			ResetCurrentLanguageDirectoryEntry();
		}
		void ResourceDirectoryIterator::ResetCurrentTypeDirectoryEntry()
		{
			currentTypeDirectoryEntry = NULL;
		}
		void ResourceDirectoryIterator::ResetCurrentResourceNameDirectoryEntry()
		{
			if (currentTypeDirectoryEntry)
			{
				SetEntryArrayRange(LocateResourceDirectory(root, currentTypeDirectoryEntry), firstResourceNameDirectoryEntry, lastResourceNameDirectoryEntry);
			}
			
			currentResourceNameDirectoryEntry = NULL;
		}
		void ResourceDirectoryIterator::ResetCurrentLanguageDirectoryEntry()
		{
			if (currentResourceNameDirectoryEntry)
			{
				SetEntryArrayRange(LocateResourceDirectory(root, currentResourceNameDirectoryEntry), firstLanguageDirectoryEntry, lastLanguageDirectoryEntry);
			}
			currentLanguageDirectoryEntry = NULL;
		}

		PIMAGE_RESOURCE_DIRECTORY_ENTRY ResourceDirectoryIterator::CurrentTypeDirectoryEntry()
		{
			return currentTypeDirectoryEntry;
		}
		PIMAGE_RESOURCE_DIRECTORY_ENTRY ResourceDirectoryIterator::CurrentResourceNameDirectoryEntry()
		{
			return currentResourceNameDirectoryEntry;
		}
		PIMAGE_RESOURCE_DIRECTORY_ENTRY ResourceDirectoryIterator::CurrentLanguageDirectoryEntry()
		{
			return currentLanguageDirectoryEntry;
		}


		PIMAGE_RESOURCE_DIRECTORY ResourceDirectoryIterator::CurrentTypeDirectory()
		{
			return currentTypeDirectoryEntry?LocateResourceDirectory(root, currentTypeDirectoryEntry):NULL;
		}
		PIMAGE_RESOURCE_DIRECTORY ResourceDirectoryIterator::CurrentResourceNameDirectory()
		{
			return currentResourceNameDirectoryEntry?LocateResourceDirectory(root, currentResourceNameDirectoryEntry): NULL;
		}
		PIMAGE_RESOURCE_DATA_ENTRY ResourceDirectoryIterator::CurrentResourceDataEntry()
		{
			return currentLanguageDirectoryEntry?LocateResourceDataEntry(root, currentLanguageDirectoryEntry):NULL;
		}

		ResourceDirectoryIterator::~ResourceDirectoryIterator()
		{
		}

		DWORD GetNumberOfEntries(PIMAGE_RESOURCE_DIRECTORY Directory)
		{
			return Directory->NumberOfIdEntries + Directory->NumberOfNamedEntries;
		}
		PIMAGE_RESOURCE_DIR_STRING_U LocateEntryName(PIMAGE_RESOURCE_DIRECTORY directoryRoot, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry)
		{
			return PIMAGE_RESOURCE_DIR_STRING_U((PUINT8)directoryRoot + entry->NameOffset);
		}
		PIMAGE_RESOURCE_DIRECTORY_ENTRY LocateFirstEntry(PIMAGE_RESOURCE_DIRECTORY res)
		{
			return (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((PUINT8)res + sizeof(IMAGE_RESOURCE_DIRECTORY));
		}
		PIMAGE_RESOURCE_DIRECTORY LocateResourceDirectory(PIMAGE_RESOURCE_DIRECTORY directoryRoot, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry)
		{
			return PIMAGE_RESOURCE_DIRECTORY((PUINT8)directoryRoot + entry->OffsetToDirectory);
		}
		PIMAGE_RESOURCE_DATA_ENTRY LocateResourceDataEntry(PIMAGE_RESOURCE_DIRECTORY directoryRoot, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry)
		{
			return PIMAGE_RESOURCE_DATA_ENTRY((PUINT8)directoryRoot + entry->OffsetToDirectory);
		}
	}
}