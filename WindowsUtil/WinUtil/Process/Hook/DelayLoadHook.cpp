#include "DelayLoadHook.h"
namespace Process
{
	namespace Hook
	{
		using EnvironmentBlock::PTEB_Ex;
		using EnvironmentBlock::PEB_Ex;
		PVOID HookDelayLoad(LPCSTR dllName, LPCSTR procName, PVOID hookFunc, OUT PVOID* oldFuncAddr)
		{
			if (!hookFunc)
			{
				return NULL;
			}
			auto currentProcessBaseAddress = NtCurrentPeb->ImageBaseAddress;
			PE::PeDecoder pe;
			if (!pe.LoadPEImage(currentProcessBaseAddress, true))
			{
				return NULL;
			}
			auto result = (PVOID*)PE::GetDelayLoadAddressTableAddress(pe, dllName, procName);
			if (result)
			{
				if (oldFuncAddr)
				{
					*oldFuncAddr = (PVOID)*result;
				}
				*result = hookFunc;
			}
			return result;
		}
	}
}