#include "stdafx.h"
#include <bitset>
#include "DosHeader.h"
#include "NtHeader.h"
#include "NtHeader32.h"
#include "NtHeader64.h"
#include "DataDirectoryEntries.h"
namespace PeDecoder
{
	NtHeaderType NtHeader::GetHeaderType(const void* ptr)
	{
		switch (reinterpret_cast<const IMAGE_NT_HEADERS32*>(ptr)->OptionalHeader.Magic)
		{
		case IMAGE_NT_OPTIONAL_HDR64_MAGIC:
			return NtHeaderType::NtHeader64;
		case IMAGE_NT_OPTIONAL_HDR32_MAGIC:
			return NtHeaderType::NtHeader32;
		case IMAGE_ROM_OPTIONAL_HDR_MAGIC:
			return NtHeaderType::Rom;
		default:
			// UnKnown
			break;
		}
		return NtHeaderType::UnKnown;
	}
	void * NtHeader::GetNtHeaderPtr(const PIMAGE_DOS_HEADER dosHeader)
	{
		return reinterpret_cast<unsigned char*>(dosHeader) + dosHeader->e_lfanew;
	}
	NtHeaderType NtHeader::GetHeaderType() const
	{
		return GetHeaderType(RawPtr());
	}
	MachineType NtHeader::GetMachineType() const
	{
		return static_cast<MachineType>(GetFileHeader()->Machine);
	}
	FileHeaderCharacteristics NtHeader::GetFileHeaderCharacteristics() const
	{
		return static_cast<FileHeaderCharacteristics>(GetFileHeader()->Characteristics);
	}
	bool NtHeader::IsValid() const
	{
		// 根据枚举值查表返回内容，验证过后GetHeaderType返回必为NtHeader32或NtHeader64之一
		// 主要是验证NtHeader32或NtHeader64和IMAGE_NT_SIGNATURE标识，Rom先不理
		static const _STD bitset<8> resultTable(0b11000000);

		auto&& ntHeader = reinterpret_cast<const PIMAGE_NT_HEADERS32>(const_cast<unsigned char*>(RawPtr()));
		auto&& pos = static_cast<unsigned char>(GetHeaderType()) +
			(static_cast<unsigned char>(ntHeader->Signature == IMAGE_NT_SIGNATURE) << 2);

		return resultTable.test(pos);
	}
	PIMAGE_FILE_HEADER NtHeader::GetFileHeader() const
	{
		return &GetHeader32()->FileHeader;
	}
	WORD NtHeader::GetNumberOfSections() const
	{
		return GetFileHeader()->NumberOfSections;
	}
	unsigned char * NtHeader::RawPtr() const
	{
		return static_cast<unsigned char *>(ptr_);
	}
	NtHeader::NtHeader(void * ntHeaderRawPtr) :
		ptr_(ntHeaderRawPtr)
	{
	}
	PIMAGE_NT_HEADERS32 NtHeader::GetHeader32() const
	{
		return static_cast<PIMAGE_NT_HEADERS32>(ptr_);
	}
}  // namespace PeDecoder
