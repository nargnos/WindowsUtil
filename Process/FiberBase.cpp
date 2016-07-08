#include "stdafx.h"
#include "FiberBase.h"

void Process::Fiber::SetFiberData(void * ptr)
{
	auto data = (PVOID *)::GetCurrentFiber();
	*data = ptr;
}

void Process::Fiber::Detail::FiberDeletor::operator()(void* fiber)
{
	if (fiber != nullptr)
	{
		Process::Fiber::DeleteFiber(fiber);
		fiber = nullptr;
	}
}