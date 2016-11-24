#pragma once
#include <iterator>
#include "CategoryPolicy.h"
template<
	typename TIterator,
	typename TCategory,
	typename TValueType,
	typename TDiff = ptrdiff_t,
	typename TPointer = TValueType *,
	typename TReference = TValueType&>
	struct IteratorBase :
	public CategoryPolicy<TIterator, TCategory, TValueType, TDiff, TPointer, TReference>,
	public _STD iterator<TCategory, TValueType, TDiff, TPointer, TReference>
{
	typedef TIterator TIterator;
/*
	没怎么检查，可能有错

	在子类friend IteratorFriendAccess;

	根据选择的tag实现对应的接口
	隐式接口为：

	// 可反向遍历的迭代器都有
	void Decrement()
	{
	}
	// val-自身 距离
	difference_type DistanceTo(const TIterator & val) const
	{
	}
	void Advance(int n)
	{
	}

	// 所有
	bool Equal(const TIterator & val) const
	{
	}
	void Increment()
	{
	}
	reference Dereference()
	{
	}
	// 当用指针代理的时候用的自定义
	pointer AddressOf()
	{
	}
*/
};
