#pragma once
#include "LazyLoad.h"
namespace Process
{
	namespace LazyLoad
	{
#define NtCurrentProcess()                      ((HANDLE)(LONG_PTR)-1)
#define NtCurrentThread()                       ((HANDLE)(LONG_PTR)-2)

#pragma region 程序自实现的函数(调用较底层函数, 如果需要调用dll内的函数则定义USE_DLL_FUNC)
		DEF_FUNC(HANDLE,
			OpenProcess, (
			_In_ DWORD dwDesiredAccess,
			_In_ BOOL bInheritHandle,
			_In_ DWORD dwProcessId
			));
		DEF_FUNC(BOOL,
			SetThreadContext, (
			_In_ HANDLE hThread,
			_In_ CONST CONTEXT * lpContext
			));

		DEF_FUNC(BOOL,
			VirtualProtectEx, (IN HANDLE hProcess,
			IN LPVOID lpAddress,
			IN SIZE_T dwSize,
			IN DWORD flNewProtect,
			OUT PDWORD lpflOldProtect));

		DEF_FUNC(BOOL,
			ReadProcessMemory, (
			_In_ HANDLE hProcess,
			_In_ LPCVOID lpBaseAddress,
			_Out_writes_bytes_to_(nSize, *lpNumberOfBytesRead) LPVOID lpBuffer,
			_In_ SIZE_T nSize,
			_Out_opt_ SIZE_T * lpNumberOfBytesRead
			));

		DEF_FUNC(BOOL,
			WriteProcessMemory, (
			_In_ HANDLE hProcess,
			_In_ LPVOID lpBaseAddress,
			_In_reads_bytes_(nSize) LPCVOID lpBuffer,
			_In_ SIZE_T nSize,
			_Out_opt_ SIZE_T * lpNumberOfBytesWritten
			));

		DEF_FUNC(LPVOID,
			VirtualAlloc, (
			_In_opt_ LPVOID lpAddress,
			_In_ SIZE_T dwSize,
			_In_ DWORD flAllocationType,
			_In_ DWORD flProtect
			));
		DEF_FUNC(LPVOID,
			VirtualAllocEx, (
			_In_ HANDLE hProcess,
			_In_opt_ LPVOID lpAddress,
			_In_ SIZE_T dwSize,
			_In_ DWORD flAllocationType,
			_In_ DWORD flProtect
			));
		DEF_FUNC(BOOL,
			VirtualProtect, (
			_In_ LPVOID lpAddress,
			_In_ SIZE_T dwSize,
			_In_ DWORD flNewProtect,
			_Out_ PDWORD lpflOldProtect
			));
		DEF_FUNC(BOOL,
			VirtualProtectEx, (
			_In_ HANDLE hProcess,
			_In_ LPVOID lpAddress,
			_In_ SIZE_T dwSize,
			_In_ DWORD flNewProtect,
			_Out_ PDWORD lpflOldProtect
			));
		DEF_FUNC(SIZE_T,
			VirtualQuery, (
			_In_opt_ LPCVOID lpAddress,
			_Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer,
			_In_ SIZE_T dwLength
			));
		DEF_FUNC(SIZE_T,
			VirtualQueryEx, (
			_In_ HANDLE hProcess,
			_In_opt_ LPCVOID lpAddress,
			_Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer,
			_In_ SIZE_T dwLength
			));
		DEF_FUNC(BOOL,
			VirtualFreeEx, (
			_In_ HANDLE hProcess,
			_Pre_notnull_ _When_(dwFreeType == MEM_DECOMMIT, _Post_invalid_) _When_(dwFreeType == MEM_RELEASE, _Post_ptr_invalid_) LPVOID lpAddress,
			_In_ SIZE_T dwSize,
			_In_ DWORD dwFreeType
			));
		DEF_FUNC(BOOL,
			VirtualFree, (IN LPVOID lpAddress,
			IN SIZE_T dwSize,
			IN DWORD dwFreeType));
#pragma endregion

#pragma region NtDll
		typedef struct _CLIENT_ID {
			HANDLE UniqueProcess;
			HANDLE UniqueThread;
		} CLIENT_ID, *PCLIENT_ID;

		DEF_FUNC(NTSTATUS,
			NtOpenProcess, (OUT PHANDLE ProcessHandle,
			IN ACCESS_MASK DesiredAccess,
			IN POBJECT_ATTRIBUTES ObjectAttributes,
			IN PCLIENT_ID ClientId));

		DEF_FUNC(NTSTATUS,
			NtSetContextThread, (
			_In_ HANDLE ThreadHandle,
			_In_ PCONTEXT Context
			));
		DEF_FUNC(NTSTATUS,
			NtProtectVirtualMemory, (
			_In_ HANDLE ProcessHandle,
			_In_ PVOID *BaseAddress,
			_In_ SIZE_T *NumberOfBytesToProtect,
			_In_ ULONG NewAccessProtection,
			_Out_ PULONG OldAccessProtection
			));


		DEF_FUNC(NTSTATUS,
			NtReadVirtualMemory, (
			_In_ HANDLE ProcessHandle,
			_In_ PVOID BaseAddress,
			_Out_ PVOID Buffer,
			_In_ SIZE_T NumberOfBytesToRead,
			_Out_opt_ PSIZE_T NumberOfBytesRead
			));



		DEF_FUNC(NTSTATUS,
			NtWriteVirtualMemory, (
			_In_ HANDLE ProcessHandle,
			_In_ PVOID  BaseAddress,
			_In_ PVOID Buffer,
			_In_ SIZE_T NumberOfBytesToWrite,
			_Out_opt_ PSIZE_T NumberOfBytesWritten
			));

		DEF_FUNC(NTSTATUS,
			NtFlushInstructionCache,(
			_In_ HANDLE ProcessHandle,
			_In_ PVOID BaseAddress,
			_In_ ULONG NumberOfBytesToFlush
			));

		DEF_FUNC(NTSTATUS, NtAllocateVirtualMemory, (HANDLE, PVOID*, ULONG, SIZE_T*, ULONG, ULONG)); 

		typedef enum _MEMORY_INFORMATION_CLASS {
			MemoryBasicInformation,
			MemoryWorkingSetList,
			MemorySectionName,
			MemoryBasicVlmInformation
		} MEMORY_INFORMATION_CLASS;

		DEF_FUNC(NTSTATUS,
			NtQueryVirtualMemory,(
			_In_ HANDLE ProcessHandle,
			_In_ PVOID Address,
			_In_ MEMORY_INFORMATION_CLASS VirtualMemoryInformationClass,
			_Out_ PVOID VirtualMemoryInformation,
			_In_ SIZE_T Length,
			_Out_opt_ PSIZE_T ResultLength
			));
		DEF_FUNC(NTSTATUS,
			NtFreeVirtualMemory, (
			_In_ HANDLE ProcessHandle,
			_Inout_ __drv_freesMem(Mem) PVOID *BaseAddress,
			_Inout_ PSIZE_T RegionSize,
			_In_ ULONG FreeType));
#pragma endregion

#pragma region User32
		// MessageBoxA
		DEF_FUNC(int, MessageBoxA, (
			_In_opt_ HWND hWnd,
			_In_opt_ LPCSTR lpText,
			_In_opt_ LPCSTR lpCaption,
			_In_ UINT uType));
#pragma endregion

#pragma region Kernel32
		DEF_FUNC(VOID,
			GetSystemInfo, (
			_Out_ LPSYSTEM_INFO lpSystemInfo
			));

		DEF_FUNC(HANDLE,
			CreateFileMappingW, (
			_In_ HANDLE hFile,
			_In_opt_ LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
			_In_ DWORD flProtect,
			_In_ DWORD dwMaximumSizeHigh,
			_In_ DWORD dwMaximumSizeLow,
			_In_opt_ LPCWSTR lpName
			));

		DEF_FUNC(HANDLE,
			OpenFileMappingW, (
			_In_ DWORD dwDesiredAccess,
			_In_ BOOL bInheritHandle,
			_In_ LPCWSTR lpName
			));

		DEF_FUNC(LPVOID,
			MapViewOfFile, (
			_In_ HANDLE hFileMappingObject,
			_In_ DWORD dwDesiredAccess,
			_In_ DWORD dwFileOffsetHigh,
			_In_ DWORD dwFileOffsetLow,
			_In_ SIZE_T dwNumberOfBytesToMap
			));

		DEF_FUNC(LPVOID,
			MapViewOfFileEx, (
			_In_ HANDLE hFileMappingObject,
			_In_ DWORD dwDesiredAccess,
			_In_ DWORD dwFileOffsetHigh,
			_In_ DWORD dwFileOffsetLow,
			_In_ SIZE_T dwNumberOfBytesToMap,
			_In_opt_ LPVOID lpBaseAddress
			));

		DEF_FUNC(BOOL,
			FlushViewOfFile, (
			_In_ LPCVOID lpBaseAddress,
			_In_ SIZE_T dwNumberOfBytesToFlush
			));

		DEF_FUNC(BOOL,
			UnmapViewOfFile, (
			_In_ LPCVOID lpBaseAddress
			));

		DEF_FUNC(BOOL,
			VirtualLock, (
			_In_ LPVOID lpAddress,
			_In_ SIZE_T dwSize
			));

		DEF_FUNC(BOOL,
			VirtualUnlock, (
			_In_ LPVOID lpAddress,
			_In_ SIZE_T dwSize
			));

#pragma endregion


	}
}