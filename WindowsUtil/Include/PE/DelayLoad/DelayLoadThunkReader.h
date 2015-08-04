#pragma once
#include <cassert>
#include "DelayLoadDescriptorReader.h"

namespace PE
{
	namespace DelayLoad
	{
		// 装了2015，winnt的PIMAGE_DELAYLOAD_DESCRIPTOR结构怎么没了，换成PImgDelayDescr
		class DelayLoadThunkReader
		{
			PVOID importAddressTable;
			PVOID importNameTable;
			PImgDelayDescr descriptor;
			PVOID currentImportAddressTable;
			PVOID currentImportNameTable;
		public:
			DelayLoadThunkReader(PeDecoder& pe, PImgDelayDescr descriptor);
			DelayLoadThunkReader();
			~DelayLoadThunkReader();
			void Init(PeDecoder& pe, PImgDelayDescr descriptor);
			PVOID CurrentNameTable();
			PVOID CurrentAddressTable();
			bool Next();
			void Reset();
		};

	}
}