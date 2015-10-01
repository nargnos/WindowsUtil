#include "LazyLoadSystemApi.h"
namespace Process
{
	namespace LazyLoad
	{
		_Kernel32 Kernel32_Dll = _Kernel32(L"kernel32.dll");
		_User32 User32_Dll = _User32(L"user32.dll");;



		// kernel32.dll 函数注册
		void Process::LazyLoad::_Kernel32::FuncRegister()
		{
			_GetSystemInfo = decltype(_GetSystemInfo)(this, "GetSystemInfo");
			_CreateFileMappingW = decltype(_CreateFileMappingW)(this, "CreateFileMappingW");
			_OpenFileMappingW = decltype(_OpenFileMappingW)(this, "OpenFileMappingW");
			_MapViewOfFile = decltype(_MapViewOfFile)(this, "MapViewOfFile");
			_MapViewOfFileEx = decltype(_MapViewOfFileEx)(this, "MapViewOfFileEx");
			_FlushViewOfFile = decltype(_FlushViewOfFile)(this, "FlushViewOfFile");
			_UnmapViewOfFile = decltype(_UnmapViewOfFile)(this, "UnmapViewOfFile");
			_VirtualLock = decltype(_VirtualLock)(this, "VirtualLock");
			_VirtualUnlock = decltype(_VirtualUnlock)(this, "VirtualUnlock");

			// 下面的函数已经重写了不用系统dll的版本,可以不用
			_OpenProcess = decltype(_OpenProcess)(this, "OpenProcess");
			_SetThreadContext = decltype(_SetThreadContext)(this, "SetThreadContext");
			_VirtualProtect = decltype(_VirtualProtect)(this, "VirtualProtect");
			_VirtualProtectEx = decltype(_VirtualProtectEx)(this, "VirtualProtectEx");
			_ReadProcessMemory = decltype(_ReadProcessMemory)(this, "ReadProcessMemory");
			_WriteProcessMemory = decltype(_WriteProcessMemory)(this, "WriteProcessMemory");
			_VirtualAlloc = decltype(_VirtualAlloc)(this, "VirtualAlloc");
			_VirtualAllocEx = decltype(_VirtualAllocEx)(this, "VirtualAllocEx");
			_VirtualQuery = decltype(_VirtualQuery)(this, "VirtualQuery");
			_VirtualQueryEx = decltype(_VirtualQueryEx)(this, "VirtualQueryEx");
			_VirtualFreeEx = decltype(_VirtualFreeEx)(this, "VirtualFreeEx");
			_VirtualFree = decltype(_VirtualFree)(this, "VirtualFree");


		}
		// user32.dll 函数注册
		void Process::LazyLoad::_User32::FuncRegister()
		{
			_MessageBoxA = decltype(_MessageBoxA)(this, "MessageBoxA");
		}

	}
}