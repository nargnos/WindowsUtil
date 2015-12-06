#pragma once
#include <memory>
template<typename IteratorType, typename StructType>
class GetIterator
{
public:

	GetIterator()
	{
	}
	_STD shared_ptr<IteratorType> CreateIterator()
	{
		return _STD make_shared<IteratorType>(dynamic_cast<StructType&>(*this));
	}
	virtual ~GetIterator()
	{
	}
};

