#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class TlsDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::Tls>
	{
	public:
		TlsDirectory(PeImage& pe) :
			DirectoryBase(pe)
		{
		}
		~TlsDirectory() = default;
	};
}  // namespace PeDecoder

