#include "stdafx.h"
#include "OpenProcess.h"
#include "EnvironmentBlock.h"
#include "NtDll.h"
using Process::EnvironmentBlock::CLIENT_ID;
using Process::LazyLoad::NtDll;
HANDLE WINAPI Process::Overwrite::OpenProcess(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId)
{
	auto& ntOpenProcess = NtDll::Instance().NtOpenProcess;

	if (!ntOpenProcess.Load())
	{
		return NULL;
	}

	OBJECT_ATTRIBUTES objectAttributes;
	InitializeObjectAttributes(&objectAttributes,
		NULL,
		(bInheritHandle ? OBJ_INHERIT : 0),
		NULL,
		NULL);

	CLIENT_ID clientId;
	clientId.UniqueProcess = UlongToHandle(dwProcessId);
	clientId.UniqueThread = 0;
	HANDLE processHandle;
	NTSTATUS status = ntOpenProcess(&processHandle,
		dwDesiredAccess,
		&objectAttributes,
		&clientId);

	return NT_SUCCESS(status) ? processHandle : NULL;
}
