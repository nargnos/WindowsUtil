#pragma once
#include "..\PeImage.h"
namespace PE
{
	PDWORD GetProcExportFuncTableAddress(PeDecoder & pe, LPCSTR lpProcName);  // 二分查找
	// NOTICE: 下面的函数只支持搜索函数名, 不使用序数
	FARPROC GetProcAddress(PeDecoder & pe, LPCSTR lpProcName);
	FARPROC GetProcAddress(HMODULE module, LPCSTR lpProcName);
	FARPROC GetProcAddress(HMODULE module, PVOID compareName, bool compareCallback(PVOID compare, LPCSTR procName));  // 顺序查找, 带比较器, 返回true表示值相同
	FARPROC GetProcAddress(PeDecoder & pe, PVOID compareName, bool compareCallback(PVOID compare, LPCSTR procName));

}
