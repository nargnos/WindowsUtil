#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class LoadConfigDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::LoadConfig>
	{
	public:
		LoadConfigDirectory(PeImage& pe) :
			DirectoryBase(pe)
		{
		}
		~LoadConfigDirectory() = default;
	};
}  // namespace PeDecoder
