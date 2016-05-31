#include "stdafx.h"
#include "RelocDirectory.h"
#include "RelocDirectoryIterator.h"
namespace PeDecoder
{
	RelocDirectory::RelocDirectory(PeImage & pe, TDataPtr ptr, TSizePtr sizePtr) :
		DirectoryBase(pe, ptr, sizePtr)
	{
	}
	RelocDirectory::iterator RelocDirectory::begin()
	{
		return iterator(*this, GetPtr());
	}
	RelocDirectory::iterator RelocDirectory::end()
	{
		return iterator(*this, GetPtr() + GetSize() / sizeof(IMAGE_BASE_RELOCATION));
	}
}  // namespace PeDecoder
