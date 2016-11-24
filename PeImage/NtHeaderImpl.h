#pragma once
#include "NtHeader.h"
#include "SubsystemType.h"
#include "DllCharacteristics.h"
namespace PeDecoder
{
	template<typename TNtHeaderType>
	class NtHeaderImpl :
		public NtHeader
	{
	public:
		static_assert(_STD is_same<TNtHeaderType, PIMAGE_NT_HEADERS32>::value ||
			_STD is_same<TNtHeaderType, PIMAGE_NT_HEADERS64>::value, "PIMAGE_NT_HEADERS32 PIMAGE_NT_HEADERS64");

		explicit NtHeaderImpl(const TNtHeaderType nt32) :NtHeader(nt32)
		{}
		TNtHeaderType RawNtHeaderPtr() const
		{
			return reinterpret_cast<TNtHeaderType>(RawPtr());
		}
		auto GetOptionalHeader() const
		{
			return &RawNtHeaderPtr()->OptionalHeader;
		}
		virtual void ReadDetails(const INtHeaderVisitor & visitor) const override
		{
			visitor.Visit(*this);
		}

		virtual SubsystemType GetSubsystem() const override
		{
			return static_cast<SubsystemType>(GetOptionalHeader()->Subsystem);
		}
		virtual DllCharacteristics GetDllCharacteristics() const override
		{
			return static_cast<DllCharacteristics>(GetOptionalHeader()->DllCharacteristics);
		}

		virtual DWORD GetSizeOfImage() const override
		{
			return GetOptionalHeader()->SizeOfImage;
		}
		virtual DWORD GetSectionAlignment() const override
		{
			return GetOptionalHeader()->SectionAlignment;
		}
		virtual DWORD GetEntryPointRva() const override
		{
			return GetOptionalHeader()->AddressOfEntryPoint;
		}

		virtual PIMAGE_SECTION_HEADER GetSectionHeaderPtr() const override
		{
			return IMAGE_FIRST_SECTION(RawNtHeaderPtr());
		}
		virtual PIMAGE_DATA_DIRECTORY GetDataDirectory() const override
		{
			return GetOptionalHeader()->DataDirectory;
		}
		virtual DWORD GetDataDirectorySize() const override
		{
			return GetOptionalHeader()->NumberOfRvaAndSizes;
		}
	};

}  // namespace PeDecoder
