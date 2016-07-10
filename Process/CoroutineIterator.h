#pragma once
#include "FiberBase.h"

namespace Process
{
	namespace Fiber
	{
		namespace Detail
		{
			// 如果返回类型无默认构造、无拷贝赋值、类型大于指针大小，就使用指针返回
			template<typename T>
			struct IsPointerReturnType
			{
				static constexpr int value = !_STD is_default_constructible<T>::value ||
					!_STD is_copy_assignable<T>::value ||
					sizeof(T) > sizeof(void*);
			};

			template<typename T>
			using CoroutineResultStorageType = _STD conditional_t<IsPointerReturnType<T>::value,
				T*, T>;
			template<typename T>
			using CoroutineResultType = _STD conditional_t<_STD is_pointer<CoroutineResultStorageType<T>>::value, const T&, T>;


			// 回调外可访问部分
			template<typename TRet>
			struct CoroutineContext
			{
				using TRetStorage = CoroutineResultStorageType<TRet>;
				CoroutineContext() :
					LastFiber(nullptr),
					IsDone(false),
					Ret(TRetStorage())
				{
					
				}
				bool IsDone;
				volatile PVOID LastFiber;

				TRetStorage Ret;
			};



			// 回调内持有部分
			template<typename TRet>
			struct CoroutineStorageHead
			{
				CoroutineStorageHead(_STD shared_ptr<CoroutineContext<TRet>>& contextPtr) :
					ContextPtr(contextPtr)
				{

				}
				virtual ~CoroutineStorageHead() = default;
				_STD shared_ptr<CoroutineContext<TRet>> ContextPtr;
			};

			enum class _CoroutineFuncStorageIndex :int
			{
				_Func,
				_Args
			};
			template<typename TFunc, typename... TArgs>
			using CoroutineFuncStorage = _STD tuple <TFunc, _STD tuple<TArgs...>>;

			template<typename TFunc, typename... TArgs>
			using CoroutineFuncStoragePtr = _STD shared_ptr<CoroutineFuncStorage<TFunc, TArgs...>>;


			template<typename TRet, typename TFunc, typename... TArgs>
			struct CoroutineStorage :
				public CoroutineStorageHead<TRet>
			{
				CoroutineStorage(_STD shared_ptr<CoroutineContext<TRet>>& context, CoroutineFuncStoragePtr<TFunc, TArgs...>& func) :
					FuncTuplePtr(func),
					CoroutineStorageHead<TRet>(context)
				{

				}
				CoroutineFuncStoragePtr<TFunc, TArgs...> FuncTuplePtr;

			};

			template<typename TRet>
			void _SwitchToLastFiber(CoroutineStorageHead<TRet>* data)
			{
				assert(data->ContextPtr->LastFiber != nullptr);
				Process::Fiber::SwitchToFiber(data->ContextPtr->LastFiber);
			}
			template<typename TRet>
			struct _ContextInit
			{
			protected:
				_ContextInit() :
					context_(_STD make_shared<CoroutineContext<TRet>>())
				{

				}
				_STD shared_ptr<CoroutineContext<TRet>> context_;
			};




			template<typename TRet, typename TFunc, typename... TArgs>
			class CoroutineIterator :
				public Detail::_ContextInit<TRet>,
				public Detail::FiberBase<
				CoroutineIterator<TRet, TFunc, TArgs...>,
				Detail::CoroutineStorage<TRet, TFunc, TArgs...>>,
				public _STD iterator<_STD forward_iterator_tag, TRet>
			{
			public:
				static_assert(!_STD is_void<TRet>::value, "TRet != void");
				friend Base;

				CoroutineIterator(Detail::CoroutineFuncStoragePtr<TFunc, TArgs...>& func) :
					Base(context_, func)
				{

				}
				CoroutineIterator() = default;

				~CoroutineIterator() = default;

				CoroutineResultType<TRet> operator->()
				{
					return Dereference<TRet>();
				}
				CoroutineResultType<TRet> operator*()
				{
					return Dereference<TRet>();
				}

				void operator++()
				{
					Do();
				}

				/*value_type operator++(int)
				{
					auto result = Dereference();
					Do();
					return result;
				}*/

				bool IsDone()
				{
					assert(context_);
					return context_->IsDone;
				}
				bool operator==(CoroutineIterator& tag)
				{
					assert(context_);
					return context_->IsDone;
				}
				bool operator!=(CoroutineIterator& tag)
				{
					return !operator==(tag);
				}

			protected:
				void Do()
				{
					assert(context_);
					assert(!context_->IsDone);

					if (!Process::Fiber::IsThreadAFiber())
					{
						Process::Fiber::ConvertThreadToFiber(NULL);
					}
					SetLastFiber();
					Switch();
				}
				//
				
				template<typename T>
				CoroutineResultType<T> Dereference(_STD enable_if_t<Detail::IsPointerReturnType<TRet>::value>* =nullptr) const
				{
					assert(!context_->IsDone);
					return *context_->Ret;
				}
				template<typename T>
				CoroutineResultType<T> Dereference(_STD enable_if_t<!Detail::IsPointerReturnType<TRet>::value>* =nullptr) const
				{
					assert(!context_->IsDone);
					return context_->Ret;
				}
				

				void SetLastFiber()
				{
					context_->LastFiber = Process::Fiber::GetCurrentFiber();
				}

				static void WINAPI Callback(const TStoragePtr& storage)
				{
					assert(storage != nullptr);
					auto& ptr = *storage->FuncTuplePtr;
					auto& func = _STD get<static_cast<int>(Detail::_CoroutineFuncStorageIndex::_Func)>(ptr);
					auto& args = _STD get<static_cast<int>(Detail::_CoroutineFuncStorageIndex::_Args)>(ptr);
					Tuple::Invoke(func, args);

					// 运行结束
					storage->ContextPtr->IsDone = true;
					_SwitchToLastFiber(storage.get());

				}

			};
		}  // namespace Detail
	}  // namespace Fiber
}  // namespace Process