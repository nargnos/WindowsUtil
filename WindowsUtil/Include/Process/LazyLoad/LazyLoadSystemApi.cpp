#include "LazyLoadSystemApi.h"
namespace Process
{
	namespace LazyLoad
	{
		using EnvironmentBlock::PTEB_Ex;
		using EnvironmentBlock::PBASE_STATIC_SERVER_DATA;

		extern LPCWSTR NtDllDll;
		LPCWSTR Kernel32Dll = L"kernel32.dll";
		LPCWSTR User32Dll = L"user32.dll";
#pragma region 程序自实现的函数

#ifdef USE_DLL_FUNC

		INIT_FUNC(HANDLE,
			OpenProcess, (
			_In_ DWORD dwDesiredAccess,
			_In_ BOOL bInheritHandle,
			_In_ DWORD dwProcessId
			))
			DEF_FUNC_CODE(Kernel32Dll, OpenProcess, NULL, (
			dwDesiredAccess,
			bInheritHandle,
			dwProcessId
			));

		INIT_FUNC(BOOL,
			SetThreadContext, (
			_In_ HANDLE hThread,
			_In_ CONST CONTEXT * lpContext
			))
			DEF_FUNC_CODE(Kernel32Dll, SetThreadContext, FALSE, (
			hThread,
			lpContext
			));
		INIT_FUNC(BOOL,
			VirtualProtect, (
			_In_ LPVOID lpAddress,
			_In_ SIZE_T dwSize,
			_In_ DWORD flNewProtect,
			_Out_ PDWORD lpflOldProtect
			))
			DEF_FUNC_CODE(Kernel32Dll, VirtualProtect, FALSE, (
			lpAddress,
			dwSize,
			flNewProtect,
			lpflOldProtect
			));
		INIT_FUNC(BOOL,
			VirtualProtectEx, (
			_In_ HANDLE hProcess,
			_In_ LPVOID lpAddress,
			_In_ SIZE_T dwSize,
			_In_ DWORD flNewProtect,
			_Out_ PDWORD lpflOldProtect
			))
			DEF_FUNC_CODE(Kernel32Dll, VirtualProtectEx, FALSE, (
			hProcess,
			lpAddress,
			dwSize,
			flNewProtect,
			lpflOldProtect
			));
		INIT_FUNC(BOOL,
			ReadProcessMemory, (
			_In_ HANDLE hProcess,
			_In_ LPCVOID lpBaseAddress,
			_Out_writes_bytes_to_(nSize, *lpNumberOfBytesRead) LPVOID lpBuffer,
			_In_ SIZE_T nSize,
			_Out_opt_ SIZE_T * lpNumberOfBytesRead
			))
			DEF_FUNC_CODE(Kernel32Dll, ReadProcessMemory, FALSE, (
			hProcess,
			lpBaseAddress,
			lpBuffer,
			nSize,
			lpNumberOfBytesRead
			));
		INIT_FUNC(BOOL,
			WriteProcessMemory, (
			_In_ HANDLE hProcess,
			_In_ LPVOID lpBaseAddress,
			_In_reads_bytes_(nSize) LPCVOID lpBuffer,
			_In_ SIZE_T nSize,
			_Out_opt_ SIZE_T * lpNumberOfBytesWritten
			))
			DEF_FUNC_CODE(Kernel32Dll, WriteProcessMemory, FALSE, (
			hProcess,
			lpBaseAddress,
			lpBuffer,
			nSize,
			lpNumberOfBytesWritten
			));
		INIT_FUNC(LPVOID,
			VirtualAlloc, (
			_In_opt_ LPVOID lpAddress,
			_In_ SIZE_T dwSize,
			_In_ DWORD flAllocationType,
			_In_ DWORD flProtect
			))
			DEF_FUNC_CODE(Kernel32Dll, VirtualAlloc, NULL, (
			lpAddress,
			dwSize,
			flAllocationType,
			flProtect
			));
		INIT_FUNC(LPVOID,
			VirtualAllocEx, (
			_In_ HANDLE hProcess,
			_In_opt_ LPVOID lpAddress,
			_In_ SIZE_T dwSize,
			_In_ DWORD flAllocationType,
			_In_ DWORD flProtect
			))
			DEF_FUNC_CODE(Kernel32Dll, VirtualAllocEx, NULL, (
			hProcess,
			lpAddress,
			dwSize,
			flAllocationType,
			flProtect
			));
		INIT_FUNC(SIZE_T,
			VirtualQuery, (
			_In_opt_ LPCVOID lpAddress,
			_Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer,
			_In_ SIZE_T dwLength
			))
			DEF_FUNC_CODE(Kernel32Dll, VirtualQuery, NULL, (
			lpAddress,
			lpBuffer,
			dwLength
			));

		INIT_FUNC(SIZE_T,
			VirtualQueryEx, (
			_In_ HANDLE hProcess,
			_In_opt_ LPCVOID lpAddress,
			_Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer,
			_In_ SIZE_T dwLength
			))
			DEF_FUNC_CODE(Kernel32Dll, VirtualQueryEx, NULL, (
			hProcess,
			lpAddress,
			lpBuffer,
			dwLength
			));

		INIT_FUNC(BOOL,
			VirtualFreeEx, (
			_In_ HANDLE hProcess,
			_Pre_notnull_ _When_(dwFreeType == MEM_DECOMMIT, _Post_invalid_) _When_(dwFreeType == MEM_RELEASE, _Post_ptr_invalid_) LPVOID lpAddress,
			_In_ SIZE_T dwSize,
			_In_ DWORD dwFreeType
			))
			DEF_FUNC_CODE(Kernel32Dll, VirtualFreeEx, FALSE, (
			hProcess,
			lpAddress,
			dwSize,
			dwFreeType
			));
		INIT_FUNC(BOOL,
			VirtualFree, (IN LPVOID lpAddress,
			IN SIZE_T dwSize,
			IN DWORD dwFreeType))
			DEF_FUNC_CODE(Kernel32Dll, VirtualFree, FALSE, (
			lpAddress,
			dwSize,
			dwFreeType));
#else
		// 这里重写代码修改自reactOS
		INIT_FUNC(HANDLE,
			OpenProcess, (
			_In_ DWORD dwDesiredAccess,
			_In_ BOOL bInheritHandle,
			_In_ DWORD dwProcessId
			))
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

			Status = _NtOpenProcess(&ProcessHandle,
				dwDesiredAccess,
				&ObjectAttributes,
				&ClientId);
			if (!NT_SUCCESS(Status))
			{
				return NULL;
			}
			return ProcessHandle;
		}

		INIT_FUNC(BOOL,
			SetThreadContext, (
			_In_ HANDLE hThread,
			_In_ CONST CONTEXT * lpContext
			))
		{
			NTSTATUS Status;

			Status = _NtSetContextThread(hThread, (PCONTEXT)lpContext);
			if (!NT_SUCCESS(Status))
			{
				return FALSE;
			}
			return TRUE;
		}
		INIT_FUNC(BOOL,
			VirtualProtect, (
			_In_ LPVOID lpAddress,
			_In_ SIZE_T dwSize,
			_In_ DWORD flNewProtect,
			_Out_ PDWORD lpflOldProtect
			))
		{
			return _VirtualProtectEx(NtCurrentProcess(), lpAddress, dwSize, flNewProtect, lpflOldProtect);
		}

		INIT_FUNC(BOOL,
			VirtualProtectEx, (IN HANDLE hProcess,
			IN LPVOID lpAddress,
			IN SIZE_T dwSize,
			IN DWORD flNewProtect,
			OUT PDWORD lpflOldProtect))
		{
			NTSTATUS Status;
			Status = _NtProtectVirtualMemory(hProcess,
				&lpAddress,
				&dwSize,
				flNewProtect,
				(PULONG)lpflOldProtect);
			if (!NT_SUCCESS(Status))
			{
				return FALSE;
			}

			return TRUE;
		}

		INIT_FUNC(BOOL,
			ReadProcessMemory, (
			_In_ HANDLE hProcess,
			_In_ LPCVOID lpBaseAddress,
			_Out_writes_bytes_to_(nSize, *lpNumberOfBytesRead) LPVOID lpBuffer,
			_In_ SIZE_T nSize,
			_Out_opt_ SIZE_T * lpNumberOfBytesRead
			))
		{
			NTSTATUS Status;
			Status = _NtReadVirtualMemory(hProcess,
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

		INIT_FUNC(BOOL,
			WriteProcessMemory, (
			_In_ HANDLE hProcess,
			_In_ LPVOID lpBaseAddress,
			_In_reads_bytes_(nSize) LPCVOID lpBuffer,
			_In_ SIZE_T nSize,
			_Out_opt_ SIZE_T * lpNumberOfBytesWritten
			))
		{
			NTSTATUS Status;
			ULONG OldValue;
			SIZE_T RegionSize;
			PVOID Base;
			BOOLEAN UnProtect;

			RegionSize = nSize;
			Base = lpBaseAddress;

			Status = _NtProtectVirtualMemory(hProcess,
				&Base,
				&RegionSize,
				PAGE_EXECUTE_READWRITE,
				&OldValue);
			if (NT_SUCCESS(Status))
			{
				Status = _NtWriteVirtualMemory(hProcess,
					lpBaseAddress,
					(LPVOID)lpBuffer,
					nSize,
					&nSize);
				_NtProtectVirtualMemory(hProcess,
					&Base,
					&RegionSize,
					OldValue,
					&OldValue);
				if (lpNumberOfBytesWritten) *lpNumberOfBytesWritten = nSize;

				if (!NT_SUCCESS(Status))
				{
					return FALSE;
				}
				_NtFlushInstructionCache(hProcess, lpBaseAddress, nSize);
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}

		INIT_FUNC(LPVOID,
			VirtualAlloc, (
			_In_opt_ LPVOID lpAddress,
			_In_ SIZE_T dwSize,
			_In_ DWORD flAllocationType,
			_In_ DWORD flProtect
			))
		{
			return _VirtualAllocEx(NtCurrentProcess(), lpAddress, dwSize, flAllocationType, flProtect);
		}

		INIT_FUNC(LPVOID,
			VirtualAllocEx, (
			_In_ HANDLE hProcess,
			_In_opt_ LPVOID lpAddress,
			_In_ SIZE_T dwSize,
			_In_ DWORD flAllocationType,
			_In_ DWORD flProtect
			))
		{
			NTSTATUS Status;
			SYSTEM_INFO sysinfo;
			_GetSystemInfo(&sysinfo);
			if ((lpAddress) &&
				(lpAddress < (PVOID)sysinfo.dwAllocationGranularity))
			{				
				return NULL;
			}
			__try
			{
				Status = _NtAllocateVirtualMemory(hProcess,
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

		INIT_FUNC(SIZE_T,
			VirtualQuery, (
			_In_opt_ LPCVOID lpAddress,
			_Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer,
			_In_ SIZE_T dwLength
			))
		{
			return _VirtualQueryEx(NtCurrentProcess(), lpAddress, lpBuffer, dwLength);
		}

		INIT_FUNC(SIZE_T,
			VirtualQueryEx, (
			_In_ HANDLE hProcess,
			_In_opt_ LPCVOID lpAddress,
			_Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer,
			_In_ SIZE_T dwLength
			))
		{
			NTSTATUS Status;
			SIZE_T ResultLength;

			Status = _NtQueryVirtualMemory(hProcess,
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
		INIT_FUNC(BOOL,
			VirtualFreeEx, (
			_In_ HANDLE hProcess,
			_Pre_notnull_ _When_(dwFreeType == MEM_DECOMMIT, _Post_invalid_) _When_(dwFreeType == MEM_RELEASE, _Post_ptr_invalid_) LPVOID lpAddress,
			_In_ SIZE_T dwSize,
			_In_ DWORD dwFreeType
			))
		{
			NTSTATUS Status;
			if (!(dwSize) || !(dwFreeType & MEM_RELEASE))
			{
				Status = _NtFreeVirtualMemory(hProcess,
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
		INIT_FUNC(BOOL,
			VirtualFree, (IN LPVOID lpAddress,
			IN SIZE_T dwSize,
			IN DWORD dwFreeType))
		{
			return _VirtualFreeEx(NtCurrentProcess(), lpAddress, dwSize, dwFreeType);
		}
#endif
#pragma endregion


#pragma region NtDll
#define STATUS_OPEN_FAILED 0xC0000136
#define STATUS_UNSUCCESSFUL 0xC0000001
		INIT_FUNC(NTSTATUS,
			NtOpenProcess, (
			OUT PHANDLE ProcessHandle,
			IN ACCESS_MASK DesiredAccess,
			IN POBJECT_ATTRIBUTES ObjectAttributes,
			IN PCLIENT_ID ClientId))
			DEF_FUNC_CODE(NtDllDll, NtOpenProcess,  STATUS_OPEN_FAILED, (
			ProcessHandle,
			DesiredAccess,
			ObjectAttributes,
			ClientId));

		INIT_FUNC(NTSTATUS,
			NtSetContextThread, (
			_In_ HANDLE ThreadHandle,
			_In_ PCONTEXT Context
			))DEF_FUNC_CODE(NtDllDll, NtSetContextThread,  STATUS_UNSUCCESSFUL, (ThreadHandle, Context));

		INIT_FUNC(NTSTATUS,
			NtProtectVirtualMemory, (
			_In_ HANDLE ProcessHandle,
			_In_ PVOID *BaseAddress,
			_In_ SIZE_T *NumberOfBytesToProtect,
			_In_ ULONG NewAccessProtection,
			_Out_ PULONG OldAccessProtection
			))
			DEF_FUNC_CODE(NtDllDll, NtProtectVirtualMemory, STATUS_UNSUCCESSFUL, (
			ProcessHandle,
			BaseAddress,
			NumberOfBytesToProtect,
			NewAccessProtection,
			OldAccessProtection
			));

		INIT_FUNC(NTSTATUS,
			NtReadVirtualMemory, (
			_In_ HANDLE ProcessHandle,
			_In_ PVOID BaseAddress,
			_Out_ PVOID Buffer,
			_In_ SIZE_T NumberOfBytesToRead,
			_Out_opt_ PSIZE_T NumberOfBytesRead
			))
			DEF_FUNC_CODE(NtDllDll, NtReadVirtualMemory, STATUS_UNSUCCESSFUL, (
			ProcessHandle,
			BaseAddress,
			Buffer,
			NumberOfBytesToRead,
			NumberOfBytesRead
			));

		INIT_FUNC(NTSTATUS,
			NtWriteVirtualMemory, (
			_In_ HANDLE ProcessHandle,
			_In_ PVOID  BaseAddress,
			_In_ PVOID Buffer,
			_In_ SIZE_T NumberOfBytesToWrite,
			_Out_opt_ PSIZE_T NumberOfBytesWritten
			))
			DEF_FUNC_CODE(NtDllDll, NtWriteVirtualMemory,  STATUS_UNSUCCESSFUL, (
			ProcessHandle,
			BaseAddress,
			Buffer,
			NumberOfBytesToWrite,
			NumberOfBytesWritten
			));

		INIT_FUNC(NTSTATUS,
			NtFlushInstructionCache, (
			_In_ HANDLE ProcessHandle,
			_In_ PVOID BaseAddress,
			_In_ ULONG NumberOfBytesToFlush
			))
			DEF_FUNC_CODE(NtDllDll, NtFlushInstructionCache, STATUS_UNSUCCESSFUL, (
			 ProcessHandle,
			BaseAddress,
			NumberOfBytesToFlush
			));

		INIT_FUNC(NTSTATUS, NtAllocateVirtualMemory, (
			_In_ HANDLE ProcessHandle,
			_Inout_ _Outptr_result_buffer_(*RegionSize) PVOID *BaseAddress,
			_In_ ULONG_PTR ZeroBits,
			_Inout_ PSIZE_T RegionSize,
			_In_ ULONG AllocationType,
			_In_ ULONG Protect))
			DEF_FUNC_CODE(NtDllDll, NtAllocateVirtualMemory, STATUS_UNSUCCESSFUL, (
			ProcessHandle,
			BaseAddress,
			ZeroBits,
			RegionSize,
			AllocationType,
			Protect));

		INIT_FUNC(NTSTATUS,
			NtQueryVirtualMemory, (
			_In_ HANDLE ProcessHandle,
			_In_ PVOID Address,
			_In_ MEMORY_INFORMATION_CLASS VirtualMemoryInformationClass,
			_Out_ PVOID VirtualMemoryInformation,
			_In_ SIZE_T Length,
			_Out_opt_ PSIZE_T ResultLength
			))
			DEF_FUNC_CODE(NtDllDll, NtQueryVirtualMemory, STATUS_UNSUCCESSFUL, (
			 ProcessHandle,
			Address,
			 VirtualMemoryInformationClass,
			 VirtualMemoryInformation,
			 Length,
			 ResultLength
			));

		INIT_FUNC(NTSTATUS,
			NtFreeVirtualMemory, (
			_In_ HANDLE ProcessHandle,
			_Inout_ __drv_freesMem(Mem) PVOID *BaseAddress,
			_Inout_ PSIZE_T RegionSize,
			_In_ ULONG FreeType))
			DEF_FUNC_CODE(NtDllDll, NtFreeVirtualMemory, STATUS_UNSUCCESSFUL, (
			ProcessHandle,
			BaseAddress,
			RegionSize,
			FreeType));

#pragma endregion

#pragma region User32

		// FIX: 32位实现可以用__declspec(naked) __stdcall声明并在函数中jmp到api地址实现跳转, 但是64位不能用这个方法,所以先暂时用一个通用的方法
		// 下面的MessageBoxA是例子
		INIT_FUNC(int, MessageBoxA, (
			_In_opt_ HWND hWnd,
			_In_opt_ LPCSTR lpText,
			_In_opt_ LPCSTR lpCaption,
			_In_ UINT uType
			))
			DEF_FUNC_CODE(User32Dll,
			MessageBoxA, NULL, (
			hWnd,
			lpText,
			lpCaption,
			uType
			));


#pragma endregion

#pragma region Kernel32

		// NOTICE: 用到的慢慢补充
		
		INIT_FUNC(VOID,
			GetSystemInfo, (
			_Out_ LPSYSTEM_INFO lpSystemInfo
			))
			DEF_FUNC_CODE(Kernel32Dll, GetSystemInfo, , (lpSystemInfo));




		INIT_FUNC(HANDLE,
			CreateFileMappingW, (
			_In_ HANDLE hFile,
			_In_opt_ LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
			_In_ DWORD flProtect,
			_In_ DWORD dwMaximumSizeHigh,
			_In_ DWORD dwMaximumSizeLow,
			_In_opt_ LPCWSTR lpName
			))
			DEF_FUNC_CODE(Kernel32Dll, CreateFileMappingW, NULL, (
			hFile,
			lpFileMappingAttributes,
			flProtect,
			dwMaximumSizeHigh,
			dwMaximumSizeLow,
			lpName
			));

		INIT_FUNC(HANDLE,
			OpenFileMappingW, (
			_In_ DWORD dwDesiredAccess,
			_In_ BOOL bInheritHandle,
			_In_ LPCWSTR lpName
			))
			DEF_FUNC_CODE(Kernel32Dll, OpenFileMappingW, NULL, (
			dwDesiredAccess,
			bInheritHandle,
			lpName
			));

		INIT_FUNC(LPVOID,
			MapViewOfFile, (
			_In_ HANDLE hFileMappingObject,
			_In_ DWORD dwDesiredAccess,
			_In_ DWORD dwFileOffsetHigh,
			_In_ DWORD dwFileOffsetLow,
			_In_ SIZE_T dwNumberOfBytesToMap
			))
			DEF_FUNC_CODE(Kernel32Dll, MapViewOfFile, NULL, (
			hFileMappingObject,
			dwDesiredAccess,
			dwFileOffsetHigh,
			dwFileOffsetLow,
			dwNumberOfBytesToMap
			));

		INIT_FUNC(LPVOID,
			MapViewOfFileEx, (
			_In_ HANDLE hFileMappingObject,
			_In_ DWORD dwDesiredAccess,
			_In_ DWORD dwFileOffsetHigh,
			_In_ DWORD dwFileOffsetLow,
			_In_ SIZE_T dwNumberOfBytesToMap,
			_In_opt_ LPVOID lpBaseAddress
			))
			DEF_FUNC_CODE(Kernel32Dll, MapViewOfFileEx, NULL, (
			hFileMappingObject,
			dwDesiredAccess,
			dwFileOffsetHigh,
			dwFileOffsetLow,
			dwNumberOfBytesToMap,
			lpBaseAddress
			));

		INIT_FUNC(BOOL,
			FlushViewOfFile, (
			_In_ LPCVOID lpBaseAddress,
			_In_ SIZE_T dwNumberOfBytesToFlush
			))
			DEF_FUNC_CODE(Kernel32Dll, FlushViewOfFile, FALSE, (
			lpBaseAddress,
			dwNumberOfBytesToFlush
			));

		INIT_FUNC(BOOL,
			UnmapViewOfFile, (
			_In_ LPCVOID lpBaseAddress
			))
			DEF_FUNC_CODE(Kernel32Dll, UnmapViewOfFile, FALSE, (
			lpBaseAddress
			));

		INIT_FUNC(BOOL,
			VirtualLock, (
			_In_ LPVOID lpAddress,
			_In_ SIZE_T dwSize
			))
			DEF_FUNC_CODE(Kernel32Dll, VirtualLock, FALSE, (
			lpAddress,
			dwSize
			));

		INIT_FUNC(BOOL,
			VirtualUnlock, (
			_In_ LPVOID lpAddress,
			_In_ SIZE_T dwSize
			))
			DEF_FUNC_CODE(Kernel32Dll, VirtualUnlock, FALSE, (
			lpAddress,
			dwSize
			));

#pragma endregion

	}
}