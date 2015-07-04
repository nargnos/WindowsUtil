#pragma once
#include <Windows.h>
#include <WinBase.h>
#include <intrin.h>
#include "..\EnvironmentBlock.h"
#include "..\..\PE\Export\ExportReader.h"
namespace LazyLoad
{
#pragma region 基本函数
#define INIT_FUNC(result,name,params) FuncType_##name _##name=Def_##name;result WINAPI Def_##name params
#define DEF_FUNC(result,name,params) typedef result (WINAPI *FuncType_##name)params;result WINAPI Def_##name params;extern FuncType_##name _##name;


	VOID NTAPI _RtlInitUnicodeString(IN OUT PUNICODE_STRING DestinationString, IN PCWSTR SourceString);

	DEF_FUNC(
		NTSTATUS, LdrLoadDll, (_In_opt_ PWSTR SearchPath, _In_opt_ PULONG LoadFlags, _In_ PUNICODE_STRING Name, _Out_opt_ PVOID *BaseAddress)
		);


	HINSTANCE WINAPI _LoadLibraryExW(LPCWSTR lpLibFileName, HANDLE ignore, DWORD dwFlags);
	HINSTANCE WINAPI _LoadLibraryW(LPCWSTR lpLibFileName);
	FARPROC _GetProcAddress(HMODULE module, LPCSTR procName);
	FARPROC _GetProcAddressEx(LPCWSTR dllName, LPCSTR procName);

#define DEF_FUNC_CODE(dllName, procName, failedReturn, params)	\
		{														\
			auto addr = _GetProcAddressEx(dllName, #procName);	\
			if (addr)											\
			{													\
				_##procName = (FuncType_##procName)addr;		\
				return _##procName params;						\
			}													\
			return failedReturn;								\
		}
#pragma endregion

#pragma region 常用函数定义
#define DEF_DEFAULT_FUNC
#ifdef DEF_DEFAULT_FUNC

	// MessageBoxA函数替换
	DEF_FUNC(int, MessageBoxA, (
		_In_opt_ HWND hWnd,
		_In_opt_ LPCSTR lpText,
		_In_opt_ LPCSTR lpCaption,
		_In_ UINT uType));

	DEF_FUNC(BOOL, VirtualProtect, (
		_In_ LPVOID lpAddress,
		_In_ SIZE_T dwSize,
		_In_ DWORD flNewProtect,
		_Out_ PDWORD lpflOldProtect
		));

#endif
#pragma endregion


}