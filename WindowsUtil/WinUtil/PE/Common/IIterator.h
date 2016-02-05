#pragma once
namespace PE
{
	template<typename T>
	class IIterator
	{
	public:
		typedef IIterator<T> IIteratorBase;
		virtual T Current() = 0;
		virtual bool Next() = 0;
		virtual void Reset() = 0;
		IIterator()
		{
		}

		virtual ~IIterator()
		{
		}
	};

}  // namespace PE
