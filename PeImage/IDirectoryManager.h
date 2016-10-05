#pragma once
#include <Windows.h>
#include "DataDirectoryEntryType.h"
namespace PeDecoder
{
	__interface IDirectoryManager
	{
		bool HasDirectory(DataDirectoryEntryType index) const;
		PIMAGE_DATA_DIRECTORY GetDirectoryEntry(DataDirectoryEntryType index) const;
	};
}  // namespace PeDecoder
