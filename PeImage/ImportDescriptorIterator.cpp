#include "stdafx.h"
#include "ImportDescriptorIterator.h"
#include "ImportDescriptor.h"
namespace PeDecoder
{
	ImportDescriptorIterator::ImportDescriptorIterator(ImportDirectory & importDirectory, PIMAGE_IMPORT_DESCRIPTOR begin) :
		importDirectory_(&importDirectory),
		current_(begin)
	{
#ifdef _DEBUG
		end_ = FindEndDescriptor(begin);
#endif // _DEBUG

	}
	IMAGE_IMPORT_DESCRIPTOR * ImportDescriptorIterator::FindEndDescriptor(IMAGE_IMPORT_DESCRIPTOR * bgn)
	{
		if (bgn == nullptr)
		{
			return nullptr;
		}
		while (bgn->FirstThunk != 0 && bgn->Name != 0)
		{
			++bgn;
		}
		return bgn;
	}
	ImportDescriptorIterator::~ImportDescriptorIterator()
	{
		importDirectory_ = nullptr;
		current_ = nullptr;
	}
	bool ImportDescriptorIterator::Equal(const TIterator & val) const
	{
		return val.current_ == current_;
	}
	void ImportDescriptorIterator::Increment()
	{
		++current_;
	}
	unique_ptr<ImportDescriptor> ImportDescriptorIterator::Dereference()
	{
		return AddressOf();
	}
	unique_ptr<ImportDescriptor> ImportDescriptorIterator::AddressOf()
	{
		assert(current_);
		assert(importDirectory_);

#ifdef _DEBUG
		assert(CheckRange());
#endif // _DEBUG
		return _STD make_unique<ImportDescriptor>(*importDirectory_, current_);
	}
#ifdef _DEBUG
	bool ImportDescriptorIterator::CheckRange() const
	{
		return current_ < end_;
	}
#endif // _DEBUG

}  // namespace PeDecoder
