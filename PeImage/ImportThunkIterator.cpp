#include "stdafx.h"
#include "ImportThunkIterator.h"
#include "ImportThunkFactory.h"
#include "ImportThunk.h"
namespace PeDecoder
{
	ImportThunkIterator::ImportThunkIterator(const IPeImage & util, PIMAGE_THUNK_DATA32 thunk, PIMAGE_THUNK_DATA32 originalThunk) :
		thunk_(reinterpret_cast<unsigned char*>(thunk)),
		originalThunk_(reinterpret_cast<unsigned char*>(originalThunk)),
		incrementSize_(sizeof(IMAGE_THUNK_DATA32)),
		util_(&util)
	{
	}
	ImportThunkIterator::ImportThunkIterator(const IPeImage & util, PIMAGE_THUNK_DATA64 thunk, PIMAGE_THUNK_DATA64 originalThunk) :
		thunk_(reinterpret_cast<unsigned char*>(thunk)),
		originalThunk_(reinterpret_cast<unsigned char*>(originalThunk)),
		incrementSize_(sizeof(IMAGE_THUNK_DATA64)),
		util_(&util)
	{
	}

	ImportThunkIterator::~ImportThunkIterator()
	{
		thunk_ = nullptr;
		originalThunk_ = nullptr;
		util_ = nullptr;
		incrementSize_ = 0;
	}

	ImportThunkIterator::ImportThunkIterator(const IPeImage & util):
		thunk_(nullptr),
		originalThunk_(nullptr),
		incrementSize_(0),
		util_(&util)
	{
	}

	bool ImportThunkIterator::Equal(const TIterator & val) const
	{
		return thunk_ == val.thunk_  &&
			originalThunk_ == val.originalThunk_;
	}
	void ImportThunkIterator::Increment()
	{
		assert(incrementSize_ > 0);
		assert(originalThunk_);
		assert(thunk_);
		originalThunk_ += incrementSize_;
		thunk_ += incrementSize_;
		if (*originalThunk_ == 0)
		{
			// µ½Ä©Î²ÁË
			originalThunk_ = nullptr;
			thunk_ = nullptr;
		}
	}
	ImportThunkIterator::reference ImportThunkIterator::Dereference()
	{
		assert(originalThunk_);
		assert(thunk_);
		unique_ptr<IImportThunk> result;
		auto type = util_->GetImageType();
		switch (type)
		{
		case PeDecoder::ImageType::PE32:
			result = ImportThunkFactory::CreateThunk(*util_, reinterpret_cast<PIMAGE_THUNK_DATA32>(thunk_),
				reinterpret_cast<PIMAGE_THUNK_DATA32>(originalThunk_));
			break;
		case PeDecoder::ImageType::PE64:
			result = ImportThunkFactory::CreateThunk(*util_, reinterpret_cast<PIMAGE_THUNK_DATA64>(thunk_),
				reinterpret_cast<PIMAGE_THUNK_DATA64>(originalThunk_));
			break;
		default:
			assert(false);
			break;
		}
		return result;
	}
	ImportThunkIterator::pointer ImportThunkIterator::AddressOf()
	{
		return Dereference();
	}
}  // namespace PeDecoder