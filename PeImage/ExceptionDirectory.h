#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class ExceptionDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::Exception>
	{
	public:
		using DirectoryBase::DirectoryBase;
	};
}  // namespace PeDecoder
