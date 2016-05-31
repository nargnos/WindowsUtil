#pragma once
#include "PeImageFwd.h"
#include "TypeOffset.h"

#include "GetRelocPtr.h"
namespace PeDecoder
{
	class TypeOffsetIterator :
		public iterator_facade<TypeOffsetIterator, TypeOffset, random_access_traversal_tag>
	{
	public:
		friend class iterator_core_access;
		TypeOffsetIterator(PeImage& pe, PIMAGE_BASE_RELOCATION baseReloc, PWORD ptr);

	protected:
		bool equal(const TypeOffsetIterator & val) const;
		void increment();
		void decrement();
		void advance(int n);
		difference_type distance_to(const TypeOffsetIterator & val);
		reference dereference() const;

		TypeOffset& GetStore();
		const TypeOffset& GetStore() const;
		bool InRange() const;
		TypeOffset store_;
	};
}  // namespace PeDecoder
