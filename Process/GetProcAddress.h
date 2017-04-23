#pragma once
#include "Common.h"

namespace Process
{
	namespace Overwrite
	{
		// NOTICE: 下面的函数只支持搜索函数名, 不使用序数
		// 二分查找(导出表有序)
		_Ret_maybenull_ void* GetProcAddress(_In_ _Notnull_ HMODULE module,
			_In_ _Notnull_ LPCSTR lpProcName);
		// 顺序查找
		// function参数是读到的字符
		_Ret_maybenull_ void* GetProcAddress(_In_ _Notnull_ HMODULE module,
			const _STD function<bool(LPCSTR)>& comp);

		// 二分查找, 自定制比较函数
		// @lpProcName: 表示名字指针，可以是加密什么的，需要在回调中自己处理
		// @comp: function第一参数为导出表节点函数名，第二参数为lpProcName，返回大小关系,小返回<0,大>0,等==0
		_Ret_maybenull_ void* GetProcAddress(_In_ _Notnull_ HMODULE module,
			_In_ _Notnull_ const void* lpProcName, const _STD function<int(LPCSTR, const void*)>& comp);

	}  // namespace Overwrite
}  // namespace Process
