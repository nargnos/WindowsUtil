#pragma once
#include "..\LazyLoad\LazyLoadSystemApi.h"
#include "..\..\PE\Export\Export.h"
namespace Process
{
	namespace Hook
	{
		// 失败返回NULL, 成功返回函数对应导出表中的funcTable地址(unhook用到)
		PVOID HookEat(LPCWSTR dllName, LPCSTR procName, LPCVOID hookFunc, OUT PDWORD oldFuncRva);

	}
}