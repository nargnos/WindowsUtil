#include "stdafx.h"
#include "ThreadPool.h"
#include "ThreadPoolApi.h"
bool Process::Thread::ThreadPool::SubmitCallback(_STD function<void(CallbackInstance&)>&& func)
{
	auto funcPtr = new _STD function<void(CallbackInstance&)>(_STD move(func));
	assert(funcPtr);
	auto result = Detail::WinApi::TrySubmitThreadpoolCallback(Callback, funcPtr, GetEnviron());
	if (!result)
	{
		delete funcPtr;
	}
	return result;
}

void Process::Thread::ThreadPool::SetEnviron(PTP_CALLBACK_ENVIRON env)
{
	environ_ = env;
}

PTP_CALLBACK_ENVIRON Process::Thread::ThreadPool::GetEnviron()
{
	return environ_;
}
void Process::Thread::ThreadPool::Callback(PTP_CALLBACK_INSTANCE instance, PVOID param)
{
	assert(param != nullptr);
	std::function<void(CallbackInstance&)> func;
	auto funcPtr = static_cast<std::function<void(CallbackInstance&)>*>(param);
	// 不用try/cacth，防止接下来运行的东西出异常内存泄露，先析构了再说
	func.swap(*funcPtr);	
	delete funcPtr;
	CallbackInstance inst(instance);
	func(inst);
}
PTP_CALLBACK_ENVIRON Process::Thread::ThreadPool::environ_ = nullptr;