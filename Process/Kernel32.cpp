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
					static LoadKernel32 instance;
					return instance;
				}

			}  // namespace Detail
		}  // namespace Kernel32

	}  // namespace LazyLoad
}  // namespace Process

