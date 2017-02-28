#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	class ResourceEntryIterator;
	// UNDONE: 
	class ResourceDirectory :
		public Detail::DirectoryBase<ResourceDirectory, DataDirectoryEntryType::Resource>
	{
	public:
		ResourceEntryIterator begin();
		ResourceEntryIterator end();
		
		friend TBase;
	protected:
		using DirectoryBase::DirectoryBase;
	};
}  // namespace PeDecoder
