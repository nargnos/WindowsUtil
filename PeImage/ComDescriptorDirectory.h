#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class ComDescriptorDirectory :
		public DirectoryBase<DataDirectoryEntryType::ComDescriptor>
	{
	public:
		ComDescriptorDirectory(PeImage& pe, TDataPtr ptr, TSizePtr sizePtr);
		~ComDescriptorDirectory() = default;
	};
}  // namespace PeDecoder

