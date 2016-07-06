#include "stdafx.h"
#include "VirtualQuery.h"
#include "NtDll.h"
#include "EnvironmentBlock.h"
using Process::LazyLoad::NtDll;
SIZE_T WINAPI Process::Overwrite::VirtualQuery(_In_opt_ LPCVOID lpAddress, _Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer, _In_ SIZE_T dwLength)
{
	return Process::Overwrite::VirtualQueryEx(NtCurrentProcess(), lpAddress, lpBuffer, dwLength);
}

SIZE_T WINAPI Process::Overwrite::VirtualQueryEx(_In_ HANDLE hProcess, _In_opt_ LPCVOID lpAddress, _Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer, _In_ SIZE_T dwLength)
{
	auto& ntQueryVirtualMemory = NtDll::Instance().NtQueryVirtualMemory;
	if (!ntQueryVirtualMemory.Load())
	{
		return 0;
	}
	SIZE_T resultLength;
	auto status = ntQueryVirtualMemory(hProcess,
		(LPVOID)lpAddress,
		Process::EnvironmentBlock::MemoryBasicInformation,
		lpBuffer,
		dwLength,
		&resultLength);
	if (!NT_SUCCESS(status))
	{
		return 0;
	}
	return resultLength;
}
