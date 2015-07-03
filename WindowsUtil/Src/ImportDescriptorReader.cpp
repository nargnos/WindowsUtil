#include <PE\Import\ImportDescriptorReader.h>
namespace PE
{
	namespace Import{
		// 导入表Descriptor结构读取器
		ImportDescriptorReader::ImportDescriptorReader(PeDecoder& pe)
		{
			descriptorLength = NULL;
			descriptor = pe.GetImageImport(&descriptorLength);			
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
		LPSTR ImportDescriptorReader::GetDescriptorName(PeDecoder& pe, PIMAGE_IMPORT_DESCRIPTOR descriptor)
		{
			return (LPSTR)pe.GetRvaData(descriptor->Name);
		}
	}
}