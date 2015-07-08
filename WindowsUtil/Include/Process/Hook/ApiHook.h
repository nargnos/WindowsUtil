#pragma once
#include "..\LazyLoad\LazyLoadSystemApi.h"
namespace Process
{
	namespace Hook
	{
		// hook后会继续调用原先函数
		bool HookApi(LPCWSTR dllName, LPCSTR procName, LPCVOID hookFunc);
	}
}