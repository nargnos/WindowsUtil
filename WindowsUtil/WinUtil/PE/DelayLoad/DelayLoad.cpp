#include "DelayLoad.h"

namespace PE
{
	namespace DelayLoad
	{

		LPCSTR GetDelayloadDllName(PeDecoder& pe, PImgDelayDescr descriptor)
		{
			assert(descriptor != NULL);
			return (LPCSTR)pe.GetRvaData(descriptor->rvaDLLName);
		}
		PVOID GetDelayLoadAddressTableAddress(PeDecoder& pe,LPCSTR dllName, LPCSTR procName)
		{
			assert(dllName != NULL&&procName != NULL);
			PE::DelayLoad::DelayLoadDescriptorReader ddr(pe);
			PE::DelayLoad::DelayLoadThunkReader dtr;
			while (ddr.Next())
			{
				auto curDdr = ddr.Current();
				auto currentDllName = PE::DelayLoad::GetDelayloadDllName(pe, curDdr);
				if (_stricmp(currentDllName, dllName))
				{
					continue;
				}
				dtr.Init(pe, curDdr);
				while (dtr.Next())
				{
					auto curNameTable = dtr.CurrentNameTable();
					PIMAGE_IMPORT_BY_NAME funcName = NULL;
					if (pe.hasNtHeader32)
					{
						if (!PE::Import::IsSnapByOrdinal((PIMAGE_THUNK_DATA32)curNameTable))
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
						if (!PE::Import::IsSnapByOrdinal((PIMAGE_THUNK_DATA64)curNameTable))
						{
							funcName = (PIMAGE_IMPORT_BY_NAME)pe.GetRvaData(*(HANDLE_PTR*)curNameTable);
						}
					}
					if (funcName && (strcmp((char*)funcName->Name, procName) == 0))
					{
						return dtr.CurrentAddressTable();
					}
				}
			}
			return NULL;
		}
	}
}