#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class GlobalptrDirectory :
		public DirectoryBase<DataDirectoryEntryType::Globalptr>
	{
	public:
		GlobalptrDirectory(PeImage& pe, TDataPtr ptr, TSizePtr sizePtr) :
			DirectoryBase(pe, ptr, sizePtr)
		{
		}
		~GlobalptrDirectory() = default;
	};
}  // namespace PeDecoder
