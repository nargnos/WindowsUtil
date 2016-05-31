#include "stdafx.h"
#include "TypeOffsetIterator.h"

namespace PeDecoder
{
	TypeOffsetIterator::TypeOffsetIterator(PeImage & pe, PIMAGE_BASE_RELOCATION baseReloc, PWORD ptr) :
		store_(pe, baseReloc, ptr)
	{
	}
	bool TypeOffsetIterator::equal(const TypeOffsetIterator & val) const
	{
		return GetStore().ptr_ == val.GetStore().ptr_&&
			GetStore().baseReloc_ == val.GetStore().baseReloc_&&
			&GetStore().pe_ == &val.GetStore().pe_;
	}
	void TypeOffsetIterator::increment()
	{
		assert(InRange());
		++GetStore().ptr_;
	}
	void TypeOffsetIterator::decrement()
	{
		assert(InRange());
		--GetStore().ptr_;
	}
	void TypeOffsetIterator::advance(int n)
	{
		assert(InRange());
		GetStore().ptr_ += n;
	}
	TypeOffsetIterator::difference_type TypeOffsetIterator::distance_to(const TypeOffsetIterator & val)
	{
		return val.GetStore().ptr_ - GetStore().ptr_;
	}
	TypeOffsetIterator::reference TypeOffsetIterator::dereference() const
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
