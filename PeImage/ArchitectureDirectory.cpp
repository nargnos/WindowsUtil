#include "stdafx.h"
#include "ArchitectureDirectory.h"

namespace PeDecoder
{
	ArchitectureDirectory::ArchitectureDirectory(PeImage& pe) :
		DirectoryBase(pe)
	{
	}


	ArchitectureDirectory::~ArchitectureDirectory()
	{
	}

}  // namespace PeDecoder

