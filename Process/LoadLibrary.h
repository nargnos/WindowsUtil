#pragma once
#include "Common.h"
#include "EnvironmentBlock.h"
namespace Process
{
	namespace Overwrite
	{
		VOID NTAPI _RtlInitUnicodeString(IN OUT PUNICODE_STRING destinationString, IN PCWSTR sourceString);
		HINSTANCE WINAPI LoadLibraryExW(LPCWSTR lpLibFileName, HANDLE ignore, DWORD dwFlags);
		HINSTANCE WINAPI LoadLibraryW(LPCWSTR lpLibFileName);

	}  // namespace Overwrite
}  // namespace Process
