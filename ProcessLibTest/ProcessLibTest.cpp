#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <condition_variable>
#include <string>
#include <codecvt>
#include <Process\FindLoadedModuleHandle.h>
#include <Process\GetProcAddress.h>
#include <Process\NtDll.h>
#include <Process\User32.h>
#include <Process\Guard.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProcessLibTest
{
	using namespace Process::EnvironmentBlock;

	TEST_CLASS(ProcessLib)
	{
	public:

		TEST_METHOD(TestLdrDataTable)
		{
			auto dllName = L"user32.dll";
			auto handle = FindLoadedModuleHandle(dllName);
			auto handle2 = LoadLibrary(dllName);
			Assert::IsTrue(handle == handle2);

		}
		TEST_METHOD(TestGetProcAddress)
		{
			auto dllName = L"user32.dll";
			auto dllHandle = FindLoadedModuleHandle(dllName);
			auto funcNameGrp = { "MessageBoxW" ,"NotExist" };
			for each (auto var in funcNameGrp)
			{
				auto funcName = var;
				auto funcHandle1 = Process::Overwrite::GetProcAddress(dllHandle, [funcName](LPCSTR val)
				{
					return strcmp(funcName, val) == 0;
				});
				auto funcHandle2 = Process::Overwrite::GetProcAddress(dllHandle, funcName);
				auto trueValue = ::GetProcAddress(dllHandle, funcName);
				Assert::IsTrue(trueValue == funcHandle1);
				Assert::IsTrue(trueValue == funcHandle2);
			}

		}
		TEST_METHOD(TestLazyload)
		{
			using namespace Process::LazyLoad;
			auto& ldrLoadDll = NtDll::Instance().LdrLoadDll;
			ldrLoadDll.Load();
			// funtion没有取指针的函数验证不了只能下断点了
			auto ntdll = GetModuleHandleA("ntdll.dll");
			if (ntdll == NULL)
			{
				Assert::Fail();
				return;
			}
			auto trueValue = GetProcAddress(ntdll, "LdrLoadDll");
			if (trueValue == NULL)
			{
				Assert::Fail();
				return;
			}

			auto& mbox = User32::Instance().MessageBoxA;
			mbox(0, "Hello World!", "Goodbye World!", MB_OK);
		}
		
		TEST_METHOD(TestGuard)
		{
			_STD vector<int> ret;
			Guard([&]() {ret.push_back(1); Logger::WriteMessage("A"); });
			auto ld = [&]()
			{
				Guard g([&]() {ret.push_back(3); Logger::WriteMessage("C"); });
				return[&, g_ = _STD move(g)](){ret.push_back(2); Logger::WriteMessage("B"); };
			};
			ld()();
			Guard t0([&]()
			{
				int num = 1;
				for (auto& i : ret)
				{
					Assert::IsTrue(i == num++);
				}
				
				Logger::WriteMessage("End");
			});
			Guard t1([&]() {ret.push_back(5); Logger::WriteMessage("E"); });
			Guard t2([&]() {ret.push_back(4); Logger::WriteMessage("D"); });
			
		}
	};

}