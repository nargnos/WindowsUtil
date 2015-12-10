#pragma once

#include "..\Common\Common.h"
#include <delayimp.h>
namespace PE
{
	class DelayImportDescriptorIterator;
	class DelayImportThunkIterator
	{
		PVOID importAddressTable;
		PVOID importNameTable;
		PImgDelayDescr descriptor;
		PVOID currentImportAddressTable;
		PVOID currentImportNameTable;

	public:

		DelayImportThunkIterator(DelayImportDescriptorIterator& delayImportDescriptorIterator);

		~DelayImportThunkIterator();
		PVOID CurrentNameTable();
		PVOID CurrentAddressTable();
		bool Next();
		void Reset();
	};

}