#pragma once
#include <mutex>
#include "PeImageFwd.h"
#include "NtHeaderType.h"
#include "DataPtr.h"
namespace PeDecoder
{
	class NtHeader:
		public Detail::DataPtr<void*>
	{
	public:
		using DataPtr::DataPtr;
		~NtHeader() = default;
	
		static bool Valid(const void* ptr);
		static NtHeaderType GetHeaderType(const void* ptr);

		PIMAGE_FILE_HEADER GetFileHeader();
		PIMAGE_OPTIONAL_HEADER64 GetOptionalHeader64();
		PIMAGE_OPTIONAL_HEADER32 GetOptionalHeader32();

		PIMAGE_NT_HEADERS32 GetPtr32() const;
		PIMAGE_NT_HEADERS64 GetPtr64() const;
		// 只要是pe，这个结构不需验证ntHeader
		const unique_ptr<DataDirectoryEntries>& GetDataDirectoryEntries();
	protected:
		_STD once_flag dataDirInit_;
		unique_ptr<DataDirectoryEntries> dataDirectoryEntries_;
	};
}  // namespace PeDecoder
