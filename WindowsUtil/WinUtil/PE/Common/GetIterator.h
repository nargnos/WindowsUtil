#pragma once
#include <memory>
namespace PE
{
	template<typename IteratorType, typename ParamType>
	class GetIterator
	{
	protected:
		bool canCreateIterator;
	public:
		typedef GetIterator<IteratorType, ParamType> GetIteratorBase;
		typedef IteratorType Iterator;
		GetIterator()
		{
			canCreateIterator = false;
		}
		_STD shared_ptr<IteratorType> CreateIterator()
		{
			assert(canCreateIterator);
			return _STD make_shared<IteratorType>(dynamic_cast<ParamType*>(this));
		}
		virtual ~GetIterator()
		{
		}
	};

}  // namespace PE
