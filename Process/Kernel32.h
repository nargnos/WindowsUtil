#pragma once
#include "Common.h"
#include "LoadDllBase.h"
#include "DefaultGetDllModulePolicy.h"
#include "DynamicCall.h"
namespace Process
{
	namespace LazyLoad
	{
		using Process::LazyLoad::Detail::DynamicCall;
		using Process::LazyLoad::Detail::LoadDllBase;
		using Process::LazyLoad::Detail::DefaultGetDllModulePolicy;

		class Kernel32
		{
		public:
			class LoadKernel32;
			static const LoadKernel32& Instance();
		private:
			Kernel32() = delete;
			~Kernel32() = delete;
			static LoadKernel32 instance_;
		};

		class Kernel32::LoadKernel32 :
			public LoadDllBase<DefaultGetDllModulePolicy>
		{
		public:
			friend class Kernel32;
			~LoadKernel32() = default;


			DynamicCall<VOID WINAPI(
				_Out_ LPSYSTEM_INFO lpSystemInfo
			), TLoadDllBase>
				GetSystemInfo;

			DynamicCall<HANDLE WINAPI(
				_In_ HANDLE hFile,
				_In_opt_ LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
				_In_ DWORD flProtect,
				_In_ DWORD dwMaximumSizeHigh,
				_In_ DWORD dwMaximumSizeLow,
				_In_opt_ LPCWSTR lpName
			), TLoadDllBase>
				CreateFileMappingW;

			DynamicCall<HANDLE WINAPI(
				_In_ DWORD dwDesiredAccess,
				_In_ BOOL bInheritHandle,
				_In_ LPCWSTR lpName
			), TLoadDllBase>
				OpenFileMappingW;

			DynamicCall<LPVOID WINAPI(
				_In_ HANDLE hFileMappingObject,
				_In_ DWORD dwDesiredAccess,
				_In_ DWORD dwFileOffsetHigh,
				_In_ DWORD dwFileOffsetLow,
				_In_ SIZE_T dwNumberOfBytesToMap
			), TLoadDllBase>
				MapViewOfFile;

			DynamicCall<LPVOID WINAPI(
				_In_ HANDLE hFileMappingObject,
				_In_ DWORD dwDesiredAccess,
				_In_ DWORD dwFileOffsetHigh,
				_In_ DWORD dwFileOffsetLow,
				_In_ SIZE_T dwNumberOfBytesToMap,
				_In_opt_ LPVOID lpBaseAddress
			), TLoadDllBase>
				MapViewOfFileEx;

			DynamicCall<BOOL WINAPI(
				_In_ LPCVOID lpBaseAddress,
				_In_ SIZE_T dwNumberOfBytesToFlush
			), TLoadDllBase>
				FlushViewOfFile;

			DynamicCall<BOOL WINAPI(
				_In_ LPCVOID lpBaseAddress
			), TLoadDllBase>
				UnmapViewOfFile;

			DynamicCall<BOOL WINAPI(
				_In_ LPVOID lpAddress,
				_In_ SIZE_T dwSize
			), TLoadDllBase>
				VirtualLock;

			DynamicCall<BOOL WINAPI(
				_In_ LPVOID lpAddress,
				_In_ SIZE_T dwSize
			), TLoadDllBase>
				VirtualUnlock;

			// 下面有重写的不用dll的版本, 可以不用下面的函数
			DynamicCall<HANDLE WINAPI(
				_In_ DWORD dwDesiredAccess,
				_In_ BOOL bInheritHandle,
				_In_ DWORD dwProcessId
			), TLoadDllBase>
				OpenProcess;

			DynamicCall<BOOL WINAPI(
				_In_ HANDLE hThread,
				_In_ CONST CONTEXT * lpContext
			), TLoadDllBase>
				SetThreadContext;

			DynamicCall<BOOL WINAPI(
				_In_ LPVOID lpAddress,
				_In_ SIZE_T dwSize,
				_In_ DWORD flNewProtect,
				_Out_ PDWORD lpflOldProtect
			), TLoadDllBase>
				VirtualProtect;

			DynamicCall<BOOL WINAPI(
				_In_ HANDLE hProcess,
				_In_ LPVOID lpAddress,
				_In_ SIZE_T dwSize,
				_In_ DWORD flNewProtect,
				_Out_ PDWORD lpflOldProtect
			), TLoadDllBase>
				VirtualProtectEx;

			DynamicCall<BOOL WINAPI(
				_In_ HANDLE hProcess,
				_In_ LPCVOID lpBaseAddress,
				_Out_writes_bytes_to_(nSize, *lpNumberOfBytesRead) LPVOID lpBuffer,
				_In_ SIZE_T nSize,
				_Out_opt_ SIZE_T * lpNumberOfBytesRead
			), TLoadDllBase>
				ReadProcessMemory;

			DynamicCall<BOOL WINAPI(
				_In_ HANDLE hProcess,
				_In_ LPVOID lpBaseAddress,
				_In_reads_bytes_(nSize) LPCVOID lpBuffer,
				_In_ SIZE_T nSize,
				_Out_opt_ SIZE_T * lpNumberOfBytesWritten
			), TLoadDllBase>
				WriteProcessMemory;

			DynamicCall<LPVOID WINAPI(
				_In_opt_ LPVOID lpAddress,
				_In_ SIZE_T dwSize,
				_In_ DWORD flAllocationType,
				_In_ DWORD flProtect
			), TLoadDllBase>
				VirtualAlloc;

			DynamicCall<LPVOID WINAPI(
				_In_ HANDLE hProcess,
				_In_opt_ LPVOID lpAddress,
				_In_ SIZE_T dwSize,
				_In_ DWORD flAllocationType,
				_In_ DWORD flProtect
			), TLoadDllBase>
				VirtualAllocEx;

			DynamicCall<SIZE_T WINAPI(
				_In_opt_ LPCVOID lpAddress,
				_Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer,
				_In_ SIZE_T dwLength
			), TLoadDllBase>
				VirtualQuery;

			DynamicCall<SIZE_T WINAPI(
				_In_ HANDLE hProcess,
				_In_opt_ LPCVOID lpAddress,
				_Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer,
				_In_ SIZE_T dwLength
			), TLoadDllBase>
				VirtualQueryEx;

			DynamicCall<BOOL WINAPI(
				_In_ HANDLE hProcess,
				_Pre_notnull_ _When_(dwFreeType == MEM_DECOMMIT, _Post_invalid_) _When_(dwFreeType == MEM_RELEASE, _Post_ptr_invalid_)
				LPVOID lpAddress,
				_In_ SIZE_T dwSize,
				_In_ DWORD dwFreeType
			), TLoadDllBase>
				VirtualFreeEx;

			DynamicCall<BOOL WINAPI(
				IN LPVOID lpAddress,
				IN SIZE_T dwSize,
				IN DWORD dwFreeType
			), TLoadDllBase>
				VirtualFree;


		protected:
			LoadKernel32();

		};

	}  // namespace LazyLoad
}  // namespace Process
