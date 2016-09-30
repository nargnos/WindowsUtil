#pragma once
#include "PeImageFwd.h"
#include "TypeOffset.h"

#include "GetRelocPtr.h"
#include "IteratorBase.h"
namespace PeDecoder
{
	class TypeOffsetIterator :
		public IteratorBase<TypeOffsetIterator, _STD random_access_iterator_tag, TypeOffset>
	{
	public:
		friend IteratorFriendAccess;
		TypeOffsetIterator(PeImage& pe, PIMAGE_BASE_RELOCATION baseReloc, PWORD ptr);

	protected:
		bool Equal(const TypeOffsetIterator & val) const;
		void Increment();
		void Decrement();
		void Advance(int n);
		difference_type DistanceTo(const TypeOffsetIterator & val);
		reference Dereference() const;

		TypeOffset& GetStore();
		const TypeOffset& GetStore() const;
		bool InRange() const;
		TypeOffset store_;
	};
}  // namespace PeDecoder
