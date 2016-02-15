#include "Export.h"
namespace PE
{

	PDWORD GetProcExportFuncTableAddress(PeDecoder* pe, LPCSTR lpProcName)
	{
		assert(pe!=NULL && lpProcName != NULL);
		if (!pe->IsPE())
		{
			return NULL;
		}
		// 导出表名字有序, 二分
		auto er = pe->GetExport();
		PDWORD nameTable = er->NameTable();
		DWORD right = *er->NumberOfNames();
		DWORD left = 0;
		DWORD mid;
		int cmpResult;
		while (left <= right)
		{
			mid = (left + right) >> 1;
			cmpResult = strcmp(lpProcName, (LPCSTR)pe->GetRvaData(nameTable[mid]));
			if (!cmpResult)
			{
				// 找到
				auto nameOrdinal = er->OrdinalTable()[mid];
				return &er->FuncTable()[nameOrdinal];
			}
			if (cmpResult < 0)
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		}
		return NULL;
	}
	FARPROC GetProcAddress(PeDecoder* pe, LPCSTR lpProcName)
	{
		auto result = GetProcExportFuncTableAddress(pe, lpProcName);
		if (!result)
		{
			return NULL;
		}
		return (FARPROC)pe->GetRvaData(*result);
	}
	FARPROC GetProcAddress(HMODULE module, LPCSTR lpProcName)
	{
		PeDecoder pe;
		if (!pe.Attach(module, true))
		{
			return NULL;
		}
		return GetProcAddress(&pe, lpProcName);
	}

	FARPROC GetProcAddress(PeDecoder* pe, PVOID compareName, bool compareCallback(PVOID compare, LPCSTR procName))
	{
		assert(compareCallback != NULL && compareName != NULL);
		if (!pe->IsPE())
		{
			return NULL;
		}
		auto er = pe->GetExport()->CreateIterator();
		while (er->Next())
		{
			auto nameRva = er->CurrentNameRva();
			if (nameRva)
			{
				auto name = (PCHAR)pe->GetRvaData(*nameRva);
				if (compareCallback(compareName, name))
				{
					return (FARPROC)pe->GetRvaData(*er->CurrentFuncRva());
				}
			}
		}
		return NULL;
	}
	FARPROC GetProcAddress(HMODULE module, PVOID compareName, bool compareCallback(PVOID compare, LPCSTR procName))
	{
		PeDecoder pe;
		if (!pe.Attach(module, true))
		{
			return NULL;
		}
		return GetProcAddress(&pe, compareName, compareCallback);
	}
}  // namespace PE
