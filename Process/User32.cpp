#include "stdafx.h"
#include "User32.h"

Process::LazyLoad::User32::LoadUser32 Process::LazyLoad::User32::instance_;
Process::LazyLoad::User32::LoadUser32::LoadUser32() :
	LoadDllBase(L"user32.dll"),
	MessageBoxA(*this,"MessageBoxA")
{
}

const Process::LazyLoad::User32::LoadUser32 & Process::LazyLoad::User32::Instance()
{
	return instance_;
}
