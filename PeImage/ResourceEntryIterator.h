#pragma once
#include "ResourceEntry.h"
#include "ResourceUtil.h"
#include "IteratorBase.h"
namespace PeDecoder
{
	class ResourceEntryIterator :
		public IteratorBase<ResourceEntryIterator,_STD random_access_iterator_tag, ResourceEntry>
	{
	public:
		friend IteratorFriendAccess;
		ResourceEntryIterator(PIMAGE_RESOURCE_DIRECTORY root, PIMAGE_RESOURCE_DIRECTORY_ENTRY ptr);
	protected:
		bool Equal(const ResourceEntryIterator & val) const;
		void Increment();
		void Decrement();
		void Advance(int n);
		difference_type DistanceTo(const ResourceEntryIterator & val);
		reference Dereference() const;

		bool InRange() const;
		ResourceEntry& GetStore();
		const ResourceEntry& GetStore() const;
		ResourceEntry store_;
	};
}  // namespace PeDecoder
