#pragma once
#include "Common.h"
namespace Process
{
	namespace Thread
	{
			class CallbackInstance
			{
			public:
				CallbackInstance(PTP_CALLBACK_INSTANCE instance);

				//SetEventWhenCallbackReturns
				//ReleaseSemaphoreWhenCallbackReturns
				//LeaveCriticalSectionWhenCallbackReturns
				//ReleaseMutexWhenCallbackReturns
				//FreeLibraryWhenCallbackReturns
				//CallbackMayRunLong
				//DisassociateCurrentThreadFromCallback
				bool MayRunLong();
				PTP_CALLBACK_INSTANCE GetInstance();
				~CallbackInstance() = default;

			protected:
				PTP_CALLBACK_INSTANCE instance_;
				_STD once_flag flag_;
			};
	}  // namespace Thread
}  // namespace Process