#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class DebugDirectory :
		public Detail::DirectoryBase<DebugDirectory, DataDirectoryEntryType::Debug>
	{
	public:
		friend TBase;
	protected:
		using DirectoryBase::DirectoryBase;
	};
}  // namespace PeDecoder
