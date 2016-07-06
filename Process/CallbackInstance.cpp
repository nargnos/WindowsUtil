#include "stdafx.h"
#include "CallbackInstance.h"
#include "ThreadPoolApi.h"

Process::Thread::CallbackInstance::CallbackInstance(PTP_CALLBACK_INSTANCE instance) :
	instance_(instance)
{
}

bool Process::Thread::CallbackInstance::MayRunLong()
{
	bool result = false;
	_STD call_once(flag_, [&result](PTP_CALLBACK_INSTANCE instance)
	{
		result = Detail::WinApi::CallbackMayRunLong(instance);
	}, instance_);
	return result;
}

PTP_CALLBACK_INSTANCE Process::Thread::CallbackInstance::GetInstance()
{
	return instance_;
}
