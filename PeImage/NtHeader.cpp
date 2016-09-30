#include "stdafx.h"
#include <bitset>
#include "NtHeader.h"
#include "DataDirectoryEntries.h"
namespace PeDecoder
{

	bool NtHeader::Valid(const void * ptr)
	{
		// 根据枚举值查表返回内容
		static const _STD bitset<8> resultTable(0b11000000);

		auto&& ntHeader = reinterpret_cast<const PIMAGE_NT_HEADERS32>(const_cast<void*>(ptr));
		auto&& pos = static_cast<unsigned char>(GetHeaderType(ptr)) +
			(static_cast<unsigned char>(ntHeader->Signature == IMAGE_NT_SIGNATURE) << 2);

		return resultTable.test(pos);
	}

	NtHeaderType NtHeader::GetHeaderType(const void* ptr)
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

	PIMAGE_FILE_HEADER NtHeader::GetFileHeader()
	{
		return &GetPtr32()->FileHeader;
	}
	PIMAGE_OPTIONAL_HEADER64 NtHeader::GetOptionalHeader64()
	{
		return &GetPtr64()->OptionalHeader;
	}
	PIMAGE_OPTIONAL_HEADER32 NtHeader::GetOptionalHeader32()
	{
		return &GetPtr32()->OptionalHeader;
	}
	PIMAGE_NT_HEADERS32 NtHeader::GetPtr32() const
	{
		return reinterpret_cast<PIMAGE_NT_HEADERS32>(GetPtr());
	}
	PIMAGE_NT_HEADERS64 NtHeader::GetPtr64() const
	{
		return reinterpret_cast<PIMAGE_NT_HEADERS64>(GetPtr());
	}
	const unique_ptr<DataDirectoryEntries>& NtHeader::GetDataDirectoryEntries()
	{
		if (!dataDirectoryEntries_)
		{
			_STD call_once(dataDirInit_, [&]()
			{
				dataDirectoryEntries_ = make_unique<DataDirectoryEntries>(*this);
			});
		}
		return dataDirectoryEntries_;
	}
}  // namespace PeDecoder
