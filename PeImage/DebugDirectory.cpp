#include "stdafx.h"
#include "DebugDirectory.h"

namespace PeDecoder
{
	DebugDirectory::DebugDirectory(PeImage & pe) :
		DirectoryBase(pe)
	{
	}
}  // namespace PeDecoder
