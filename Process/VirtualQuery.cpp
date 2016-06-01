#include "stdafx.h"
#include "VirtualQuery.h"
#include "NtDll.h"
#include "EnvironmentBlock.h"
using Process::LazyLoad::NtDll;
SIZE_T WINAPI Process::Overwrite::VirtualQuery(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength)
{
	return Process::Overwrite::VirtualQueryEx(NtCurrentProcess(), lpAddress, lpBuffer, dwLength);
}

SIZE_T WINAPI Process::Overwrite::VirtualQueryEx(HANDLE hProcess, LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength)
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
