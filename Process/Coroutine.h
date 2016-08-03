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
		// 返回调用第一个参数（是函数指针）返回
		// 多线程情况未测试，可能有bug
		// FIX: 在运行到一半时销毁fiber不会使在函数中创建的临时对象析构，fiber类也有这个问题（windows的锅），如何解决
		// 如果能控制context，在销毁fiber时先修改eip跳到最后的return应该可以


		namespace Detail
		{

			template<typename TRet>
			_STD enable_if_t<IsSavePointer<TRet>::value>
				YieldReturn(CoroutineParamType<TRet> ret)
			{

				auto data = Process::Fiber::GetFiberData<Detail::CoroutineStorageHead<TRet>>();
				assert(data);
				assert(data->ContextPtr);

				data->ContextPtr->Ret = const_cast<CoroutineStorageType<TRet>>(&ret);

				Detail::_SwitchToLastFiber(data);
			}

			template<typename TRet>
			_STD enable_if_t<!IsSavePointer<TRet>::value>
				YieldReturn(CoroutineParamType<TRet> ret)
			{
				auto data = Process::Fiber::GetFiberData<Detail::CoroutineStorageHead<TRet>>();
				assert(data);
				assert(data->ContextPtr);
				data->ContextPtr->Ret = ret;

				Detail::_SwitchToLastFiber(data);
			}
			template<typename TRet>
			auto GetYieldReturnFunc()
			{
				return YieldReturn<TRet>;
			}
		}  // namespace Detail







		// 注意如果在纤程里修改了用传入参数的值，第二次迭代的时候会用新的值
		template<typename TRet, typename TFunc, typename... TArgs>
		class Coroutine
		{
		public:

			using ReturnFunc = decltype(Detail::GetYieldReturnFunc<TRet>());
			typedef Detail::CoroutineIterator<TRet, TFunc, ReturnFunc, TArgs...> iterator;
			Coroutine(TFunc&& func, TArgs... args) :
				func_(_STD make_shared<Detail::CoroutineFuncStorage<TFunc, ReturnFunc, TArgs...>>(
					_STD move(func),
					_STD forward_as_tuple<ReturnFunc, TArgs...>(Detail::GetYieldReturnFunc<TRet>(), _STD forward<TArgs>(args)...)))
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
					_STD forward_as_tuple<ReturnFunc, TArgs...>(Detail::GetYieldReturnFunc<TRet>(), _STD forward<TArgs>(args)...);
			}
		protected:
			Detail::CoroutineFuncStoragePtr<TFunc, ReturnFunc, TArgs...> func_;
		};

		template<typename TRet, typename TFunc, typename... TArgs>
		Coroutine<TRet, TFunc, TArgs...> MakeCoroutine(TFunc&& func, TArgs... args)
		{
			return Coroutine<TRet, TFunc, TArgs...>(_STD move(func), _STD forward<TArgs>(args)...);
		}
	}  // namespace Fiber
}  // namespace Process