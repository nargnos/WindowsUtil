#include "Common.h"
#include "HookEat.h"
#include <algorithm>
#include <PeImage\PeDecoder.h>
#include <Process\EnvironmentBlock.h>
#include <Process\WriteProcessMemory.h>
#include <Process\FindLoadedModuleHandle.h>
#include <Process\VirtualProtect.h>
PVOID Hook::HookEat(HMODULE module, LPCSTR procName, LPCVOID hookFunc, OUT PDWORD* oldFuncRva)
{
	using namespace PeDecoder;
	if (module == nullptr || procName == nullptr || hookFunc == nullptr)
	{
		return nullptr;
	}
	auto dll = PeImage::Create(module, true);

	if (!dll)
	{
		return nullptr;
	}
	auto exp = ExportDirectory::Create(dll);
	if (!exp)
	{
		return nullptr;
	}

	auto end = exp->end();
	auto proc = _STD lower_bound(exp->begin(), end, procName, []
	(auto& node, LPCSTR val)
	{
		return strcmp(node->NamePtr(), val) < 0;
	});
	if (end == proc || strcmp(proc->NamePtr(), procName) != 0)
	{
		return nullptr;
	}
	PVOID result = proc->FuncPtr();
	PDWORD rvaPtr = proc->FuncRva();
	// dll base + rva = funcRealAddress 可推导出
	// base + setRva = hookAddress

	DWORD setRva;
	auto imageType = dll->GetImageType();
#ifdef WIN32
	assert(imageType == PeDecoder::ImageType::PE32);
	setRva = (DWORD)hookFunc - (DWORD)module;
#else
	assert(imageType == PeDecoder::ImageType::PE64);
	auto tmpDta = (DWORD64)hookFunc - (DWORD64)module;
	if (tmpDta > 0 && tmpDta < LONG_MAX)
	{
		setRva = (DWORD)tmpDta;
	}
	else
	{
		// NOTICE: 因为导出表存储rva，如果超界就不能设置了
		return nullptr;
	}
#endif // WIN32

	if (Process::Overwrite::WriteProcessMemory(NtCurrentProcess(), rvaPtr, &setRva, sizeof(DWORD), NULL))
	{
		if (oldFuncRva)
		{
			*oldFuncRva = rvaPtr;
		}
		return result;
	}
	return nullptr;
}
