#include "Common.h"

PE::DataDirectory_PeDecoder::DataDirectory_PeDecoder(PeDecoder & pe) :PeStruct(pe)
{

}

PVOID PE::DataDirectory_PeDecoder::DirectoryEntryToData()
{
	if (!dataDirectory || dataDirectory->VirtualAddress == NULL)
	{
		return NULL;
	}
	return peDecoder.GetRvaData(dataDirectory->VirtualAddress);
}
