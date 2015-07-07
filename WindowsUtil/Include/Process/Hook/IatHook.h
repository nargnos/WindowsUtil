#pragma once
#include "..\LazyLoad\LazyLoadSystemApi.h"
#include "..\..\PE\Import\Import.h"
namespace Process
{
	namespace Hook
	{
		// 成功hook返回thunk地址, unhook的时候用到, 失败返回NULL
		PVOID HookIat(LPCSTR dllName, LPCSTR procName, LPCVOID hookFunc, OUT PVOID* oldFuncAddress);
		PVOID HookIat(LPCSTR procName, LPCVOID hookFunc, OUT PVOID* oldFuncAddress); 
		
	}
}
