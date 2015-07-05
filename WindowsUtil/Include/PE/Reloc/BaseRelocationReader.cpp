#include "BaseRelocationReader.h"
#include <new>
namespace PE
{
	namespace Reloc{
		BaseRelocationReader::BaseRelocationReader(PIMAGE_BASE_RELOCATION reloc, DWORD relocSize)
			:reloc(reloc), endReloc(reloc + (relocSize / sizeof(IMAGE_BASE_RELOCATION)))
		{
			Reset();
		}
		BaseRelocationReader::BaseRelocationReader(PeDecoder& pe)
		{
			PDWORD size;
			auto reloc = pe.GetImageBasereloc(&size);
			if (reloc)
			{
				new(this) BaseRelocationReader(reloc, *size);
			}
		}

		BaseRelocationReader::~BaseRelocationReader()
		{
		}
		bool BaseRelocationReader::Next()
		{
			if (!reloc)
			{
				return false;
			}
			if (currentReloc)
			{
				auto tmpReloc = PIMAGE_BASE_RELOCATION((PUINT8)currentReloc + currentReloc->SizeOfBlock);
				if (tmpReloc < endReloc)
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
}