#include "stdafx.h"
#include "FindLoadedModuleHandle.h"
#include "LdrDataTableEntryIterator.h"
#include "IteratorAdaptors.h"

namespace Process
{
	namespace EnvironmentBlock
	{
		HMODULE __stdcall FindLoadedModuleHandle(LPCWSTR name)
		{
			assert(name != NULL);
			LdrDataTable ldr(LdrDataTableModuleList::InLoadOrderModuleList);
			auto result = _STD find_if(ldr.begin(), ldr.end(), [name](LDR_DATA_TABLE_ENTRY_Ex& val)
			{
				auto moduleName = val.BaseDllName.Buffer;
				return moduleName != nullptr && _wcsicmp(name, moduleName) == 0;
			});
			if (result == ldr.end())
			{
				return nullptr;
			}
			return (HMODULE)result->DllBase;
		}
	}  // namespace EnvironmentBlock
	
}  // namespace Process
