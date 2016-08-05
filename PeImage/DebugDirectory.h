#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class DebugDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::Debug>
	{
	public:
		DebugDirectory(PeImage& pe);
		~DebugDirectory() = default;
	};
}  // namespace PeDecoder
