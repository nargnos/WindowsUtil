#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class DebugDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::Debug>
	{
	public:
		using DirectoryBase::DirectoryBase;
	};
}  // namespace PeDecoder
