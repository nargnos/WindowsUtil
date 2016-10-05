#pragma once
#include <Windows.h>
namespace PeDecoder
{
	__interface IRvaConverter
	{
		DWORD RvaToOffset(DWORD rva) const;
		ULONGLONG RvaToOffset(ULONGLONG rva) const;
		DWORD OffsetToRva(DWORD fileOffset) const;
		PVOID RvaToDataPtr(DWORD rva) const;
		PVOID RvaToDataPtr(ULONGLONG rva) const;
	};
}  // namespace PeDecoder