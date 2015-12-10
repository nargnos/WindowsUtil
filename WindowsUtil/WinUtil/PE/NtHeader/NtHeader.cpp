#include "NtHeader.h"

PE::NtHeader::NtHeader(PeDecoder & pe) :PeStructBase(pe)
{
	ntHeader = reinterpret_cast<PBYTE>(peDecoder.GetBase()) + peDecoder.GetDosHeader()->GetValue()->e_lfanew;
	hasNtHeader32 = false;
}

PE::NtHeader::~NtHeader() {}

bool PE::NtHeader::VerifyNtSignature()
{
	return GetNtHeader32()->Signature == IMAGE_NT_SIGNATURE;
}

const PIMAGE_NT_HEADERS32 PE::NtHeader::GetNtHeader32()
{
	return reinterpret_cast<PIMAGE_NT_HEADERS32>(ntHeader);
}

const PIMAGE_NT_HEADERS64 PE::NtHeader::GetNtHeader64()
{
	return reinterpret_cast<PIMAGE_NT_HEADERS64>(ntHeader);
}

// IMAGE_ROM_OPTIONAL_HDR_MAGIC类型返回false（没写解析代码）

bool PE::NtHeader::InitFunc()
{
	switch (GetNtHeader32()->OptionalHeader.Magic)
	{
	case IMAGE_NT_OPTIONAL_HDR64_MAGIC:
		hasNtHeader32 = false;
		imageDataDirectoryEntry = GetNtHeader64()->OptionalHeader.DataDirectory;
		imageDataDirectorySize = &GetNtHeader64()->OptionalHeader.NumberOfRvaAndSizes;
		return true;
	case IMAGE_NT_OPTIONAL_HDR32_MAGIC:
		hasNtHeader32 = true;
		imageDataDirectoryEntry = GetNtHeader32()->OptionalHeader.DataDirectory;
		imageDataDirectorySize = &GetNtHeader32()->OptionalHeader.NumberOfRvaAndSizes;
		return true;

	default:
		break;
	}
	return false;
}

bool PE::NtHeader::HasNtHeader32()
{
	return hasNtHeader32;
}

const PIMAGE_DATA_DIRECTORY PE::NtHeader::GetImageDataDirectoryEntry()
{
	return	imageDataDirectoryEntry;
}

const PDWORD PE::NtHeader::GetImageDataDirectorySize()
{
	return imageDataDirectorySize;
}
