#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class SecurityDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::Security>
	{
	public:
		SecurityDirectory(PeImage& pe) :
			DirectoryBase(pe)
		{
		}
		~SecurityDirectory() = default;
	};
}  // namespace PeDecoder
