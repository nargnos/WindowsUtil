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
		ResourceDirectory(PeImage& pe) :
			DirectoryBase(pe)
		{
			
		}
		ResourceEntryIterator begin();
		ResourceEntryIterator end();

	protected:

	};
}  // namespace PeDecoder
