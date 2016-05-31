#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class TlsDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::Tls>
	{
	public:
		TlsDirectory(PeImage& pe, TDataPtr ptr, TSizePtr sizePtr) :
			DirectoryBase(pe, ptr, sizePtr)
		{
		}
		~TlsDirectory() = default;
	};
}  // namespace PeDecoder

