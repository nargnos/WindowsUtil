#pragma once
#include "PeImageFwd.h"
#include "DataDirectoryEntryType.h"
#include "DataPtr.h"
#include "DataSize.h"

namespace PeDecoder
{
	template<DataDirectoryEntryType id,
		typename TDirectoryPtr = typename DataDirectoryEntryTypeTrait<id>::Type>
		class DirectoryBase :
		public DataSize<PDWORD>,
		public DataPtr<TDirectoryPtr>
	{
	public:
		DirectoryBase(PeImage& pe, TDirectoryPtr ptr, TSizePtr sizePtr) :
			DataPtr(ptr),
			DataSize(sizePtr),
			pe_(pe)
		{
		}
		~DirectoryBase() = default;
	protected:
		PeImage& pe_;
	};
}  // namespace PeDecoder
