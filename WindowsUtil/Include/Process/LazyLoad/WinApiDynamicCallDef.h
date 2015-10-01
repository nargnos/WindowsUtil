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
		public:
			_LoadDll(LPCWSTR dllName);
			_LoadDll(HMODULE DllModule); 
			_LoadDll(_LoadDll& obj);
			~_LoadDll();
			bool Load();
			virtual HINSTANCE GetDll();
			// 需要在模板类使用,所以设置public, 使用时不要改数值
			HMODULE DllModule;
		protected:
			_LoadDll();
			LPCWSTR dllName;
			bool isInit;
			virtual void FuncRegister();
		};

		template<typename T>
		class WinApiDynamicCall;

		template<typename Ret, typename... T>
		class WinApiDynamicCall<Ret WINAPI (T...)>
		{
		private:
			bool hasModule = false;
		protected:
			typedef Ret(WINAPI* Func)(T...);
			Func ptr = NULL;
			_LoadDll* dll=NULL;
			LPCSTR func;
			virtual Func GetAddress()
			{
				auto result = _GetProcAddress(dll->DllModule, func);
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
					if (!dll->Load() || !func)
					{
						return false;
					}
					ptr = GetAddress();
				}
				return ptr != NULL;
			}
			HINSTANCE GetDllModule()
			{
				return dll->DllModule;
			}
			Func GetFuncAddress()
			{
				return ptr;
			}
		};

	}
}