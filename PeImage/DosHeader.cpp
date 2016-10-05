#include "stdafx.h"
#include "DosHeader.h"
namespace PeDecoder
{
	bool DosHeader::Valid(const PIMAGE_DOS_HEADER ptr)
	{
		assert(ptr);
		return ptr->e_magic == IMAGE_DOS_SIGNATURE;
	}

	bool DosHeader::Valid() const
	{
		return Valid(GetPtr());
	}


}  // namespace PeDecoder
