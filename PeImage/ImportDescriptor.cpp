#include "stdafx.h"
#include "ImportDescriptor.h"
#include "ImportDirectory.h"
#include "ImportThunkFactory.h"

namespace PeDecoder
{
	ImportDescriptor::ImportDescriptor(ImportDirectory & importDirectory, PIMAGE_IMPORT_DESCRIPTOR ptr) :
		importDirectory_(&importDirectory),
		dataPtr_(ptr)
	{

	}
	ImportThunkIterator ImportDescriptor::begin() const
	{
		assert(importDirectory_);
		return ImportThunkFactory::CreateThunkIterator(importDirectory_->GetUtil(), dataPtr_);
	}
	ImportThunkIterator ImportDescriptor::end() const
	{
		assert(importDirectory_);
		return ImportThunkFactory::CreateThunkIterator(importDirectory_->GetUtil(), nullptr);
	}

	PCHAR ImportDescriptor::GetName() const
	{
		return reinterpret_cast<PCHAR>(importDirectory_->GetUtil().RvaToDataPtr(RawPtr()->Name));
	}
	PIMAGE_IMPORT_DESCRIPTOR ImportDescriptor::RawPtr() const
	{
		assert(dataPtr_);
		return dataPtr_;
	}
	ImportDescriptor::~ImportDescriptor()
	{
		dataPtr_ = nullptr;
		importDirectory_ = nullptr;
	}
	ImportDescriptor * ImportDescriptor::operator->()
	{
		return this;
	}
	const ImportDescriptor * ImportDescriptor::operator->() const
	{
		return this;
	}
}  // namespace PeDecoder

