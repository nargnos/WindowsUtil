#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class ExceptionDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::Exception>
	{
	public:
		ExceptionDirectory(PeImage& pe) :
			DirectoryBase(pe)
		{
		}
		~ExceptionDirectory() = default;
	};
}  // namespace PeDecoder
