#pragma once
#include "Common.h"
namespace Process
{
	namespace Overwrite
	{
		bool WINAPI VirtualFreeEx(_In_ HANDLE hProcess, _Pre_notnull_ _When_(dwFreeType == MEM_DECOMMIT, _Post_invalid_) _When_(dwFreeType == MEM_RELEASE, _Post_ptr_invalid_) LPVOID lpAddress, _In_ SIZE_T dwSize, _In_ DWORD dwFreeType);
		bool WINAPI VirtualFree(IN LPVOID lpAddress, IN SIZE_T dwSize, IN DWORD dwFreeType);
	}  // namespace Overwrite
}  // namespace Process
