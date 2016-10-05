#pragma once
#include <Windows.h>
#include <memory>
#include "NtHeaderType.h"
#include "DataPtr.h"
namespace PeDecoder
{
	class DataDirectoryEntries;
	class NtHeader :
		public Detail::DataPtr<void*>
	{
	public:
		NtHeader(const PIMAGE_DOS_HEADER dosHeader);
		NtHeader(const PIMAGE_NT_HEADERS32 ntPtr32);
		NtHeader(const PIMAGE_NT_HEADERS64 ntPtr64);

		static bool Valid(const void* ptr);
		static NtHeaderType GetHeaderType(const void* ptr);
		static void* GetNtHeaderPtr(const PIMAGE_DOS_HEADER dosHeader);

		bool Valid() const;
		NtHeaderType GetHeaderType() const;
		PIMAGE_FILE_HEADER GetFileHeader() const;
		PIMAGE_OPTIONAL_HEADER64 GetOptionalHeader64() const;
		PIMAGE_OPTIONAL_HEADER32 GetOptionalHeader32() const;

		PIMAGE_NT_HEADERS32 GetPtr32() const;
		PIMAGE_NT_HEADERS64 GetPtr64() const;
		// 只要是pe，这个结构不需验证ntHeader
		unique_ptr<DataDirectoryEntries> GetDataDirectoryEntries() const;
	protected:
		void CreateDataDirectoryEntries() const;
	};
}  // namespace PeDecoder
