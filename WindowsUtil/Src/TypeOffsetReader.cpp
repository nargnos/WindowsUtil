#include <PE\Reloc\TypeOffsetReader.h>
namespace PE
{
	namespace Reloc
	{
		TypeOffsetReader::TypeOffsetReader()
		{
			typeOffset = NULL;
		}
		TypeOffsetReader::TypeOffsetReader(PIMAGE_BASE_RELOCATION reloc)
		{
			Init(reloc);

		}
		TypeOffsetReader::~TypeOffsetReader()
		{
		}
		void TypeOffsetReader::Init(PIMAGE_BASE_RELOCATION reloc)
		{
			virtualAddress = reloc->VirtualAddress;
			typeOffset = PWORD((PCHAR)reloc + sizeof(IMAGE_BASE_RELOCATION));
			endTypeOffset = typeOffset + ((reloc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD));
			Reset();
		}
		PWORD TypeOffsetReader::Current()
		{
			return currentTypeOffset;
		}


		bool TypeOffsetReader::Next()
		{
			if (!typeOffset)
			{
				return false;
			}
			if (!currentTypeOffset)
			{
				currentTypeOffset = typeOffset;
				return true;
			}
			if (++currentTypeOffset < endTypeOffset)
			{
				return true;
			}
			return false;
		}
		void TypeOffsetReader::Reset()
		{
			currentTypeOffset = NULL;
		}

		WORD TypeOffsetReader::CurrentType()
		{
			return (*currentTypeOffset) >> 12;
		}
		DWORD TypeOffsetReader::CurrentRelocRva()
		{
			return ((*currentTypeOffset) & 0xFFF) + virtualAddress;
		}
		void TypeOffsetReader::ApplyCurrentReloc(PVOID oldBase, PVOID currentBase)
		{
			auto oldValAddr = PVOID((PCHAR)currentBase + CurrentRelocRva());
			auto baseDelta = (PUINT8)currentBase - (PUINT8)oldBase;

			// oldValAddr + baseDelta = 要应用的值
			// 应用方式		
			switch (CurrentType())
			{
			case IMAGE_REL_BASED_HIGH:
				*PWORD(oldValAddr) = HIWORD(MAKELONG(0, *PWORD(oldValAddr)) + (baseDelta & MAXDWORD));
				break;

			case IMAGE_REL_BASED_LOW:
				*PWORD(oldValAddr) = *PWORD(oldValAddr) + LOWORD(baseDelta & MAXWORD);
				break;

			case IMAGE_REL_BASED_HIGHLOW:
				*PDWORD(oldValAddr) = *PDWORD(oldValAddr) + (baseDelta & MAXDWORD);
				break;

			case IMAGE_REL_BASED_DIR64:
				*PDWORDLONG(oldValAddr) = *PDWORDLONG(oldValAddr) + baseDelta;
				break;
			case IMAGE_REL_BASED_ABSOLUTE:
				// 末尾标识不处理
				break;
			default:
				break;
			}
		}
	}
}