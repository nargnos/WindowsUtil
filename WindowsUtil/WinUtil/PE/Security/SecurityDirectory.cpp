#include "SecurityDirectory.h"

PVOID PE::SecurityDirectory::DirectoryEntryToData()
{
	if (peDecoder.IsMapped())  // 不会映射到内存，VirtualAddress即offset
	{
		return NULL;
	}
	if (!dataDirectory || dataDirectory->VirtualAddress == NULL)
	{
		return NULL;
	}
	return reinterpret_cast<PBYTE>(peDecoder.GetBase()) + dataDirectory->VirtualAddress;
}

PE::SecurityDirectory::SecurityDirectory(PeDecoder & pe) :DataDirectoryBase(pe)
{
}

PE::SecurityDirectory::~SecurityDirectory()
{
}
