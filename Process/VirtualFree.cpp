#include "stdafx.h"
#include "VirtualFree.h"
#include "NtDll.h"
using namespace Process::LazyLoad;
bool WINAPI Process::Overwrite::VirtualFreeEx(_In_ HANDLE hProcess, _Pre_notnull_ _When_(dwFreeType == MEM_DECOMMIT, _Post_invalid_) _When_(dwFreeType == MEM_RELEASE, _Post_ptr_invalid_) LPVOID lpAddress, _In_ SIZE_T dwSize, _In_ DWORD dwFreeType)
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
