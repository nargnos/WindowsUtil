#pragma once
#include "../Common/Common.h"
namespace PE
{
	template<typename _BaseRelocationIterator>
	class TypeOffsetIterator :
		public IIterator<PWORD>
	{
	public:
		TypeOffsetIterator(_BaseRelocationIterator& baseRelocationIterator)
		{
			Init(baseRelocationIterator.currentReloc);
		}
		~TypeOffsetIterator() {}

		PWORD Current()
		{
			return currentTypeOffset;
		}
		bool Next()
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
		void Reset()
		{
			currentTypeOffset = NULL;
		}
		WORD CurrentType()
		{
			return (*currentTypeOffset) >> 12;
		}
		DWORD CurrentRelocRva()
		{
			return ((*currentTypeOffset) & 0xFFF) + virtualAddress;
		}
		void ApplyCurrentReloc(PVOID oldBase, PVOID currentBase)// 当程序已经映射完毕后不要使用
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

		static void RelocHighLow(PVOID oldBase, PVOID currentBase, DWORD relocRva)
		{
			auto baseDelta = (PUINT8)currentBase - (PUINT8)oldBase;
			auto currentRelocAddress = PDWORD((PUINT8)currentBase + relocRva);
			*currentRelocAddress = *currentRelocAddress + (baseDelta & MAXDWORD);
		}
		static void RelocLow(PVOID oldBase, PVOID currentBase, DWORD relocRva)
		{
			// FIX: 这里不确定
			/*auto baseDelta = (PUINT8)currentBase - (PUINT8)oldBase;
			auto currentRelocAddress = PWORD((PUINT8)currentBase + relocRva);
			*currentRelocAddress = *currentRelocAddress + LOWORD(baseDelta & MAXWORD);*/
		}
		static void RelocHigh(PVOID oldBase, PVOID currentBase, DWORD relocRva)
		{
			/*auto baseDelta = (PUINT8)currentBase - (PUINT8)oldBase;
			auto currentRelocAddress = PWORD((PUINT8)currentBase + relocRva);
			*currentRelocAddress = HIWORD(MAKELONG(0, *currentRelocAddress) + (baseDelta & MAXDWORD));*/
		}
		static void RelocDir64(PVOID oldBase, PVOID currentBase, DWORD relocRva)
		{
			auto baseDelta = (PUINT8)currentBase - (PUINT8)oldBase;
			auto currentRelocAddress = PDWORDLONG((PUINT8)currentBase + relocRva);
			*currentRelocAddress = *currentRelocAddress + baseDelta;
		}
	private:
		DWORD virtualAddress;
		PWORD endTypeOffset;
		PWORD typeOffset;
		PWORD currentTypeOffset;

		PIMAGE_BASE_RELOCATION currentReloc;
		void Init(PIMAGE_BASE_RELOCATION reloc)
		{
			assert(reloc);
			currentReloc = reloc;
			virtualAddress = reloc->VirtualAddress;
			typeOffset = PWORD((PUINT8)reloc + sizeof(IMAGE_BASE_RELOCATION));
			endTypeOffset = typeOffset + ((reloc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD));
			Reset();
		}

	};



}