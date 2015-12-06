#include "ExportIterator.h"

namespace PE
{
	
	/*	ExportIterator::ExportIterator(PeDecoder& pe) :ExportIterator(pe, pe.GetImageExport())
		{
		}
		ExportIterator::ExportIterator(PeDecoder& pe, PIMAGE_EXPORT_DIRECTORY exportDirectory)
		{
			assert(exportDirectory != NULL);
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
		ExportIterator::~ExportIterator(){}
		PDWORD ExportIterator::FuncTable()
		{
			return funcs;
		}
		PDWORD ExportIterator::NameTable()
		{
			return names;
		}
		PWORD ExportIterator::OrdinalTable()
		{
			return nameOrdinals;
		}
		PDWORD ExportIterator::NumberOfFunctions()
		{
			return numberOfFunctions;
		}
		PDWORD ExportIterator::NumberOfNames()
		{
			return numberOfNames;
		}
		PIMAGE_EXPORT_DIRECTORY ExportIterator::GetExportDirectory()
		{
			return exportDirectory;
		}

		PDWORD ExportIterator::CurrentFuncRva()
		{
			if (currentIndex == -1)
			{
				return NULL;
			}
			return &funcs[nameOrdinals[currentIndex]];
		}
		PDWORD ExportIterator::CurrentNameRva()
		{
			if (currentIndex == -1)
			{
				return NULL;
			}
			return &names[currentIndex];
		}
		PWORD ExportIterator::CurrentNameOrdinals()
		{
			if (currentIndex == -1)
			{
				return NULL;
			}
			return &nameOrdinals[currentIndex];
		}
		bool ExportIterator::Next()
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
		void ExportIterator::Reset()
		{
			currentIndex = -1;
		}*/
	
}