#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class DebugDirectory :
		public DirectoryBase<DataDirectoryEntryType::Debug>
	{
	public:
		DebugDirectory(PeImage& pe, TDataPtr ptr, TSizePtr sizePtr);
		~DebugDirectory() = default;
	};
}  // namespace PeDecoder
