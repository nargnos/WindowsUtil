#include "stdafx.h"
#include "NtHeader64.h"
#include "DataDirectoryEntries.h"
namespace PeDecoder
{
	NtHeader64::NtHeader64(const PIMAGE_NT_HEADERS64 nt64) :NtHeader(nt64) {}
	PIMAGE_NT_HEADERS64 NtHeader64::RawPtr64() const
	{
		return static_cast<PIMAGE_NT_HEADERS64>(ptr_);
	}
	PIMAGE_OPTIONAL_HEADER64 NtHeader64::GetOptionalHeader() const
	{
		return &RawPtr64()->OptionalHeader;
	}
	SubsystemType NtHeader64::GetSubsystem() const
	{
		return static_cast<SubsystemType>(GetOptionalHeader()->Subsystem);
	}
	void NtHeader64::ReadDetails(const INtHeaderVisitor & visitor) const
	{
		visitor.Visit(*this);
	}

	DllCharacteristics NtHeader64::GetDllCharacteristics() const
	{
		return static_cast<DllCharacteristics>(GetOptionalHeader()->DllCharacteristics);
	}

	DWORD NtHeader64::GetSizeOfImage() const
	{
		return GetOptionalHeader()->SizeOfImage;
	}

	DWORD NtHeader64::GetSectionAlignment() const
	{
		return GetOptionalHeader()->SectionAlignment;
	}

	DWORD NtHeader64::GetEntryPointRva() const
	{
		return GetOptionalHeader()->AddressOfEntryPoint;
	}

	PIMAGE_SECTION_HEADER NtHeader64::GetSectionHeaderPtr() const
	{
		return IMAGE_FIRST_SECTION(RawPtr64());
	}

	PIMAGE_DATA_DIRECTORY NtHeader64::GetDataDirectory() const
	{
		return GetOptionalHeader()->DataDirectory;
	}

	DWORD NtHeader64::GetDataDirectorySize() const
	{
		return GetOptionalHeader()->NumberOfRvaAndSizes;
	}

}  // namespace PeDecoder
