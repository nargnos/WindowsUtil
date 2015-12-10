#include "DelayImport.h"

LPCSTR PE::GetDelayloadDllName(PeDecoder & pe, PImgDelayDescr descriptor)
{
	assert(descriptor != NULL);
	return (LPCSTR)pe.GetRvaData(descriptor->rvaDLLName);
}

PVOID PE::GetDelayLoadAddressTableAddress(PeDecoder & pe, LPCSTR dllName, LPCSTR procName)
{
	assert(dllName != NULL&&procName != NULL);
	auto delayImport = pe.GetDelayImport();
	if (!delayImport->IsExist())
	{
		return NULL;
	}
	auto ddr = delayImport->CreateIterator();

	while (ddr->Next())
	{
		auto curDdr = ddr->Current();
		auto currentDllName = PE::GetDelayloadDllName(pe, curDdr);
		if (_stricmp(currentDllName, dllName))
		{
			continue;
		}
		auto dtr = ddr->CreateIterator();
		while (dtr->Next())
		{
			auto curNameTable = dtr->CurrentNameTable();
			PIMAGE_IMPORT_BY_NAME funcName = NULL;
			if (pe.HasNtHeader32())
			{
				if (!PE::IsSnapByOrdinal((PIMAGE_THUNK_DATA32)curNameTable))
				{
					funcName = (PIMAGE_IMPORT_BY_NAME)pe.GetRvaData(*(HANDLE_PTR*)curNameTable);

				}
				//else
				//{
				//	auto curOrd = PE::Import::GetOrdinal(curNameTable);
				//	
				//}
			}
			else
			{
				if (!PE::IsSnapByOrdinal((PIMAGE_THUNK_DATA64)curNameTable))
				{
					funcName = (PIMAGE_IMPORT_BY_NAME)pe.GetRvaData(*(HANDLE_PTR*)curNameTable);
				}
			}
			if (funcName && (strcmp((char*)funcName->Name, procName) == 0))
			{
				return dtr->CurrentAddressTable();
			}
		}
	}
	return NULL;
}
