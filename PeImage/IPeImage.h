#pragma once
#include <Windows.h>
#include <memory>
#include "IDosHeader.h"
#include "INtHeader.h"
#include "ISectionHeaders.h"
#include "DataDirectoryEntryType.h"
#include "ImageType.h"
namespace PeDecoder
{
	__interface IPeImage
	{

		bool HasDirectory(DataDirectoryEntryType index) const;
		bool IsMapped() const;
		bool IsPe() const;
		const _STD unique_ptr<IDosHeader>& GetDosHeader() const;
		const _STD unique_ptr<INtHeader>& GetNtHeader() const;
		const _STD unique_ptr<ISectionHeaders>& GetSections() const;
		DWORD OffsetToRva(DWORD fileOffset) const;
		ImageType GetImageType() const;
		PIMAGE_DATA_DIRECTORY GetDirectoryEntry(DataDirectoryEntryType index) const;
		PVOID RvaToDataPtr(DWORD rva) const;
		PVOID RvaToDataPtr(ULONGLONG rva) const;
		void* GetBase() const;
	};
}  // namespace PeDecoder
