#include "ResourceDirectory.h"

DWORD PE::ResourceDirectory::GetNumberOfEntries(PIMAGE_RESOURCE_DIRECTORY Directory)
{
	return Directory->NumberOfIdEntries + Directory->NumberOfNamedEntries;
}

PIMAGE_RESOURCE_DIR_STRING_U PE::ResourceDirectory::LocateEntryName(PIMAGE_RESOURCE_DIRECTORY directoryRoot, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry)
{
	return PIMAGE_RESOURCE_DIR_STRING_U((PUINT8)directoryRoot + entry->NameOffset);
}

PIMAGE_RESOURCE_DIRECTORY_ENTRY PE::ResourceDirectory::LocateFirstEntry(PIMAGE_RESOURCE_DIRECTORY res)
{
	return (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((PUINT8)res + sizeof(IMAGE_RESOURCE_DIRECTORY));
}

PIMAGE_RESOURCE_DIRECTORY PE::ResourceDirectory::LocateResourceDirectory(PIMAGE_RESOURCE_DIRECTORY directoryRoot, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry)
{
	return PIMAGE_RESOURCE_DIRECTORY((PUINT8)directoryRoot + entry->OffsetToDirectory);
}

PIMAGE_RESOURCE_DATA_ENTRY PE::ResourceDirectory::LocateResourceDataEntry(PIMAGE_RESOURCE_DIRECTORY directoryRoot, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry)
{
	return PIMAGE_RESOURCE_DATA_ENTRY((PUINT8)directoryRoot + entry->OffsetToDirectory);
}

PE::ResourceDirectory::ResourceDirectory(PeDecoder* pe) :DataDirectoryBase(pe)
{
	canCreateIterator = true;
}

PE::ResourceDirectory::~ResourceDirectory()
{
}
