#pragma once
#include <Windows.h>
#include "SubsystemType.h"
#include "DllCharacteristics.h"
#include "INtHeaderVisitor.h"
namespace PeDecoder
{
	__interface IOptionalHeader
	{
		PIMAGE_DATA_DIRECTORY GetDataDirectory() const;
		DWORD GetDataDirectorySize() const;
		DWORD GetSizeOfImage() const;
		WORD GetNumberOfSections() const;
		DWORD GetSectionAlignment() const;
		DWORD GetEntryPointRva() const;
		PIMAGE_SECTION_HEADER GetSectionHeaderPtr() const;
		SubsystemType GetSubsystem() const;
		DllCharacteristics GetDllCharacteristics() const;
		void ReadDetails(const INtHeaderVisitor & visitor) const;
	};
}  // namespace PeDecoder