#pragma once
#include "..\LazyLoad\LazyLoadSystemApi.h"
#include "..\..\PE\Import\Import.h"
#include "..\..\PE\PeDecoder.h"
#include "..\..\PE\DelayImport\DelayImport.h"
namespace Process
{
	namespace Hook
	{
		// 不支持序数,成功会返回延迟导入表函数指针Table的地址
		PVOID HookDelayLoad(LPCSTR dllName, LPCSTR procName, PVOID hookFunc, OUT PVOID* oldFuncAddr = NULL);
	}
}