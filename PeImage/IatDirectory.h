#pragma once
#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class IatDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::Iat>
	{
	public:
		IatDirectory(PeImage& pe) :
			DirectoryBase(pe)
		{
		}
		~IatDirectory() = default;
	};
}  // namespace PeDecoder

