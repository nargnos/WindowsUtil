#include "stdafx.h"
#include "DefaultGetDllModulePolicy.h"
#include "LoadLibrary.h"
HMODULE Process::LazyLoad::Detail::DefaultGetDllModulePolicy::GetDllModule(LPCWSTR dllName)
{
	return Process::Overwrite::LoadLibraryW(dllName);
}
