#include "stdafx.h"
#include "NtDll.h"
namespace Process
{
	namespace LazyLoad
	{
		namespace NtDll
		{
			namespace Detail
			{
				_STD unique_ptr<LoadNtDll> instance_;
				_STD once_flag flag_;

				const LoadNtDll& Instance()
				{
					if (!instance_)
					{
						_STD call_once(flag_, []()
						{
							instance_ = _STD unique_ptr<LoadNtDll>(new LoadNtDll());
						});
					}
					return *instance_;
				}
				LoadNtDll::LoadNtDll() :
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
			}  // namespace Detail

		}  // namespace NtDll

	}  // namespace LazyLoad
}  // namespace Process
