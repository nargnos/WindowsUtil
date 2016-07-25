#include "stdafx.h"
#include "Kernel32.h"


namespace Process
{
	namespace LazyLoad
	{
		namespace Kernel32
		{
			namespace Detail
			{
				_STD unique_ptr<LoadKernel32> instance_;
				_STD once_flag flag_;

				LoadKernel32::LoadKernel32() :
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

				const LoadKernel32 & Instance()
				{
					if (!instance_)
					{
						_STD call_once(flag_, []()
						{
							instance_ = _STD unique_ptr<LoadKernel32>(new LoadKernel32());
						});
					}

					return *instance_;
				}

			}  // namespace Detail
		}  // namespace Kernel32

	}  // namespace LazyLoad
}  // namespace Process

