#pragma once
#include <iterator>
#include <cassert>
#include "Section.h"
#include "IteratorBase.h"
namespace PeDecoder
{
	namespace Detail
	{
		class SectionIterator :
			public IteratorBase<SectionIterator, _STD random_access_iterator_tag, Section>
		{
		public:
			friend IteratorFriendAccess;
			SectionIterator(PIMAGE_SECTION_HEADER begin, WORD size);

		protected:

			bool Equal(const SectionIterator & val) const;
			void Increment();
			void Decrement();
			void Advance(difference_type n);
			difference_type DistanceTo(const SectionIterator & val) const;
			reference Dereference();
			reference Dereference() const;
			pointer begin_;
			pointer current_;
			WORD size_;
		};
	}  // namespace Detail
}  // namespace PeDecoder
