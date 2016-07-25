#pragma once
#include "Common.h"
namespace Process
{
	namespace Fiber
	{
		// fls的东西就忽略吧
		using ::GetCurrentFiber;
		using ::SwitchToFiber;
		using ::ConvertFiberToThread;
		using ::ConvertThreadToFiber;
		using ::CreateFiber;
		using ::DeleteFiber;
		using ::IsThreadAFiber;
		using ::GetFiberData;
		template<typename T>
		inline T* GetFiberData()
		{
			return static_cast<T*>(::GetFiberData());
		}
		// 这是看winnt得出的结论
		void SetCurrentFiberData(void* ptr);
		void SetFiberData(PVOID fiber, void* ptr);

		// 这个可能不对，有一些成员的值不对，应该有一部分是teb的内容
		const PNT_TIB GetCurrentFiberContext();

		template<typename T>
		inline T* GetFiberData(PVOID fiber)
		{
			assert(fiber != nullptr);
			return static_cast<T*>(*(PVOID *)fiber);
		}




		namespace Detail
		{
			template<typename TParamStoragePtr>
			class FiberObjectBase
			{
			public:
				FiberObjectBase(TParamStoragePtr&& storage) :
					paramStorage_(_STD move(storage))
				{

				}
				virtual ~FiberObjectBase() = default;
			protected:
				TParamStoragePtr paramStorage_;
			};

			template<typename TParamStoragePtr>
			class FiberObject :
				public FiberObjectBase<TParamStoragePtr>
			{
			public:
				// 默认stacksize, 不设置浮点支持(xp不支持)
				FiberObject(LPFIBER_START_ROUTINE lpStartAddress,
					TParamStoragePtr&& storage) :
					fiber_(Process::Fiber::CreateFiber(0, lpStartAddress, &paramStorage_)),
					FiberObjectBase<TParamStoragePtr>(_STD move(storage))
				{
				}

				~FiberObject()
				{
					if (fiber_ != nullptr)
					{
						Process::Fiber::DeleteFiber(fiber_);
						fiber_ = nullptr;
					}
				}
				explicit operator bool() const
				{
					return fiber_ != nullptr;
				}
				const void* GetDataPtr() const
				{
					return GetFiberData<void*>(fiber_);
				}
				void Switch()
				{
					// 切换线程必须转换为fiber
					assert(Process::Fiber::IsThreadAFiber());

					assert(fiber_);
					Process::Fiber::SwitchToFiber(fiber_);
				}
				void SetFiberData(void* dataPtr)
				{
					assert(fiber_);
					Process::Fiber::SetFiberData(fiber_, dataPtr);
				}
			private:
				FiberObject(const FiberObject&) = delete;
				const FiberObject operator=(const FiberObject&) = delete;

				void* fiber_;

			};

			template<typename TChild, typename TStorage>
			class FiberBase
			{
			public:
				typedef TStorage TStorage;
				typedef FiberBase TFiberBase;
				using TStoragePtr = _STD unique_ptr<TStorage>;
				using FiberPtr = _STD shared_ptr<FiberObject<TStoragePtr>>;

				virtual ~FiberBase() = default;
				explicit operator bool() const
				{
					return fiber_ && *fiber_;
				}
			protected:

				FiberBase()
				{
				}

				// 注意创建过程中不能出现异常
				// 传入的参数为TStorage的构造参数
				template<typename... TArgs>
				FiberBase(TArgs... args)
				{
					assert(!fiber_);

					TStoragePtr storage(new TStorage(_STD forward<TArgs>(args)...));

					if (!storage)
					{
						return;
					}
					fiber_ = _STD make_shared<FiberObject<TStoragePtr>>(Run, _STD move(storage));
				}


				void Switch()
				{
					assert(fiber_);
					fiber_->Switch();
				}


				static void WINAPI Run(LPVOID param)
				{
					assert(param != nullptr);

					auto& storageParam = *static_cast<TStoragePtr*>(param);
					// 重新设置fiberdata
					Process::Fiber::SetCurrentFiberData(storageParam.get());

					// 子类必须设置友元
					void* returnFiber = TChild::Callback(storageParam);
					assert(returnFiber);
					Process::Fiber::SwitchToFiber(returnFiber);

					// 运行结束了又跳回
					assert(false);
					__assume(false);
				}

				FiberPtr fiber_;
			};
		}  // namespace Detail
	}  // namespace Fiber
}  // namespace Process