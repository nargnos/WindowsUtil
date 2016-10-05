#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class ComDescriptorDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::ComDescriptor>
	{
	public:
		
		using DirectoryBase::DirectoryBase;
	};
}  // namespace PeDecoder

