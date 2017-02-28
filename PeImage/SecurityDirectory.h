#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class SecurityDirectory :
		public Detail::DirectoryBase<SecurityDirectory, DataDirectoryEntryType::Security>
	{
	public:
		friend TBase;
	protected:
		using DirectoryBase::DirectoryBase;
	};
}  // namespace PeDecoder
