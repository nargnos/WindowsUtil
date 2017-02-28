#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	class DelayImportDescriptorIterator;
	// UNDONE: 
	class DelayImportDirectory :
		public Detail::DirectoryBase<DelayImportDirectory, DataDirectoryEntryType::DelayImport>
	{
	public:
		typedef DelayImportDescriptorIterator iterator;
		iterator begin();
		iterator end();
	
		friend TBase;
	protected:
		using DirectoryBase::DirectoryBase;
	};
	
}  // namespace PeDecoder
