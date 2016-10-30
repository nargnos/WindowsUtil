#pragma once
#include "IteratorFriendAccess.h"
#include <utility>
template<
	typename TIterator,
	typename TCategory,
	typename TValueType,
	typename TDiff,
	typename TPointer,
	typename TReference>
	struct CategoryPolicy;

template<
	typename TIterator,
	typename TValueType,
	typename TDiff,
	typename TPointer,
	typename TReference>
	struct CategoryPolicy<TIterator, _STD forward_iterator_tag, TValueType, TDiff, TPointer, TReference>
{
public:
	TReference operator*()
	{
		return IteratorFriendAccess::Dereference(Self());
	}

	TPointer operator->()
	{
		return AddressOf();
	}
	const TReference operator*() const
	{
		return IteratorFriendAccess::Dereference(Self());
	}

	const TPointer operator->() const
	{
		return AddressOf();
	}

	bool operator==(const TIterator& val) const
	{
		return IteratorFriendAccess::Equal(Self(), val);
	}

	bool operator!=(const TIterator& val) const
	{
		return !IteratorFriendAccess::Equal(Self(), val);
	}

	TIterator operator++(int)
	{
		TIterator result(*this);
		IteratorFriendAccess::Increment(Self());
		return result;
	}

	TIterator& operator++()
	{
		IteratorFriendAccess::Increment(Self());
		return Self();
	}

protected:
	TIterator& Self()
	{
		return static_cast<TIterator&>(*this);
	}
	const TIterator& Self() const
	{
		return static_cast<const TIterator&>(*this);
	}
	const TPointer AddressOf() const
	{
		return _STD addressof(IteratorFriendAccess::Dereference(Self()));
	}
	TPointer AddressOf()
	{
		return _STD addressof(IteratorFriendAccess::Dereference(Self()));
	}
	TIterator& _Advance(TDiff val)
	{
		TIterator result(Self());
		IteratorFriendAccess::Advance(Self(), val);
		return result;
	}
};

template<
	typename TIterator,
	typename TValueType,
	typename TDiff,
	typename TPointer,
	typename TReference>
	struct CategoryPolicy<TIterator, _STD bidirectional_iterator_tag, TValueType, TDiff, TPointer, TReference> :
	public CategoryPolicy<TIterator, _STD forward_iterator_tag, TValueType, TDiff, TPointer, TReference>
{
	TIterator operator+(TDiff val)
	{
		assert(val >= 0);
		return _Advance(val);
	}

	void operator+=(TDiff val)
	{
		assert(val >= 0);
		IteratorFriendAccess::Advance(Self(), val);
	}

	TDiff operator-(const TIterator& val) const
	{
		return IteratorFriendAccess::DistanceTo(val, Self());
	}
	TIterator operator--(int)
	{
		IteratorFriendAccess::Decrement(Self());
		return result;
	}
	TIterator& operator--()
	{
		IteratorFriendAccess::Decrement(Self());
		return Self();
	}
	TIterator operator-(TDiff val)
	{
		assert(val >= 0);
		return _Advance(-val);
	}
	void operator-=(TDiff val)
	{
		assert(val >= 0);
		IteratorFriendAccess::Advance(Self(), -val);
	}
};

template<
	typename TIterator,
	typename TValueType,
	typename TDiff,
	typename TPointer,
	typename TReference>
	struct CategoryPolicy<TIterator, _STD random_access_iterator_tag, TValueType, TDiff, TPointer, TReference> :
	public CategoryPolicy<TIterator, _STD bidirectional_iterator_tag, TValueType, TDiff, TPointer, TReference>
{
	bool operator<(const TIterator& val) const
	{
		return IteratorFriendAccess::DistanceTo(Self(), val) > 0;
	}
	bool operator<=(const TIterator& val) const
	{
		return IteratorFriendAccess::DistanceTo(Self(), val) >= 0;
	}
	bool operator>=(const TIterator& val) const
	{
		return IteratorFriendAccess::DistanceTo(Self(), val) <= 0;
	}
	bool operator>(const TIterator& val) const
	{
		return IteratorFriendAccess::DistanceTo(Self(), val) < 0;
	}
	TReference operator[](TDiff index)
	{
		return AddressOf()[index];
	}
	const TReference operator[](TDiff index) const
	{
		return AddressOf()[index];
	}
};