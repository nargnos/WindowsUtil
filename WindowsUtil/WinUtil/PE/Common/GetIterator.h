#pragma once
#include <memory>
template<typename IteratorType, typename StructType>
class GetIterator
{
protected:
	bool canCreateIterator;
public:

	GetIterator()
	{
		canCreateIterator = false;
	}
	_STD shared_ptr<IteratorType> CreateIterator()
	{
		assert(canCreateIterator);
		return _STD make_shared<IteratorType>(dynamic_cast<StructType&>(*this));
	}
	virtual ~GetIterator()
	{
	}
};

