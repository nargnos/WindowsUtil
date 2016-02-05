#include "DelayImportDirectory.h"

PE::DelayImportThunkIterator::DelayImportThunkIterator(DelayImportDescriptorIterator & delayImportDescriptorIterator)
{
	descriptor = delayImportDescriptorIterator.currentDelay;
	importAddressTable = delayImportDescriptorIterator.delayImport.GetPeDecoder().GetRvaData(descriptor->rvaIAT);
	importNameTable = delayImportDescriptorIterator.delayImport.GetPeDecoder().GetRvaData(descriptor->rvaINT);
	Reset();
}

PE::DelayImportThunkIterator::~DelayImportThunkIterator()
{
}

PVOID PE::DelayImportThunkIterator::CurrentNameTable()
{
	return currentImportNameTable;
}

PVOID PE::DelayImportThunkIterator::CurrentAddressTable()
{
	return currentImportAddressTable;
}

bool PE::DelayImportThunkIterator::Next()
{
	if (currentImportAddressTable && currentImportNameTable)
	{
		currentImportAddressTable = reinterpret_cast<HANDLE_PTR*>(currentImportAddressTable) + 1;
		currentImportNameTable = reinterpret_cast<HANDLE_PTR*>(currentImportNameTable) + 1;
		if (*reinterpret_cast<HANDLE_PTR*>(currentImportAddressTable) &&
			*reinterpret_cast<HANDLE_PTR*>(currentImportNameTable))
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

void PE::DelayImportThunkIterator::Reset()
{
	currentImportAddressTable = NULL;
	currentImportNameTable = NULL;
}
