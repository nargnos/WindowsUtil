#pragma once
namespace PeDecoder
{
	DWORD GetRelocCount(DWORD sizeOfBlock);
	PWORD GetBeginPtr(PIMAGE_BASE_RELOCATION ptr);
	PWORD GetEndPtr(PIMAGE_BASE_RELOCATION ptr);
}  // namespace PeDecoder
