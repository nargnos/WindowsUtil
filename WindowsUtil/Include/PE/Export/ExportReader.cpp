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

	
	}
}