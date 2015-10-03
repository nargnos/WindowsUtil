
#include "CppUnitTest.h"
#include <iostream>
#include <string>
#include <strstream>
#include <Process\LazyLoad\LazyLoadSystemApi.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTest1
{

	// 测试32位部分
	TEST_CLASS(TestLoadWinApi)
	{

	public:
		
		TEST_METHOD(Load_MessageBoxA)
		{
			using namespace Process::LazyLoad;
			// 这一步会用到取PEB,解析PEB,读取已经载入的ntdll.dll句柄,使用pe解析器获得ldrloaddll函数指针,
			if (!User32_Dll.Load())
			{
				Assert::Fail();
			}
			// 这一步用到使用该函数指针载入user32.dll,再使用pe解析获取msgbox指针
			if (!User32_Dll._MessageBoxA)
			{
				Assert::Fail();
			}
			
			// 这一步转发参数调用函数, 指针错误或调用方式非stdcall都会导致出错
			User32_Dll._MessageBoxA(0, "成功", "动态调用", MB_OK);
		}
	private:
		
	};
}