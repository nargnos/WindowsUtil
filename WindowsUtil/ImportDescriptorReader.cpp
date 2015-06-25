#include "ImportDescriptorReader.h"
namespace PE
{
	// 导入表Descriptor结构读取器
	ImportDescriptorReader::ImportDescriptorReader(PeDecoder& pe)
	{

		descriptor = pe.GetImageImport();
		if (descriptor)
		{
			descriptorLength = &pe.GetDataDirectory(IMAGE_DIRECTORY_ENTRY_IMPORT)->Size;
		}
		else
		{
			descriptorLength = 0;
		}
		Reset();
	}
	ImportDescriptorReader::~ImportDescriptorReader(){}
	bool ImportDescriptorReader::Next()
	{
		if (descriptorLength)
		{
			if (++currentIndex < *descriptorLength)
			{
				auto checkResult = descriptor[currentIndex];
				if (checkResult.Name == NULL || checkResult.FirstThunk == NULL)
				{
					return false;
				}
				return true;
			}
		}
		return false;
	}
	PIMAGE_IMPORT_DESCRIPTOR ImportDescriptorReader::Current()
	{
		if (currentIndex == -1)
		{
			return NULL;
		}
		return &descriptor[currentIndex];
	}

	void ImportDescriptorReader::Reset()
	{
		currentIndex = -1;
	}
	PCHAR ImportDescriptorReader::GetDescriptorName(PeDecoder& pe, PIMAGE_IMPORT_DESCRIPTOR descriptor)
	{
		return (PCHAR)pe.GetRvaData(descriptor->Name);
	}
}