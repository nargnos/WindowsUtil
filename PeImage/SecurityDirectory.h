#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class SecurityDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::Security>
	{
	public:
		using DirectoryBase::DirectoryBase;
	};
}  // namespace PeDecoder
