#include "TypeOffsetReader.h"
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
			assert(reloc);
			virtualAddress = reloc->VirtualAddress;
			typeOffset = PWORD((PUINT8)reloc + sizeof(IMAGE_BASE_RELOCATION));
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
			// oldValAddr + baseDelta = 要应用的值
			// 应用方式		
			switch (CurrentType())
			{
			case IMAGE_REL_BASED_HIGH:
				RelocHigh(oldBase, currentBase, CurrentRelocRva());
				break;
			case IMAGE_REL_BASED_LOW:
				RelocLow(oldBase, currentBase, CurrentRelocRva());
				break;
			case IMAGE_REL_BASED_HIGHLOW:
				RelocHighLow(oldBase, currentBase, CurrentRelocRva());
				break;
			case IMAGE_REL_BASED_DIR64:
				RelocDir64(oldBase, currentBase, CurrentRelocRva());
				break;
			case IMAGE_REL_BASED_ABSOLUTE:
				// 末尾标识不处理
				break;
			default:
				break;
			}
		}
		void RelocLow(PVOID oldBase, PVOID currentBase, DWORD relocRva)
		{
			// FIX: 这里不确定
			/*auto baseDelta = (PUINT8)currentBase - (PUINT8)oldBase;
			auto currentRelocAddress = PWORD((PUINT8)currentBase + relocRva);
			*currentRelocAddress = *currentRelocAddress + LOWORD(baseDelta & MAXWORD);*/
		}
		void RelocHigh(PVOID oldBase, PVOID currentBase, DWORD relocRva)
		{
			/*auto baseDelta = (PUINT8)currentBase - (PUINT8)oldBase;
			auto currentRelocAddress = PWORD((PUINT8)currentBase + relocRva);
			*currentRelocAddress = HIWORD(MAKELONG(0, *currentRelocAddress) + (baseDelta & MAXDWORD));*/
		}

		void RelocHighLow(PVOID oldBase, PVOID currentBase, DWORD relocRva)
		{
			auto baseDelta = (PUINT8)currentBase - (PUINT8)oldBase;
			auto currentRelocAddress = PDWORD((PUINT8)currentBase + relocRva);
			*currentRelocAddress = *currentRelocAddress + (baseDelta & MAXDWORD);
		}
		void RelocDir64(PVOID oldBase, PVOID currentBase, DWORD relocRva)
		{
			auto baseDelta = (PUINT8)currentBase - (PUINT8)oldBase;
			auto currentRelocAddress = PDWORDLONG((PUINT8)currentBase + relocRva);
			*currentRelocAddress = *currentRelocAddress + baseDelta;
		}

	}
}