#pragma once
#include <delayimp.h>
#include "../Common/Common.h"
#include "DelayImportDescriptorIterator.h"
namespace PE
{
	template<typename _PeDecoder>
	class DelayImportDirectory :
		public DataDirectory<_PeDecoder, PImgDelayDescr, IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT>,
		public IGetValue<PImgDelayDescr>,
		public GetIterator<DelayImportDescriptorIterator<DelayImportDirectory<_PeDecoder>>, DelayImportDirectory<_PeDecoder>>
	{
		
	public:
		friend GetIteratorBase::Iterator;
		DelayImportDirectory(_PeDecoder& pe) :DataDirectoryBase(pe)
		{
			canCreateIterator = true;
		}

		~DelayImportDirectory()
		{
		}

		virtual PImgDelayDescr GetValue() override
		{
			return data;
		}
	};

}