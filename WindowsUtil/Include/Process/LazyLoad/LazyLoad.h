#pragma once
#include <Windows.h>
#include <WinBase.h>
#include <intrin.h>
#include "..\EnvironmentBlock.h"
#include "..\..\PE\Export\ExportReader.h"
namespace LazyLoad
{ 

#define DEF_FUNC(dll,name) void Load_##name();\
Def_##name Lazy_##name = (Def_##name)Load_##name;\
__declspec(naked) void Load_##name()\
{\
	Lazy_##name = (Def_##name)Lazy_GetProcAddress(dll, #name);\
	_asm jmp Lazy_##name\
}
//InitLazyLoad();\*(PINT_PTR)_AddressOfReturnAddress() = (INT_PTR)Lazy_##name;\

#define  DEF0(result,name) typedef  result(WINAPI *Def_##name)();
#define  DEF1(result,name,param1) typedef result(WINAPI *Def_##name)(param1);
#define  DEF2(result,name,param1,param2) typedef result(WINAPI *Def_##name)(param1,param2);
#define  DEF3(result,name,param1,param2,param3) typedef result(WINAPI *Def_##name)(param1,param2,param3);
#define  DEF4(result,name,param1,param2,param3,param4) typedef result(WINAPI *Def_##name)(param1,param2,param3,param4);
#define  DEF5(result,name,param1,param2,param3,param4,param5) typedef result(WINAPI *Def_##name)(param1,param2,param3,param4,param5);
#define  DEF6(result,name,param1,param2,param3,param4,param5,param6) typedef result(WINAPI *Def_##name)(param1,param2,param3,param4,param5,param6);
#define  DEF7(result,name,param1,param2,param3,param4,param5,param6,param7) typedef result(WINAPI *Def_##name)(param1,param2,param3,param4,param5,param6,param7);
#define  DEF8(result,name,param1,param2,param3,param4,param5,param6,param7,param8) typedef result(WINAPI *Def_##name)(param1,param2,param3,param4,param5,param6,param7,param8);
#define  DEF9(result,name,param1,param2,param3,param4,param5,param6,param7,param8,param9) typedef result(WINAPI *Def_##name)(param1,param2,param3,param4,param5,param6,param7,param8,param9);
#define DEF10(result,name,param1,param2,param3,param4,param5,param6,param7,param8,param9,param10) typedef result(WINAPI *Def_##name)(param1,param2,param3,param4,param5,param6,param7,param8,param9,param10);
#define DEF11(result,name,param1,param2,param3,param4,param5,param6,param7,param8,param9,param10,param11) typedef result(WINAPI *Def_##name)(param1,param2,param3,param4,param5,param6,param7,param8,param9,param10,param11);


#define  DEF_FUNC0(dll,result,name) typedef  result(WINAPI *Def_##name)();\
DEF_FUNC(dll,name)
#define  DEF_FUNC1(dll,result,name,param1) typedef result(WINAPI *Def_##name)(param1);\
DEF_FUNC(dll,name)
#define  DEF_FUNC2(dll,result,name,param1,param2) typedef result(WINAPI *Def_##name)(param1,param2);\
DEF_FUNC(dll,name)
#define  DEF_FUNC3(dll,result,name,param1,param2,param3) typedef result(WINAPI *Def_##name)(param1,param2,param3);\
DEF_FUNC(dll,name)
#define  DEF_FUNC4(dll,result,name,param1,param2,param3,param4) typedef result(WINAPI *Def_##name)(param1,param2,param3,param4);\
DEF_FUNC(dll,name)
#define  DEF_FUNC5(dll,result,name,param1,param2,param3,param4,param5) typedef result(WINAPI *Def_##name)(param1,param2,param3,param4,param5);\
DEF_FUNC(dll,name)
#define  DEF_FUNC6(dll,result,name,param1,param2,param3,param4,param5,param6) typedef result(WINAPI *Def_##name)(param1,param2,param3,param4,param5,param6);\
DEF_FUNC(dll,name)
#define  DEF_FUNC7(dll,result,name,param1,param2,param3,param4,param5,param6,param7) typedef result(WINAPI *Def_##name)(param1,param2,param3,param4,param5,param6,param7);\
DEF_FUNC(dll,name)
#define  DEF_FUNC8(dll,result,name,param1,param2,param3,param4,param5,param6,param7,param8) typedef result(WINAPI *Def_##name)(param1,param2,param3,param4,param5,param6,param7,\
DEF_FUNC(dll,name)param8);
#define  DEF_FUNC9(dll,result,name,param1,param2,param3,param4,param5,param6,param7,param8,param9) typedef result(WINAPI *Def_##name)(param1,param2,param3,param4,param5,param6,\
DEF_FUNC(dll,name)param7,param8,param9);
#define DEF_FUNC10(dll,result,name,param1,param2,param3,param4,param5,param6,param7,param8,param9,param10) typedef result(WINAPI *Def_##name)(param1,param2,param3,param4,param5,\
DEF_FUNC(dll,name)param6,param7,param8,param9,param10);
#define DEF_FUNC11(dll,result,name,param1,param2,param3,param4,param5,param6,param7,param8,param9,param10,param11) typedef result(WINAPI *Def_##name)(param1,param2,param3,param4,\
DEF_FUNC(dll,name)param5,param6,param7,param8,param9,param10,param11);


//HMODULE LazyKernel32;
//HMODULE GetKernel32Base()
//{
//	return GetModuleHandleA("kernel32.dll"); // TODO
//}
//HMODULE LazyUser32;
//HMODULE GetUser32Base()
//{
//	
//	return LoadLibraryA("user32.dll"); // TODO
//}
//
//
//typedef HMODULE(WINAPI*Def_LoadLibraryW)(LPCWSTR);
//typedef FARPROC(WINAPI*Def_GetProcAddress)(HMODULE, LPCSTR);
//
//void Load_LoadLibraryW();
//void Load_GetProcAddress();
//
//Def_LoadLibraryW Lazy_LoadLibraryW = (Def_LoadLibraryW)Load_LoadLibraryW;
//Def_GetProcAddress Lazy_GetProcAddress = (Def_GetProcAddress)Load_GetProcAddress;
//
//__declspec(naked) void Load_LoadLibraryW()
//{
//	Lazy_LoadLibraryW = LoadLibraryW; // TODO
//	_asm jmp Lazy_LoadLibraryW;
//}
//__declspec(naked) void Load_GetProcAddress()
//{
//	Lazy_GetProcAddress = GetProcAddress; // TODO
//	_asm jmp Lazy_GetProcAddress;
//}





//typedef bool(*Def_Beep)(int, int);
//__declspec(naked) void Load_Beep()
//{
//	Lazy_Beep = (Def_Beep)Lazy_GetProcAddress(LazyKernel32, "Beep");
//	//_asm jmp Lazy_Beep;
//	auto retAddr = (PINT_PTR)_AddressOfReturnAddress();
//	*retAddr = (INT_PTR)Lazy_Beep;
//}
//Def_Beep Lazy_Beep = (Def_Beep)Load_Beep;

//DEF_FUNC2(LazyKernel32,bool, Beep, int, int)
//
//DEF_FUNC4(LazyUser32,int, MessageBoxA, int, int, int, int)
//



void WINAPI XXAA();
HMODULE WINAPI XXAA2(LPCSTR dllName);

static HMODULE NtDll = NULL;
DEF4(NTSTATUS, LdrLoadDll,
	_In_opt_ PWSTR SearchPath,
	_In_opt_ PULONG LoadFlags,
	_In_ PUNICODE_STRING Name,
	_Out_opt_ PVOID *BaseAddress
	); 
NTSTATUS WINAPI __InitLdrLoadDllAddress(
	_In_opt_ PWSTR SearchPath,
	_In_opt_ PULONG LoadFlags,
	_In_ PUNICODE_STRING Name,
	_Out_opt_ PVOID *BaseAddress);
Def_LdrLoadDll _LdrLoadDll = Def_LdrLoadDll(__InitLdrLoadDllAddress);

NTSTATUS WINAPI __InitLdrLoadDllAddress(
	_In_opt_ PWSTR SearchPath,
	_In_opt_ PULONG LoadFlags,
	_In_ PUNICODE_STRING Name,
	_Out_opt_ PVOID *BaseAddress)
{
	if (!NtDll)
	{
		NtDll = Peb::FindLoadedModuleHandle(L"ntdll.dll");
	}
	_LdrLoadDll = Def_LdrLoadDll(PE::Export::GetProcAddress(NtDll, "LdrLoadDll"));
	return _LdrLoadDll(SearchPath, LoadFlags, Name, BaseAddress);
}


DEF1(HMODULE, LoadLibraryA, LPCSTR);
Def_LoadLibraryA __LoadLibraryA = (Def_LoadLibraryA)XXAA;


PCHAR Name = "LoadLibraryA";

FARPROC GetAddr(LPCWSTR moduleName, LPCSTR funcName)
{
	// 样板, 大概这个流程
	auto dll = Peb::FindLoadedModuleHandle(moduleName);
	if (!dll)
	{
		if (!_LdrLoadDll(0, 0, 0, (PVOID*)&dll))
		{
			return NULL;
		}
	}
	return PE::Export::GetProcAddress(dll, "LdrLoadDll");
}

void Test()
{
	MessageBoxA(0, "test start", "test", 0);
	auto a = Peb::FindLoadedModuleHandle(L"user32.dll");
	auto b = (int (*)(HWND,LPCSTR,LPCSTR,UINT))PE::Export::GetProcAddress(a, "MessageBoxA");
	b(0, "test success", "success", 0);
}
__declspec(naked) void WINAPI XXAA()
{
	__LoadLibraryA = (Def_LoadLibraryA)GetAddr(L"ntdll.dll", "LdrLoadDll");
	//__LoadLibraryA = (Def_LoadLibraryA)XXAA2;
	// jmp64位不能内联,换个方法
	_asm jmp __LoadLibraryA
	//return __LoadLibraryA(dllName);
}

HMODULE WINAPI XXAA2(LPCSTR dllName)
{
	
	return (HMODULE)1;
}

}