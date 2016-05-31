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

	bool ExportDirectoryIterator::equal(const ExportDirectoryIterator & val) const
	{
		return val.GetStore().directory_ == GetStore().directory_ && val.GetStore().index_ == GetStore().index_;
	}

	void ExportDirectoryIterator::increment()
	{
		assert(InRange());
		++GetStore().index_;
	}

	void ExportDirectoryIterator::decrement()
	{
		assert(InRange());
		--GetStore().index_;
	}

	void ExportDirectoryIterator::advance(int n)
	{
		assert(InRange());
		GetStore().index_ += n;
	}

	ExportDirectoryIterator::difference_type ExportDirectoryIterator::distance_to(const ExportDirectoryIterator & val) const
	{
		assert(val.GetStore().directory_ == GetStore().directory_);
		return val.GetStore().index_ - GetStore().index_;
	}

	ExportDirectoryIterator::reference ExportDirectoryIterator::dereference() const
	{
		assert(InRange());
		return const_cast<reference>(GetStore());
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
