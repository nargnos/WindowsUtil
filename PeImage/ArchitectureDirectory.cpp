#include "stdafx.h"
#include "ArchitectureDirectory.h"

namespace PeDecoder
{
	ArchitectureDirectory::ArchitectureDirectory(PeImage& pe, TDataPtr ptr, TSizePtr sizePtr) :
		DirectoryBase(pe, ptr, sizePtr)
	{
	}


	ArchitectureDirectory::~ArchitectureDirectory()
	{
	}

}  // namespace PeDecoder

