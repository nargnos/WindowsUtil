#pragma once
#include "..\PeDecoder.h"
namespace PE
{
	namespace DelayLoad
	{
		class DelayLoadDescriptorReader
		{
			PIMAGE_DELAYLOAD_DESCRIPTOR delayArray;
			PIMAGE_DELAYLOAD_DESCRIPTOR currentDelay;
		public:
			DelayLoadDescriptorReader(PeDecoder& pe);
			~DelayLoadDescriptorReader();
			PIMAGE_DELAYLOAD_DESCRIPTOR Current();
			bool Next();
			void Reset();
		};

	}
}