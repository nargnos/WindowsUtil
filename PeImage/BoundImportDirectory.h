#pragma once
#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class BoundImportDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::BoundImport>
	{
	public:
		BoundImportDirectory(PeImage& pe, TDataPtr ptr, TSizePtr sizePtr);
		~BoundImportDirectory() = default;
	};
}  // namespace PeDecoder

