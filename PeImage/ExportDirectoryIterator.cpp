#include "stdafx.h"
#include "ExportDirectoryIterator.h"
#include "ExportIteratorNode.h"
#include "ExportDirectory.h"
namespace PeDecoder
{
	ExportDirectoryIterator::ExportDirectoryIterator(const ExportDirectory & directory, DWORD index) :
		directory_(&directory),
		index_(index)
	{

	}

	ExportDirectoryIterator::~ExportDirectoryIterator()
	{
		directory_ = nullptr;
	}

	bool ExportDirectoryIterator::Equal(const ExportDirectoryIterator & val) const
	{
		return val.directory_ == directory_ && val.index_ == index_;
	}

	void ExportDirectoryIterator::Increment()
	{
		assert(InRange());
		++index_;
	}

	void ExportDirectoryIterator::Decrement()
	{
		assert(InRange());
		--index_;
	}

	void ExportDirectoryIterator::Advance(int n)
	{
		assert(InRange());
		index_ += n;
	}

	ExportDirectoryIterator::difference_type ExportDirectoryIterator::DistanceTo(const ExportDirectoryIterator & val) const
	{
		assert(val.directory_ ==directory_);
		return val.index_ - index_;
	}

	ExportDirectoryIterator::reference ExportDirectoryIterator::Dereference()
	{
		assert(InRange());
		assert(directory_);
		return _STD make_unique<ExportIteratorNode>(*directory_, index_);
	}

	ExportDirectoryIterator::pointer ExportDirectoryIterator::AddressOf()
	{
		return Dereference();
	}

	bool ExportDirectoryIterator::InRange() const
	{
		return index_ >= 0 && index_ < *directory_->GetNumberOfNamesPtr();
	}

}  // namespace PeDecoder
