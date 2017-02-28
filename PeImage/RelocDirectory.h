#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	class RelocDirectoryIterator;
	// UNDONE: 
	class RelocDirectory :
		public Detail::DirectoryBase<RelocDirectory, DataDirectoryEntryType::BaseReloc>
	{
	public:
		typedef RelocDirectoryIterator iterator;
		
		iterator begin();
		iterator end();
		friend TBase;
	protected:
		using DirectoryBase::DirectoryBase;
	};
	
}  // namespace PeDecoder
