#pragma once
#include "Common.h"
namespace Process
{
	namespace Overwrite
	{
		bool WINAPI SetThreadContext(_In_ HANDLE hThread, _In_ CONST CONTEXT * lpContext);
	}  // namespace Overwrite
}  // namespace Process
