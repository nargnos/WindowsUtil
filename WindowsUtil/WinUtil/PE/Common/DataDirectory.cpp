#include "Common.h"

PE::DataDirectoryBase::DataDirectoryBase(PeDecoder & pe) :PeStruct(pe)
{

}

PVOID PE::DataDirectoryBase::DirectoryEntryToData()
{
	if (!dataDirectory || dataDirectory->VirtualAddress == NULL)
	{
		return NULL;
	}
	return peDecoder.GetRvaData(dataDirectory->VirtualAddress);
}
