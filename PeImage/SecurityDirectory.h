#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class SecurityDirectory :
		public DirectoryBase<DataDirectoryEntryType::Security>
	{
	public:
		SecurityDirectory(PeImage& pe, TDataPtr ptr, TSizePtr sizePtr) :
			DirectoryBase(pe, ptr, sizePtr)
		{
		}
		~SecurityDirectory() = default;
	};
}  // namespace PeDecoder
