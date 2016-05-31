#include "stdafx.h"
#include "DelayImportDirectory.h"
namespace PeDecoder
{
	DelayImportDirectory::DelayImportDirectory(PeImage & pe, TDataPtr ptr, TSizePtr sizePtr) :
		DirectoryBase(pe, ptr, sizePtr)
	{
	}
	DelayImportDirectory::iterator DelayImportDirectory::begin()
	{
		return iterator(*this, GetPtr());
	}
	DelayImportDirectory::iterator DelayImportDirectory::end()
	{
		return iterator(*this, nullptr);
	}
	DelayImportDirectory::iterator::iterator(DelayImportDirectory & delayImportDirectory, PImgDelayDescr ptr) :
		DelayImportDescriptor(delayImportDirectory, ptr)
	{
	}
	bool DelayImportDirectory::iterator::equal(const iterator & val) const
	{
		return &val.delayImportDirectory_ == &delayImportDirectory_ && dataPtr_ == val.dataPtr_;
	}
	void DelayImportDirectory::iterator::increment()
	{
		++dataPtr_;
		if (dataPtr_->grAttrs == 0)
		{
			dataPtr_ = nullptr;
		}
	}
	DelayImportDirectory::iterator::reference DelayImportDirectory::iterator::dereference() const
	{
		return *this;
	}
}  // namespace PeDecoder
