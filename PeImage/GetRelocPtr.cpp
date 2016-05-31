#include "stdafx.h"
#include "GetRelocPtr.h"

namespace PeDecoder
{
	DWORD GetRelocCount(DWORD sizeOfBlock)
	{ 
		return (sizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);
	}
	PWORD GetBeginPtr(PIMAGE_BASE_RELOCATION ptr)
	{
		return reinterpret_cast<PWORD>(reinterpret_cast<unsigned char*>(ptr) + sizeof(IMAGE_BASE_RELOCATION));
	}
	PWORD GetEndPtr(PIMAGE_BASE_RELOCATION ptr)
	{
		return GetBeginPtr(ptr) + GetRelocCount(ptr->SizeOfBlock);
	}
	
}  // namespace PeDecoder
