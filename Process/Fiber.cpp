#include "stdafx.h"
#include "Fiber.h"

Process::Fiber::Fiber::Fiber(Func && func) :
	fiber_(Process::Fiber::CreateFiber(0, Run, this)),
	func_(_STD move(func))
{
}

Process::Fiber::Fiber::~Fiber()
{
	if (fiber_ != nullptr)
	{
		Process::Fiber::DeleteFiber(fiber_);
		fiber_ = nullptr;
	}
}

void Process::Fiber::Fiber::Switch()
{
	assert(Process::Fiber::IsThreadAFiber());
	auto ptr = GetAddress();
	assert(ptr);
	Process::Fiber::SwitchToFiber(ptr);
}

LPVOID Process::Fiber::Fiber::GetAddress()
{
	return fiber_;
}

void Process::Fiber::Fiber::Run(LPVOID param)
{
	assert(param != nullptr);
	auto self = static_cast<Fiber*>(param);
	assert(self->func_);
	self->func_();
}
