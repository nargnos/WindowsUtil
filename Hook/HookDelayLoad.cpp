#include "Common.h"
#include "HookDelayLoad.h"
#include <algorithm>
#include <PeImage\PeDecoder.h>
#include <Process\EnvironmentBlock.h>
#include <Process\WriteProcessMemory.h>
#include <Process\FindLoadedModuleHandle.h>
#include <Process\VirtualProtect.h>
using Process::EnvironmentBlock::PTEB_Ex;
using Process::EnvironmentBlock::PEB_Ex;
PVOID Hook::HookDelayLoad(HMODULE module, LPCSTR dllName, LPCSTR procName, PVOID hookFunc, OUT PVOID * unhookAddress)
{
	using namespace PeDecoder;

	if (dllName == nullptr || procName == nullptr || hookFunc == nullptr)
	{
		return nullptr;
	}
	if (module == NULL)
	{
		module = (HMODULE)NtCurrentPeb->ImageBaseAddress;
	}
	auto pe = PeImage::Create(module, true);
	if (!pe)
	{
		return nullptr;
	}
	auto delay = DelayImportDirectory::Create(pe);
	if (!delay)
	{
		return nullptr;
	}
	auto dlEnd = delay->end();
	// ÕÒdll
	auto dll = _STD find_if(delay->begin(), dlEnd, [dllName](auto& node)
	{
		return strcmp(node->GetName(), dllName) == 0;
	});
	if (dll == dlEnd)
	{
		return nullptr;
	}
	auto type = pe->GetImageType();
	PVOID writeAddress;
	PVOID result;
	auto thunkEnd = dll->end();
	auto func = PeDecoder::FindThunk(dll->begin(), thunkEnd, procName);
	if (func == thunkEnd)
	{
		return nullptr;
	}
	writeAddress = func->GetThunkPtr();
	result = func->GetFuncAddress();

	DWORD size = sizeof(PVOID);
	if (Process::Overwrite::WriteProcessMemory(NtCurrentProcess(), writeAddress, &hookFunc, size, NULL))
	{
		if (unhookAddress)
		{
			*unhookAddress = writeAddress;
		}
		return result;
	}
	return nullptr;
}
