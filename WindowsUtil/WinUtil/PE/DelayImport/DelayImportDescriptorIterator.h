#pragma once

#include "..\Common\Common.h"
#include "DelayImportThunkIterator.h"


namespace PE
{
	class DelayImportThunkIterator;
	class DelayImportDescriptorIterator :
		public IIterator<PImgDelayDescr>,
		public GetIterator<DelayImportThunkIterator, DelayImportDescriptorIterator>
	{
		DelayImportDirectory& delayImport;
		PImgDelayDescr currentDelay;
	public:
		friend class DelayImportThunkIterator;
		explicit DelayImportDescriptorIterator(DelayImportDirectory& delayImport);

		~DelayImportDescriptorIterator();

		// Í¨¹ý IIterator ¼Ì³Ð
		virtual PImgDelayDescr Current() override;
		virtual bool Next() override;
		virtual void Reset() override;
	};

}  // namespace PE
