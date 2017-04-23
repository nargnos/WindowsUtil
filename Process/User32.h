#pragma once
#include "Common.h"
#include "LoadDllBase.h"
#include "DefaultGetDllModulePolicy.h"
#include "DynamicCall.h"
namespace Process
{
	namespace LazyLoad
	{


		namespace User32
		{
			namespace Detail
			{
				using Process::LazyLoad::Detail::DynamicCall;
				using Process::LazyLoad::Detail::LoadDllBase;
				using Process::LazyLoad::Detail::DefaultGetDllModulePolicy;
				class LoadUser32 :
					public LoadDllBase<DefaultGetDllModulePolicy>
				{
				public:
					friend const LoadUser32& Instance();
					~LoadUser32() = default;
					// ”√¿¥≤‚ ‘µƒ
					DynamicCall<int WINAPI(
						_In_opt_ HWND hWnd,
						_In_opt_ LPCSTR lpText,
						_In_opt_ LPCSTR lpCaption,
						_In_ UINT uType
					), TLoadDllBase> MessageBoxA;
				protected:
					LoadUser32();
				};
			}  // namespace Detail
			using User32::Detail::Instance;
		}  // namespace User32
	}  // namespace LazyLoad
}  // namespace Process
