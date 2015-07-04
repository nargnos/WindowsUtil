#include <Process\LazyLoad\LazyLoad.h>
namespace LazyLoad
{
#pragma region 基本函数

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
		auto ntDll = Peb::FindLoadedModuleHandle(L"ntdll.dll");
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
		hInst = Peb::FindLoadedModuleHandle(lpLibFileName);
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



#pragma region 常用函数定义
#define DEF_DEFAULT_FUNC
#ifdef DEF_DEFAULT_FUNC


	// FIX: 32位实现可以用__declspec(naked) __stdcall声明并在函数中jmp到api地址实现跳转, 但是64位不能用这个方法,所以先暂时用一个通用的方法
	// 下面的MessageBoxA是例子
	INIT_FUNC(int, MessageBoxA, (
		_In_opt_ HWND hWnd,
		_In_opt_ LPCSTR lpText,
		_In_opt_ LPCSTR lpCaption,
		_In_ UINT uType
		))
		DEF_FUNC_CODE(L"user32.dll",
		MessageBoxA, NULL, (
		hWnd,
		lpText,
		lpCaption,
		uType
		));

	// NOTICE: 用到的慢慢补充
	INIT_FUNC(BOOL, VirtualProtect, (
		_In_ LPVOID lpAddress,
		_In_ SIZE_T dwSize,
		_In_ DWORD flNewProtect,
		_Out_ PDWORD lpflOldProtect
		))
		DEF_FUNC_CODE(L"kernel32.dll",
		VirtualProtect, FALSE, (
		lpAddress,
		dwSize,
		flNewProtect,
		lpflOldProtect
		));


#endif
#pragma endregion

}
