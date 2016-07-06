#include "stdafx.h"
#include "ReadProcessMemory.h"
#include "NtDll.h"
bool WINAPI Process::Overwrite::ReadProcessMemory(_In_ HANDLE hProcess, _In_ LPCVOID lpBaseAddress, _Out_writes_bytes_to_(nSize, *lpNumberOfBytesRead) LPVOID lpBuffer, _In_ SIZE_T nSize, _Out_opt_ SIZE_T * lpNumberOfBytesRead)
{
	if (lpNumberOfBytesRead) *lpNumberOfBytesRead = 0;
	auto& ntReadVirtualMemory = Process::LazyLoad::NtDll::Instance().NtReadVirtualMemory;
	if (!ntReadVirtualMemory.Load())
	{
		return false;
	}
	auto status = ntReadVirtualMemory(hProcess,
		(PVOID)lpBaseAddress,
		lpBuffer,
		nSize,
		&nSize);
	if (lpNumberOfBytesRead) *lpNumberOfBytesRead = nSize;

	return NT_SUCCESS(status);
}
