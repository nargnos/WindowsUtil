#pragma once
#include <delayimp.h>
#include "..\Common\Common.h"
#include "DelayImportThunkIterator.h"
namespace PE
{
	template<typename _DelayImport>
	class DelayImportDescriptorIterator:
		public IIterator<PImgDelayDescr>,
		public GetIterator<DelayImportThunkIterator<DelayImportDescriptorIterator<_DelayImport>>, DelayImportDescriptorIterator<_DelayImport>>
	{
		_DelayImport& delayImport;
		PImgDelayDescr currentDelay;
	public:
		friend GetIteratorBase::Iterator;
		DelayImportDescriptorIterator(_DelayImport& delayImport) :delayImport(delayImport)
		{
		}

		~DelayImportDescriptorIterator()
		{
		}

		// Í¨¹ý IIterator ¼Ì³Ð
		virtual PImgDelayDescr Current() override
		{
			return currentDelay;
		}
		virtual bool Next() override
		{
			if (!currentDelay)
			{
				currentDelay = delayImport.data;
				canCreateIterator = true;
				return true;
			}
			else
			{
				currentDelay++;
				if (currentDelay->grAttrs)
				{
					canCreateIterator = true;
					return true;
				}
			}
			canCreateIterator = false;
			return false;
		}
		virtual void Reset() override
		{
			currentDelay = NULL;
		}
	};

}