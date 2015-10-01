#pragma once
#include "..\PeDecoder.h"
namespace PE
{
	namespace Import
	{
		// 导入表Descriptor结构读取器
		class ImportDescriptorReader
		{
		public:
			ImportDescriptorReader(PeDecoder& pe);
			~ImportDescriptorReader();
			bool Next();
			PIMAGE_IMPORT_DESCRIPTOR Current();
			void Reset();

		private:
			PDWORD descriptorLength;
			int currentIndex;
			PIMAGE_IMPORT_DESCRIPTOR descriptor;
		};

	}
}