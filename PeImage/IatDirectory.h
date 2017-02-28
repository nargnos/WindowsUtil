#pragma once
#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class IatDirectory :
		public Detail::DirectoryBase<IatDirectory, DataDirectoryEntryType::Iat>
	{
	public:
		friend TBase;
	protected:
		using DirectoryBase::DirectoryBase;
	};
}  // namespace PeDecoder

