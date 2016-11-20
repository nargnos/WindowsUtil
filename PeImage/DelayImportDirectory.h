#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	class DelayImportDirectoryIterator;
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
