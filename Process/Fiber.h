#pragma once
#include "Common.h"
#include "UnpackTupleInvoke.h"
#include "FiberBase.h"
namespace Process
{
	namespace Fiber
	{
		template<typename TFunc, typename... TArgs>
		class Fiber :
			public Detail::FiberBase<
			Fiber<TFunc, TArgs...>,
			_STD tuple<TFunc, _STD tuple<TArgs...>>>
		{
		public:
			friend Base;
			Fiber(TFunc&& func, TArgs... args) :
				Base(_STD move(func), _STD make_tuple(_STD forward<TArgs>(args)...))
			{
			}

			~Fiber() = default;

			void Switch()
			{
				FiberBase::Switch();
			}
			
		protected:
			enum class _FiberTupleIndex:int
			{
				_Func,
				_Args
			};
			static void WINAPI Callback(const TStoragePtr& storage)
			{
				assert(storage);

				auto& func = _STD get<static_cast<int>(_FiberTupleIndex::_Func)>(*storage);

				Tuple::Invoke(func, _STD get<static_cast<int>(_FiberTupleIndex::_Args)>(*storage));				
			}
		};

		template<typename TFunc, typename... TArgs>
		Fiber<TFunc, TArgs...> MakeFiber(TFunc&& func, TArgs... args)
		{
			return Fiber<TFunc, TArgs...>(_STD move(func), _STD forward<TArgs>(args)...);
		}


	}  // namespace Fiber
}  // namespace Process