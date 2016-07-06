#pragma once
#include "Common.h"
#include "CallbackBase.h"
#include "CallbackInstance.h"
namespace Process
{
	namespace Thread
	{
		class ThreadPoolSimpleCallback :
			public Detail::CallbackBase<_STD function<void(CallbackInstance&)>>
		{
		public:
			using CallbackBase::CallbackBase;

			friend class ThreadPool;
		protected:
			bool Submit(PTP_CALLBACK_ENVIRON env);
			static void NTAPI Callback(PTP_CALLBACK_INSTANCE instance, PVOID param);
		};
	}  // namespace Thread
}  // namespace Process