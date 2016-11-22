#pragma once
#include <windows.h>
namespace PeDecoder
{
	__interface IRvaConverter
	{
		PVOID RvaToDataPtr(DWORD rva) const;
		PVOID RvaToDataPtr(ULONGLONG rva) const;
	};
}  // namespace PeDecoder