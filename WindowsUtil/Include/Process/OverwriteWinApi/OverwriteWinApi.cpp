#include "OverwriteWinApi.h"

namespace Process
{
	
	namespace Overwrite
	{

		using Process::LazyLoad::NtDll_Dll;
		using Process::LazyLoad::Kernel32_Dll;

		using EnvironmentBlock::PTEB_Ex;
		using EnvironmentBlock::PBASE_STATIC_SERVER_DATA;
		using namespace Process::Overwrite;

		HANDLE WINAPI _OpenProcess(_In_ DWORD dwDesiredAccess, _In_ BOOL bInheritHandle, _In_ DWORD dwProcessId)
		{
			NTSTATUS Status;
			HANDLE ProcessHandle;
			OBJECT_ATTRIBUTES ObjectAttributes;
			CLIENT_ID ClientId;

			ClientId.UniqueProcess = UlongToHandle(dwProcessId);
			ClientId.UniqueThread = 0;

			InitializeObjectAttributes(&ObjectAttributes,
				NULL,
				(bInheritHandle ? OBJ_INHERIT : 0),
				NULL,
				NULL);
			if (!NtDll_Dll.Load() || !NtDll_Dll._NtOpenProcess)
			{
				return NULL;
			}
			Status = NtDll_Dll._NtOpenProcess(&ProcessHandle,
				dwDesiredAccess,
				&ObjectAttributes,
				&ClientId);
			if (!NT_SUCCESS(Status))
			{
				return NULL;
			}
			return ProcessHandle;
		}
		BOOL WINAPI _SetThreadContext(_In_ HANDLE hThread, _In_ CONST CONTEXT * lpContext)
		{
			NTSTATUS Status;
			if (!NtDll_Dll.Load() || !NtDll_Dll._NtSetContextThread)
			{
				return FALSE;
			}
			Status = NtDll_Dll._NtSetContextThread(hThread, (PCONTEXT)lpContext);
			if (!NT_SUCCESS(Status))
			{
				return FALSE;
			}
			return TRUE;
		}
		BOOL WINAPI _VirtualProtect(_In_ LPVOID lpAddress, _In_ SIZE_T dwSize, _In_ DWORD flNewProtect, _Out_ PDWORD lpflOldProtect)
		{
			return _VirtualProtectEx(NtCurrentProcess(), lpAddress, dwSize, flNewProtect, lpflOldProtect);
		}

		BOOL WINAPI _VirtualProtectEx(IN HANDLE hProcess, IN LPVOID lpAddress, IN SIZE_T dwSize, IN DWORD flNewProtect, OUT PDWORD lpflOldProtect)
		{
			NTSTATUS Status;
			ULONG oldProtect;
			if (!NtDll_Dll.Load() || !NtDll_Dll._NtProtectVirtualMemory)
			{
				return FALSE;
			}

			Status = NtDll_Dll._NtProtectVirtualMemory(hProcess,
				&lpAddress,
				&dwSize,
				flNewProtect,
				&oldProtect);
			if (lpflOldProtect)
			{
				*lpflOldProtect = oldProtect;
			}
			if (!NT_SUCCESS(Status))
			{
				return FALSE;
			}

			return TRUE;
		}
		BOOL WINAPI _ReadProcessMemory(_In_ HANDLE hProcess, _In_ LPCVOID lpBaseAddress, _Out_writes_bytes_to_(nSize, *lpNumberOfBytesRead) LPVOID lpBuffer, _In_ SIZE_T nSize, _Out_opt_ SIZE_T * lpNumberOfBytesRead)
		{
			NTSTATUS Status;
			if (!NtDll_Dll.Load() || !NtDll_Dll._NtReadVirtualMemory)
			{
				return FALSE;
			}
			Status = NtDll_Dll._NtReadVirtualMemory(hProcess,
				(PVOID)lpBaseAddress,
				lpBuffer,
				nSize,
				&nSize);
			if (lpNumberOfBytesRead) *lpNumberOfBytesRead = nSize;
			if (!NT_SUCCESS(Status))
			{
				return FALSE;
			}
			return TRUE;
		}

		BOOL WINAPI _WriteProcessMemory(_In_ HANDLE hProcess, _In_ LPVOID lpBaseAddress, _In_reads_bytes_(nSize) LPCVOID lpBuffer, _In_ SIZE_T nSize, _Out_opt_ SIZE_T * lpNumberOfBytesWritten)
		{
			NTSTATUS Status;
			ULONG OldValue;
			SIZE_T RegionSize;
			PVOID Base;
			BOOLEAN UnProtect;
			if (!NtDll_Dll.Load() ||
				!NtDll_Dll._NtProtectVirtualMemory ||
				!NtDll_Dll._NtWriteVirtualMemory ||
				!NtDll_Dll._NtFlushInstructionCache
				)
			{
				return FALSE;
			}
			RegionSize = nSize;
			Base = lpBaseAddress;

			Status = NtDll_Dll._NtProtectVirtualMemory(hProcess,
				&Base,
				&RegionSize,
				PAGE_EXECUTE_READWRITE,
				&OldValue);
			if (NT_SUCCESS(Status))
			{
				Status = NtDll_Dll._NtWriteVirtualMemory(hProcess,
					lpBaseAddress,
					(LPVOID)lpBuffer,
					nSize,
					&nSize);
				NtDll_Dll._NtProtectVirtualMemory(hProcess,
					&Base,
					&RegionSize,
					OldValue,
					&OldValue);
				if (lpNumberOfBytesWritten) *lpNumberOfBytesWritten = nSize;

				if (!NT_SUCCESS(Status))
				{
					return FALSE;
				}
				NtDll_Dll._NtFlushInstructionCache(hProcess, lpBaseAddress, nSize);
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		LPVOID WINAPI _VirtualAlloc(_In_opt_ LPVOID lpAddress, _In_ SIZE_T dwSize, _In_ DWORD flAllocationType, _In_ DWORD flProtect)
		{
			return _VirtualAllocEx(NtCurrentProcess(), lpAddress, dwSize, flAllocationType, flProtect);
		}
		LPVOID WINAPI _VirtualAllocEx(_In_ HANDLE hProcess, _In_opt_ LPVOID lpAddress, _In_ SIZE_T dwSize, _In_ DWORD flAllocationType, _In_ DWORD flProtect)
		{
			NTSTATUS Status;
			SYSTEM_INFO sysinfo;
			if (!NtDll_Dll.Load() || !NtDll_Dll._NtAllocateVirtualMemory)
			{
				return NULL;
			}
			if (!Kernel32_Dll.Load() || !Kernel32_Dll._GetSystemInfo)
			{
				return NULL;
			}
			Kernel32_Dll._GetSystemInfo(&sysinfo);
			if ((lpAddress) &&
				(lpAddress < (PVOID)sysinfo.dwAllocationGranularity))
			{
				return NULL;
			}
			__try
			{
				Status = NtDll_Dll._NtAllocateVirtualMemory(hProcess,
					&lpAddress,
					0,
					&dwSize,
					flAllocationType,
					flProtect);
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				Status = 0;
			}


			if (!NT_SUCCESS(Status))
			{
				return NULL;
			}
			return lpAddress;
		}
		SIZE_T WINAPI _VirtualQuery(_In_opt_ LPCVOID lpAddress, _Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer, _In_ SIZE_T dwLength)
		{
			return _VirtualQueryEx(NtCurrentProcess(), lpAddress, lpBuffer, dwLength);
		}
		SIZE_T WINAPI _VirtualQueryEx(_In_ HANDLE hProcess, _In_opt_ LPCVOID lpAddress, _Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer, _In_ SIZE_T dwLength)
		{
			NTSTATUS Status;
			SIZE_T ResultLength;
			if (!NtDll_Dll.Load() || !NtDll_Dll._NtQueryVirtualMemory)
			{
				return FALSE;
			}
			Status = NtDll_Dll._NtQueryVirtualMemory(hProcess,
				(LPVOID)lpAddress,
				MemoryBasicInformation,
				lpBuffer,
				dwLength,
				&ResultLength);
			if (!NT_SUCCESS(Status))
			{
				return 0;
			}
			return ResultLength;
		}
		BOOL WINAPI _VirtualFreeEx(_In_ HANDLE hProcess, _Pre_notnull_ _When_(dwFreeType == MEM_DECOMMIT, _Post_invalid_) _When_(dwFreeType == MEM_RELEASE, _Post_ptr_invalid_) LPVOID lpAddress, _In_ SIZE_T dwSize, _In_ DWORD dwFreeType)
		{
			NTSTATUS Status;
			if (!NtDll_Dll.Load() || !NtDll_Dll._NtFreeVirtualMemory)
			{
				return FALSE;
			}

			if (!(dwSize) || !(dwFreeType & MEM_RELEASE))
			{
				Status = NtDll_Dll._NtFreeVirtualMemory(hProcess,
					&lpAddress,
					&dwSize,
					dwFreeType);
				if (!NT_SUCCESS(Status))
				{
					return FALSE;
				}
				return TRUE;
			}
			return FALSE;
		}
		BOOL WINAPI _VirtualFree(IN LPVOID lpAddress, IN SIZE_T dwSize, IN DWORD dwFreeType)
		{
			return _VirtualFreeEx(NtCurrentProcess(), lpAddress, dwSize, dwFreeType);
		}
	}
}
