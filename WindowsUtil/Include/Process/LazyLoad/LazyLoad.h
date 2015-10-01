#pragma once
#include <Windows.h>
#include <WinBase.h>
#include <intrin.h>
#include "..\EnvironmentBlock\EnvironmentBlock.h"
#include "..\..\PE\Export\Export.h"
#include "WinApiDynamicCallDef.h"
#include "..\OverwriteWinApi\OverwriteWinApi.h"
using namespace Process::EnvironmentBlock;
namespace Process
{
	namespace LazyLoad
	{
		// 取dll用的是LdrLoadDll,取函数用的是本地自实现的版本
#pragma region 基本核心函数
	
		VOID NTAPI _RtlInitUnicodeString(IN OUT PUNICODE_STRING DestinationString, IN PCWSTR SourceString);

		HINSTANCE WINAPI _LoadLibraryExW(LPCWSTR lpLibFileName, HANDLE ignore, DWORD dwFlags);
		HINSTANCE WINAPI _LoadLibraryW(LPCWSTR lpLibFileName);
		FARPROC _GetProcAddress(HMODULE module, LPCSTR procName);
		FARPROC _GetProcAddressEx(LPCWSTR dllName, LPCSTR procName);


		class _NtDll;

		class _NtDll:public _LoadDll
		{
		public:
			_NtDll(LPCWSTR dllName) :_LoadDll(dllName)
			{
			}
			~_NtDll();
			virtual HINSTANCE GetDll();

			WinApiDynamicCall<NTSTATUS WINAPI(_In_opt_ PWSTR SearchPath,
				_In_opt_ PULONG LoadFlags,
				_In_ PUNICODE_STRING Name,
				_Out_opt_ PVOID *BaseAddress)> _LdrLoadDll;
			
			WinApiDynamicCall<NTSTATUS WINAPI(
					OUT PHANDLE ProcessHandle,
					IN ACCESS_MASK DesiredAccess,
					IN POBJECT_ATTRIBUTES ObjectAttributes,
					IN PCLIENT_ID ClientId)> _NtOpenProcess;
			WinApiDynamicCall<NTSTATUS WINAPI(
				_In_ HANDLE ThreadHandle,
				_In_ PCONTEXT Context
				)> _NtSetContextThread;

			WinApiDynamicCall<NTSTATUS WINAPI(
				_In_ HANDLE ProcessHandle,
				_In_ PVOID *BaseAddress,
				_In_ SIZE_T *NumberOfBytesToProtect,
				_In_ ULONG NewAccessProtection,
				_Out_ PULONG OldAccessProtection
				)> _NtProtectVirtualMemory;


			WinApiDynamicCall<NTSTATUS WINAPI(
				_In_ HANDLE ProcessHandle,
				_In_ PVOID BaseAddress,
				_Out_ PVOID Buffer,
				_In_ SIZE_T NumberOfBytesToRead,
				_Out_opt_ PSIZE_T NumberOfBytesRead
				)> _NtReadVirtualMemory;


			WinApiDynamicCall<NTSTATUS WINAPI(
				_In_ HANDLE ProcessHandle,
				_In_ PVOID  BaseAddress,
				_In_ PVOID Buffer,
				_In_ SIZE_T NumberOfBytesToWrite,
				_Out_opt_ PSIZE_T NumberOfBytesWritten
				)> _NtWriteVirtualMemory;


			WinApiDynamicCall<NTSTATUS WINAPI(
				_In_ HANDLE ProcessHandle,
				_In_ PVOID BaseAddress,
				_In_ ULONG NumberOfBytesToFlush
				)> _NtFlushInstructionCache;


			WinApiDynamicCall<NTSTATUS WINAPI(
				_In_ HANDLE ProcessHandle,
				_Inout_ _Outptr_result_buffer_(*RegionSize) PVOID *BaseAddress,
				_In_ ULONG_PTR ZeroBits,
				_Inout_ PSIZE_T RegionSize,
				_In_ ULONG AllocationType,
				_In_ ULONG Protect)> _NtAllocateVirtualMemory;


			WinApiDynamicCall<NTSTATUS WINAPI(
				_In_ HANDLE ProcessHandle,
				_In_ PVOID Address,
				_In_ MEMORY_INFORMATION_CLASS VirtualMemoryInformationClass,
				_Out_ PVOID VirtualMemoryInformation,
				_In_ SIZE_T Length,
				_Out_opt_ PSIZE_T ResultLength
				)> _NtQueryVirtualMemory;


			WinApiDynamicCall<NTSTATUS WINAPI(
				_In_ HANDLE ProcessHandle,
				_Inout_ __drv_freesMem(Mem) PVOID *BaseAddress,
				_Inout_ PSIZE_T RegionSize,
				_In_ ULONG FreeType)> _NtFreeVirtualMemory;


		protected:
			virtual void FuncRegister();
		};

		extern _NtDll NtDll_Dll;
	}
}