#pragma once
#include "PeImageFwd.h"
#include "DataDirectoryEntryType.h"
#include "DataPtr.h"
#include "DataSize.h"
#include "PeRef.h"
namespace PeDecoder
{
	namespace Detail
	{
		template<DataDirectoryEntryType id,
			typename TDirectoryPtr = typename DataDirectoryEntryTypeTrait<id>::Type>
			class DirectoryBase :
			public DataSize<PDWORD>,
			public DataPtr<TDirectoryPtr>,
			public PeRef
		{
		public:
			DirectoryBase(PeImage& pe, TDirectoryPtr ptr, TSizePtr sizePtr) :
				DataPtr(ptr),
				DataSize(sizePtr),
				PeRef(pe)
			{
			}
			~DirectoryBase() = default;
		protected:
		};
	}  // namespace Detail


}  // namespace PeDecoder
