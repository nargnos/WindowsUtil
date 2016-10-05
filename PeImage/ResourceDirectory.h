#pragma once

#include "DirectoryBase.h"
#include "PeImageFwd.h"
namespace PeDecoder
{
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
