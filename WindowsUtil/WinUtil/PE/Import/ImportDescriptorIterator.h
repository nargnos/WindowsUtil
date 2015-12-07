#pragma once

#include "../Common/Common.h"
#include "ImportThunkIterator.h"
namespace PE
{
	// 导入表Descriptor结构读取器
	template<typename _ImportDirectory>
	class ImportDescriptorIterator :
		public IIterator<PIMAGE_IMPORT_DESCRIPTOR>,
		public GetIterator<ImportThunkIterator<ImportDescriptorIterator<_ImportDirectory>>, ImportDescriptorIterator<_ImportDirectory>>
	{
		_ImportDirectory& importDirectory;
		int currentIndex;
	public:
		friend ImportThunkIterator<ImportDescriptorIterator<_ImportDirectory>>;
		ImportDescriptorIterator(_ImportDirectory& importDirectory) :importDirectory(importDirectory)
		{

		}
		~ImportDescriptorIterator() {}
		bool Next()
		{
			if (importDirectory.size)
			{
				if (++currentIndex < *importDirectory.size)
				{
					auto checkResult = importDirectory.data[currentIndex];
					canCreateIterator = !(checkResult.Name == NULL || checkResult.FirstThunk == NULL);
					return canCreateIterator;
				}
			}
			canCreateIterator = false;
			return false;
		}

		void Reset()
		{
			currentIndex = -1;
		}
		virtual PIMAGE_IMPORT_DESCRIPTOR Current() override
		{
			assert(currentIndex > 0 && currentIndex < *importDirectory.size);
			return &importDirectory.data[currentIndex];
		}
	};


}