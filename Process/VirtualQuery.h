#pragma once
#include "Common.h"
namespace Process
{
	namespace Overwrite
	{
		SIZE_T WINAPI VirtualQuery(_In_opt_ LPCVOID lpAddress, _Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer, _In_ SIZE_T dwLength);
		SIZE_T WINAPI VirtualQueryEx(_In_ HANDLE hProcess, _In_opt_ LPCVOID lpAddress, _Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer, _In_ SIZE_T dwLength);
	}  // namespace Overwrite
}  // namespace Process
