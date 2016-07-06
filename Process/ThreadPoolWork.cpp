#include "stdafx.h"
#include "ThreadPoolWork.h"
#include "ThreadPoolApi.h"
Process::Thread::ThreadPoolWork::ThreadPoolWork(Func && func) :
	work_(nullptr),
	CallbackBase(_STD move(func))
{
}

Process::Thread::ThreadPoolWork::~ThreadPoolWork()
{
	if (IsSubmitted())
	{
		WaitForCallbacks(true);
		Detail::WinApi::CloseThreadpoolWork(work_);
		work_ = nullptr;
	}
}

void Process::Thread::ThreadPoolWork::WaitForCallbacks(bool cancelPendingCallbacks)
{
	assert(IsSubmitted());
	Detail::WinApi::WaitForThreadpoolWorkCallbacks(work_, cancelPendingCallbacks);

}

bool Process::Thread::ThreadPoolWork::Submit(PTP_CALLBACK_ENVIRON env)
{
	assert(GetFunc());
	if (work_ == nullptr)
	{
		work_ = Detail::WinApi::CreateThreadpoolWork(Callback, this, env);
		if (work_ == nullptr)
		{
			return false;
		}
	}


	Detail::WinApi::SubmitThreadpoolWork(work_);
	Submitted();
	return true;
}

void Process::Thread::ThreadPoolWork::Callback(PTP_CALLBACK_INSTANCE instance, PVOID param, PTP_WORK work)
{
	assert(param != nullptr);
	auto self = static_cast<ThreadPoolWork*>(param);
	assert(self->GetFunc());

	CallbackInstance inst(instance);
	self->GetFunc()(inst, *self);
}
