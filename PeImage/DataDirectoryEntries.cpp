#include "stdafx.h"
#include "DataDirectoryEntries.h"
#include "INtHeaderVisitor.h"
#include "NtHeader32.h"
#include "NtHeader64.h"


namespace PeDecoder
{
	DataDirectoryEntries::DataDirectoryEntries(PIMAGE_DATA_DIRECTORY ptr, PDWORD sizePtr) :
		ptr_(ptr),
		sizePtr_(sizePtr)
	{
		assert(ptr);
		assert(sizePtr);
	}
	DataDirectoryEntries::DataDirectoryEntries(const NtHeader & nt) :
		ptr_(nullptr),
		sizePtr_(nullptr)
	{
		auto getInfo = MakeNtHeaderVisitor(
			[this](const NtHeader32 & nt)
		{
			const auto& opHeader = nt.GetOptionalHeader();
			Set(opHeader->DataDirectory, &opHeader->NumberOfRvaAndSizes);
		},
			[this](const NtHeader64 & nt)
		{
			const auto& opHeader = nt.GetOptionalHeader();
			Set(opHeader->DataDirectory, &opHeader->NumberOfRvaAndSizes);
		});

		nt.ReadDetails(getInfo);
	}
	bool DataDirectoryEntries::IsValid() const
	{
		return GetSize() <= IMAGE_NUMBEROF_DIRECTORY_ENTRIES;
	}

	bool DataDirectoryEntries::HasDirectory(DataDirectoryEntryType index) const
	{
		return GetDirectoryEntry(index) != nullptr;
	}
	PIMAGE_DATA_DIRECTORY DataDirectoryEntries::GetDirectoryEntry(DataDirectoryEntryType index) const
	{
		assert(IsValid());
		if (index < GetSize())
		{
			return &GetPtr()[index];
		}
		return nullptr;
	}
	PIMAGE_DATA_DIRECTORY DataDirectoryEntries::operator[](DataDirectoryEntryType index) const
	{
		return GetDirectoryEntry(index);
	}


	// 实际最大大小（跟数组大小不一样）

	DWORD DataDirectoryEntries::MaxSize()
	{
		return _DataDirectoryEntryTypeEnd + 1;
	}

	PIMAGE_DATA_DIRECTORY DataDirectoryEntries::begin() const
	{
		assert(IsValid());
		return GetPtr();
	}

	PIMAGE_DATA_DIRECTORY DataDirectoryEntries::end() const
	{
		assert(IsValid());
		auto size = GetSize();
		size = size > MaxSize() ? MaxSize() : size;
		return GetPtr() + size;
	}

	DWORD DataDirectoryEntries::GetSize() const
	{
		assert(sizePtr_);
		return *sizePtr_;
	}

	PIMAGE_DATA_DIRECTORY DataDirectoryEntries::GetPtr() const
	{
		return ptr_;
	}

	void DataDirectoryEntries::Set(PIMAGE_DATA_DIRECTORY data, PDWORD size)
	{
		ptr_ = data;
		sizePtr_ = size;
	}

}  // namespace PeDecoder
