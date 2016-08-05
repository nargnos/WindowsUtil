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
		_STD pair<PVOID, PDWORD> GetDataDirectoryEntry(PeImage& pe, DataDirectoryEntryType index);

		template<DataDirectoryEntryType id,
			typename TDirectoryPtr = typename DataDirectoryEntryTypeTrait<id>::Type>
			class DirectoryBase :
			public DataSize<PDWORD>,
			public DataPtr<TDirectoryPtr>,
			public PeRef
		{
		public:
			DirectoryBase(PeImage& pe) :
				PeRef(pe),
				DataSize(nullptr),
				DataPtr(nullptr)
			{
				auto data = GetDataDirectoryEntry(pe, id);
				if (data.first != nullptr)
				{
					dataPtr_ = reinterpret_cast<typename DataDirectoryEntryTypeTrait<id>::Type>(data.first);
					sizePtr_ = data.second;
				}
			}

			~DirectoryBase() = default;
		protected:
		};
	}  // namespace Detail


}  // namespace PeDecoder
