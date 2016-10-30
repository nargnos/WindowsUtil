#include "stdafx.h"
#include "ExportDirectoryIterator.h"
#include "ExportIteratorNode.h"
#include "ExportDirectory.h"
namespace PeDecoder
{
	ExportDirectoryIterator::ExportDirectoryIterator(ExportDirectory & directory, DWORD index) :
		store_(directory, index)
	{

	}

	bool ExportDirectoryIterator::Equal(const ExportDirectoryIterator & val) const
	{
		return val.GetStore().directory_ == GetStore().directory_ && val.GetStore().index_ == GetStore().index_;
	}

	void ExportDirectoryIterator::Increment()
	{
		assert(InRange());
		++GetStore().index_;
	}

	void ExportDirectoryIterator::Decrement()
	{
		assert(InRange());
		--GetStore().index_;
	}

	void ExportDirectoryIterator::Advance(int n)
	{
		assert(InRange());
		GetStore().index_ += n;
	}

	ExportDirectoryIterator::difference_type ExportDirectoryIterator::DistanceTo(const ExportDirectoryIterator & val) const
	{
		assert(val.GetStore().directory_ == GetStore().directory_);
		return val.GetStore().index_ - GetStore().index_;
	}

	ExportDirectoryIterator::reference ExportDirectoryIterator::Dereference()
	{
		assert(InRange());
		return GetStore();
	}

	bool ExportDirectoryIterator::InRange() const
	{
		return GetStore().index_ >= 0 && GetStore().index_ < *GetStore().directory_->GetNumberOfNamesPtr();
	}

	ExportIteratorNode & ExportDirectoryIterator::GetStore()
	{
		return store_;
	}

	const ExportIteratorNode & ExportDirectoryIterator::GetStore() const
	{
		return store_;
	}
}  // namespace PeDecoder
