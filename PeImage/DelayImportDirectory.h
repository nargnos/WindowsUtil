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
		DelayImportDirectory(PeImage& pe);
		iterator begin();
		iterator end();
	};
	
}  // namespace PeDecoder
