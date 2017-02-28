#pragma once
#include <Windows.h>
#include <memory>
#include "IPeImage.h"
#include "DataDirectoryEntryType.h"
namespace PeDecoder
{
	// 注意这里的GetSize不一定反映真实大小
	class DataDirectoryEntries
	{
	public:
		explicit DataDirectoryEntries(const _STD shared_ptr<IPeImage>& pe);
		bool IsValid() const;
		// 实际最大大小（跟数组大小不一样）
		static DWORD MaxSize();
		PIMAGE_DATA_DIRECTORY begin() const;
		PIMAGE_DATA_DIRECTORY end() const;
		DWORD GetSize() const;

		bool HasDirectory(DataDirectoryEntryType index) const;
		static bool HasDirectory(PIMAGE_DATA_DIRECTORY first, DataDirectoryEntryType index);
		static PIMAGE_DATA_DIRECTORY GetDirectoryEntry(PIMAGE_DATA_DIRECTORY first, DataDirectoryEntryType index);
		PIMAGE_DATA_DIRECTORY GetDirectoryEntry(DataDirectoryEntryType index) const;
		PIMAGE_DATA_DIRECTORY operator[](DataDirectoryEntryType index) const;
		virtual ~DataDirectoryEntries();
	protected:
		PIMAGE_DATA_DIRECTORY GetPtr() const;
		_STD shared_ptr<IPeImage> pe_;
		DWORD size_;
		PIMAGE_DATA_DIRECTORY ptr_;
	};

}  // namespace PeDecoder
