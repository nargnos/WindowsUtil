#include "stdafx.h"
#include "VirtualFree.h"
#include "NtDll.h"
using Process::LazyLoad::NtDll;
bool WINAPI Process::Overwrite::VirtualFreeEx(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType)
{
	auto& ntFreeVirtualMemory = NtDll::Instance().NtFreeVirtualMemory;
	if (!ntFreeVirtualMemory.Load())
	{
		return false;
	}
	if (!(dwSize) || !(dwFreeType & MEM_RELEASE))
	{
		auto status = ntFreeVirtualMemory(hProcess,
			&lpAddress,
			&dwSize,
			dwFreeType);

		return NT_SUCCESS(status);
	}
	return false;
}

bool WINAPI Process::Overwrite::VirtualFree(IN LPVOID lpAddress, IN SIZE_T dwSize, IN DWORD dwFreeType)
{
	return Process::Overwrite::VirtualFreeEx(NtCurrentProcess(), lpAddress, dwSize, dwFreeType);
}
