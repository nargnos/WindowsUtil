#include "Common.h"
#include "HookIat.h"
#include <algorithm>
#include <PeImage\PeDecoder.h>
#include <Process\EnvironmentBlock.h>
#include <Process\WriteProcessMemory.h>
#include <Process\FindLoadedModuleHandle.h>
#include <Process\VirtualProtect.h>
using Process::EnvironmentBlock::PTEB_Ex;
using Process::EnvironmentBlock::PEB_Ex;

PVOID Hook::HookIat(HMODULE module, LPCSTR dllName, LPCSTR procName, LPCVOID hookFunc, OUT PVOID * unhookAddress)
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
	PeImage pe(module, true);
	if (!pe.IsPe() && !pe.HasDirectory(DataDirectoryEntryType::Import))
	{
		return nullptr;
	}

	ImportDirectory imp(pe);
	assert(imp);
	auto endImp = imp.end();
	auto dllImp = _STD find_if(imp.begin(), endImp, [dllName](auto& node)
	{
		return _stricmp(node->GetName(), dllName) == 0;
	});
	if (dllImp == endImp)
	{
		return nullptr;
	}
	PVOID writeAddress = nullptr;
	PVOID result = nullptr;

	auto thunkEnd = dllImp->end();
	auto func = PeDecoder::FindThunk(dllImp->begin(), thunkEnd, procName);
	if (func == thunkEnd)
	{
		return nullptr;
	}
	result = func->GetFuncAddress();
	writeAddress = func->GetThunkPtr();
	DWORD size = sizeof(PVOID);
	// 原本需要设置区块可读写性, 这里使用替代的写入函数, 里面包含了这个设置
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

bool Hook::UnHookIat(PVOID unhookAddress, PVOID oldFunctionAddress)
{
	DWORD size = sizeof(PVOID);
	return Process::Overwrite::WriteProcessMemory(
		NtCurrentProcess(),
		unhookAddress,
		&oldFunctionAddress,
		size,
		NULL);
}
