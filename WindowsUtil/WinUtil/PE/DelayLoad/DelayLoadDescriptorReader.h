#pragma once
#include "..\PeDecoder.h"
namespace PE
{
	namespace DelayLoad
	{
		class DelayLoadDescriptorReader
		{
			PImgDelayDescr delayArray;
			PImgDelayDescr currentDelay;
		public:
			DelayLoadDescriptorReader(PeDecoder& pe);
			~DelayLoadDescriptorReader();
			PImgDelayDescr Current();
			bool Next();
			void Reset();
		};

	}
}