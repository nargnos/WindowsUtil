// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
//#include "../LazyLoad/LazyLoad.h"
#include "../WindowsUtil/EnvironmentBlock.h"
int _tmain(int argc, _TCHAR* argv[])
{
	//_asm pushad
	//InitLazyLoad();
	////InitLazyLoad();
	//Lazy_MessageBoxA(0, 0, 0, 0);
	//MessageBoxA(0, 0, 0, 0);
	auto x = Peb::FindLoadedModuleHandle(L"ntdll.dll");
	return 0;
}

