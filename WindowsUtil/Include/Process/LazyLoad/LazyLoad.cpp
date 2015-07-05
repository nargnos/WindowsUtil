#include "LazyLoad.h"
namespace Process
{
	namespace LazyLoad
	{
		LPCWSTR NtDllDll = L"ntdll.dll";
		
#pragma region 基本核心函数

		VOID NTAPI _RtlInitUnicodeString(IN OUT PUNICODE_STRING DestinationString, IN PCWSTR SourceString)
		{
			SIZE_T Size;
			CONST SIZE_T MaxSize = (MAXUINT16 & ~1) - sizeof(UNICODE_NULL);

			if (SourceString)
			{
				Size = wcslen(SourceString) * sizeof(WCHAR);
				__analysis_assume(Size <= MaxSize);

				if (Size > MaxSize)
					Size = MaxSize;
				DestinationString->Length = (USHORT)Size;
				DestinationString->MaximumLength = (USHORT)Size + sizeof(UNICODE_NULL);
			}
			else
			{
				DestinationString->Length = 0;
				DestinationString->MaximumLength = 0;
			}

			DestinationString->Buffer = (PWCHAR)SourceString;
		}

		INIT_FUNC(
			NTSTATUS, LdrLoadDll, (_In_opt_ PWSTR SearchPath, _In_opt_ PULONG LoadFlags, _In_ PUNICODE_STRING Name, _Out_opt_ PVOID *BaseAddress)
			)
		{
			auto ntDll = EnvironmentBlock::FindLoadedModuleHandle(NtDllDll);
			if (!ntDll)
			{
				// 找不到ntdll
				return STATUS_DLL_NOT_FOUND;
			}
			_LdrLoadDll = (FuncType_LdrLoadDll)PE::Export::GetProcAddress(ntDll, "LdrLoadDll");
			return _LdrLoadDll(SearchPath, LoadFlags, Name, BaseAddress);
		};


		HINSTANCE WINAPI _LoadLibraryExW(LPCWSTR lpLibFileName, HANDLE ignore, DWORD dwFlags)
		{
			UNICODE_STRING DllName;
			HINSTANCE hInst;
			ULONG DllCharacteristics = 0;
			if (dwFlags & DONT_RESOLVE_DLL_REFERENCES)
			{
				DllCharacteristics = IMAGE_FILE_EXECUTABLE_IMAGE;
			}
			hInst = EnvironmentBlock::FindLoadedModuleHandle(lpLibFileName);
			if (hInst)
			{
				return hInst;
			}
			_RtlInitUnicodeString(&DllName, (PCWSTR)lpLibFileName);
			if (!NT_SUCCESS(_LdrLoadDll(NULL, &DllCharacteristics, &DllName, (PVOID*)&hInst)))
			{
				return NULL;
			}
			return hInst;
		}


		HINSTANCE WINAPI _LoadLibraryW(LPCWSTR lpLibFileName)
		{
			return _LoadLibraryExW(lpLibFileName, NULL, 0);
		}

		// 使用重写的版本,非dll里的
		FARPROC _GetProcAddress(HMODULE module, LPCSTR procName)
		{
			return PE::Export::GetProcAddress(module, procName);
		}
		FARPROC _GetProcAddressEx(LPCWSTR dllName, LPCSTR procName)
		{
			auto dll = _LoadLibraryW(dllName);
			if (dll)
			{
				auto result = _GetProcAddress(dll, procName);
				if (result)
				{
					return result;
				}
			}
			return NULL;
		}
#pragma endregion


	}
}