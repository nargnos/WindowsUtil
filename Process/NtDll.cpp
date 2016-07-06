#include "stdafx.h"
#include "NtDll.h"
namespace Process
{
	namespace LazyLoad
	{
		_STD unique_ptr<NtDll::LoadNtDll> NtDll::instance_;
		SpinLock Process::LazyLoad::NtDll::lock_;
		const NtDll::LoadNtDll & NtDll::Instance()
		{
			Init();
			return *instance_;
		}
		void NtDll::Init()
		{
			if (!instance_)
			{
				_STD lock_guard<SpinLock> lock(lock_);
				if (!instance_)
				{
					instance_ = _STD unique_ptr<LoadNtDll>(new LoadNtDll());
				}

			}
		}
		NtDll::LoadNtDll::LoadNtDll() :
			LoadDllBase(L"ntdll.dll"),
			LdrLoadDll(*this, "LdrLoadDll"),
			NtOpenProcess(*this, "NtOpenProcess"),
			NtSetContextThread(*this, "NtSetContextThread"),
			NtProtectVirtualMemory(*this, "NtProtectVirtualMemory"),
			NtReadVirtualMemory(*this, "NtReadVirtualMemory"),
			NtWriteVirtualMemory(*this, "NtWriteVirtualMemory"),
			NtFlushInstructionCache(*this, "NtFlushInstructionCache"),
			NtAllocateVirtualMemory(*this, "NtAllocateVirtualMemory"),
			NtQueryVirtualMemory(*this, "NtQueryVirtualMemory"),
			NtFreeVirtualMemory(*this, "NtFreeVirtualMemory")
		{
		}
	}  // namespace LazyLoad
}  // namespace Process
