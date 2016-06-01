#pragma once
#include "Common.h"
namespace Process
{
	namespace Overwrite
	{
		// 修改成写之前不需要设置可写标识
		bool WINAPI WriteProcessMemory(_In_ HANDLE hProcess, _In_ LPVOID lpBaseAddress, _In_reads_bytes_(nSize) LPCVOID lpBuffer, _In_ SIZE_T nSize, _Out_opt_ SIZE_T * lpNumberOfBytesWritten);
	}  // namespace Overwrite
}  // namespace Process