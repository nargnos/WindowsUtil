#include "stdafx.h"
#include "SetThreadContext.h"
#include "NtDll.h"
bool WINAPI Process::Overwrite::SetThreadContext(_In_ HANDLE hThread, _In_ CONST CONTEXT * lpContext)
{
	auto& ntSetContextThread = Process::LazyLoad::NtDll::Instance().NtSetContextThread;
	if (!ntSetContextThread.Load())
	{
		return false;
	}
	NTSTATUS Status = ntSetContextThread(hThread, (PCONTEXT)lpContext);
	return NT_SUCCESS(Status);
}
