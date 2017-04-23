#pragma once
#include "Common.h"
#include "EnvironmentBlock.h"
namespace Process
{
	namespace Overwrite
	{
		VOID NTAPI _RtlInitUnicodeString(_Out_ PUNICODE_STRING destinationString, _In_ PCWSTR sourceString);
		_Ret_maybenull_ HINSTANCE WINAPI LoadLibraryExW(_In_ LPCWSTR lpLibFileName, _Reserved_ HANDLE ignore, _In_ DWORD dwFlags);
		_Ret_maybenull_ HINSTANCE WINAPI LoadLibraryW(_In_ LPCWSTR lpLibFileName);

	}  // namespace Overwrite
}  // namespace Process
