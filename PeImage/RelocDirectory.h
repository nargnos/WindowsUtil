#pragma once
#include "PeImageFwd.h"
#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class RelocDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::BaseReloc>
	{
	public:
		typedef RelocDirectoryIterator iterator;
		using DirectoryBase::DirectoryBase;
		iterator begin();
		iterator end();
	};
	
}  // namespace PeDecoder
