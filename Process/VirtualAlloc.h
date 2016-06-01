#pragma once
#include "Common.h"
namespace Process
{
	namespace Overwrite
	{
		LPVOID WINAPI VirtualAlloc(_In_opt_ LPVOID lpAddress, _In_ SIZE_T dwSize, _In_ DWORD flAllocationType, _In_ DWORD flProtect);
		LPVOID WINAPI VirtualAllocEx(_In_ HANDLE hProcess, _In_opt_ LPVOID lpAddress, _In_ SIZE_T dwSize, _In_ DWORD flAllocationType, _In_ DWORD flProtect);
	}  // namespace Overwrite
}  // namespace Process
