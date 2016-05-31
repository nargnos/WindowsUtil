#include "stdafx.h"
#include "ResourceUtil.h"
namespace PeDecoder
{
	DWORD GetNumberOfEntries(PIMAGE_RESOURCE_DIRECTORY directory)
	{
		return directory->NumberOfIdEntries + directory->NumberOfNamedEntries;
	}

	PIMAGE_RESOURCE_DIR_STRING_U LocateEntryName(PIMAGE_RESOURCE_DIRECTORY root, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry)
	{
		return reinterpret_cast<PIMAGE_RESOURCE_DIR_STRING_U>(reinterpret_cast<unsigned char*>(root) + entry->NameOffset);
	}

	PIMAGE_RESOURCE_DIRECTORY_ENTRY LocateFirstEntry(PIMAGE_RESOURCE_DIRECTORY res)
	{
		return reinterpret_cast<PIMAGE_RESOURCE_DIRECTORY_ENTRY>(reinterpret_cast<unsigned char*>(res) + sizeof(IMAGE_RESOURCE_DIRECTORY));
	}
	unsigned char* GetDirectory(PIMAGE_RESOURCE_DIRECTORY root, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry)
	{
		return reinterpret_cast<unsigned char*>(root) + entry->OffsetToDirectory;
	}


	PIMAGE_RESOURCE_DIRECTORY LocateResourceDirectory(PIMAGE_RESOURCE_DIRECTORY root, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry)
	{
		return reinterpret_cast<PIMAGE_RESOURCE_DIRECTORY>(GetDirectory(root,entry));
	}

	PIMAGE_RESOURCE_DATA_ENTRY LocateResourceDataEntry(PIMAGE_RESOURCE_DIRECTORY root, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry)
	{
		return reinterpret_cast<PIMAGE_RESOURCE_DATA_ENTRY>(GetDirectory(root, entry));
	}
}  // namespace PeDecoder


