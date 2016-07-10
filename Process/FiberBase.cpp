#include "stdafx.h"
#include "FiberBase.h"

void Process::Fiber::SetCurrentFiberData(void * ptr)
{
	SetFiberData(::GetCurrentFiber(), ptr);

}

void Process::Fiber::SetFiberData(PVOID fiber, void * ptr)
{
	auto data = (PVOID *)fiber;
	*data = ptr;
}

const PNT_TIB Process::Fiber::GetCurrentFiberContext()
{
	return CONTAINING_RECORD(::GetCurrentFiber(), NT_TIB, FiberData);
}

void Process::Fiber::Detail::FiberDeletor::operator()(void* fiber)
{
	if (fiber != nullptr)
	{
		Process::Fiber::DeleteFiber(fiber);
		fiber = nullptr;
	}
}