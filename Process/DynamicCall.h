#pragma once
#include "DynamicCallBase.h"
#include "GetProcAddress.h"
#include "DefaultLazyLoadDecryptStrPolicy.h"
namespace Process
{
	namespace LazyLoad
	{
		namespace Detail
		{
			template<typename TFunc, typename TLoadDll, typename TDecryptStrPolicy = Detail::DefaultLazyLoadDecryptStrPolicyA>
			class DynamicCall :
				public Detail::GetFunctionType<TFunc, TLoadDll, TDecryptStrPolicy, TFunc>::type
			{
			public:
				using DynamicCallBase::DynamicCallBase;				
			};


		}  // namespace Detail

	}  // namespace LazyLoad
}  // namespace Process
