#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class LoadConfigDirectory :
		public Detail::DirectoryBase<LoadConfigDirectory, DataDirectoryEntryType::LoadConfig>
	{

	public:
		friend TBase;
	protected:
		using DirectoryBase::DirectoryBase;
	};
}  // namespace PeDecoder
