#include "stdafx.h"
#include "ThreadPoolWait.h"
#include "ThreadPoolApi.h"
Process::Thread::ThreadPoolWait::ThreadPoolWait(HANDLE waitHandle, PFILETIME timeout, Func && func) :
	waitHandle_(waitHandle),
	CallbackBase(_STD move(func)),
	wait_(nullptr),
	timeout_(timeout)
{
}
void Process::Thread::ThreadPoolWait::WaitForCallbacks(bool cancelPendingCallbacks)
{
	assert(IsSubmitted());
	Detail::WinApi::WaitForThreadpoolWaitCallbacks(wait_, cancelPendingCallbacks);
}
Process::Thread::ThreadPoolWait::~ThreadPoolWait()
{
	if (wait_ != nullptr)
	{
		Detail::WinApi::SetThreadpoolWait(wait_, NULL, NULL);
		Detail::WinApi::CloseThreadpoolWait(wait_);
		wait_ = nullptr;
	}
}
VOID Process::Thread::ThreadPoolWait::Callback(PTP_CALLBACK_INSTANCE instance, PVOID param, PTP_WAIT wait, TP_WAIT_RESULT waitResult)
{
	assert(param != nullptr);
	auto self = static_cast<ThreadPoolWait*>(param);
	assert(self->GetFunc());

	CallbackInstance inst(instance);
	self->GetFunc()(inst, *self, static_cast<WaitResult>(waitResult));
}
bool Process::Thread::ThreadPoolWait::Register(PTP_CALLBACK_ENVIRON env)
{
	assert(GetFunc());
	if (wait_ == nullptr)
	{
		wait_ = Detail::WinApi::CreateThreadpoolWait(Callback, this, env);
		if (wait_ == nullptr)
		{
			return false;
		}
	}
	Detail::WinApi::SetThreadpoolWait(wait_, waitHandle_, timeout_);

	Submitted();
	return true;
}
