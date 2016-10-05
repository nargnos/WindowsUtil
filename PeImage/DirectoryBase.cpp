#include "stdafx.h"
#include "DirectoryBase.h"
#include "NtHeader.h"

std::pair<PVOID, PDWORD> PeDecoder::Detail::GetDataDirectoryEntry(IPeImage & pe, DataDirectoryEntryType index)
{
	_STD pair<PVOID, PDWORD> result;
	auto entry = pe.GetDirectoryEntry(index);
	if (entry->VirtualAddress != 0)
	{
		result.first = pe.RvaToDataPtr(entry->VirtualAddress);
		result.second = &entry->Size;
	}
	return result;
}
