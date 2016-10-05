#pragma once
#include <Windows.h>
#include "DataDirectoryEntryType.h"
#include "DataSize.h"
#include "DataPtr.h"

namespace PeDecoder
{
	class NtHeader;

	// 注意这里的GetSize不一定反映真实大小
	class DataDirectoryEntries :
		public Detail::DataSize<PDWORD>,
		public Detail::DataPtr<PIMAGE_DATA_DIRECTORY>
	{
	public:
		typedef TDataPtr iterator;
		DataDirectoryEntries(TDataPtr ptr, TSizePtr sizePtr);
		DataDirectoryEntries(const NtHeader& nt);
		~DataDirectoryEntries() = default;
		bool IsValid() const;
		// index越界返回nullptr
		bool HasDirectory(DataDirectoryEntryType index);
		TDataPtr GetDirectoryEntry(DataDirectoryEntryType index);
		TDataPtr operator[](DataDirectoryEntryType index);
		iterator begin() const;
		iterator end() const;
		// 实际最大大小（跟数组大小不一样）
		static constexpr TSizeType MaxSize();
	protected:
	};

}  // namespace PeDecoder
