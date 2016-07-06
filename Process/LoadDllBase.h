#pragma once
#include "Common.h"
#include "DefaultLazyLoadDecryptStrPolicy.h"
#include "SpinLock.h"
namespace Process
{
	namespace LazyLoad
	{
		namespace Detail
		{
			// 内部使用mutex会引入其它dll，有空再重写mutex部分
			template<typename TGetDllModulePolicy, typename TDecryptStrPolicy = DefaultLazyLoadDecryptStrPolicyW>
			class LoadDllBase
			{
			public:
				typedef TGetDllModulePolicy TGetDllModulePolicy;
				typedef TDecryptStrPolicy TDecryptStrPolicy;
				typedef LoadDllBase TLoadDllBase;
				using EncryptStr = typename TDecryptStrPolicy::EncryptStr;
				using DecryptStr = typename TDecryptStrPolicy::DecryptStr;
				
				DecryptStr GetDllName()
				{
					return TDecryptStrPolicy::Decrypt(dllName_);
				}
				HMODULE GetDllModule()
				{
					if (dllModule_ == NULL)
					{
						_STD lock_guard<SpinLock> lock(lock_);
						if (dllModule_ == NULL)
						{
							auto dllName = GetDllName();
							dllModule_ = TGetDllModulePolicy::GetDllModule(TDecryptStrPolicy::GetStr(dllName));
						}
					}
					return dllModule_;
				}

			protected:
				explicit LoadDllBase(EncryptStr dllName) :
					dllName_(dllName),
					dllModule_(NULL)
				{
					
				}
				LoadDllBase(const LoadDllBase&) = delete;
				LoadDllBase& operator=(const LoadDllBase&) = delete;
				HMODULE dllModule_;
				EncryptStr dllName_;
				SpinLock lock_;
			};
		}  // namespace Detail

	}  // namespace LazyLoad
}  // namespace Process
