#pragma once
#include <windows.h>
#include <memory>
#include "NtHeaderType.h"
#include "INtHeaderVisitor.h"
#include "DataDirectoryEntries.h"
namespace PeDecoder
{
	class DosHeader;
	class NtHeader
	{
	public:
		virtual ~NtHeader() = default;

		static NtHeaderType GetHeaderType(const void* ptr);
		static void* GetNtHeaderPtr(const PIMAGE_DOS_HEADER dosHeader);
		static bool IsValid(const void* ptr);
		static unique_ptr<NtHeader> GetNtHeaderInstance(const DosHeader& dosHeader);

		NtHeaderType GetHeaderType() const;
		bool IsValid() const;
		PIMAGE_FILE_HEADER GetFileHeader() const;
		unique_ptr<DataDirectoryEntries> GetDataDirectoryEntries() const;
		unsigned char* GetPos() const;

		virtual void ReadDetails(const INtHeaderVisitor & visitor) const = 0;
	protected:
		explicit NtHeader(const PIMAGE_DOS_HEADER dosHeader);

		PIMAGE_NT_HEADERS32 GetHeader32() const;


		void* ptr_;
	};
}  // namespace PeDecoder
