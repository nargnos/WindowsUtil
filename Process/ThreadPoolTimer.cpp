#include "stdafx.h"
#include "ThreadPoolTimer.h"
#include "ThreadPoolApi.h"
Process::Thread::ThreadPoolTimer::ThreadPoolTimer(PFILETIME pftDueTime, DWORD msPeriod, DWORD msWindowLength, Func && func) :
	CallbackBase(_STD move(func)),
	timer_(nullptr),
	msPeriod_(msPeriod),
	msWindowLength_(msWindowLength),
	pftDueTime_(pftDueTime)
{
}

Process::Thread::ThreadPoolTimer::~ThreadPoolTimer()
{
	if (timer_ != nullptr)
	{
		pftDueTime_ = NULL;
		msPeriod_ = 0;
		Detail::WinApi::SetThreadpoolTimer(timer_, pftDueTime_, msPeriod_, msWindowLength_);
		
		Detail::WinApi::CloseThreadpoolTimer(timer_);
		timer_ = nullptr;
	}
}

void Process::Thread::ThreadPoolTimer::WaitForCallbacks(bool cancelPendingCallbacks)
{
	assert(IsSubmitted());
	Detail::WinApi::WaitForThreadpoolTimerCallbacks(timer_, cancelPendingCallbacks);
}

bool Process::Thread::ThreadPoolTimer::IsThreadpoolTimerSet()
{
	assert(timer_ != nullptr);
	return Detail::WinApi::IsThreadpoolTimerSet(timer_) == TRUE;
}

bool Process::Thread::ThreadPoolTimer::Register(PTP_CALLBACK_ENVIRON env)
{
	assert(GetFunc());
	if (timer_ == nullptr)
	{
		timer_ = Detail::WinApi::CreateThreadpoolTimer(Callback, this, env);
		if (timer_ == nullptr)
		{
			return false;
		}
	}
	Detail::WinApi::SetThreadpoolTimer(timer_, pftDueTime_, msPeriod_, msWindowLength_);

	Submitted();
	return true;
}

void NTAPI Process::Thread::ThreadPoolTimer::Callback(PTP_CALLBACK_INSTANCE instance, PVOID param, PTP_TIMER timer)
{
	assert(param != nullptr);
	auto self = static_cast<ThreadPoolTimer*>(param);
	assert(self->GetFunc());

	CallbackInstance inst(instance);
	self->GetFunc()(inst, *self);
}
