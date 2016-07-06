#include "stdafx.h"
#include "User32.h"

_STD unique_ptr<Process::LazyLoad::User32::LoadUser32> Process::LazyLoad::User32::instance_;
SpinLock Process::LazyLoad::User32::lock_;
Process::LazyLoad::User32::LoadUser32::LoadUser32() :
	LoadDllBase(L"user32.dll"),
	MessageBoxA(*this, "MessageBoxA")
{
}

const Process::LazyLoad::User32::LoadUser32 & Process::LazyLoad::User32::Instance()
{
	Init();
	return *instance_;
}

void Process::LazyLoad::User32::Init()
{
	if (!instance_)
	{
		_STD lock_guard<SpinLock> lock(lock_);
		if (!instance_)
		{
			instance_ = _STD unique_ptr<LoadUser32>(new LoadUser32());
		}
	}
}
