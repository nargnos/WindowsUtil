#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class GlobalptrDirectory :
		public Detail::DirectoryBase<GlobalptrDirectory, DataDirectoryEntryType::Globalptr>
	{
	public:
		friend TBase;
	protected:
		using DirectoryBase::DirectoryBase;
	};
}  // namespace PeDecoder
