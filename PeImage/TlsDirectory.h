#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class TlsDirectory :
		public Detail::DirectoryBase<TlsDirectory, DataDirectoryEntryType::Tls>
	{
	public:
		friend TBase;
	protected:
		using DirectoryBase::DirectoryBase;
	};
}  // namespace PeDecoder

