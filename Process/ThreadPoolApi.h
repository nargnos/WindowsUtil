#pragma once
#include "Common.h"

namespace Process
{
	namespace Thread
	{
		namespace Detail
		{
			namespace WinApi
			{
				using ::BindIoCompletionCallback;
				using ::CallbackMayRunLong;
				using ::CancelThreadpoolIo;
				using ::ChangeTimerQueueTimer;
				using ::CloseThreadpool;
				using ::CloseThreadpoolCleanupGroup;
				using ::CloseThreadpoolCleanupGroupMembers;
				using ::CloseThreadpoolIo;
				using ::CloseThreadpoolTimer;
				using ::CloseThreadpoolWait;
				using ::CloseThreadpoolWork;
				using ::CreateThreadpool;
				using ::CreateThreadpoolCleanupGroup;
				using ::CreateThreadpoolIo;
				using ::CreateThreadpoolTimer;
				using ::CreateThreadpoolWait;
				using ::CreateThreadpoolWork;
				using ::CreateTimerQueue;
				using ::CreateTimerQueueTimer;
				using ::DeleteTimerQueueEx;
				using ::DeleteTimerQueueTimer;
				using ::DestroyThreadpoolEnvironment;
				using ::DisassociateCurrentThreadFromCallback;
				using ::FreeLibraryWhenCallbackReturns;
				using ::InitializeThreadpoolEnvironment;
				using ::IsThreadpoolTimerSet;
				using ::LeaveCriticalSectionWhenCallbackReturns;
				using ::QueueUserWorkItem;
				using ::RegisterWaitForSingleObject;
				using ::ReleaseMutexWhenCallbackReturns;
				using ::ReleaseSemaphoreWhenCallbackReturns;
				using ::SetEventWhenCallbackReturns;
				using ::SetThreadpoolCallbackCleanupGroup;
				using ::SetThreadpoolCallbackLibrary;
				using ::SetThreadpoolCallbackPool;
				using ::SetThreadpoolCallbackPriority;
				using ::SetThreadpoolCallbackRunsLong;
				using ::SetThreadpoolThreadMaximum;
				using ::SetThreadpoolThreadMinimum;
				using ::SetThreadpoolTimer;
				using ::SetThreadpoolWait;
				using ::StartThreadpoolIo;
				using ::SubmitThreadpoolWork;
				using ::TrySubmitThreadpoolCallback;
				using ::UnregisterWaitEx;
				using ::WaitForThreadpoolIoCallbacks;
				using ::WaitForThreadpoolTimerCallbacks;
				using ::WaitForThreadpoolWaitCallbacks;
				using ::WaitForThreadpoolWorkCallbacks;
			}  // namespace WinApi
		}  // namespace Detail
	}  // namespace Thread
}  // namespace Process