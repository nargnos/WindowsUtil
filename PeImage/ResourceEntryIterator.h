#pragma once
#include "ResourceEntry.h"
#include "ResourceUtil.h"
namespace PeDecoder
{
	class ResourceEntryIterator :
		public iterator_facade<ResourceEntryIterator, ResourceEntry, random_access_traversal_tag>
	{
	public:
		friend class iterator_core_access;
		ResourceEntryIterator(PIMAGE_RESOURCE_DIRECTORY root, PIMAGE_RESOURCE_DIRECTORY_ENTRY ptr);
	protected:
		bool equal(const ResourceEntryIterator & val) const;
		void increment();
		void decrement();
		void advance(int n);
		difference_type distance_to(const ResourceEntryIterator & val);
		reference dereference() const;

		bool InRange() const;
		ResourceEntry& GetStore();
		const ResourceEntry& GetStore() const;
		ResourceEntry store_;
	};
}  // namespace PeDecoder
