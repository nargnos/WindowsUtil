#pragma once
#include "..\PeDecoder.h"
#include "..\Import\Import.h"
#include "DelayLoadDescriptorReader.h"
#include "DelayLoadThunkReader.h"
namespace PE
{
	namespace DelayLoad
	{
		LPCSTR GetDelayloadDllName(PeDecoder& pe, PIMAGE_DELAYLOAD_DESCRIPTOR descriptor);
		PVOID GetDelayLoadAddressTableAddress(PeDecoder& pe,LPCSTR dllName, LPCSTR procName);
	}
}