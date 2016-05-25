#include "stdafx.h"
#include "DebugDirectory.h"

namespace PeDecoder
{
	DebugDirectory::DebugDirectory(PeImage & pe, TDataPtr ptr, TSizePtr sizePtr) :
		DirectoryBase(pe, ptr, sizePtr)
	{
	}
}  // namespace PeDecoder
