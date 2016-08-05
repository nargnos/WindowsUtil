#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class ComDescriptorDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::ComDescriptor>
	{
	public:
		ComDescriptorDirectory(PeImage& pe);
		~ComDescriptorDirectory() = default;
	};
}  // namespace PeDecoder

