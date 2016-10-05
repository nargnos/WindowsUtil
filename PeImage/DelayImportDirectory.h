#pragma once
#include "PeImageFwd.h"
#include "DirectoryBase.h"
namespace PeDecoder
{

	// UNDONE: 
	class DelayImportDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::DelayImport>
	{
	public:
		typedef DelayImportDirectoryIterator iterator;
		using DirectoryBase::DirectoryBase;
		iterator begin();
		iterator end();
	};
	
}  // namespace PeDecoder
