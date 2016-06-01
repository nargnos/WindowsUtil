#include "stdafx.h"
#include "VirtualAlloc.h"
#include "NtDll.h"
#include "Kernel32.h"
LPVOID WINAPI Process::Overwrite::VirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect)
{
	return Process::Overwrite::VirtualAllocEx(NtCurrentProcess(), lpAddress, dwSize, flAllocationType, flProtect);
}

LPVOID WINAPI Process::Overwrite::VirtualAllocEx(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect)
{
	auto& ntAllocateVirtualMemory = Process::LazyLoad::NtDll::Instance().NtAllocateVirtualMemory;
	if (!ntAllocateVirtualMemory.Load())
	{
		return NULL;
	}
	auto& getSystemInfo = Process::LazyLoad::Kernel32::Instance().GetSystemInfo;

	if (!getSystemInfo.Load())
	{
		return NULL;
	}
	SYSTEM_INFO sysinfo;
	getSystemInfo(&sysinfo);
	if ((lpAddress) &&
		(lpAddress < (PVOID)sysinfo.dwAllocationGranularity))
	{
		return NULL;
	}
	NTSTATUS status;
	__try
	{
		status = ntAllocateVirtualMemory(hProcess,
			&lpAddress,
			0,
			&dwSize,
			flAllocationType,
			flProtect);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		status = 0;
	}

	return NT_SUCCESS(status) ? lpAddress : NULL;
}
