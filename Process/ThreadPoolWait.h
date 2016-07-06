#pragma once
#include "Common.h"
#include "CallbackBase.h"
#include "CallbackInstance.h"
namespace Process
{
	namespace Thread
	{
		// msdn只写了两个
		enum class WaitResult:TP_WAIT_RESULT
		{
			WaitObject0 = WAIT_OBJECT_0,
			WaitTimeout = WAIT_TIMEOUT,
			WaitAbandoned0=WAIT_ABANDONED_0
		};
		class ThreadPoolWait :
			public Detail::CallbackBase<_STD function<void(CallbackInstance&, ThreadPoolWait&, WaitResult)>>
		{
		public:

			ThreadPoolWait(HANDLE waitHandle, PFILETIME timeout, Func&& func);
			void WaitForCallbacks(bool cancelPendingCallbacks = false);
			~ThreadPoolWait();
			friend class ThreadPool;
		protected:
			static VOID NTAPI Callback(
				PTP_CALLBACK_INSTANCE instance,
				PVOID                 param,
				PTP_WAIT              wait,
				TP_WAIT_RESULT        waitResult
			);
			bool Register(PTP_CALLBACK_ENVIRON env);
			PTP_WAIT wait_;
			HANDLE waitHandle_;
			PFILETIME timeout_;
		};
	}  // namespace Thread
}  // namespace Process


