#include "DelayLoadThunkReader.h"

namespace PE
{
	namespace DelayLoad
	{
		DelayLoadThunkReader::DelayLoadThunkReader(PeDecoder& pe, PImgDelayDescr descriptor)
		{
			Init(pe, descriptor);
		}
		DelayLoadThunkReader::DelayLoadThunkReader()
		{
			Reset();
		}
		void DelayLoadThunkReader::Init(PeDecoder& pe, PImgDelayDescr descriptor)
		{
			assert(descriptor != NULL);
			this->descriptor = descriptor;
			importAddressTable = pe.GetRvaData(descriptor->rvaIAT);
			importNameTable = pe.GetRvaData(descriptor->rvaINT);
			Reset();
		}

		DelayLoadThunkReader::~DelayLoadThunkReader()
		{
		}
		PVOID DelayLoadThunkReader::CurrentNameTable()
		{
			return currentImportNameTable;
		}
		PVOID DelayLoadThunkReader::CurrentAddressTable()
		{
			return currentImportAddressTable;
		}
		bool DelayLoadThunkReader::Next()
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
		void DelayLoadThunkReader::Reset()
		{
			currentImportAddressTable = NULL;
			currentImportNameTable = NULL;
		}
	}
}