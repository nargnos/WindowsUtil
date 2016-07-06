#include "stdafx.h"
#include "CallbackBase.h"

Process::Thread::Detail::_Submitted::_Submitted() :isSubmitted_(false)
{
}

bool Process::Thread::Detail::_Submitted::IsSubmitted() const
{
	return isSubmitted_;
}

void Process::Thread::Detail::_Submitted::Submitted()
{
	isSubmitted_ = true;
}
