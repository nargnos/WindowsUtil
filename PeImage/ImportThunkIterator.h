#pragma once
#include <memory>
#include "IPeImage.h"
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
		explicit ImportThunkIterator(const IPeImage& util);
		ImportThunkIterator(const IPeImage& util, PIMAGE_THUNK_DATA32 thunk, PIMAGE_THUNK_DATA32 originalThunk);
		ImportThunkIterator(const IPeImage& util, PIMAGE_THUNK_DATA64 thunk, PIMAGE_THUNK_DATA64 originalThunk);
		virtual ~ImportThunkIterator();
	protected:
		bool Equal(const TIterator & val) const;

		void Increment();
		reference Dereference();
		pointer AddressOf();
		const IPeImage* util_;
		unsigned char* thunk_;
		unsigned char* originalThunk_;
		unsigned char incrementSize_;
	};

}  // namespace PeDecoder


