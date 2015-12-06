#include "ImportDescriptorIterator.h"
namespace PE
{
	//namespace Import
	//{
	//	// 导入表Descriptor结构读取器
	//	ImportDescriptorIterator::ImportDescriptorIterator(PeDecoder& pe)
	//	{
	//		descriptorLength = NULL;
	//		descriptor = pe.GetImageImport(&descriptorLength);
	//		Reset();
	//	}
	//	ImportDescriptorIterator::~ImportDescriptorIterator() {}
	//	bool ImportDescriptorIterator::Next()
	//	{
	//		if (descriptorLength)
	//		{
	//			if (++currentIndex < *descriptorLength)
	//			{
	//				auto checkResult = descriptor[currentIndex];
	//				return !(checkResult.Name == NULL || checkResult.FirstThunk == NULL);
	//			}
	//		}
	//		return false;
	//	}
	//	PIMAGE_IMPORT_DESCRIPTOR ImportDescriptorIterator::Current()
	//	{
	//		return currentIndex == -1 ?NULL:&descriptor[currentIndex];
	//	}

	//	void ImportDescriptorIterator::Reset()
	//	{
	//		currentIndex = -1;
	//	}

	//}
}