#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	class DelayImportDescriptorIterator;
	// UNDONE: 
	class DelayImportDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::DelayImport>
	{
	public:
		typedef DelayImportDescriptorIterator iterator;
		using DirectoryBase::DirectoryBase;
		iterator begin();
		iterator end();
	};
	
}  // namespace PeDecoder
