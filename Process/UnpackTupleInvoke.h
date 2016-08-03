#pragma once
#include <tuple>
namespace Tuple
{
	namespace Detail
	{
		template<int index>
		struct UnpackTupleInvoke
		{
			template<typename TFunc, typename TTuple, typename... TArgs>
			inline static auto Invoke(TFunc&& func, TTuple&& t, TArgs&&... arg)
			{
				using TElement = _STD tuple_element_t<index, _STD decay_t<TTuple>>;
				
				return UnpackTupleInvoke<index - 1>::Invoke(
					_STD forward<TFunc>(func),
					_STD forward<TTuple>(t),
					_STD forward<TElement>(_STD get<index>(_STD forward<TTuple>(t))),
					_STD forward<TArgs>(arg)...);
			}
		};

		template<>
		struct UnpackTupleInvoke<-1>
		{
			template<typename TFunc, typename TTuple, typename... TArgs>
			inline static auto Invoke(TFunc&& func, TTuple&& t, TArgs&&... arg)
			{
				return func(_STD forward<TArgs>(arg)...);
			}
		};
	}  // namespace Detail

	// 把tuple中的内容解包成参数给函数调用
	template<typename TFunc, typename TTuple>
	inline auto Invoke(TFunc&& func, TTuple&& t)
	{
		return Detail::UnpackTupleInvoke<_STD tuple_size<_STD decay_t<TTuple>>::value - 1>::Invoke(
			_STD forward<TFunc>(func), _STD forward<TTuple>(t));
	}
}  // namespace Tuple