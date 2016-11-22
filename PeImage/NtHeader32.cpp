#include "stdafx.h"
#include "NtHeader32.h"
#include "DataDirectoryEntries.h"
namespace PeDecoder
{
	NtHeader32::NtHeader32(const PIMAGE_NT_HEADERS32 nt32) :NtHeader(nt32)
	{}
	PIMAGE_NT_HEADERS32 NtHeader32::RawPtr32() const
	{
		return GetHeader32();
	}
	PIMAGE_OPTIONAL_HEADER32 NtHeader32::GetOptionalHeader() const
	{
		return &RawPtr32()->OptionalHeader;
	}
	SubsystemType NtHeader32::GetSubsystem() const
	{
		return static_cast<SubsystemType>(GetOptionalHeader()->Subsystem);
	}
	void NtHeader32::ReadDetails(const INtHeaderVisitor & visitor) const
	{
		visitor.Visit(*this);
	}

	DllCharacteristics NtHeader32::GetDllCharacteristics() const
	{
		return static_cast<DllCharacteristics>(GetOptionalHeader()->DllCharacteristics);
	}

	DWORD NtHeader32::GetSizeOfImage() const
	{
		return GetOptionalHeader()->SizeOfImage;
	}

	DWORD NtHeader32::GetSectionAlignment() const
	{
		return GetOptionalHeader()->SectionAlignment;
	}

	DWORD NtHeader32::GetEntryPointRva() const
	{
		return GetOptionalHeader()->AddressOfEntryPoint;
	}

	PIMAGE_SECTION_HEADER NtHeader32::GetSectionHeaderPtr() const
	{
		return IMAGE_FIRST_SECTION(RawPtr32());
	}

	PIMAGE_DATA_DIRECTORY NtHeader32::GetDataDirectory() const
	{
		return GetOptionalHeader()->DataDirectory;
	}

	DWORD NtHeader32::GetDataDirectorySize() const
	{
		return GetOptionalHeader()->NumberOfRvaAndSizes;
	}

}  // namespace PeDecoder
