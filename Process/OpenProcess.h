#pragma once
#include "Common.h"
namespace Process
{
	namespace Overwrite
	{
		HANDLE WINAPI OpenProcess(_In_ DWORD dwDesiredAccess, _In_ BOOL bInheritHandle, _In_ DWORD dwProcessId);
	}  // namespace Overwrite
}  // namespace Process
