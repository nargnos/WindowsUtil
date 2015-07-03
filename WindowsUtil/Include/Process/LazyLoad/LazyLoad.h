#pragma once
#include <Windows.h>
#include <WinBase.h>
#include <intrin.h>
#include "..\EnvironmentBlock.h"
#include "..\..\PE\Export\ExportReader.h"
namespace LazyLoad
{
#pragma region 基本函数

#define DEF_FUNC(result,name,params) typedef result (WINAPI *FuncType_##name)params;result WINAPI Def_##name params;extern FuncType_##name _##name;

	VOID NTAPI _RtlInitUnicodeString(IN OUT PUNICODE_STRING DestinationString, IN PCWSTR SourceString);

	DEF_FUNC(
		NTSTATUS, LdrLoadDll, (_In_opt_ PWSTR SearchPath, _In_opt_ PULONG LoadFlags, _In_ PUNICODE_STRING Name, _Out_opt_ PVOID *BaseAddress)
		);


	HINSTANCE WINAPI _LoadLibraryExW(LPCWSTR lpLibFileName, HANDLE ignore, DWORD dwFlags);
	HINSTANCE WINAPI _LoadLibraryW(LPCWSTR lpLibFileName);
	FARPROC _GetProcAddress(HMODULE module, LPCSTR lpProcName);

#pragma endregion

#pragma region 常用函数定义
#define DEF_DEFAULT_FUNC
#ifdef DEF_DEFAULT_FUNC
	DEF_FUNC(int, MessageBoxA, (
		_In_opt_ HWND hWnd,
		_In_opt_ LPCSTR lpText,
		_In_opt_ LPCSTR lpCaption,
		_In_ UINT uType));

#endif
#pragma endregion


}