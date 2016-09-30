#include "stdafx.h"
#include <tuple>
#include "DataDirectoryEntries.h"
#include "NtHeader.h"

namespace PeDecoder
{
	_STD tuple<DataDirectoryEntries::TDataPtr, DataDirectoryEntries::TSizePtr> GetDataDirectoryPtrAndSize(NtHeader & nt)
	{
		_STD tuple<DataDirectoryEntries::TDataPtr, DataDirectoryEntries::TSizePtr> result;
		switch (NtHeader::GetHeaderType(nt.GetPtr32()))
		{
		case NtHeaderType::NtHeader32:
		{
			auto tmp = nt.GetOptionalHeader32();
			_STD make_tuple(tmp->DataDirectory, &tmp->NumberOfRvaAndSizes).swap(result);
		}
		break;
		case NtHeaderType::NtHeader64:
		{
			auto tmp = nt.GetOptionalHeader64();
			_STD make_tuple(tmp->DataDirectory, &tmp->NumberOfRvaAndSizes).swap(result);
		}
		break;
		default:
			break;
		}
		return result;
	}
	DataDirectoryEntries::DataDirectoryEntries(TDataPtr ptr, TSizePtr sizePtr) :
		DataPtr(ptr),
		DataSize(sizePtr)
	{
		assert(ptr);
		assert(sizePtr);
	}
	DataDirectoryEntries::DataDirectoryEntries(NtHeader & nt) :
		DataPtr(nullptr),
		DataSize(nullptr)
	{
		auto val = GetDataDirectoryPtrAndSize(nt);
		SetPtr(_STD get<0>(val));
		SetSizePtr(_STD get<1>(val));
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
