#include <PE\Resource\ResourceDirectoryReader.h>

namespace PE
{
	namespace Resource
	{
		ResourceDirectoryReader::ResourceDirectoryReader(PIMAGE_RESOURCE_DIRECTORY root) :root(root)
		{
			SetEntryArrayRange(root, firstTypeDirectoryEntry, lastTypeDirectoryEntry);
			Reset();
		}
		void ResourceDirectoryReader::SetEntryArrayRange(PIMAGE_RESOURCE_DIRECTORY Directory, PIMAGE_RESOURCE_DIRECTORY_ENTRY& begin, PIMAGE_RESOURCE_DIRECTORY_ENTRY& end)
		{
			begin = LocateFirstEntry(Directory);
			end = begin + GetNumberOfEntries(Directory);
		}
		bool ResourceDirectoryReader::NextTypeDirectoryEntry()
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
		bool ResourceDirectoryReader::NextResourceNameDirectoryEntry()
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
		bool ResourceDirectoryReader::NextLanguageDirectoryEntry()
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

		void ResourceDirectoryReader::Reset()
		{
			ResetCurrentTypeDirectoryEntry();
			ResetCurrentResourceNameDirectoryEntry();
			ResetCurrentLanguageDirectoryEntry();
		}
		void ResourceDirectoryReader::ResetCurrentTypeDirectoryEntry()
		{
			currentTypeDirectoryEntry = NULL;
		}
		void ResourceDirectoryReader::ResetCurrentResourceNameDirectoryEntry()
		{
			if (currentTypeDirectoryEntry)
			{
				SetEntryArrayRange(LocateResourceDirectory(root, currentTypeDirectoryEntry), firstResourceNameDirectoryEntry, lastResourceNameDirectoryEntry);
			}
			
			currentResourceNameDirectoryEntry = NULL;
		}
		void ResourceDirectoryReader::ResetCurrentLanguageDirectoryEntry()
		{
			if (currentResourceNameDirectoryEntry)
			{
				SetEntryArrayRange(LocateResourceDirectory(root, currentResourceNameDirectoryEntry), firstLanguageDirectoryEntry, lastLanguageDirectoryEntry);
			}
			currentLanguageDirectoryEntry = NULL;
		}

		PIMAGE_RESOURCE_DIRECTORY_ENTRY ResourceDirectoryReader::CurrentTypeDirectoryEntry()
		{
			return currentTypeDirectoryEntry;
		}
		PIMAGE_RESOURCE_DIRECTORY_ENTRY ResourceDirectoryReader::CurrentResourceNameDirectoryEntry()
		{
			return currentResourceNameDirectoryEntry;
		}
		PIMAGE_RESOURCE_DIRECTORY_ENTRY ResourceDirectoryReader::CurrentLanguageDirectoryEntry()
		{
			return currentLanguageDirectoryEntry;
		}


		PIMAGE_RESOURCE_DIRECTORY ResourceDirectoryReader::CurrentTypeDirectory()
		{
			if (currentTypeDirectoryEntry)
			{
				return LocateResourceDirectory(root, currentTypeDirectoryEntry);
			}
			return NULL;
		}
		PIMAGE_RESOURCE_DIRECTORY ResourceDirectoryReader::CurrentResourceNameDirectory()
		{
			if (currentResourceNameDirectoryEntry)
			{
				return LocateResourceDirectory(root, currentResourceNameDirectoryEntry);
			}
			return NULL;
		}
		PIMAGE_RESOURCE_DATA_ENTRY ResourceDirectoryReader::CurrentResourceDataEntry()
		{
			if (currentLanguageDirectoryEntry)
			{
				return LocateResourceDataEntry(root, currentLanguageDirectoryEntry);
			}
			return NULL;
		}

		ResourceDirectoryReader::~ResourceDirectoryReader()
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