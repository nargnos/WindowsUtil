#include "stdafx.h"
#include "DelayImportDescriptor.h"
#include "DelayImportDirectory.h"
#include "IDataDirectoryUtil.h"
#include "ImportThunk.h"
#include "ImportThunkFactory.h"
namespace PeDecoder
{
	DelayImportDescriptor::DelayImportDescriptor(const DelayImportDirectory & delayImportDirectory, PImgDelayDescr ptr) :
		delayImportDirectory_(&delayImportDirectory),
		dataPtr_(ptr)
	{
	}
	ImportThunkIterator DelayImportDescriptor::begin() const
	{
		assert(delayImportDirectory_);
		return ImportThunkFactory::CreateDelayThunkIterator(delayImportDirectory_->GetUtil(), GetPtr());
	}
	ImportThunkIterator DelayImportDescriptor::end() const
	{
		assert(delayImportDirectory_);
		return ImportThunkFactory::CreateDelayThunkIterator(delayImportDirectory_->GetUtil(), nullptr);
	}
	PCHAR DelayImportDescriptor::GetName()
	{
		assert(GetPtr());
		return reinterpret_cast<PCHAR>(delayImportDirectory_->GetUtil().RvaToDataPtr(GetPtr()->rvaDLLName));
	}
	PImgDelayDescr DelayImportDescriptor::GetPtr() const
	{
		assert(dataPtr_);
		return dataPtr_;
	}
	DelayImportDescriptor::~DelayImportDescriptor()
	{
		dataPtr_ = nullptr;
		delayImportDirectory_ = nullptr;
	}
	DelayImportDescriptor * DelayImportDescriptor::operator->()
	{
		return this;
	}
	const DelayImportDescriptor * DelayImportDescriptor::operator->() const
	{
		return this;
	}
}  // namespace PeDecoder
