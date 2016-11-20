#include "stdafx.h"
#include <bitset>
#include "DosHeader.h"
#include "NtHeader.h"
#include "NtHeader32.h"
#include "NtHeader64.h"
#include "DataDirectoryEntries.h"
namespace PeDecoder
{
	NtHeader::NtHeader(const PIMAGE_DOS_HEADER dosHeader) :
		ptr_(GetNtHeaderPtr(dosHeader))
	{
	}
	NtHeaderType NtHeader::GetHeaderType() const
	{
		return GetHeaderType(ptr_);
	}
	bool NtHeader::IsValid() const
	{
		return IsValid(ptr_);
	}
	NtHeaderType NtHeader::GetHeaderType(const void * ptr)
	{
		switch (reinterpret_cast<const PIMAGE_NT_HEADERS32>(const_cast<void*>(ptr))->OptionalHeader.Magic)
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
	bool NtHeader::IsValid(const void * ptr)
	{
		// 根据枚举值查表返回内容，验证过后GetHeaderType返回必为NtHeader32或NtHeader64之一
		// 主要是验证NtHeader32或NtHeader64和IMAGE_NT_SIGNATURE标识，Rom先不理
		static const _STD bitset<8> resultTable(0b11000000);

		auto&& ntHeader = reinterpret_cast<const PIMAGE_NT_HEADERS32>(const_cast<void*>(ptr));
		auto&& pos = static_cast<unsigned char>(GetHeaderType(ptr)) +
			(static_cast<unsigned char>(ntHeader->Signature == IMAGE_NT_SIGNATURE) << 2);

		return resultTable.test(pos);
	}
	unique_ptr<NtHeader> NtHeader::GetNtHeaderInstance(const DosHeader& dosHeader)
	{
		using namespace std;
		assert(dosHeader.IsValid());
		
		auto type = GetHeaderType(GetNtHeaderPtr(dosHeader.RawPtr()));
		unique_ptr<NtHeader> result;
		switch (type)
		{
		case PeDecoder::NtHeaderType::NtHeader32:
			result = make_unique<NtHeader32>(dosHeader.RawPtr());
			break;
		case PeDecoder::NtHeaderType::NtHeader64:
			result = make_unique<NtHeader64>(dosHeader.RawPtr());
			break;
		default:
			break;
		}
		return result;
	}
	PIMAGE_FILE_HEADER NtHeader::GetFileHeader() const
	{
		return &GetHeader32()->FileHeader;
	}
	unique_ptr<DataDirectoryEntries> NtHeader::GetDataDirectoryEntries() const
	{
		return make_unique<DataDirectoryEntries>(*this);
	}
	unsigned char * NtHeader::GetPos() const
	{
		return static_cast<unsigned char *>(ptr_);
	}
	PIMAGE_NT_HEADERS32 NtHeader::GetHeader32() const
	{
		return static_cast<PIMAGE_NT_HEADERS32>(ptr_);
	}
}  // namespace PeDecoder
