#pragma once
#include "Common.h"
namespace Process
{
	namespace Thread
	{
		enum class ContextFlag :DWORD
		{
			All = CONTEXT_ALL,
			Control = CONTEXT_CONTROL,
			DebugRegisters = CONTEXT_DEBUG_REGISTERS,
#ifdef	_X86_
			ExtendedRegisters = CONTEXT_EXTENDED_REGISTERS,
#endif
			FloatingPoint = CONTEXT_FLOATING_POINT,
			Full = CONTEXT_FULL,
			Integer = CONTEXT_INTEGER,
			Segments = CONTEXT_SEGMENTS,
			Xstate = CONTEXT_XSTATE,
		};

		enum class ThreadPriority :int
		{
			TimeCritical = THREAD_PRIORITY_TIME_CRITICAL,
			Highest = THREAD_PRIORITY_HIGHEST,
			AboveNormal = THREAD_PRIORITY_ABOVE_NORMAL,
			Normal = THREAD_PRIORITY_NORMAL,
			BelowNormal = THREAD_PRIORITY_BELOW_NORMAL,
			Lowest = THREAD_PRIORITY_LOWEST,
			Idle = THREAD_PRIORITY_IDLE,
		};
		// 为了方便替换各个函数的实现，所以统一用这个命名空间里的
		using ::SuspendThread;
		using ::ResumeThread;
		using ::GetThreadPriority;
		using ::SetThreadPriority;
		using ::SetThreadAffinityMask;
		using ::GetThreadContext;
		// 这个有重写版本，需要就直接替换就行了
		using ::SetThreadContext;
		using ::SetThreadIdealProcessor;

		namespace this_thread
		{
			DWORD Suspend();
			ThreadPriority GetPriority();
			bool SetPriority(ThreadPriority priority);
			DWORD_PTR SetAffinityMask(DWORD_PTR mask);
			_STD pair<bool, CONTEXT> GetContext(ContextFlag flag);
			bool SetContext(CONTEXT& context);

		}  // namespace this_thread


		template<typename TThread = _STD thread>
		class ThreadEx : public TThread
		{
		public:
			using TThread::TThread;


			class SuspendGuard
			{
			public:
				SuspendGuard(ThreadEx & t) :t_(t)
				{
					assert(t_.get_id() != _STD this_thread::get_id());
					t_.Suspend();
				}

				~SuspendGuard()
				{
					t_.Resume();
				}

			private:
				ThreadEx & t_;
			};
			// 注意在线程占有锁时挂起很容易引起死锁，无法确定在哪个位置挂起
			DWORD Suspend()
			{
				return Process::Thread::SuspendThread(Handle());
			}

			DWORD Resume()
			{
				return Process::Thread::ResumeThread(Handle());
			}

			ThreadPriority GetPriority()
			{
				return static_cast<ThreadPriority>(Process::Thread::GetThreadPriority(Handle()));
			}
			bool SetPriority(ThreadPriority priority)
			{
				return Process::Thread::SetThreadPriority(Handle(), static_cast<int>(priority)) != FALSE;
			}
			DWORD_PTR SetAffinityMask(DWORD_PTR mask)
			{
				return Process::Thread::SetThreadAffinityMask(Handle(), mask);
			}
			// 注意要挂起线程
			_STD pair<bool, CONTEXT> GetContext(ContextFlag flag)
			{
				_STD pair<bool, CONTEXT> result{ false,{ 0 } };
				result.second.ContextFlags = static_cast<DWORD>(flag);
				result.first = Process::Thread::GetThreadContext(Handle(), &result.second) != FALSE;
				return result;
			}
			bool SetContext(CONTEXT& context)
			{
				return Process::Thread::SetThreadContext(Handle(), &context) != FALSE;
			}

			DWORD SetIdealProcessor(DWORD idealProcessor)
			{
				return Process::Thread::SetThreadIdealProcessor(Handle(), idealProcessor);
			}
		protected:
			HANDLE Handle()
			{
				return static_cast<HANDLE>(native_handle());
			}
		};

	}  // namespace Thread

}  // namespace Process