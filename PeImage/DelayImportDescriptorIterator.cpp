#include "stdafx.h"
#include "DelayImportDescriptorIterator.h"

namespace PeDecoder
{
	DelayImportDescriptorIterator::DelayImportDescriptorIterator(const DelayImportDirectory & delayImportDirectory, PImgDelayDescr ptr) :
		delayImportDirectory_(&delayImportDirectory),
		dataPtr_(ptr)
	{
	}
	bool DelayImportDescriptorIterator::Equal(const DelayImportDescriptorIterator & val) const
	{
		assert(delayImportDirectory_ == val.delayImportDirectory_);
		return dataPtr_ == val.dataPtr_;
	}
	void DelayImportDescriptorIterator::Increment()
	{
		assert(dataPtr_);
		++dataPtr_;
		if (dataPtr_->grAttrs == 0)
		{
			dataPtr_ = nullptr;
		}
	}
	DelayImportDescriptorIterator::reference DelayImportDescriptorIterator::Dereference()
	{
		assert(dataPtr_);
		return DelayImportDescriptor(*delayImportDirectory_, dataPtr_);
	}
	DelayImportDescriptorIterator::pointer DelayImportDescriptorIterator::AddressOf()
	{
		return Dereference();
	}
}  // namespace PeDecoder