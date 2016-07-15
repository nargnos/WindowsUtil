#include "stdafx.h"
#include "ThreadPool.h"
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
	
	auto funcPtr = static_cast<std::function<void(CallbackInstance&)>*>(param);
	// 不用try/cacth，防止接下来运行的东西出异常内存泄露，先析构了再说
	std::function<void(CallbackInstance&)> func(_STD move(*funcPtr));

	delete funcPtr;
	CallbackInstance inst(instance);
	func(inst);
}
PTP_CALLBACK_ENVIRON Process::Thread::ThreadPool::environ_ = nullptr;