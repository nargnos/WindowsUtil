#pragma once
#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class IatDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::Iat>
	{
	public:
		using DirectoryBase::DirectoryBase;
	};
}  // namespace PeDecoder

