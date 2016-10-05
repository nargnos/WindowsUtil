#pragma once
#include "IPeImage.h"

#include "PeImageFwd.h"
#include "DataDirectoryEntryType.h"
#include "DataPtr.h"
#include "DataSize.h"
namespace PeDecoder
{
	namespace Detail
	{
		_STD pair<PVOID, PDWORD> GetDataDirectoryEntry(IPeImage& pe, DataDirectoryEntryType index);

		template<DataDirectoryEntryType id,
			typename TDirectoryPtr = typename DataDirectoryEntryTypeTrait<id>::Type>
			class DirectoryBase :
			public DataSize<PDWORD>,
			public DataPtr<TDirectoryPtr>
		{
		public:
			DirectoryBase(IPeImage& pe) :
				DataSize(nullptr),
				DataPtr(nullptr),
				pe_(pe)
			{
				auto data = GetDataDirectoryEntry(pe, id);
				if (data.first != nullptr)
				{
					dataPtr_ = reinterpret_cast<typename DataDirectoryEntryTypeTrait<id>::Type>(data.first);
					sizePtr_ = data.second;
				}
			}
			IPeImage& GetPe()
			{
				return pe_;
			}
			const IPeImage& GetPe() const
			{
				return pe_;
			}
			~DirectoryBase() = default;
		protected:
		private:
			IPeImage& pe_;
		};
	}  // namespace Detail


}  // namespace PeDecoder
