#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	class ResourceEntryIterator;
	// UNDONE: 
	class ResourceDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::Resource>
	{
	public:
		using DirectoryBase::DirectoryBase;
		ResourceEntryIterator begin();
		ResourceEntryIterator end();

	protected:

	};
}  // namespace PeDecoder
