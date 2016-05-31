#pragma once
#include "Common.h"
#include "LoadDllBase.h"
#include "DefaultGetDllModulePolicy.h"
#include "DynamicCall.h"
namespace Process
{
	namespace LazyLoad
	{
		using Process::LazyLoad::Detail::DynamicCall;
		using Process::LazyLoad::Detail::LoadDllBase;
		using Process::LazyLoad::Detail::DefaultGetDllModulePolicy;
		// ”√¿¥≤‚ ‘µƒ

		class User32
		{
		public:
			class LoadUser32;
			static const LoadUser32& Instance();
		private:
			User32() = delete;
			~User32() = delete;
			static LoadUser32 instance_;
		};

		class User32::LoadUser32 :
			public LoadDllBase<DefaultGetDllModulePolicy>
		{
		public:
			friend class User32;
			~LoadUser32() = default;
			DynamicCall<int WINAPI(
				_In_opt_ HWND hWnd,
				_In_opt_ LPCSTR lpText,
				_In_opt_ LPCSTR lpCaption,
				_In_ UINT uType
			),TLoadDllBase> MessageBoxA;
		protected:
			LoadUser32();

		};

	}  // namespace LazyLoad
}  // namespace Process
