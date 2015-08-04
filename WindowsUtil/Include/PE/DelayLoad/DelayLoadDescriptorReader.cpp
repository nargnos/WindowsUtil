#include "DelayLoadDescriptorReader.h"

namespace PE
{
	namespace DelayLoad
	{
		DelayLoadDescriptorReader::DelayLoadDescriptorReader(PeDecoder& pe)
		{
			
			delayArray = pe.ImageDelayImport();
			Reset();
		}


		DelayLoadDescriptorReader::~DelayLoadDescriptorReader()
		{
		}
		PImgDelayDescr DelayLoadDescriptorReader::Current()
		{
			return currentDelay;
		}
		bool DelayLoadDescriptorReader::Next()
		{
			if (!currentDelay)
			{
				currentDelay = delayArray;
				return true;
			}
			else
			{
				currentDelay++;
				if (currentDelay->grAttrs)
				{
					return true;
				}
			}
			return false;
		}
		void DelayLoadDescriptorReader::Reset()
		{
			currentDelay = NULL;
		}
	}
}