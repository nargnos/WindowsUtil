#include "LazyLoad.h"
namespace Process
{
	namespace LazyLoad
	{
#pragma region LoadDll核心函数
		
		_NtDll NtDll_Dll = _NtDll(L"ntdll.dll");
		_NtDll::_NtDll(LPCWSTR dllName) :_LoadDll(dllName)
		{
		}
		_NtDll::~_NtDll()
		{
		}
		HINSTANCE _NtDll::GetDll()
		{
			return EnvironmentBlock::FindLoadedModuleHandle(dllName);
		}
		// 注册函数
		void _NtDll::FuncRegister()
		{
			_LdrLoadDll = decltype(_LdrLoadDll)(this, "LdrLoadDll");
			_NtOpenProcess = decltype(_NtOpenProcess)(this, "NtOpenProcess");
			_NtSetContextThread = decltype(_NtSetContextThread)(this, "NtSetContextThread");
			_NtProtectVirtualMemory = decltype(_NtProtectVirtualMemory)(this, "NtProtectVirtualMemory");
			_NtReadVirtualMemory = decltype(_NtReadVirtualMemory)(this, "NtReadVirtualMemory");
			_NtWriteVirtualMemory = decltype(_NtWriteVirtualMemory)(this, "NtWriteVirtualMemory");
			_NtFlushInstructionCache = decltype(_NtFlushInstructionCache)(this, "NtFlushInstructionCache");
			_NtAllocateVirtualMemory = decltype(_NtAllocateVirtualMemory)(this, "NtAllocateVirtualMemory");
			_NtQueryVirtualMemory = decltype(_NtQueryVirtualMemory)(this, "NtQueryVirtualMemory");
			_NtFreeVirtualMemory = decltype(_NtFreeVirtualMemory)(this, "NtFreeVirtualMemory");

		}

#pragma endregion
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


		HINSTANCE WINAPI _LoadLibraryExW(LPCWSTR lpLibFileName, HANDLE ignore, DWORD dwFlags)
		{
			UNICODE_STRING DllName;
			HINSTANCE hInst = NULL;
			ULONG DllCharacteristics = 0;

			if (!NtDll_Dll.Load() || !NtDll_Dll._LdrLoadDll)
			{
				return NULL;
			}
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
			if (!NT_SUCCESS(NtDll_Dll._LdrLoadDll(NULL, &DllCharacteristics, &DllName, (PVOID*)&hInst)))
			{
				return NULL;
			}
			return hInst;
		}


		HINSTANCE WINAPI _LoadLibraryW(LPCWSTR lpLibFileName)
		{
			return _LoadLibraryExW(lpLibFileName, NULL, 0);
		}

		// 使用重写的版本,非系统dll里的
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