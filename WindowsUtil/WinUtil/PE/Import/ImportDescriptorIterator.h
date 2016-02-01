#pragma once
#include "ImportThunkIterator.h"
namespace PE
{
	class ImportDirectory;
	// 导入表Descriptor结构读取器
	class ImportDescriptorIterator :
		public IIterator<PIMAGE_IMPORT_DESCRIPTOR>,
		public GetIterator<ImportThunkIterator, ImportDescriptorIterator>
	{
		ImportDirectory& importDirectory;
		int currentIndex;
	public:
		friend GetIteratorBase::Iterator;
		explicit ImportDescriptorIterator(ImportDirectory& importDirectory);
		~ImportDescriptorIterator();
		bool Next();

		void Reset();
		virtual PIMAGE_IMPORT_DESCRIPTOR Current() override;
	};


}