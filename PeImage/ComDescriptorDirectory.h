#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class ComDescriptorDirectory :
		public Detail::DirectoryBase<ComDescriptorDirectory, DataDirectoryEntryType::ComDescriptor>
	{
	public:
		friend TBase;
	protected:
		using DirectoryBase::DirectoryBase;
	};
}  // namespace PeDecoder

