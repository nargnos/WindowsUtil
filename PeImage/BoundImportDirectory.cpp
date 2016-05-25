#include "stdafx.h"
#include "BoundImportDirectory.h"

namespace PeDecoder
{
	BoundImportDirectory::BoundImportDirectory(PeImage & pe, TDataPtr ptr, TSizePtr sizePtr) :
		DirectoryBase(pe, ptr, sizePtr)
	{
	}
}  // namespace PeDecoder
