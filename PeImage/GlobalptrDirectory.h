#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class GlobalptrDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::Globalptr>
	{
	public:
		using DirectoryBase::DirectoryBase;
	};
}  // namespace PeDecoder
