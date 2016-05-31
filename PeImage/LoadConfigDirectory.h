#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class LoadConfigDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::LoadConfig>
	{
	public:
		LoadConfigDirectory(PeImage& pe, TDataPtr ptr, TSizePtr sizePtr) :
			DirectoryBase(pe, ptr, sizePtr)
		{
		}
		~LoadConfigDirectory() = default;
	};
}  // namespace PeDecoder
