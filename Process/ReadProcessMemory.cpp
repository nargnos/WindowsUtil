#include "stdafx.h"
#include "ReadProcessMemory.h"
#include "NtDll.h"
bool WINAPI Process::Overwrite::ReadProcessMemory(HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T * lpNumberOfBytesRead)
{
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
