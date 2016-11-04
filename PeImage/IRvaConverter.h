#pragma once
#include <windows.h>
__interface IRvaConverter
{
	PVOID RvaToDataPtr(DWORD rva) const;
	PVOID RvaToDataPtr(ULONGLONG rva) const;
};