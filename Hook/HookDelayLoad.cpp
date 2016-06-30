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
	if (dllName == nullptr || procName == nullptr || hookFunc == nullptr)
	{
		return NULL;
	}
	if (module == NULL)
	{
		module = (HMODULE)NtCurrentPeb->ImageBaseAddress;
	}
	PeDecoder::PeImage pe(module, true);
	if (!pe.IsPe())
	{
		return NULL;
	}
	auto& delay = pe.GetDelayImportDirectory();
	auto dlEnd = delay->end();
	// ÕÒdll
	auto dll = _STD find_if(delay->begin(), dlEnd, [dllName](PeDecoder::DelayImportDescriptor& node)
	{
		return strcmp(node.GetName(), dllName) == 0;
	});
	if (dll == dlEnd)
	{
		return NULL;
	}
	auto type = pe.GetImageType();
	PVOID writeAddress;
	PVOID result;
#ifdef WIN32
	auto& thunk = dll->GetThunk32();
	auto thunkEnd = thunk.end();
	auto func = PeDecoder::FindThunk<PeDecoder::ImportThunkIterator32, PeDecoder::ImportThunkIteratorNode32>(
		thunk.begin(), thunkEnd, procName);
	if (func == thunkEnd)
	{
		return NULL;
	}
	writeAddress = func->GetAddressThunk();
	result = func->GetFuncAddress();
#else
	auto& thunk = dll->GetThunk32();
	auto thunkEnd = thunk.end();
	auto func = PeDecoder::FindThunk<PeDecoder::ImportThunkIterator32, PeDecoder::ImportThunkIteratorNode32>(
		thunk.begin(), thunkEnd, procName);
	if (func == thunkEnd)
	{
		return NULL;
	}
	writeAddress = func->GetAddressThunk();
	result = func->GetFuncAddress();
#endif // WIN32

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
