#include "stdafx.h"
#include "VirtualProtect.h"
#include "NtDll.h"
bool WINAPI Process::Overwrite::VirtualProtect(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect)
{
	return Process::Overwrite::VirtualProtectEx(NtCurrentProcess(), lpAddress, dwSize, flNewProtect, lpflOldProtect);
}

bool WINAPI Process::Overwrite::VirtualProtectEx(IN HANDLE hProcess, IN LPVOID lpAddress, IN SIZE_T dwSize, IN DWORD flNewProtect, OUT PDWORD lpflOldProtect)
{
	auto& ntProtectVirtualMemory = Process::LazyLoad::NtDll::Instance().NtProtectVirtualMemory;
	if (!ntProtectVirtualMemory.Load())
	{
		return false;
	}
	ULONG oldProtect;
	NTSTATUS status = ntProtectVirtualMemory(hProcess,
		&lpAddress,
		&dwSize,
		flNewProtect,
		&oldProtect);
	if (lpflOldProtect)
	{
		*lpflOldProtect = oldProtect;
	}
	return NT_SUCCESS(status);
}
