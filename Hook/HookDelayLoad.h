#pragma once
#include "Common.h"
namespace Hook
{
	// 不支持序数,成功会返回延迟导入表函数指针Table的地址
	// 修改指定模块的延迟导入表
	// @module: 要修改的模块，NULL表示自身程序
	// @dllName: 延迟导入的dll名
	// @return: 旧函数地址
	PVOID HookDelayLoad(HMODULE module, LPCSTR dllName, LPCSTR procName, PVOID hookFunc, OUT PVOID* oldFuncAddr = NULL);
}  // namespace Hook