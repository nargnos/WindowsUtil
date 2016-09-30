#include "stdafx.h"
#include "DelayImportDirectoryIterator.h"

namespace PeDecoder
{
	DelayImportDirectoryIterator::DelayImportDirectoryIterator(DelayImportDirectory & delayImportDirectory, PImgDelayDescr ptr) :
		store_(delayImportDirectory, ptr)
	{
	}
	 bool DelayImportDirectoryIterator::Equal(const DelayImportDirectoryIterator & val) const
	{
		return val.GetStore().delayImportDirectory_ == GetStore().delayImportDirectory_ && 
			GetStore().dataPtr_ == val.GetStore().dataPtr_;
	}
	 void DelayImportDirectoryIterator::Increment()
	{
		++GetStore().dataPtr_;
		if (GetStore().dataPtr_->grAttrs == 0)
		{
			GetStore().dataPtr_ = nullptr;
		}
	}
	DelayImportDirectoryIterator::reference DelayImportDirectoryIterator::Dereference() const
	{
		return const_cast<reference>(GetStore());
	}
	 DelayImportDescriptor& DelayImportDirectoryIterator::GetStore()
	{
		return store_;
	}
	 const DelayImportDescriptor& DelayImportDirectoryIterator::GetStore() const
	{
		return store_;
	}
}  // namespace PeDecoder