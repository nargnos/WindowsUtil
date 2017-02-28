#pragma once
#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class BoundImportDirectory :
		public Detail::DirectoryBase<BoundImportDirectory, DataDirectoryEntryType::BoundImport>
	{
	public:
		friend TBase;
	protected:
		using DirectoryBase::DirectoryBase;
	};
}  // namespace PeDecoder

