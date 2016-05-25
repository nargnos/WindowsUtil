#pragma once
#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class IatDirectory :
		public DirectoryBase<DataDirectoryEntryType::Iat>
	{
	public:
		IatDirectory(PeImage& pe, TDataPtr ptr, TSizePtr sizePtr) :
			DirectoryBase(pe, ptr, sizePtr)
		{
		}
		~IatDirectory() = default;
	};
}  // namespace PeDecoder

