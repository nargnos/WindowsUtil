#include "stdafx.h"
#include "ThreadPoolSimpleCallback.h"
#include "ThreadPoolApi.h"
bool Process::Thread::ThreadPoolSimpleCallback::Submit(PTP_CALLBACK_ENVIRON env)
{
	assert(GetFunc());
	Submitted();
	return Detail::WinApi::TrySubmitThreadpoolCallback(Callback, this, env);
}

void Process::Thread::ThreadPoolSimpleCallback::Callback(PTP_CALLBACK_INSTANCE instance, PVOID param)
{
	assert(param != nullptr);
	auto self = static_cast<ThreadPoolSimpleCallback*>(param);
	assert(self->GetFunc());
	CallbackInstance inst(instance);
	self->GetFunc()(inst);
}
