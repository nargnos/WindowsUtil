#pragma once
#include "Common.h"
namespace Hook
{
	// 非线程安全
	// 修改指定模块的导入表存储的函数指针，只会对直接调用的函数有效
	// @module: 目标MODULE, NULL表示自身程序
	// @dllName: hook函数所在的dll
	// @procName: hook的函数名
	// @hookFunc: 需要写入的函数地址
	// @unhookAddress: 成功hook将返回thunk地址,unhook的时候用到(把oldFuncAddress写入就可以),传入NULL则忽略掉
	// @return:  成功会返回旧函数地址，hook后不会自动调用原先函数, 如果需要可以调用此指针, 失败返回NULL
	PVOID HookIat(HMODULE module, LPCSTR dllName, LPCSTR procName, LPCVOID hookFunc, OUT PVOID* unhookAddress);

	bool UnHookIat(PVOID unhookAddress, PVOID oldFunctionAddress);
}  // namespace Hook