#include "stdafx.h"
#include "WriteProcessMemory.h"
#include "NtDll.h"
using Process::LazyLoad::NtDll;
bool WINAPI Process::Overwrite::WriteProcessMemory(_In_ HANDLE hProcess, _In_ LPVOID lpBaseAddress, _In_reads_bytes_(nSize) LPCVOID lpBuffer, _In_ SIZE_T nSize, _Out_opt_ SIZE_T * lpNumberOfBytesWritten)
{
	if (lpNumberOfBytesWritten) *lpNumberOfBytesWritten = 0;
	auto& ntdll = NtDll::Instance();
	// 便于跟踪分成3个
	if (!ntdll.NtProtectVirtualMemory.Load() ||
		!ntdll.NtWriteVirtualMemory.Load() ||
		!ntdll.NtFlushInstructionCache.Load())
	{
		return false;
	}

	ULONG oldValue;
	SIZE_T regionSize = nSize;
	PVOID base = lpBaseAddress;

	auto status = ntdll.NtProtectVirtualMemory(hProcess,
		&base,
		&regionSize,
		PAGE_EXECUTE_READWRITE,
		&oldValue);
	if (NT_SUCCESS(status))
	{
		status = ntdll.NtWriteVirtualMemory(hProcess,
			lpBaseAddress,
			(LPVOID)lpBuffer,
			nSize,
			&nSize);
		ntdll.NtProtectVirtualMemory(hProcess,
			&base,
			&regionSize,
			oldValue,
			&oldValue);
		if (lpNumberOfBytesWritten)
		{
			*lpNumberOfBytesWritten = nSize;
		}

		if (!NT_SUCCESS(status))
		{
			return false;
		}
		ntdll.NtFlushInstructionCache(hProcess, lpBaseAddress, nSize);
		return true;
	}
	else
	{
		return false;
	}
}
