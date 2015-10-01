#pragma once
#include "WinApiDynamicCallDef.h"

namespace Process
{
	namespace LazyLoad
	{
		_LoadDll::_LoadDll(): isInit(false)
		{
		}
		_LoadDll::_LoadDll(LPCWSTR dllName) :dllName(dllName), isInit(false)
		{
		}
		_LoadDll::_LoadDll(HMODULE DllModule) : DllModule(DllModule), isInit(false)
		{
		}
		_LoadDll::_LoadDll(_LoadDll & obj)
		{
			this->DllModule = obj.DllModule;
			this->dllName = obj.dllName;
			this->isInit = obj.isInit;
		}
		_LoadDll::~_LoadDll()
		{
		}
		void _LoadDll::FuncRegister()
		{
		}
		bool _LoadDll::Load()
		{

			if (DllModule)
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
			DllModule = GetDll();
			return DllModule > 0;
		}
		HINSTANCE _LoadDll::GetDll()
		{
			return _LoadLibraryW(dllName);
		}


	}
}