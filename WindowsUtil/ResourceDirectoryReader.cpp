#include "ResourceDirectoryReader.h"

namespace PE
{
	ResourceDirectoryReader::ResourceDirectoryReader(PIMAGE_RESOURCE_DIRECTORY res)		
	{		
		Init(res);
	}
	ResourceDirectoryReader::ResourceDirectoryReader()
	{
		firstEntry = NULL;
		Reset();
	}
	void ResourceDirectoryReader::Init(PIMAGE_RESOURCE_DIRECTORY res)
	{
		this->res = res;
		numberOfEntries = res->NumberOfIdEntries + res->NumberOfNamedEntries;
		if (numberOfEntries > 0)
		{
			firstEntry = LocateFirstEntry(res);
		}
		else
		{
			firstEntry = NULL;
		}
		Reset();
	}
	bool ResourceDirectoryReader::Next()
	{
		if (firstEntry == NULL)
		{
			return false;
		}
		if (currentIndex < numberOfEntries)
		{
			currentIndex++;			
			return true;
		}
		return false;
	}
	PIMAGE_RESOURCE_DIRECTORY_ENTRY ResourceDirectoryReader::Current()
	{
		if (currentIndex == -1)
		{
			return NULL;
		}
		return &firstEntry[currentIndex];
	}
	void ResourceDirectoryReader::Reset()
	{
		currentIndex = -1;
	}
	
	ResourceDirectoryReader::~ResourceDirectoryReader()
	{
	}


	PIMAGE_RESOURCE_DIRECTORY_STRING LocateEntryName(PIMAGE_RESOURCE_DIRECTORY directoryRoot, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry)
	{
		return PIMAGE_RESOURCE_DIRECTORY_STRING((PCHAR)directoryRoot + entry->NameOffset);
	}
	 PIMAGE_RESOURCE_DIRECTORY_ENTRY LocateFirstEntry(PIMAGE_RESOURCE_DIRECTORY res)
	{
		return (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((PCHAR)res + sizeof(IMAGE_RESOURCE_DIRECTORY));
	}
	PIMAGE_RESOURCE_DIRECTORY LocateResourceDirectory(PIMAGE_RESOURCE_DIRECTORY directoryRoot, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry)
	{
		return PIMAGE_RESOURCE_DIRECTORY((PCHAR)directoryRoot + entry->OffsetToDirectory);
	}
	PIMAGE_RESOURCE_DATA_ENTRY LocateResourceDataEntry(PIMAGE_RESOURCE_DIRECTORY directoryRoot, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry)
	{
		return PIMAGE_RESOURCE_DATA_ENTRY((PCHAR)directoryRoot + entry->OffsetToDirectory);
	}
}