#include "stdafx.h"
#include "Kernel32.h"

_STD unique_ptr<Process::LazyLoad::Kernel32::LoadKernel32> Process::LazyLoad::Kernel32::instance_;
SpinLock Process::LazyLoad::Kernel32::lock_;
Process::LazyLoad::Kernel32::LoadKernel32::LoadKernel32() :
	LoadDllBase(L"kernel32.dll"),
	GetSystemInfo(*this, "GetSystemInfo"),
	CreateFileMappingW(*this, "CreateFileMappingW"),
	OpenFileMappingW(*this, "OpenFileMappingW"),
	MapViewOfFile(*this, "MapViewOfFile"),
	MapViewOfFileEx(*this, "MapViewOfFileEx"),
	FlushViewOfFile(*this, "FlushViewOfFile"),
	UnmapViewOfFile(*this, "UnmapViewOfFile"),
	VirtualLock(*this, "VirtualLock"),
	VirtualUnlock(*this, "VirtualUnlock"),
	OpenProcess(*this, "OpenProcess"),
	SetThreadContext(*this, "SetThreadContext"),
	VirtualProtect(*this, "VirtualProtect"),
	VirtualProtectEx(*this, "VirtualProtectEx"),
	ReadProcessMemory(*this, "ReadProcessMemory"),
	WriteProcessMemory(*this, "WriteProcessMemory"),
	VirtualAlloc(*this, "VirtualAlloc"),
	VirtualAllocEx(*this, "VirtualAllocEx"),
	VirtualQuery(*this, "VirtualQuery"),
	VirtualQueryEx(*this, "VirtualQueryEx"),
	VirtualFreeEx(*this, "VirtualFreeEx"),
	VirtualFree(*this, "VirtualFree")
{
}

const Process::LazyLoad::Kernel32::LoadKernel32 & Process::LazyLoad::Kernel32::Instance()
{
	Init();
	return *instance_;
}

void Process::LazyLoad::Kernel32::Init()
{
	if (!instance_)
	{
		_STD lock_guard<SpinLock> lock(lock_);
		if (!instance_)
		{
			instance_ = _STD unique_ptr<LoadKernel32>(new LoadKernel32());
		}
	}
}
