#include "stdafx.h"
#include "ResourceEntryIterator.h"


namespace PeDecoder
{
	ResourceEntryIterator::ResourceEntryIterator(PIMAGE_RESOURCE_DIRECTORY root, PIMAGE_RESOURCE_DIRECTORY_ENTRY ptr) :
		store_(root, ptr)
	{
	}
	bool ResourceEntryIterator::equal(const ResourceEntryIterator & val) const
	{
		return val.GetStore().ptr_ == GetStore().ptr_ &&
			val.GetStore().root_ == GetStore().root_;
	}
	void ResourceEntryIterator::increment()
	{
		assert(InRange());
		++GetStore().ptr_;
	}
	void ResourceEntryIterator::decrement()
	{
		assert(InRange());
		--GetStore().ptr_;
	}
	void ResourceEntryIterator::advance(int n)
	{
		assert(InRange());
		GetStore().ptr_ += n;
	}
	ResourceEntryIterator::difference_type ResourceEntryIterator::distance_to(const ResourceEntryIterator & val)
	{
		assert(InRange());
		return val.GetStore().ptr_ - GetStore().ptr_;
	}
	ResourceEntryIterator::reference ResourceEntryIterator::dereference() const
	{
		return const_cast<reference>(GetStore());
	}
	bool ResourceEntryIterator::InRange() const
	{
		auto beginPtr = LocateFirstEntry(GetStore().root_);
		auto endPtr = beginPtr + GetNumberOfEntries(GetStore().root_);
		return GetStore().ptr_ >= beginPtr &&
			GetStore().ptr_ < endPtr;
	}
	ResourceEntry & ResourceEntryIterator::GetStore()
	{
		return store_;
	}
	const ResourceEntry & ResourceEntryIterator::GetStore() const
	{
		return store_;
	}
}  // namespace PeDecoder
