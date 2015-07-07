#include "EatHook.h"

namespace Process
{
	namespace Hook
	{
		PVOID HookEat(LPCWSTR dllName, LPCSTR procName, LPCVOID hookFunc, OUT PDWORD oldFuncRva)
		{
			auto dllBase = LazyLoad::_LoadLibraryW(dllName);
			
			PE::PeDecoder dll(dllBase, true);
			auto result = PE::Export::GetProcExportFuncTableAddress(dll, procName);
			if (!result)
			{
				return NULL;
			}
			// dll base + rva = funcRealAddress 可推导出
			// base + setRva = hookAddress
			if (oldFuncRva)
			{
				*oldFuncRva = *result;
			}
			DWORD setRva;
			if (dll.HasNtHeader32())
			{
				setRva = (DWORD)hookFunc - (DWORD)dllBase;
			}
			else
			{
				setRva = (DWORDLONG)hookFunc - (DWORDLONG)dllBase;
			}
			Process::LazyLoad::_WriteProcessMemory(NtCurrentProcess(), result, &setRva, sizeof(DWORD), NULL);
			return result;
		}
	}
}