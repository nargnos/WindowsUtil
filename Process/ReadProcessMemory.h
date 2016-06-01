#pragma once
#include "Common.h"
namespace Process
{
	namespace Overwrite
	{
		bool WINAPI ReadProcessMemory(_In_ HANDLE hProcess, _In_ LPCVOID lpBaseAddress, _Out_writes_bytes_to_(nSize, *lpNumberOfBytesRead) LPVOID lpBuffer, _In_ SIZE_T nSize, _Out_opt_ SIZE_T * lpNumberOfBytesRead);
	}  // namespace Overwrite
}  // namespace Process
