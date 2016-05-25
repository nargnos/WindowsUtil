#pragma once
#include "PeImageFwd.h"
#include "NtHeaderType.h"
namespace PeDecoder
{
	class NtHeader
	{
	public:
		explicit NtHeader(void* ntHeader);
		~NtHeader() = default;
		bool IsValid() const;
		NtHeaderType GetHeaderType() const;
		
		PIMAGE_FILE_HEADER GetFileHeader();
		PIMAGE_OPTIONAL_HEADER64 GetOptionalHeader64();
		PIMAGE_OPTIONAL_HEADER32 GetOptionalHeader32();

		PIMAGE_NT_HEADERS32 GetRawPtr32() const;
		PIMAGE_NT_HEADERS64 GetRawPtr64() const;
		const unique_ptr<DataDirectoryEntries>& GetDataDirectoryEntries();
	protected:
		void* ntHeader_;
		unique_ptr<DataDirectoryEntries> dataDirectoryEntries_;
	};
}  // namespace PeDecoder
