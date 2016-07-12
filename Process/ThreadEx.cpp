#include "stdafx.h"
#include "ThreadEx.h"

DWORD Process::Thread::this_thread::Suspend()
{
	return SuspendThread(GetCurrentThread());
}

Process::Thread::ThreadPriority Process::Thread::this_thread::GetPriority()
{
	return static_cast<ThreadPriority>(GetThreadPriority(GetCurrentThread()));
}

bool Process::Thread::this_thread::SetPriority(ThreadPriority priority)
{
	return SetThreadPriority(GetCurrentThread(), static_cast<int>(priority)) != 0;
}

DWORD_PTR Process::Thread::this_thread::SetAffinityMask(DWORD_PTR mask)
{
	return SetThreadAffinityMask(GetCurrentThread(), mask);
}

std::pair<bool, CONTEXT> Process::Thread::this_thread::GetContext(ContextFlag flag)
{
	_STD pair<bool, CONTEXT> result{ false,{ 0 } };
	result.second.ContextFlags = static_cast<DWORD>(flag);
	result.first = GetThreadContext(GetCurrentThread(), &result.second) != 0;

	return result;
}

bool Process::Thread::this_thread::SetContext(CONTEXT & context)
{
	return SetThreadContext(GetCurrentThread(), &context) != 0;
}
