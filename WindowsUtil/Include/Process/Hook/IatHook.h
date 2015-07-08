#pragma once
#include "..\LazyLoad\LazyLoadSystemApi.h"
#include "..\..\PE\Import\Import.h"
namespace Process
{
	namespace Hook
	{
		// 成功hook返回thunk地址, unhook的时候用到, 失败返回NULL, hook后不会自动调用原先函数
		// hook后不会自动调用原先函数, 如果需要则使用OUT参数
		PVOID HookIat(LPCSTR dllName, LPCSTR procName, LPCVOID hookFunc, OUT PVOID* oldFuncAddress=NULL);
		PVOID HookIat(LPCSTR procName, LPCVOID hookFunc, OUT PVOID* oldFuncAddress = NULL);
		
	}
}
