#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class LoadConfigDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::LoadConfig>
	{
	public:
		using DirectoryBase::DirectoryBase;
	};
}  // namespace PeDecoder
