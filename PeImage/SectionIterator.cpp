#include "stdafx.h"
#include "SectionIterator.h"

PeDecoder::Detail::SectionIterator::SectionIterator(PIMAGE_SECTION_HEADER begin, WORD size) :
	current_(static_cast<pointer>(begin)),
	size_(size),
	begin_(static_cast<pointer>(begin))
{

}

bool PeDecoder::Detail::SectionIterator::Equal(const SectionIterator & val) const
{
	return current_ == val.current_;
}

void PeDecoder::Detail::SectionIterator::Increment()
{
	++current_;
}

void PeDecoder::Detail::SectionIterator::Decrement()
{

	--current_;
}

void PeDecoder::Detail::SectionIterator::Advance(difference_type n)
{
	current_ += n;
}

PeDecoder::Detail::SectionIterator::difference_type PeDecoder::Detail::SectionIterator::DistanceTo(const SectionIterator & val) const
{
	return val.current_ - current_;
}

PeDecoder::Detail::SectionIterator::reference PeDecoder::Detail::SectionIterator::Dereference()
{
	assert(current_ < begin_ + size_);
	return *current_;
}

PeDecoder::Detail::SectionIterator::reference PeDecoder::Detail::SectionIterator::Dereference() const
{
	assert(current_ < begin_ + size_);
	return *current_;
}
