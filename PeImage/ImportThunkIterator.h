#pragma once
#include <memory>
#include "IDataDirectoryUtil.h"
#include "IImportThunk.h"
#include "IteratorBase.h"


namespace PeDecoder
{
	class ImportThunkFactory;
	class ImportThunkIterator :
		public IteratorBase<
		ImportThunkIterator,
		_STD forward_iterator_tag,
		unique_ptr<IImportThunk>,
		ptrdiff_t,
		unique_ptr<IImportThunk>,
		unique_ptr<IImportThunk>>
	{
	public:
		friend IteratorFriendAccess;
		friend ImportThunkFactory;
		explicit ImportThunkIterator(const IDataDirectoryUtil& util);
		ImportThunkIterator(const IDataDirectoryUtil& util, PIMAGE_THUNK_DATA32 thunk, PIMAGE_THUNK_DATA32 originalThunk);
		ImportThunkIterator(const IDataDirectoryUtil& util, PIMAGE_THUNK_DATA64 thunk, PIMAGE_THUNK_DATA64 originalThunk);
		virtual ~ImportThunkIterator();
	protected:
		bool Equal(const TIterator & val) const;

		void Increment();
		reference Dereference();
		pointer AddressOf();
		const IDataDirectoryUtil* util_;
		unsigned char* thunk_;
		unsigned char* originalThunk_;
		unsigned char incrementSize_;
	};

}  // namespace PeDecoder


