#pragma once
#include <Windows.h>
#include <WinBase.h>
#include <intrin.h>
#include "LazyLoad.h"
using namespace Process::EnvironmentBlock;
namespace Process
{
	namespace LazyLoad
	{
		// 不使用decltype定义,因为要include太多头文件
		class _Kernel32 :public _LoadDll
		{
		protected:
			virtual void FuncRegister();
		public:
			_Kernel32(LPCWSTR dllName):_LoadDll(dllName)
			{
			}
			WinApiDynamicCall<VOID WINAPI(
				_Out_ LPSYSTEM_INFO lpSystemInfo
				)> _GetSystemInfo;

			WinApiDynamicCall<HANDLE WINAPI(
				_In_ HANDLE hFile,
				_In_opt_ LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
				_In_ DWORD flProtect,
				_In_ DWORD dwMaximumSizeHigh,
				_In_ DWORD dwMaximumSizeLow,
				_In_opt_ LPCWSTR lpName
				)> _CreateFileMappingW;

			WinApiDynamicCall<HANDLE WINAPI(
				_In_ DWORD dwDesiredAccess,
				_In_ BOOL bInheritHandle,
				_In_ LPCWSTR lpName
				)> _OpenFileMappingW;

			WinApiDynamicCall<LPVOID WINAPI(
				_In_ HANDLE hFileMappingObject,
				_In_ DWORD dwDesiredAccess,
				_In_ DWORD dwFileOffsetHigh,
				_In_ DWORD dwFileOffsetLow,
				_In_ SIZE_T dwNumberOfBytesToMap
				)> _MapViewOfFile;

			WinApiDynamicCall<LPVOID WINAPI(
				_In_ HANDLE hFileMappingObject,
				_In_ DWORD dwDesiredAccess,
				_In_ DWORD dwFileOffsetHigh,
				_In_ DWORD dwFileOffsetLow,
				_In_ SIZE_T dwNumberOfBytesToMap,
				_In_opt_ LPVOID lpBaseAddress
				)> _MapViewOfFileEx;

			WinApiDynamicCall<BOOL WINAPI(
				_In_ LPCVOID lpBaseAddress,
				_In_ SIZE_T dwNumberOfBytesToFlush
				)> _FlushViewOfFile;

			WinApiDynamicCall<BOOL WINAPI(
				_In_ LPCVOID lpBaseAddress
				)> _UnmapViewOfFile;

			WinApiDynamicCall<BOOL WINAPI(
				_In_ LPVOID lpAddress,
				_In_ SIZE_T dwSize
				)> _VirtualLock;

			WinApiDynamicCall<BOOL WINAPI(
				_In_ LPVOID lpAddress,
				_In_ SIZE_T dwSize
				)> _VirtualUnlock;

			// 下面的重写的不用dll的版本, 可以不用下面的函数
			WinApiDynamicCall<HANDLE WINAPI(
					_In_ DWORD dwDesiredAccess,
					_In_ BOOL bInheritHandle,
					_In_ DWORD dwProcessId
					)> _OpenProcess;


			WinApiDynamicCall<BOOL WINAPI(
					_In_ HANDLE hThread,
					_In_ CONST CONTEXT * lpContext
					)> _SetThreadContext;

			WinApiDynamicCall<BOOL WINAPI(
					_In_ LPVOID lpAddress,
					_In_ SIZE_T dwSize,
					_In_ DWORD flNewProtect,
					_Out_ PDWORD lpflOldProtect
					)> _VirtualProtect;

			WinApiDynamicCall<BOOL WINAPI(
					_In_ HANDLE hProcess,
					_In_ LPVOID lpAddress,
					_In_ SIZE_T dwSize,
					_In_ DWORD flNewProtect,
					_Out_ PDWORD lpflOldProtect
					)> _VirtualProtectEx;

			WinApiDynamicCall<BOOL WINAPI(
					_In_ HANDLE hProcess,
					_In_ LPCVOID lpBaseAddress,
					_Out_writes_bytes_to_(nSize, *lpNumberOfBytesRead) LPVOID lpBuffer,
					_In_ SIZE_T nSize,
					_Out_opt_ SIZE_T * lpNumberOfBytesRead
					)> _ReadProcessMemory;

			WinApiDynamicCall<BOOL WINAPI(
					_In_ HANDLE hProcess,
					_In_ LPVOID lpBaseAddress,
					_In_reads_bytes_(nSize) LPCVOID lpBuffer,
					_In_ SIZE_T nSize,
					_Out_opt_ SIZE_T * lpNumberOfBytesWritten
					)> _WriteProcessMemory;

			WinApiDynamicCall<LPVOID WINAPI(
					_In_opt_ LPVOID lpAddress,
					_In_ SIZE_T dwSize,
					_In_ DWORD flAllocationType,
					_In_ DWORD flProtect
					)> _VirtualAlloc;

			WinApiDynamicCall<LPVOID WINAPI(
					_In_ HANDLE hProcess,
					_In_opt_ LPVOID lpAddress,
					_In_ SIZE_T dwSize,
					_In_ DWORD flAllocationType,
					_In_ DWORD flProtect
					)> _VirtualAllocEx;

			WinApiDynamicCall<SIZE_T WINAPI(
					_In_opt_ LPCVOID lpAddress,
					_Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer,
					_In_ SIZE_T dwLength
					)> _VirtualQuery;


			WinApiDynamicCall<SIZE_T WINAPI(
					_In_ HANDLE hProcess,
					_In_opt_ LPCVOID lpAddress,
					_Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer,
					_In_ SIZE_T dwLength
					)> _VirtualQueryEx;


			WinApiDynamicCall<BOOL WINAPI(
					_In_ HANDLE hProcess,
					_Pre_notnull_ _When_(dwFreeType == MEM_DECOMMIT, _Post_invalid_) _When_(dwFreeType == MEM_RELEASE, _Post_ptr_invalid_) LPVOID lpAddress,
					_In_ SIZE_T dwSize,
					_In_ DWORD dwFreeType
					)> _VirtualFreeEx;

			WinApiDynamicCall<BOOL WINAPI(
					IN LPVOID lpAddress,
					IN SIZE_T dwSize,
					IN DWORD dwFreeType
					)> _VirtualFree;

		};
		extern _Kernel32 Kernel32_Dll;
		class _User32 :public _LoadDll
		{
		public:
			_User32(LPCWSTR dllName) :_LoadDll(dllName)
			{
			}
			WinApiDynamicCall<int WINAPI(
				_In_opt_ HWND hWnd,
				_In_opt_ LPCSTR lpText,
				_In_opt_ LPCSTR lpCaption,
				_In_ UINT uType
				)> _MessageBoxA;
		protected:
			virtual void FuncRegister();
		};
		extern _User32 User32_Dll;

	}
}