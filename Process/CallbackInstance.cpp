#include "stdafx.h"
#include "CallbackInstance.h"
#include "ThreadPoolApi.h"

Process::Thread::CallbackInstance::CallbackInstance(PTP_CALLBACK_INSTANCE instance) :
	instance_(instance)
{
}

bool Process::Thread::CallbackInstance::MayRunLong()
{
	assert(instance_);
	return  Detail::WinApi::CallbackMayRunLong(instance_) == TRUE;
}

PTP_CALLBACK_INSTANCE Process::Thread::CallbackInstance::GetInstance()
{
	return instance_;
}
