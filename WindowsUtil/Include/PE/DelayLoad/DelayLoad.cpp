#include "DelayLoad.h"

namespace PE
{
	namespace DelayLoad
	{

		LPCSTR GetDelayloadDllName(PeDecoder& pe, PIMAGE_DELAYLOAD_DESCRIPTOR descriptor)
		{
			return (LPCSTR)pe.GetRvaData(descriptor->DllNameRVA);
		}
		PVOID GetDelayLoadAddressTableAddress(PeDecoder& pe,LPCSTR dllName, LPCSTR procName)
		{
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
					if (pe.HasNtHeader32())
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
					if (funcName && (strcmp(funcName->Name, procName) == 0))
					{
						return dtr.CurrentAddressTable();
					}
				}
			}
			return NULL;
		}
	}
}