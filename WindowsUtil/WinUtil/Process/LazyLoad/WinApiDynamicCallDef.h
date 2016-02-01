#pragma once
#include <Windows.h>
#include <WinBase.h>
#include <intrin.h>
#include <memory>
namespace Process
{
	namespace LazyLoad
	{
		FARPROC _GetProcAddress(HMODULE module, LPCSTR procName);
		HINSTANCE WINAPI _LoadLibraryW(LPCWSTR lpLibFileName);

		// 析构时不会unload dll
		class _LoadDll 
		{
			_LoadDll(const _LoadDll&) = delete;
			_LoadDll& operator = (const _LoadDll&) = delete;
		public:
			explicit _LoadDll(LPCWSTR dllName);
			explicit _LoadDll(HMODULE dllModule); 
			explicit _LoadDll(_LoadDll& obj);
			~_LoadDll();
			bool Load();
			HMODULE GetDllModule();
		protected:
			HMODULE dllModule;
			_LoadDll();
			LPCWSTR dllName;
			bool isInit;
			virtual void FuncRegister();
			virtual HINSTANCE GetDll();
		};

		template<typename T>
		class WinApiDynamicCall;
		// 只适用于_stdcall的函数
		template<typename Ret, typename... T>
		class WinApiDynamicCall<Ret WINAPI (T...)>
		{
		private:
			bool hasModule = false;
			WinApiDynamicCall(const WinApiDynamicCall&) = delete;
			WinApiDynamicCall& operator = (const WinApiDynamicCall&) = delete;
		protected:
			typedef Ret(WINAPI* Func)(T...);
			Func ptr = NULL;
			_LoadDll* dll=NULL;
			LPCSTR func=NULL;
			virtual Func GetAddress()
			{
				auto result = _GetProcAddress(dll->GetDllModule(), func);
				if (result)
				{
					return (Func)result;
				}
				return NULL;
			}

		public:
			WinApiDynamicCall() {}
			WinApiDynamicCall(_LoadDll* dllObject, LPCSTR funcName) :dll(dllObject), func(funcName) 
			{

			}

			WinApiDynamicCall(HINSTANCE dllModule, LPCSTR funcName) :
				func(funcName)
			{
				dll = new _LoadDll(dllModule);
				hasModule = true;
			}
			~WinApiDynamicCall()
			{
				if (hasModule && dll)
				{
					delete dll;
					dll = NULL;
					hasModule = false;
				}
			}
			Ret WINAPI operator()(T... args)
			{
				Load();
				assert(ptr);
				return ptr(std::forward<T>(args)...);
			}
			operator bool()
			{
				return Load();
			}
			bool Load()
			{
				if (ptr)
				{
					return true;
				}
				else
				{
					if (!dll || !dll->Load() || !func)
					{
						return false;
					}
					ptr = GetAddress();
				}
				return ptr != NULL;
			}
			HINSTANCE GetDllModule()
			{
				return dll->GetDllModule();
			}
			Func GetFuncAddress()
			{
				return ptr;
			}
		};

	}
}