#pragma once
#include "Common.h"
#include "FiberBase.h"
#include "CoroutineIterator.h"

namespace Process
{
	namespace Fiber
	{
		// 协程，用法有点类似c#的
		// 注意一旦开始迭代，线程就会被转为纤程，感觉没什么影响，就不转回了
		// 返回引用在yield return时要明确说明
		// 多线程情况未测试，可能有bug


		// 注意这个函数不要在协程外使用, 否则得到的结果是不确定的
		// 不要return不同类型的东西，否则也是不确定的
		template<typename TRet>
		_STD enable_if_t<Detail::IsPointerReturnType<TRet>::value> YieldReturn(TRet& ret)
		{
			
			auto data = Process::Fiber::GetFiberData<Detail::CoroutineStorageHead<TRet>>();
			assert(data);
			data->ContextPtr->Ret = &ret;

			Detail::_SwitchToLastFiber(data);
		}

		template<typename TRet>
		_STD enable_if_t<!Detail::IsPointerReturnType<TRet>::value> YieldReturn(TRet&& ret)
		{
			auto data = Process::Fiber::GetFiberData<Detail::CoroutineStorageHead<TRet>>();
			assert(data);
			data->ContextPtr->Ret = ret;

			Detail::_SwitchToLastFiber(data);
		}

		


		// 注意如果在纤程里修改了用传入参数的值，第二次迭代的时候会用新的值
		template<typename TRet, typename TFunc, typename... TArgs>
		class Coroutine
		{
		public:
			typedef Detail::CoroutineIterator<TRet, TFunc, TArgs...> iterator;
			Coroutine(TFunc&& func, TArgs... args) :
				func_(
					_STD make_shared<Detail::CoroutineFuncStorage<TFunc, TArgs...>>(
						_STD move(func),
						_STD make_tuple(_STD forward<TArgs>(args)...)))
			{
			}

			iterator begin()
			{
				iterator result(func_);
				++result;
				return result;
			}
			iterator end()
			{
				return iterator();
			}

			void RetsetParams(TArgs... args)
			{
				_STD get<static_cast<int>(Detail::_CoroutineFuncStorageIndex::_Args)>(*func_) =
					_STD make_tuple<TArgs...>(_STD forward<TArgs>(args)...);
			}
		protected:
			Detail::CoroutineFuncStoragePtr<TFunc, TArgs...> func_;
		};

		template<typename TRet, typename TFunc, typename... TArgs>
		Coroutine<TRet, TFunc, TArgs...> MakeCoroutine(TFunc&& func, TArgs... args)
		{
			return Coroutine<TRet, TFunc, TArgs...>(_STD move(func), _STD forward<TArgs>(args)...);
		}
	}  // namespace Fiber
}  // namespace Process