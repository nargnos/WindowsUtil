#pragma once
#include <delayimp.h>
#include "..\Common\Common.h"
namespace PE
{
	template<typename _DelayImportDescriptorIterator>
	class DelayImportThunkIterator
	{
		PVOID importAddressTable;
		PVOID importNameTable;
		PImgDelayDescr descriptor;
		PVOID currentImportAddressTable;
		PVOID currentImportNameTable;

	public:

		DelayImportThunkIterator(_DelayImportDescriptorIterator& delayImportDescriptorIterator)
		{
			descriptor = delayImportDescriptorIterator.currentDelay;
			importAddressTable = delayImportDescriptorIterator.delayImport.GetPeDecoder().GetRvaData(descriptor->rvaIAT);
			importNameTable = delayImportDescriptorIterator.delayImport.GetPeDecoder().GetRvaData(descriptor->rvaINT);
			Reset();
		}

		~DelayImportThunkIterator()
		{
		}
		PVOID CurrentNameTable()
		{
			return currentImportNameTable;
		}
		PVOID CurrentAddressTable()
		{
			return currentImportAddressTable;
		}
		bool Next()
		{
			if (currentImportAddressTable && currentImportNameTable)
			{
				currentImportAddressTable = (HANDLE_PTR*)currentImportAddressTable + 1;
				currentImportNameTable = (HANDLE_PTR*)currentImportNameTable + 1;
				if (*(HANDLE_PTR*)currentImportAddressTable && *(HANDLE_PTR*)currentImportNameTable)
				{
					return true;
				}
			}
			else
			{
				currentImportAddressTable = importAddressTable;
				currentImportNameTable = importNameTable;
				return true;
			}


			return false;
		}
		void Reset()
		{
			currentImportAddressTable = NULL;
			currentImportNameTable = NULL;
		}
	};

}