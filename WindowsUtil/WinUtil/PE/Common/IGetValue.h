#pragma once
namespace PE
{
	template<typename T>
	class IGetValue
	{
	public:
		typedef IGetValue<T> IGetValueBase;
		IGetValue() {}
		virtual ~IGetValue() {}
		virtual T GetValue() = 0;
	};

}  // namespace PE
