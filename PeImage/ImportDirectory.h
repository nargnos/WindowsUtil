#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	class ImportDescriptorIterator;
	// UNDONE: 
	class ImportDirectory :
		public Detail::DirectoryBase<ImportDirectory, DataDirectoryEntryType::Import>
	{
	public:
		typedef ImportDescriptorIterator iterator;
		// 这里的size表示整个结构包括thunk和name的大小
		iterator begin();
		iterator end();
	
		friend TBase;
	protected:
		using DirectoryBase::DirectoryBase;
	};

	

}  // namespace PeDecoder
