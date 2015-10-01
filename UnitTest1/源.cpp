#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <string>
#include <strstream>
#include <Process\LazyLoad\LazyLoad.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTest1
{

	// ²âÊÔ32Î»²¿·Ö
	TEST_CLASS(TestLoadPE)
	{

	public:
		TEST_METHOD(LoadPE)
		{
//			PE::PeDecoder l(0, 0);
			//PE::SectionReader a(0,0);
			//auto d =(PE::IPeIterator*)&a;
			auto dd = Process::LazyLoad::_LoadLibraryW(L"d3d11.dll");
			//d->Current();
		}
	private:
		
	};
}