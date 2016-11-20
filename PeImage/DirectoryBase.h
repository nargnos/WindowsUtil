#pragma once
#include "IDataDirectoryUtil.h"

#include "DataDirectoryEntryType.h"
#include "DataPtr.h"
#include "DataSize.h"
namespace PeDecoder
{
	namespace Detail
	{
		_STD pair<PVOID, PDWORD> GetDataDirectoryEntry(const IDataDirectoryUtil& util, DataDirectoryEntryType index);

		template<DataDirectoryEntryType id,
			typename TDirectoryPtr = typename DataDirectoryEntryTypeTrait<id>::Type>
			class DirectoryBase :
			public DataSize<PDWORD>,
			public DataPtr<TDirectoryPtr>
		{
		public:
			DirectoryBase(IDataDirectoryUtil& util) :
				DataSize(nullptr),
				DataPtr(nullptr),
				util_(util)
			{
				auto data = GetDataDirectoryEntry(util, id);
				if (data.first != nullptr)
				{
					dataPtr_ = reinterpret_cast<typename DataDirectoryEntryTypeTrait<id>::Type>(data.first);
					sizePtr_ = data.second;
				}
			}
			IDataDirectoryUtil& GetUtil()
			{
				return util_;
			}
			const IDataDirectoryUtil& GetUtil() const
			{
				return util_;
			}
			virtual ~DirectoryBase() = default;
		protected:
		private:
			IDataDirectoryUtil& util_;
		};
	}  // namespace Detail


}  // namespace PeDecoder
