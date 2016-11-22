#pragma once
#include "NtHeader.h"
#include "SubsystemType.h"
#include "DllCharacteristics.h"
namespace PeDecoder
{

	class NtHeader32 :
		public NtHeader
	{
	public:
		explicit NtHeader32(const PIMAGE_NT_HEADERS32 nt32);
		PIMAGE_NT_HEADERS32 RawPtr32() const;
		PIMAGE_OPTIONAL_HEADER32 GetOptionalHeader() const;
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
