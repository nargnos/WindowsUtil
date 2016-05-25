#include "stdafx.h"
#include "ComDescriptorDirectory.h"

namespace PeDecoder
{
	ComDescriptorDirectory::ComDescriptorDirectory(PeImage & pe, TDataPtr ptr, TSizePtr sizePtr) :
		DirectoryBase(pe, ptr, sizePtr)
	{
	}
}  // namespace PeDecoder
