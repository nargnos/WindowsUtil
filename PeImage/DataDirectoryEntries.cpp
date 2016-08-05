#include "stdafx.h"
#include "DataDirectoryEntries.h"

namespace PeDecoder
{
	DataDirectoryEntries::DataDirectoryEntries(TDataPtr ptr, TSizePtr sizePtr) :
		DataPtr(ptr),
		DataSize(sizePtr)
	{
		assert(ptr);
		assert(sizePtr);
	}
	bool DataDirectoryEntries::IsValid() const
	{
		return GetSize() <= IMAGE_NUMBEROF_DIRECTORY_ENTRIES;
	}
	bool DataDirectoryEntries::HasDirectory(DataDirectoryEntryType index)
	{
		return GetDirectoryEntry(index) != nullptr;
	}
	DataDirectoryEntries::TDataPtr DataDirectoryEntries::GetDirectoryEntry(DataDirectoryEntryType index)
	{
		assert(IsValid());
		if (index < GetSize())
		{
			return &GetPtr()[index];
		}
		return nullptr;
	}
	DataDirectoryEntries::TDataPtr DataDirectoryEntries::operator[](DataDirectoryEntryType index)
	{
		return GetDirectoryEntry(index);
	}

	DataDirectoryEntries::iterator DataDirectoryEntries::begin() const
	{
		assert(IsValid());
		return GetPtr();
	}

	DataDirectoryEntries::iterator DataDirectoryEntries::end() const
	{
		assert(IsValid());
		auto size = GetSize();
		size = size > MaxSize() ? MaxSize() : size;
		return GetPtr() + size;
	}

	// 实际最大大小（跟数组大小不一样）

	constexpr DataDirectoryEntries::TSizeType DataDirectoryEntries::MaxSize()
	{
		return _DataDirectoryEntryTypeEnd + 1;
	}

}  // namespace PeDecoder
