#include "stdafx.h"
#include "CppUnitTest.h"
#include "PeImage.h"
#include "SectionHeaders.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace PeDecoder;
namespace PeImageLibTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			PeImage pe(GetModuleHandle(NULL),true);
			Assert::IsTrue(pe.IsPe());
			auto& sections = pe.GetSections();
			for each (auto& var in *sections)
			{
				//auto s = var.Characteristics;
			}
			// TODO: 在此输入测试代码
		}

	};
}