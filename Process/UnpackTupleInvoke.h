#pragma once
#include <tuple>
namespace Tuple
{
	namespace Detail
	{
		template<typename TTuple, int index, typename TFunc>
		struct UnpackTupleInvoke
		{
			using TElementType = _STD tuple_element_t<index, TTuple>;
			using TForwordType = _STD remove_reference_t<TElementType>;

			template<typename... TArgs>
			inline static auto Invoke(TTuple& t, TFunc& func, TArgs... arg)->
				decltype(UnpackTupleInvoke<TTuple, index - 1, TFunc>::Invoke(
					t,
					func,
					_STD forward<TForwordType>(_STD get<index>(t)),
					_STD forward<TArgs>(arg)...))
			{

				return UnpackTupleInvoke<TTuple, index - 1, TFunc>::Invoke(
					t,
					func,
					_STD forward<TForwordType>(_STD get<index>(t)),
					_STD forward<TArgs>(arg)...);
			}
		};

		template<typename TTuple, typename TFunc>
		struct UnpackTupleInvoke<TTuple, -1, TFunc>
		{
			template<typename... TArgs>
			inline static auto Invoke(TTuple& t, TFunc& func, TArgs... arg)->decltype(func(_STD forward<TArgs>(arg)...))
			{
				return func(_STD forward<TArgs>(arg)...);
			}
		};
	}  // namespace Detail

	// 把tuple中的内容解包成参数给函数调用
	// 简单测试了一下，可能会有BUG
	template<typename TFunc, typename TTuple>
	inline constexpr auto Invoke(TFunc&& func, TTuple& t)->
		decltype(Detail::UnpackTupleInvoke<TTuple, _STD tuple_size<TTuple>::value - 1, TFunc>::Invoke(t, func))
	{
		return Detail::UnpackTupleInvoke<TTuple, _STD tuple_size<TTuple>::value - 1, TFunc>::Invoke(t, func);
	}
}  // namespace Tuple