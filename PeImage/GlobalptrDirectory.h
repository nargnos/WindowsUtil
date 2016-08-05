#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class GlobalptrDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::Globalptr>
	{
	public:
		GlobalptrDirectory(PeImage& pe) :
			DirectoryBase(pe)
		{
		}
		~GlobalptrDirectory() = default;
	};
}  // namespace PeDecoder
