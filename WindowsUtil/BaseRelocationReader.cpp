#include "BaseRelocationReader.h"
namespace PE
{

	BaseRelocationReader::BaseRelocationReader(PIMAGE_BASE_RELOCATION reloc, DWORD relocSize) 
		:reloc(reloc), endReloc(reloc + (relocSize / sizeof(IMAGE_BASE_RELOCATION)))
	{
		Reset();
	}


	BaseRelocationReader::~BaseRelocationReader()
	{
	}
	bool BaseRelocationReader::Next()
	{
		if (currentReloc)
		{
			auto tmpReloc = PIMAGE_BASE_RELOCATION((PCHAR)currentReloc + currentReloc->SizeOfBlock);
			if (tmpReloc<endReloc)
			{
				currentReloc = tmpReloc;
				return true;
			}
		}
		else
		{
			currentReloc = reloc;
			return true;
		}
		return false;
	}
	PIMAGE_BASE_RELOCATION BaseRelocationReader::Current()
	{
		return currentReloc;
	}
	void BaseRelocationReader::Reset()
	{
		currentReloc = NULL;
	}
	
	
}