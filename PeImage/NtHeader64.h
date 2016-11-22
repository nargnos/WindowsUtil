#pragma once
#include "NtHeader.h"
#include "SubsystemType.h"
#include "DllCharacteristics.h"
namespace PeDecoder
{
	class NtHeader64 :
		public NtHeader
	{
	public:
		explicit NtHeader64(const PIMAGE_NT_HEADERS64 nt64);
		PIMAGE_NT_HEADERS64 RawPtr64() const;
		PIMAGE_OPTIONAL_HEADER64 GetOptionalHeader() const;
		virtual void ReadDetails(const INtHeaderVisitor & visitor) const override;

		virtual SubsystemType GetSubsystem() const override;
		virtual DllCharacteristics GetDllCharacteristics() const override;

		virtual DWORD GetSizeOfImage() const override;
		virtual DWORD GetSectionAlignment() const override;
		virtual DWORD GetEntryPointRva() const override;
		virtual PIMAGE_SECTION_HEADER GetSectionHeaderPtr() const override;
		virtual PIMAGE_DATA_DIRECTORY GetDataDirectory() const override;
		virtual DWORD GetDataDirectorySize() const override;
	};
}  // namespace PeDecoder
