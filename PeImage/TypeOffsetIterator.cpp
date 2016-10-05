#include "stdafx.h"
#include "TypeOffsetIterator.h"

namespace PeDecoder
{
	TypeOffsetIterator::TypeOffsetIterator(IPeImage & pe, PIMAGE_BASE_RELOCATION baseReloc, PWORD ptr) :
		store_(baseReloc, ptr)
	{
	}
	bool TypeOffsetIterator::Equal(const TypeOffsetIterator & val) const
	{
		return GetStore().ptr_ == val.GetStore().ptr_&&
			GetStore().baseReloc_ == val.GetStore().baseReloc_;
	}
	void TypeOffsetIterator::Increment()
	{
		assert(InRange());
		++GetStore().ptr_;
	}
	void TypeOffsetIterator::Decrement()
	{
		assert(InRange());
		--GetStore().ptr_;
	}
	void TypeOffsetIterator::Advance(int n)
	{
		assert(InRange());
		GetStore().ptr_ += n;
	}
	TypeOffsetIterator::difference_type TypeOffsetIterator::DistanceTo(const TypeOffsetIterator & val)
	{
		return val.GetStore().ptr_ - GetStore().ptr_;
	}
	TypeOffsetIterator::reference TypeOffsetIterator::Dereference() const
	{
		assert(InRange());
		return const_cast<reference>(GetStore());
	}
	TypeOffset& TypeOffsetIterator::GetStore()
	{
		return store_;
	}
	const TypeOffset& TypeOffsetIterator::GetStore() const
	{
		return store_;
	}
	bool TypeOffsetIterator::InRange() const
	{
		auto baseReloc = GetStore().baseReloc_;
		return GetStore().ptr_ >= GetBeginPtr(baseReloc) && GetStore().ptr_ < GetEndPtr(baseReloc);
	}
}  // namespace PeDecoder
