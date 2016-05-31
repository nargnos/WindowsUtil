#include "stdafx.h"
#include "LoadLibrary.h"
#include "NtDll.h"
#include "FindLoadedModuleHandle.h"
namespace Process
{
	namespace Overwrite
	{
		VOID NTAPI _RtlInitUnicodeString(IN OUT PUNICODE_STRING destinationString, IN PCWSTR sourceString)
		{
			CONST SIZE_T maxSize = (MAXUINT16 & ~1) - sizeof(UNICODE_NULL);

			if (sourceString)
			{
				SIZE_T size = wcslen(sourceString) * sizeof(WCHAR);
				__analysis_assume(size <= maxSize);

				if (size > maxSize)
					size = maxSize;
				destinationString->Length = (USHORT)size;
				destinationString->MaximumLength = (USHORT)size + sizeof(UNICODE_NULL);
			}
			else
			{
				destinationString->Length = 0;
				destinationString->MaximumLength = 0;
			}

			destinationString->Buffer = (PWCHAR)sourceString;
		}
		HINSTANCE WINAPI LoadLibraryExW(LPCWSTR lpLibFileName, HANDLE ignore, DWORD dwFlags)
		{
			HINSTANCE hInst = EnvironmentBlock::FindLoadedModuleHandle(lpLibFileName);
			if (hInst)
			{
				return hInst;
			}

			auto& ldrLoadDll = Process::LazyLoad::NtDll::Instance().LdrLoadDll;
			if (!ldrLoadDll.Load())
			{
				return NULL;
			}

			ULONG dllCharacteristics = 0;
			if (dwFlags & DONT_RESOLVE_DLL_REFERENCES)
			{
				dllCharacteristics = IMAGE_FILE_EXECUTABLE_IMAGE;
			}

			UNICODE_STRING dllName;
			_RtlInitUnicodeString(&dllName, (PCWSTR)lpLibFileName);
			if (!NT_SUCCESS(ldrLoadDll(NULL, &dllCharacteristics, &dllName, reinterpret_cast<PVOID*>(&hInst))))
			{
				return NULL;
			}
			return hInst;
		}
		HINSTANCE WINAPI LoadLibraryW(LPCWSTR lpLibFileName)
		{
			return LoadLibraryExW(lpLibFileName, NULL, 0);
		}
	}  // namespace Overwrite
}  // namespace Process
