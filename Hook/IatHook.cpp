#include "IatHook.h"
#include <algorithm>
#include <PeImage\PeDecoder.h>
#include <Process\EnvironmentBlock.h>
#include <Process\WriteProcessMemory.h>
#include <Process\LoadLibrary.h>
#include <Process\FindLoadedModuleHandle.h>
#include <Process\VirtualProtect.h>

using Process::EnvironmentBlock::PTEB_Ex;
using Process::EnvironmentBlock::PEB_Ex;
using namespace PeDecoder;

namespace Hook
{
	IatHook::IatHook(HMODULE module) :
		module_(PeImage::Create(module == NULL ? (HMODULE)NtCurrentPeb->ImageBaseAddress : module, true))
	{
		if (!module_)
		{
			return;
		}
		importDirectory_ = ImportDirectory::Create<_STD unique_ptr>(module_);
		canHook_ = (bool)importDirectory_;
		
	}
	IatHook::FunctionBackup IatHook::Find(const std::string & dllName, const std::string & procName)const
	{
		FunctionBackup result{ nullptr,nullptr };
		auto bak = backup_.find(dllName);
		if (bak != backup_.end())
		{
			auto funcBak = bak->second.find(procName);
			if (funcBak != bak->second.end())
			{
				result = funcBak->second;
			}
		}
		return result;
	}
	bool IatHook::CheckFunctionBackup(const FunctionBackup & val)
	{
		return val.first != nullptr && val.second != nullptr;;
	}
	IatHook::~IatHook()
	{
	}
	bool IatHook::CanIatHook() const
	{
		return canHook_;
	}
	IatHook::operator bool() const
	{
		return CanIatHook();
	}
	IatHook::DllNameProxy IatHook::operator[](const std::string & dllName)
	{
		return DllNameProxy(*this, dllName);
	}
	_STD shared_ptr<IatHook> IatHook::Instance(const _STD wstring& moduleName)
	{
		_STD shared_ptr<IatHook> result;
		auto module = Process::Overwrite::LoadLibraryW(moduleName.c_str());
		if (module != NULL)
		{
			result = Instance(module);
		}
		return result;
	}
	_STD shared_ptr<IatHook> IatHook::Instance(HMODULE module)
	{
		static _STD unordered_map<HMODULE, _STD shared_ptr<IatHook>> iatHooks;
		_STD shared_ptr<IatHook> result;
		auto ptr = iatHooks.find(module);
		if (ptr == iatHooks.end())
		{
			result = _STD shared_ptr<IatHook>(new IatHook(module));
			if (result->CanIatHook())
			{
				iatHooks.insert({ module,result });
			}
		}
		else
		{
			result = ptr->second;
		}
		return result;
	}
	bool IatHook::IsHooked(const _STD string& dllName, const _STD string& procName)
	{
		auto func = Find(dllName, procName);
		return CheckFunctionBackup(func);
	}
	IatHook::FuncPtr IatHook::Hook(const _STD string & dllName, const _STD string & procName, LPCVOID hookFunc)
	{
		if (hookFunc == nullptr)
		{
			return nullptr;
		}
		if (!CanIatHook())
		{
			return nullptr;
		}
		if (IsHooked(dllName, procName))
		{
			return nullptr;
		}

		auto endImp = importDirectory_->end();
		auto dllImp = _STD find_if(importDirectory_->begin(), endImp, [dllName_ = dllName.c_str()](auto& node)
		{
			return _stricmp(node->GetName(), dllName_) == 0;
		});
		if (dllImp == endImp)
		{
			return nullptr;
		}

		auto thunkEnd = dllImp->end();
		auto func = PeDecoder::FindThunk(dllImp->begin(), thunkEnd, procName.c_str());
		if (func == thunkEnd)
		{
			return nullptr;
		}
		PVOID writeAddress = func->GetThunkPtr();
		PVOID oldFunc = func->GetFuncAddress();

		// 原本需要设置区块可读写性, 这里使用替代的写入函数, 里面包含了这个设置
		if (!Process::Overwrite::WriteProcessMemory(NtCurrentProcess(), writeAddress, &hookFunc, sizeof(PVOID), NULL))
		{
			return nullptr;
		}
		backup_[dllName][procName] = { writeAddress, oldFunc };
		return oldFunc;
	}
	bool IatHook::UnHook(const std::string & dllName, const std::string & procName)
	{
		auto func = Find(dllName, procName);
		if (!CheckFunctionBackup(func))
		{
			return false;
		}
		auto result = Process::Overwrite::WriteProcessMemory(
			NtCurrentProcess(),
			func.first,
			&func.second,
			sizeof(PVOID),
			NULL);
		if (result)
		{
			backup_[dllName].erase(procName);
		}
		return result;
	}
	IatHook::FuncPtr IatHook::GetOldFunction(const std::string & dllName, const std::string & procName)const
	{
		return Find(dllName, procName).second;
	}
	IatHook::DllNameProxy::DllNameProxy(IatHook& iatHook, const _STD string & dllName) :
		dllName_(dllName),
		iatHook_(iatHook)
	{
	}

	IatHook::ProcNameProxy IatHook::DllNameProxy::operator[](const std::string & procName)
	{
		return ProcNameProxy(iatHook_, dllName_, procName);
	}

	IatHook::ProcNameProxy::ProcNameProxy(IatHook & iatHook, const std::string & dllName, const std::string & procName) :
		dllName_(dllName),
		procName_(procName),
		iatHook_(iatHook)
	{
	}

	IatHook::FuncPtr IatHook::ProcNameProxy::operator=(FuncPtr func)
	{
		return iatHook_.Hook(dllName_, procName_, func);
	}

	IatHook::ProcNameProxy::operator bool() const
	{
		return iatHook_.IsHooked(dllName_, procName_);
	}

	IatHook::FuncPtr IatHook::ProcNameProxy::operator&() const
	{
		return iatHook_.GetOldFunction(dllName_, procName_);
	}

	bool IatHook::ProcNameProxy::UnHook()
	{
		return iatHook_.UnHook(dllName_, procName_);
	}


}  // namespace Hook
