#pragma once
#include "IteratorBase.h"
template<typename TValueType, typename TContainer>
class RandomAccessIteratorBase :
	public IteratorBase<RandomAccessIteratorBase<TValueType, TContainer>, _STD random_access_iterator_tag, TValueType>
{
public:
	friend IteratorFriendAccess;

	RandomAccessIteratorBase(pointer pos, const TContainer* container) :
		pos_(pos),
		container_(container)
	{
#if _DEBUG
		size_ = container->size();
#endif // _DEBUG

	}

protected:
	void Decrement()
	{
		assert(CheckPos());
		--pos_;
	}
	difference_type DistanceTo(const TIterator & val) const
	{
		return val.pos_ - pos_;
	}
	void Advance(int n)
	{
		assert(CheckPos(pos_ + n, *this));
		pos_ += n;
	}

	bool Equal(const TIterator & val) const
	{
		assert(container_ == val.container_);
		return pos_ == val.pos_;
	}
	void Increment()
	{
		assert(CheckPos());
		++pos_;
	}
	reference Dereference()
	{
		assert(CheckPos());
		return *pos_;
	}
	bool CheckPos() const
	{
		return CheckPos(pos_, *this);
	}
	static bool CheckPos(pointer pos, const RandomAccessIteratorBase& self)
	{
		assert(self.size_ == self.container_->size());
		return pos >= self.container_->begin().pos_ && pos < self.container_->end().pos_;
	}
	pointer pos_;
	const TContainer* container_;
#if _DEBUG
	size_t size_;
#endif // _DEBUG

};