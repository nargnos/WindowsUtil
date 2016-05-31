#pragma once
#include "Common.h"
#include "LdrDataTable.h"
namespace Process
{
	namespace EnvironmentBlock
	{
		// 查找已经载入的dll
		HMODULE __stdcall FindLoadedModuleHandle(LPCWSTR name);
	}  // namespace EnvironmentBlock
}  // namespace Process
