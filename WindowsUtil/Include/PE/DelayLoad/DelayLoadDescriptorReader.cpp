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
		PIMAGE_DELAYLOAD_DESCRIPTOR DelayLoadDescriptorReader::Current()
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
				if (currentDelay->Attributes.AllAttributes)
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