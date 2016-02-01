#pragma once

#include "../Common/Common.h"
#include "DelayImportDescriptorIterator.h"
namespace PE
{
	class DelayImportDirectory :
		public DataDirectory<DelayImportDirectory, PImgDelayDescr, IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT>,
		public IGetValue<PImgDelayDescr>,
		public GetIterator<DelayImportDescriptorIterator, DelayImportDirectory>
	{

	public:
		friend GetIteratorBase::Iterator;
		explicit DelayImportDirectory(PeDecoder& pe);

		~DelayImportDirectory();

		virtual PImgDelayDescr GetValue() override;
	};

}