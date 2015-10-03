#pragma once
#include "WinApiDynamicCallDef.h"

namespace Process
{
	namespace LazyLoad
	{
		_LoadDll::_LoadDll(): dllName(NULL), dllModule(NULL), isInit(false)
		{
		}
		_LoadDll::_LoadDll(LPCWSTR dllName) :dllName(dllName), dllModule(NULL), isInit(false)
		{
		}
		_LoadDll::_LoadDll(HMODULE dllModule) : dllName(NULL), dllModule(dllModule), isInit(false)
		{
		}
		_LoadDll::_LoadDll(_LoadDll & obj)
		{
			this->dllModule = obj.dllModule;
			this->dllName = obj.dllName;
			this->isInit = obj.isInit;
		}
		_LoadDll::~_LoadDll()
		{
		}
		HMODULE _LoadDll::GetDllModule()
		{
			return dllModule;
		}
		void _LoadDll::FuncRegister()
		{
		}
		bool _LoadDll::Load()
		{
			
			if (dllModule)
			{
				return true;
			}
			if (!dllName)
			{
				return false;
			}
			if (!isInit)
			{
				isInit = true;
				FuncRegister();
			}
			dllModule = GetDll();
			return dllModule > 0;
		}
		HINSTANCE _LoadDll::GetDll()
		{
			return _LoadLibraryW(dllName);
		}


	}
}