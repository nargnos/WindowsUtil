#include "stdafx.h"
#include "NtDllGetDllModulePolicy.h"
#include "FindLoadedModuleHandle.h"

HMODULE Process::LazyLoad::Detail::NtDllGetDllModulePolicy::GetDllModule(LPCWSTR dllName)
{
	return Process::EnvironmentBlock::FindLoadedModuleHandle(dllName);
}
