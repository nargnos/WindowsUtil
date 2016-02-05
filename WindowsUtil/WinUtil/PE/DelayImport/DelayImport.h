#pragma once
#include "..\PeImage.h"
#include "..\Import\Import.h"
namespace PE
{
	LPCSTR GetDelayloadDllName(PeDecoder & pe, PImgDelayDescr descriptor);
	PVOID GetDelayLoadAddressTableAddress(PeDecoder & pe, LPCSTR dllName, LPCSTR procName);
}  // namespace PE
