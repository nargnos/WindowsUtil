#pragma once
#include "DelayLoadDescriptorReader.h"

namespace PE
{
	namespace DelayLoad
	{
		class DelayLoadThunkReader
		{
			PVOID importAddressTable;
			PVOID importNameTable;
			PIMAGE_DELAYLOAD_DESCRIPTOR descriptor;
			PVOID currentImportAddressTable;
			PVOID currentImportNameTable;
		public:
			DelayLoadThunkReader(PeDecoder& pe, PIMAGE_DELAYLOAD_DESCRIPTOR descriptor);
			DelayLoadThunkReader();
			~DelayLoadThunkReader();
			void Init(PeDecoder& pe, PIMAGE_DELAYLOAD_DESCRIPTOR descriptor);
			PVOID CurrentNameTable();
			PVOID CurrentAddressTable();
			bool Next();
			void Reset();
		};

	}
}