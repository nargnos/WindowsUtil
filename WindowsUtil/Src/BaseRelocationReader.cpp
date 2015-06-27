#include <PE\Reloc\BaseRelocationReader.h>
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
			auto dir = pe.GetDataDirectory(IMAGE_DIRECTORY_ENTRY_BASERELOC);
			if (dir==NULL)
			{
				return;
			}
			new(this) BaseRelocationReader(pe.GetImageBasereloc(), dir->Size);
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