#include "stdafx.h"
#include "VirtualAlloc.h"
#include "NtDll.h"
#include "Kernel32.h"
LPVOID WINAPI Process::Overwrite::VirtualAlloc(_In_opt_ LPVOID lpAddress, _In_ SIZE_T dwSize, _In_ DWORD flAllocationType, _In_ DWORD flProtect)
{
	return Process::Overwrite::VirtualAllocEx(NtCurrentProcess(), lpAddress, dwSize, flAllocationType, flProtect);
}

LPVOID WINAPI Process::Overwrite::VirtualAllocEx(_In_ HANDLE hProcess, _In_opt_ LPVOID lpAddress, _In_ SIZE_T dwSize, _In_ DWORD flAllocationType, _In_ DWORD flProtect)
{
	auto& ntAllocateVirtualMemory = Process::LazyLoad::NtDll::Instance().NtAllocateVirtualMemory;
	if (!ntAllocateVirtualMemory.Load())
	{
		return nullptr;
	}
	auto& getSystemInfo = Process::LazyLoad::Kernel32::Instance().GetSystemInfo;

	if (!getSystemInfo.Load())
	{
		return nullptr;
	}
	SYSTEM_INFO sysinfo;
	getSystemInfo(&sysinfo);
	if ((lpAddress) &&
		(lpAddress < (PVOID)sysinfo.dwAllocationGranularity))
	{
		return nullptr;
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

	return NT_SUCCESS(status) ? lpAddress : nullptr;
}
