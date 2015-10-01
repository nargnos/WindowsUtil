#pragma once
#include <Windows.h>
#include <WinBase.h>
#include <intrin.h>
#include <memory>
namespace Process
{
	namespace LazyLoad
	{
		using std::shared_ptr;
		using std::weak_ptr;
		FARPROC _GetProcAddress(HMODULE module, LPCSTR procName);
		HINSTANCE WINAPI _LoadLibraryW(LPCWSTR lpLibFileName);

		class _LoadDll
		{
		public:
			_LoadDll(LPCWSTR dllName) :dllName(dllName)
			{
			}
			_LoadDll(HMODULE DllModule) :DllModule(DllModule)
			{
			}
			_LoadDll(_LoadDll& obj)
			{
				this->DllModule = obj.DllModule;
				this->dllName = obj.dllName;
			}
			~_LoadDll()
			{
			}
			bool Load()
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
				return DllModule>0;
			}
			virtual HINSTANCE GetDll()
			{
				return _LoadLibraryW(dllName);
			}
			// 需要在模板类使用,所以设置public, 使用时不要改数值
			HMODULE DllModule;
		protected:
			LPCWSTR dllName;
			bool isInit = false;
			_LoadDll() {}
			virtual void FuncRegister() {};
		};

		template<typename T>
		class WinApiDynamicCall
		{};

		template<typename Ret, typename... T>
		class WinApiDynamicCall<Ret WINAPI (T...)>
		{
		protected:
			typedef Ret(WINAPI* Func)(T...);
			Func ptr = NULL;
			_LoadDll* dll;
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
				dll = std::make_shared<_LoadDll>(dllModule);
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