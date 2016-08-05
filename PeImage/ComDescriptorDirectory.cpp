#include "stdafx.h"
#include "ComDescriptorDirectory.h"

namespace PeDecoder
{
	ComDescriptorDirectory::ComDescriptorDirectory(PeImage & pe) :
		DirectoryBase(pe)
	{
	}
}  // namespace PeDecoder
