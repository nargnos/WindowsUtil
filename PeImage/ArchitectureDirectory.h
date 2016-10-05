#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class ArchitectureDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::Architecture>
	{
	public:
		using DirectoryBase::DirectoryBase;
	};
}  // namespace PeDecoder

