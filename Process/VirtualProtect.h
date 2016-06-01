#pragma once
#include "Common.h"
namespace Process
{
	namespace Overwrite
	{
		bool WINAPI VirtualProtect(_In_ LPVOID lpAddress, _In_ SIZE_T dwSize, _In_ DWORD flNewProtect, _Out_ PDWORD lpflOldProtect);

		bool WINAPI VirtualProtectEx(IN HANDLE hProcess, IN LPVOID lpAddress, IN SIZE_T dwSize, IN DWORD flNewProtect, OUT PDWORD lpflOldProtect);
	}  // namespace Overwrite
}  // namespace Process
