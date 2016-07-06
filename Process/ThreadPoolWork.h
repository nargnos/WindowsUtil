#pragma once

#include "Common.h"
#include "CallbackBase.h"
#include "CallbackInstance.h"
namespace Process
{
	namespace Thread
	{
		// 延迟到提交时才创建，注意第一次提交时非线程安全，其它结构也一样
		class ThreadPoolWork :
			public Detail::CallbackBase<_STD function<void(CallbackInstance&, ThreadPoolWork&)>>
		{
		public:
			ThreadPoolWork(Func&& func);

			~ThreadPoolWork();
			void WaitForCallbacks(bool cancelPendingCallbacks = false);
			friend class ThreadPool;
		protected:
			bool Submit(PTP_CALLBACK_ENVIRON env);
			static void NTAPI Callback(PTP_CALLBACK_INSTANCE instance, PVOID param, PTP_WORK work);
			PTP_WORK work_;
		};
	}  // namespace Thread
}  // namespace Process