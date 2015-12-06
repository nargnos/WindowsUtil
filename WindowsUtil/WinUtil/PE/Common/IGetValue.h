#pragma once
namespace PE
{
	template<typename T>
	class IGetValue
	{
	public:
		IGetValue() {}
		virtual ~IGetValue() {}
		virtual T GetValue() = 0;
	};

}