// HookLibTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <WinBase.h>
#include <Hook\HookIat.h>
#include <Hook\HookEat.h>
#include <iostream>
using std::cout;
using std::endl;

using MBox = int WINAPI(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCSTR lpText,
	_In_opt_ LPCSTR lpCaption,
	_In_ UINT uType);
int WINAPI MessageBoxAHook(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCSTR lpText,
	_In_opt_ LPCSTR lpCaption,
	_In_ UINT uType
)
{
	cout << "Succeed" << endl;
	cout << lpCaption << " - " << lpText << endl;
	return ShellAboutA(hWnd, lpCaption, lpText, NULL);
}


using SW = BOOL WINAPI(
	_In_ HWND hWnd,
	_In_ int nCmdShow);

SW* oldShowWindow = nullptr;

BOOL
WINAPI
ShowWindowHook(
	_In_ HWND hWnd,
	_In_ int nCmdShow)
{
	cout << "ShowWindow - " << hWnd << " - " << nCmdShow << endl;
	if (oldShowWindow)
	{
		return oldShowWindow(hWnd, nCmdShow);
	}
	return true;
}



auto user32dll = "user32.dll";
auto user32dllW = L"user32.dll";
auto mboxName = "MessageBoxA";
auto oldText = "原始";
auto oldTitle = "原始";
auto newText = "Hook后";
auto newTitle = "成功";

void Faild()
{
	cout << "Faild" << endl;
}
void TestIatHook()
{
	MessageBoxA(NULL, oldText, oldTitle, MB_OK);
	auto trueValue = GetProcAddress(LoadLibraryA(user32dll), mboxName);
	PVOID unhookAddr;
	auto oldAddr = Hook::HookIat(NULL, user32dll, mboxName, MessageBoxAHook, &unhookAddr);
	// iathook后可以用动态调用取到旧地址
	if (oldAddr != nullptr && trueValue == oldAddr)
	{
		// 会调用到Hook后的函数
		MessageBoxA(NULL, newText, newTitle, MB_OK);
		// 使用旧函数
		reinterpret_cast<MBox*>(oldAddr)(0, "原函数调用测试", "XXX", MB_OK);
		// unhook
		if (Hook::UnHookIat(unhookAddr, oldAddr))
		{
			// 已恢复
			MessageBoxA(NULL, "已恢复", mboxName, MB_OK);
		}
	}
	else
	{
		Faild();
		return;
	}

	// hook shell32 iat -> user32 ShowWindow
	auto shell32 = LoadLibraryA("shell32.dll");
	oldShowWindow = (SW*)Hook::HookIat(shell32, user32dll, "ShowWindow", ShowWindowHook, NULL);
	if (oldShowWindow)
	{

		ShellAboutA(NULL, "这个函数会调用到ShowWindow", "=======", NULL);
		// hook的是shell32的iat所以这里不会触发,如果hook了自身的iat情况就会相反
		ShowWindow(0, 0);
	}
	else
	{
		Faild();
	}
}


void TestEatHook()
{
	MessageBoxA(NULL, oldText, oldTitle, MB_OK);
	auto dllModule = LoadLibraryA(user32dll);
	auto oldValue = GetProcAddress(dllModule, mboxName);

	PDWORD oldFuncRva;
	// 64位有可能两个函数距离过远而hook失败，需要换其它方式

	auto oldAddr = Hook::HookEat(dllModule, mboxName, MessageBoxAHook, &oldFuncRva);
	if (oldAddr)
	{
		// eat hook后动态调用取到的就都是MessageBoxAHook函数地址了，直接调用没效果，因为地址在iat里
		auto newValue = GetProcAddress(dllModule, mboxName);
		if ((void*)newValue == (void*)MessageBoxAHook)
		{
			reinterpret_cast<MBox*>(newValue)(0, newText, newTitle, MB_OK);
		}

	}

}

int main()
{
	// TestIatHook();
	// TestEatHook();
	// delayimport要修改编译选项，先不测了
	return 0;
}

