#pragma once
#include "FiberBase.h"

namespace Process
{
	namespace Fiber
	{
		namespace Detail
		{
			// 类型->存储->返回
			// 引用->ptr->引用 
			// 指针或算术类型且大小小于指针->val->val
			// 无默认构造或无复制赋值或大于指针的算术类型->ptr->const ref
			// 其它->val->val
			// 以上需要保持const标识
			// TODO: 有必要处理&&吗？
			enum _CoroutineType :char
			{
				_Ref,
				_Value,
				_ConstRef
			};
			template<typename T>
			struct IsBigSize :
				public _STD integral_constant<bool, (sizeof(T) > sizeof(void*)) >
			{

			};
			template<typename T>
			struct CoroutineTypeID :
				public _STD integral_constant<_CoroutineType,
				(_STD is_reference<T>::value ? _Ref :
				((_STD is_fundamental<T>::value && !IsBigSize<T>::value) ? _Value :
					((!_STD is_default_constructible<T>::value ||
						!_STD is_nothrow_copy_assignable<T>::value ||
						(_STD is_compound<T>::value && IsBigSize<T>::value)) ? _ConstRef : _Value)))>
			{
			};

			// 表示类型被转换为指针存储（指针是值存储返回false）
			template<typename T>
			struct IsSavePointer :
				public _STD integral_constant<bool,
				CoroutineTypeID<T>::value == _Ref || CoroutineTypeID<T>::value == _ConstRef>
			{

			};

			template<typename T>
			using CoroutineStorageType = _STD remove_const_t<_STD conditional_t<
				IsSavePointer<T>::value, _STD decay_t<T>*, T>>;

			template<typename T>
			using CoroutineResultType = _STD conditional_t<(CoroutineTypeID<T>::value == _Ref), T&,
				_STD conditional_t<(CoroutineTypeID<T>::value == _Value), T,
				_STD conditional_t<(CoroutineTypeID<T>::value == _ConstRef), const T&, T>>>;

			template<typename T>
			using CoroutineParamType = _STD remove_const_t<_STD conditional_t<(CoroutineTypeID<T>::value == _Ref), T&,
				_STD conditional_t<(CoroutineTypeID<T>::value == _Value), T,
				_STD conditional_t<(CoroutineTypeID<T>::value == _ConstRef), T&, T>>>>;

			// 回调外可访问部分
			template<typename TRet>
			struct CoroutineContext
			{
				using TRetStorage = CoroutineStorageType<TRet>;
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
				CoroutineStorage(_STD shared_ptr<CoroutineContext<TRet>>& context,
					CoroutineFuncStoragePtr<TFunc, TArgs...>& func) :
					FuncTuplePtr(func),
					CoroutineStorageHead<TRet>(context)
				{

				}
				CoroutineFuncStoragePtr<TFunc, TArgs...> FuncTuplePtr;

			};
			template<typename TRet>
			void* _GetLastFiber(CoroutineStorageHead<TRet>* data)
			{
				assert(data);
				assert(data->ContextPtr);
				assert(data->ContextPtr->LastFiber);
				return data->ContextPtr->LastFiber;
			}

			template<typename TRet>
			void _SwitchToLastFiber(CoroutineStorageHead<TRet>* data)
			{
				Process::Fiber::SwitchToFiber(_GetLastFiber(data));
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
				public _STD iterator<_STD forward_iterator_tag,
				TRet,
				ptrdiff_t,
				_STD decay_t<TRet>*,
				_STD conditional_t<_STD is_reference<TRet>::value, TRet, TRet&>>
			{
			public:

				static_assert(!_STD is_void<TRet>::value, "TRet != void");
				friend TFiberBase;

				CoroutineIterator(Detail::CoroutineFuncStoragePtr<TFunc, TArgs...>& func) :
					TFiberBase(context_, func)
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
				_STD enable_if_t<IsSavePointer<T>::value, CoroutineResultType<T>>
					Dereference() const
				{
					assert(!context_->IsDone);
					return *context_->Ret;
				}
				template<typename T>
				_STD enable_if_t<!IsSavePointer<T>::value, CoroutineResultType<T>>
					Dereference() const
				{
					assert(!context_->IsDone);
					return context_->Ret;
				}


				void SetLastFiber()
				{
					context_->LastFiber = Process::Fiber::GetCurrentFiber();
				}

				static void* WINAPI Callback(const TStoragePtr& storage)
				{
					assert(storage != nullptr);
					auto& ptr = *storage->FuncTuplePtr;
					auto& func = _STD get<static_cast<int>(Detail::_CoroutineFuncStorageIndex::_Func)>(ptr);
					auto& args = _STD get<static_cast<int>(Detail::_CoroutineFuncStorageIndex::_Args)>(ptr);
					Tuple::Invoke(func, args);

					// 运行结束
					storage->ContextPtr->IsDone = true;
					return _GetLastFiber(storage.get());
				}

			};
		}  // namespace Detail
	}  // namespace Fiber
}  // namespace Process