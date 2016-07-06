#pragma once
#include "Common.h"
#include "CallbackBase.h"
#include "CallbackInstance.h"
namespace Process
{
	namespace Thread
	{
		class ThreadPoolTimer :
			public Detail::CallbackBase<_STD function<void(CallbackInstance&, ThreadPoolTimer&)>>
		{
		public:

			ThreadPoolTimer(PFILETIME pftDueTime, DWORD msPeriod, DWORD msWindowLength, Func&& func);

			~ThreadPoolTimer();
			void WaitForCallbacks(bool cancelPendingCallbacks = false);
			bool IsThreadpoolTimerSet();
			friend class ThreadPool;
		protected:
			bool Register(PTP_CALLBACK_ENVIRON env);
			static void NTAPI Callback(
				PTP_CALLBACK_INSTANCE instance,
				PVOID                 param,
				PTP_TIMER             timer);
			
			DWORD msPeriod_;
			DWORD msWindowLength_;
			PTP_TIMER timer_;
			PFILETIME pftDueTime_;

		};
	}  // namespace Thread
}  // namespace Process


