#pragma once
#include "Common.h"
namespace Hook
{
	// 失败返回NULL, 成功返回函数对应导出表中的funcTable地址(unhook用到)
	// hook后不会自动调用原先函数, 如果需要则使用OUT参数

	// 非线程安全
	// 修改已载入模块的导出表，只会对之后的getprocaddress返回结果有效
	// @module: 模块指针，不能为NULL
	// @procName: 该模块的导出函数名
	// @return: 旧函数地址
	PVOID HookEat(HMODULE module, LPCSTR procName, LPCVOID hookFunc, OUT PDWORD* oldFuncRva = NULL);
}  // namespace Hook