#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class TlsDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::Tls>
	{
	public:
		using DirectoryBase::DirectoryBase;
	};
}  // namespace PeDecoder

