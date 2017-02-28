#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class ExceptionDirectory :
		public Detail::DirectoryBase<ExceptionDirectory, DataDirectoryEntryType::Exception>
	{
	public:
		friend TBase;
	protected:
		using DirectoryBase::DirectoryBase;
	};
}  // namespace PeDecoder
