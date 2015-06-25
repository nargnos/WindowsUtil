#include "TypeOffsetReader.h"
namespace PE
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
		if (++currentTypeOffset<endTypeOffset)
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
		auto baseDelta = (PCHAR)currentBase - (PCHAR)oldBase;
		// Fix: 这里指针长度在64位会出问题
		// oldValAddr + baseDelta = 要应用的值
		// 应用方式
		switch (CurrentType())
		{
		case IMAGE_REL_BASED_HIGH:
#define HIWORD(x) ((WORD)(((DWORD_PTR)(x) >> 16) & 0xFFFF))
				*ShortPtr = HIWORD(MAKELONG(0, *ShortPtr) + (baseDelta & 0xFFFFFFFF));
			break;

		case IMAGE_REL_BASED_LOW:
			*ShortPtr = SWAPW(*ShortPtr) + LOWORD(baseDelta & 0xFFFF);
			break;

		case IMAGE_REL_BASED_HIGHLOW:
			LongPtr = (PULONG)RVA(Address, Offset);
			*LongPtr = SWAPD(*LongPtr) + (baseDelta & 0xFFFFFFFF);
			break;

		case IMAGE_REL_BASED_DIR64:
			LongLongPtr = (PUINT64)RVA(Address, Offset);
			*LongLongPtr = SWAPQ(*LongLongPtr) + baseDelta;
			break;
		case IMAGE_REL_BASED_ABSOLUTE:
		case IMAGE_REL_BASED_HIGHADJ:
		case IMAGE_REL_BASED_MIPS_JMPADDR:
		default:
			break;
		}
	}
}