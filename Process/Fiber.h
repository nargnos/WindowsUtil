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
		template<typename T>
		T* GetFiberData()
		{
			return static_cast<T*>(::GetFiberData());
		}


		class Fiber
		{
		public:

			typedef _STD function<void()> Func;
			// 函数参数用bind或lambda传入就行了
			Fiber(Func&& func);
			~Fiber();

			void Switch();
			LPVOID GetAddress();
		protected:
			Fiber(const Fiber&) = delete;
			Fiber& operator=(const Fiber&) = delete;

			static void WINAPI Run(LPVOID param);
			// 当前fiber指针
			LPVOID fiber_;
			// 执行体
			Func func_;
		};
	}  // namespace Fiber
}  // namespace Process