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
		ResourceDirectory(PeImage& pe, TDataPtr ptr, TSizePtr sizePtr) :
			DirectoryBase(pe, ptr, sizePtr)
		{
			
		}
		ResourceEntryIterator begin();
		ResourceEntryIterator end();

	protected:

	};
}  // namespace PeDecoder
