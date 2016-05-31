#include "stdafx.h"
#include "NtDll.h"
namespace Process
{
	namespace LazyLoad
	{
		NtDll::LoadNtDll NtDll::instance_;
		const NtDll::LoadNtDll & NtDll::Instance()
		{
			return instance_;
		}
		NtDll::LoadNtDll::LoadNtDll() :
			LoadDllBase(L"ntdll.dll"),
			LdrLoadDll(*this,"LdrLoadDll"),
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
