#pragma once
#include "..\LazyLoad\LazyLoadSystemApi.h"
namespace Process
{
	namespace Overwrite
	{
		HANDLE WINAPI _OpenProcess(_In_ DWORD dwDesiredAccess, _In_ BOOL bInheritHandle, _In_ DWORD dwProcessId);
		BOOL WINAPI _SetThreadContext(_In_ HANDLE hThread, _In_ CONST CONTEXT * lpContext);
		BOOL WINAPI _VirtualProtectEx(IN HANDLE hProcess, IN LPVOID lpAddress, IN SIZE_T dwSize, IN DWORD flNewProtect, OUT PDWORD lpflOldProtect);
		BOOL WINAPI _VirtualProtect(_In_ LPVOID lpAddress, _In_ SIZE_T dwSize, _In_ DWORD flNewProtect, _Out_ PDWORD lpflOldProtect);
		BOOL WINAPI _ReadProcessMemory(_In_ HANDLE hProcess, _In_ LPCVOID lpBaseAddress, _Out_writes_bytes_to_(nSize, *lpNumberOfBytesRead) LPVOID lpBuffer, _In_ SIZE_T nSize, _Out_opt_ SIZE_T * lpNumberOfBytesRead);
		// NOTICE: 这个会强制写入, 跟原先函数执行效果不同, 写入后会恢复原先可读写性
		BOOL WINAPI _WriteProcessMemory(_In_ HANDLE hProcess, _In_ LPVOID lpBaseAddress, _In_reads_bytes_(nSize) LPCVOID lpBuffer, _In_ SIZE_T nSize, _Out_opt_ SIZE_T * lpNumberOfBytesWritten);
		LPVOID WINAPI _VirtualAllocEx(_In_ HANDLE hProcess, _In_opt_ LPVOID lpAddress, _In_ SIZE_T dwSize, _In_ DWORD flAllocationType, _In_ DWORD flProtect);
		SIZE_T WINAPI _VirtualQuery(_In_opt_ LPCVOID lpAddress, _Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer, _In_ SIZE_T dwLength);
		SIZE_T WINAPI _VirtualQueryEx(_In_ HANDLE hProcess, _In_opt_ LPCVOID lpAddress, _Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer, _In_ SIZE_T dwLength);
		BOOL WINAPI _VirtualFreeEx(_In_ HANDLE hProcess, _Pre_notnull_ _When_(dwFreeType == MEM_DECOMMIT, _Post_invalid_) _When_(dwFreeType == MEM_RELEASE, _Post_ptr_invalid_) LPVOID lpAddress, _In_ SIZE_T dwSize, _In_ DWORD dwFreeType);
		BOOL WINAPI _VirtualFree(IN LPVOID lpAddress, IN SIZE_T dwSize, IN DWORD dwFreeType);
		LPVOID WINAPI _VirtualAlloc(_In_opt_ LPVOID lpAddress, _In_ SIZE_T dwSize, _In_ DWORD flAllocationType, _In_ DWORD flProtect);
	}
}