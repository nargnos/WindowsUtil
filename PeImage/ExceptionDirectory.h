#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class ExceptionDirectory :
		public DirectoryBase<DataDirectoryEntryType::Exception>
	{
	public:
		ExceptionDirectory(PeImage& pe, TDataPtr ptr, TSizePtr sizePtr) :
			DirectoryBase(pe, ptr, sizePtr)
		{
		}
		~ExceptionDirectory() = default;
	};
}  // namespace PeDecoder
