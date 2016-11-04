#include "stdafx.h"
#include "DirectoryBase.h"
#include "NtHeader.h"

std::pair<PVOID, PDWORD> PeDecoder::Detail::GetDataDirectoryEntry(const IDataDirectoryUtil& util, DataDirectoryEntryType index)
{
	_STD pair<PVOID, PDWORD> result;
	auto entry = util.GetDirectoryEntry(index);
	if (entry->VirtualAddress != 0)
	{
		result.first = util.RvaToDataPtr(entry->VirtualAddress);
		result.second = &entry->Size;
	}
	return result;
}
