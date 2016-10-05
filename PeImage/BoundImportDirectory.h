#pragma once
#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class BoundImportDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::BoundImport>
	{
	public:
		
		using DirectoryBase::DirectoryBase;
	};
}  // namespace PeDecoder

