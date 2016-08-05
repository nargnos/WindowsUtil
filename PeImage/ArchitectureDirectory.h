#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class ArchitectureDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::Architecture>
	{
	public:
		ArchitectureDirectory(PeImage& pe);
		~ArchitectureDirectory();
	};
}  // namespace PeDecoder

