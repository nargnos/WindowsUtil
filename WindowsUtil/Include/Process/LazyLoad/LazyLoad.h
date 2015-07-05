#pragma once
#include <Windows.h>
#include <WinBase.h>
#include <intrin.h>
#include "..\EnvironmentBlock\EnvironmentBlock.h"
#include "..\..\PE\Export\ExportReader.h"
namespace Process
{
	namespace LazyLoad
	{
#pragma region 基本核心函数
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

		//failedReturn 指的是找不到函数会返回的默认值
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


	}
}