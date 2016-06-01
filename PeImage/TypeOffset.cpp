#include "stdafx.h"
#include "TypeOffset.h"



namespace PeDecoder
{

	TypeOffset::TypeOffset(PeImage & pe, PIMAGE_BASE_RELOCATION baseReloc, PWORD ptr) :
		pe_(&pe),
		baseReloc_(baseReloc),
		ptr_(ptr)
	{

	}

	PWORD TypeOffset::GetPtr() const
	{
		return ptr_;
	}

	WORD TypeOffset::CurrentType()
	{
		return (*ptr_) >> 12;
	}

	DWORD TypeOffset::CurrentRelocRva()
	{
		return ((*ptr_) & 0xFFF) + baseReloc_->VirtualAddress;
	}

	// 下面函数会修改pe

	void TypeOffset::ApplyCurrentReloc(PVOID oldBase, PVOID currentBase)  // 当程序已经映射完毕后不要使用
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

	void TypeOffset::RelocHighLow(PVOID oldBase, PVOID currentBase, DWORD relocRva)
	{
		auto baseDelta = (PUINT8)currentBase - (PUINT8)oldBase;
		auto currentRelocAddress = PDWORD((PUINT8)currentBase + relocRva);
		*currentRelocAddress = *currentRelocAddress + (baseDelta & MAXDWORD);
	}

	void TypeOffset::RelocLow(PVOID oldBase, PVOID currentBase, DWORD relocRva)
	{
		// FIX: 这里不确定
		/*auto baseDelta = (PUINT8)currentBase - (PUINT8)oldBase;
		auto currentRelocAddress = PWORD((PUINT8)currentBase + relocRva);
		*currentRelocAddress = *currentRelocAddress + LOWORD(baseDelta & MAXWORD);*/
	}

	void TypeOffset::RelocHigh(PVOID oldBase, PVOID currentBase, DWORD relocRva)
	{
		/*auto baseDelta = (PUINT8)currentBase - (PUINT8)oldBase;
		auto currentRelocAddress = PWORD((PUINT8)currentBase + relocRva);
		*currentRelocAddress = HIWORD(MAKELONG(0, *currentRelocAddress) + (baseDelta & MAXDWORD));*/
	}

	void TypeOffset::RelocDir64(PVOID oldBase, PVOID currentBase, DWORD relocRva)
	{
		auto baseDelta = (PUINT8)currentBase - (PUINT8)oldBase;
		auto currentRelocAddress = PDWORDLONG((PUINT8)currentBase + relocRva);
		*currentRelocAddress = *currentRelocAddress + baseDelta;
	}

}  // namespace PeDecoder
