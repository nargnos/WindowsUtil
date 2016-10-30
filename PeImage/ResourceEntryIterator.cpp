#include "stdafx.h"
#include "ResourceEntryIterator.h"


namespace PeDecoder
{
	ResourceEntryIterator::ResourceEntryIterator(PIMAGE_RESOURCE_DIRECTORY root, PIMAGE_RESOURCE_DIRECTORY_ENTRY ptr) :
		store_(root, ptr)
	{
	}
	bool ResourceEntryIterator::Equal(const ResourceEntryIterator & val) const
	{
		return val.GetStore().ptr_ == GetStore().ptr_ &&
			val.GetStore().root_ == GetStore().root_;
	}
	void ResourceEntryIterator::Increment()
	{
		assert(InRange());
		++GetStore().ptr_;
	}
	void ResourceEntryIterator::Decrement()
	{
		assert(InRange());
		--GetStore().ptr_;
	}
	void ResourceEntryIterator::Advance(int n)
	{
		assert(InRange());
		GetStore().ptr_ += n;
	}
	ResourceEntryIterator::difference_type ResourceEntryIterator::DistanceTo(const ResourceEntryIterator & val)
	{
		assert(InRange());
		return val.GetStore().ptr_ - GetStore().ptr_;
	}
	ResourceEntryIterator::reference ResourceEntryIterator::Dereference()
	{
		return GetStore();
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
