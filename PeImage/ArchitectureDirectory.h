#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class ArchitectureDirectory :
		public Detail::DirectoryBase<ArchitectureDirectory, DataDirectoryEntryType::Architecture>
	{
	public:
		friend TBase;
	protected:
		using DirectoryBase::DirectoryBase;
	};
}  // namespace PeDecoder

