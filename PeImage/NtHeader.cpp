#include "stdafx.h"
#include "NtHeader.h"
#include "DataDirectoryEntries.h"
namespace PeDecoder
{

	NtHeader::NtHeader(void* ntHeader) :
		ntHeader_(ntHeader)
	{
		assert(ntHeader);
	}

	bool NtHeader::IsValid() const
	{
		auto type = GetHeaderType();
		return GetRawPtr32()->Signature == IMAGE_NT_SIGNATURE &&
			type != NtHeaderType::UnKnown &&
			type != NtHeaderType::Rom;
	}
	NtHeaderType NtHeader::GetHeaderType() const
	{
		switch (GetRawPtr32()->OptionalHeader.Magic)
		{
		case IMAGE_NT_OPTIONAL_HDR64_MAGIC:
			return NtHeaderType::NtHeader64;
		case IMAGE_NT_OPTIONAL_HDR32_MAGIC:
			return NtHeaderType::NtHeader32;
		case IMAGE_ROM_OPTIONAL_HDR_MAGIC:
			return NtHeaderType::Rom;
		default:
			return NtHeaderType::UnKnown;
		}
	}
	PIMAGE_FILE_HEADER NtHeader::GetFileHeader()
	{
		return &GetRawPtr32()->FileHeader;
	}
	PIMAGE_OPTIONAL_HEADER64 NtHeader::GetOptionalHeader64()
	{
		return &GetRawPtr64()->OptionalHeader;
	}
	PIMAGE_OPTIONAL_HEADER32 NtHeader::GetOptionalHeader32()
	{
		return &GetRawPtr32()->OptionalHeader;
	}
	PIMAGE_NT_HEADERS32 NtHeader::GetRawPtr32() const
	{
		return reinterpret_cast<PIMAGE_NT_HEADERS32>(ntHeader_);
	}
	PIMAGE_NT_HEADERS64 NtHeader::GetRawPtr64() const
	{
		return reinterpret_cast<PIMAGE_NT_HEADERS64>(ntHeader_);
	}
	const unique_ptr<DataDirectoryEntries>& NtHeader::GetDataDirectoryEntries()
	{
		if (!dataDirectoryEntries_)
		{
			auto type = GetHeaderType();
			switch (type)
			{
			case NtHeaderType::NtHeader32:
			{
				auto tmp = GetOptionalHeader32();
				auto ptr = tmp->DataDirectory;
				auto sizePtr = &tmp->NumberOfRvaAndSizes;
				dataDirectoryEntries_ = make_unique<DataDirectoryEntries>(ptr, sizePtr);
			}
			break;
			case NtHeaderType::NtHeader64:
			{
				auto tmp = GetOptionalHeader64();
				auto ptr = tmp->DataDirectory;
				auto sizePtr = &tmp->NumberOfRvaAndSizes;
				dataDirectoryEntries_ = make_unique<DataDirectoryEntries>(ptr, sizePtr);
			}
			break;
			default:
				break;
			}
		}
		return dataDirectoryEntries_;
	}
}  // namespace PeDecoder
