#pragma once
#include <memory>
#include "IPeImage.h"

#include "DataDirectoryEntryType.h"
#include "DataPtr.h"
#include "DataSize.h"
namespace PeDecoder
{
	namespace Detail
	{
		_STD pair<PVOID, PDWORD> GetDataDirectoryEntry(const IPeImage& util, DataDirectoryEntryType index);

		template<DataDirectoryEntryType id, typename TDirectoryPtr>
		class DirectoryData :
			public DataSize<PDWORD>,
			public DataPtr<TDirectoryPtr>
		{
		public:
			IPeImage& GetUtil()
			{
				return *util_;
			}
			const IPeImage& GetUtil() const
			{
				return *util_;
			}
			virtual ~DirectoryData() = default;
		protected:
			DirectoryData(const _STD shared_ptr<IPeImage>& util) :
				DataSize(nullptr),
				DataPtr(nullptr),
				util_(util)
			{
				auto data = GetDataDirectoryEntry(*util, id);
				if (data.first != nullptr)
				{
					dataPtr_ = reinterpret_cast<typename DataDirectoryEntryTypeTrait<id>::Type>(data.first);
					sizePtr_ = data.second;
				}
			}
		private:
			_STD shared_ptr<IPeImage> util_;
		};
		template<typename TChild,
			DataDirectoryEntryType id,
			typename TDirectoryPtr = typename DataDirectoryEntryTypeTrait<id>::Type>
			class DirectoryBase :public DirectoryData<id, TDirectoryPtr>
		{
		public:
			using TBase = DirectoryBase;
			template<template<typename, typename...> class TPtrType = _STD shared_ptr, typename TResult = TPtrType<TChild>>
			static TResult Create(const _STD shared_ptr<IPeImage>& util)
			{
				assert(util);
				static_assert(_STD is_same<TResult, std::shared_ptr<TChild>>::value ||
					_STD is_same<TResult, std::unique_ptr<TChild>>::value, "");

				TResult result = nullptr;
				if (util->HasDirectory(id))
				{
					result = TResult(new TChild(util));
				}
				return result;
			}
		protected:
			using DirectoryData::DirectoryData;
		};
	}  // namespace Detail


}  // namespace PeDecoder
