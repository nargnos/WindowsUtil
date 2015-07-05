#include "ExportReader.h"

namespace PE
{
	namespace Export{
		ExportReader::ExportReader(PeDecoder& pe) :ExportReader(pe, pe.GetImageExport())
		{
		}
		ExportReader::ExportReader(PeDecoder& pe, PIMAGE_EXPORT_DIRECTORY exportDirectory)
		{
			this->exportDirectory = exportDirectory;
			if (exportDirectory)
			{
				numberOfNames = &exportDirectory->NumberOfNames;
				numberOfFunctions = &exportDirectory->NumberOfFunctions;
				funcs = (PDWORD)pe.GetRvaData(exportDirectory->AddressOfFunctions);
				names = (PDWORD)pe.GetRvaData(exportDirectory->AddressOfNames);
				nameOrdinals = (PWORD)pe.GetRvaData(exportDirectory->AddressOfNameOrdinals);
			}
			else
			{
				numberOfNames = NULL;
				numberOfFunctions = NULL;
			}
			Reset();
		}
		ExportReader::~ExportReader(){}
		PDWORD ExportReader::FuncTable()
		{
			return funcs;
		}
		PDWORD ExportReader::NameTable()
		{
			return names;
		}
		PWORD ExportReader::OrdinalTable()
		{
			return nameOrdinals;
		}
		PDWORD ExportReader::NumberOfFunctions()
		{
			return numberOfFunctions;
		}
		PDWORD ExportReader::NumberOfNames()
		{
			return numberOfNames;
		}
		PIMAGE_EXPORT_DIRECTORY ExportReader::GetExportDirectory()
		{
			return exportDirectory;
		}

		PDWORD ExportReader::CurrentFuncRva()
		{
			if (currentIndex == -1)
			{
				return NULL;
			}
			return &funcs[nameOrdinals[currentIndex]];
		}
		PDWORD ExportReader::CurrentNameRva()
		{
			if (currentIndex == -1)
			{
				return NULL;
			}
			return &names[currentIndex];
		}
		PWORD ExportReader::CurrentNameOrdinals()
		{
			if (currentIndex == -1)
			{
				return NULL;
			}
			return &nameOrdinals[currentIndex];
		}
		bool ExportReader::Next()
		{
			if (numberOfNames)
			{
				if (++currentIndex < *numberOfNames)
				{
					return true;
				}
			}
			return false;
		}
		void ExportReader::Reset()
		{
			currentIndex = -1;
		}

		FARPROC GetProcAddress(PeDecoder& pe, LPCSTR lpProcName)
		{
			if (!pe.IsPE())
			{
				return NULL;
			}
			// 导出表名字有序, 二分
			auto er = ExportReader(pe);
			PDWORD nameTable = er.NameTable();
			DWORD right = *er.NumberOfNames();
			DWORD left = 0;
			DWORD mid;
			int cmpResult;
			while (left<=right)
			{
				mid = (left + right) >> 1;
				cmpResult = strcmp(lpProcName, (LPCSTR)pe.GetRvaData(nameTable[mid]));
				if (!cmpResult)
				{
					// 找到
					auto nameOrdinal = er.OrdinalTable()[mid];
					auto funcRva = er.FuncTable()[nameOrdinal];
					return (FARPROC)pe.GetRvaData(funcRva);
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
		FARPROC GetProcAddress(HMODULE module, LPCSTR lpProcName)
		{
			PeDecoder pe(module, true);
			return GetProcAddress(pe, lpProcName);
		}

		FARPROC GetProcAddress(PeDecoder& pe, PVOID compareName, bool compareCallback(PVOID compare, LPCSTR procName))
		{
			if (!pe.IsPE())
			{
				return NULL;
			}
			if (compareCallback == NULL)
			{
				return NULL;
			}
			ExportReader er(pe);
			while (er.Next())
			{
				auto nameRva = er.CurrentNameRva();
				if (nameRva)
				{
					auto name = (PCHAR)pe.GetRvaData(*nameRva);
					if (compareCallback(compareName, name))
					{
						return (FARPROC)pe.GetRvaData(*er.CurrentFuncRva());
					}
				}
			}
		}
		FARPROC GetProcAddress(HMODULE module, PVOID compareName, bool compareCallback(PVOID compare, LPCSTR procName))
		{
			PeDecoder pe(module, true);
			return GetProcAddress(pe, compareName, compareCallback);
		}
	}
}