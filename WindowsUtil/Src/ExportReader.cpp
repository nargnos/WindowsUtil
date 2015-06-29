#include <PE\Export\ExportReader.h>

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
				numberOfFunctions = &exportDirectory->NumberOfFunctions;
				funcs = (PDWORD)pe.GetRvaData(exportDirectory->AddressOfFunctions);
				names = (PDWORD)pe.GetRvaData(exportDirectory->AddressOfNames);
				nameOrdinals = (PWORD)pe.GetRvaData(exportDirectory->AddressOfNameOrdinals);
			}
			else
			{
				numberOfFunctions = NULL;
			}
			Reset();
		}
		ExportReader::~ExportReader(){}
		PIMAGE_EXPORT_DIRECTORY ExportReader::GetExportDirectory()
		{
			return exportDirectory;
		}
		// ERROR: 这里不是这么读的, 在读user32时出错了,namerva结果不正确
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
			return &names[nameOrdinals[currentIndex]];
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
			if (numberOfFunctions)
			{
				if (++currentIndex < *numberOfFunctions)
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
			return GetProcAddress(pe, (PVOID)lpProcName,
				[](PVOID compare, LPSTR procName)
			{
				if (strcmp((PCHAR)compare, procName) == 0)
				{
					return true;
				}
				return false;
			});
		}
		FARPROC GetProcAddress(HMODULE module, LPCSTR lpProcName)
		{
			PeDecoder pe(module,true);
			return GetProcAddress(pe, lpProcName);
		}

		FARPROC GetProcAddress(PeDecoder& pe, PVOID compareName, bool compareCallback(PVOID compare, LPSTR procName))
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
		FARPROC GetProcAddress(HMODULE module, PVOID compareName,bool compareCallback(PVOID compare, LPSTR procName))
		{
			PeDecoder pe(module, true);
			return GetProcAddress(pe, compareName, compareCallback);
		}
	}
}