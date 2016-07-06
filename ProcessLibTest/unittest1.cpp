#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include <condition_variable>
#include <Process\FindLoadedModuleHandle.h>
#include <Process\GetProcAddress.h>
#include <Process\NtDll.h>
#include <Process\User32.h>
#include <Process\ThreadEx.h>
#include <Process\Fiber.h>
#include <Process\ThreadPool.h>
#include <Process\ThreadPoolSimpleCallback.h>
#include <Process\ThreadPoolWork.h>
#include <Process\ThreadPoolWait.h>
#include <Process\ThreadPoolTimer.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProcessLibTest
{
	using namespace Process::EnvironmentBlock;

	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestLdrDataTable)
		{
			auto dllName = L"user32.dll";
			auto handle = FindLoadedModuleHandle(dllName);
			auto handle2 = LoadLibrary(dllName);
			Assert::IsTrue(handle == handle2);

		}
		TEST_METHOD(TestGetProcAddress)
		{
			auto dllName = L"user32.dll";
			auto dllHandle = FindLoadedModuleHandle(dllName);
			auto funcNameGrp = { "MessageBoxW" ,"NotExist" };
			for each (auto var in funcNameGrp)
			{
				auto funcName = var;
				auto funcHandle1 = Process::Overwrite::GetProcAddress(dllHandle, [funcName](LPCSTR val)
				{
					return strcmp(funcName, val) == 0;
				});
				auto funcHandle2 = Process::Overwrite::GetProcAddress(dllHandle, funcName);
				auto trueValue = ::GetProcAddress(dllHandle, funcName);
				Assert::IsTrue(trueValue == funcHandle1);
				Assert::IsTrue(trueValue == funcHandle2);
			}

		}
		TEST_METHOD(TestLazyload)
		{
			using Process::LazyLoad::NtDll;
			using Process::LazyLoad::User32;
			auto& ldrLoadDll = NtDll::Instance().LdrLoadDll;
			ldrLoadDll.Load();
			// funtion没有取指针的函数验证不了只能下断点了
			auto trueValue = GetProcAddress(GetModuleHandleA("ntdll.dll"), "LdrLoadDll");

			auto& mbox = User32::Instance().MessageBoxA;
			mbox(0, "Hello World!", "Goodbye World!", MB_OK);
		}
		static _STD pair<bool, CONTEXT> OldContext;
		static bool IsContextTestSucceed;
		static void Output()
		{
			using namespace Process::Thread;
#ifdef _X86_
			Logger::WriteMessage("Set Eip Test");
#else
			Logger::WriteMessage("Set Rip Test");
#endif // _X86_
			for (size_t i = 0; i < 10; i++)
			{
				std::ostringstream s("-> ", std::ios::ate);
				s << i;
				Logger::WriteMessage(s.str().c_str());
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			Process::Thread::this_thread::SetContext(OldContext.second);
			IsContextTestSucceed = false;

		}
		TEST_METHOD(TestThreadEx)
		{
			using namespace Process::Thread;
			using ThreadEx = ThreadEx<>;

			ThreadEx t([]()
			{
				// 测试挂起线程
				Logger::WriteMessage("Suspend");
				this_thread::Suspend();
				Logger::WriteMessage("Resume");
				for (size_t i = 0; i < 10; i++)
				{
					Logger::WriteMessage("-->");
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
				}
			});


			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			t.Resume();

			//测试设置优先级
			auto priority = ThreadPriority::AboveNormal;
			Assert::IsTrue(t.SetPriority(priority));
			Assert::IsTrue(t.GetPriority() == priority);

			// 测试cpu关联
			auto mask = 1;
			auto oldMask = t.SetAffinityMask(mask);
			Assert::IsTrue(t.SetAffinityMask(oldMask) == mask);

			// 测试修改context
			std::this_thread::sleep_for(std::chrono::seconds(1));
			{
				ThreadEx::SuspendGuard guard(t);
				OldContext = t.GetContext(ContextFlag::Full);
				auto ctx = OldContext.second;
#ifdef _X86_
				auto xip = &CONTEXT::Eip;
				auto xsp = &CONTEXT::Esp;
				using reg = DWORD;
#else
				auto xip = &CONTEXT::Rip;
				auto xsp = &CONTEXT::Rsp;
				using reg = DWORD64;
#endif // _X86_
				ctx.*xip = reinterpret_cast<reg>(&Output);
				// 栈顶上移防止附近的内容被改了
				ctx.*xsp -= sizeof(reg) * 0x10;

				t.SetContext(ctx);
			}
			t.join();
			Assert::IsTrue(IsContextTestSucceed);
		}
		TEST_METHOD(TestFiber)
		{
			using namespace Process::Fiber;
			using namespace std;

			char chr[] = "A";
			thread t([&chr]()
			{
				auto pf = ConvertThreadToFiber(NULL);
				
				{ // 测试局部变量析构
					Fiber f1([&chr, pf]() mutable
					{
						Logger::WriteMessage(chr);
						++chr[0];
						// 纤程里弄个纤程
						Fiber f2([&chr, f1Ptr = Process::Fiber::GetCurrentFiber()]() mutable
						{
							Logger::WriteMessage(chr);
							++chr[0];
							SwitchToFiber(f1Ptr);
						});
						f2.Switch();
						SwitchToFiber(pf);
					});
					f1.Switch();
				}
				Logger::WriteMessage(chr);
			});
			t.join();
			Assert::AreEqual(chr, "C");

			int num = 0;
			std::vector<unique_ptr<Fiber>> fibers;

			auto pf = ConvertThreadToFiber(NULL);
			auto tmpPf = pf;
			for (size_t i = 0; i < 100; i++)
			{

				fibers.emplace_back(new Fiber([&num, tmpPf]()
				{
					++num;
					SwitchToFiber(tmpPf);
				}));
				tmpPf = fibers.back()->GetAddress();
			}
			fibers.back()->Switch();
			Assert::IsTrue(num == 100);

			bool isDone = false;
			Fiber yield([&num, pf, &isDone]()
			{
				for (; num > 0; num--)
				{
					SwitchToFiber(pf);
				}
				isDone = true;
				SwitchToFiber(pf);
			});

			size_t i = num;
			while (!isDone)
			{
				yield.Switch();
				Assert::IsTrue(i-- == num);
			}
			Logger::WriteMessage("Exit");

		}
		TEST_METHOD(TestThreadPool)
		{
			using namespace Process::Thread;
			// 直接提交函数
			ThreadPool::Submit([](CallbackInstance& instance)
			{
				Logger::WriteMessage("Submit");
			});

			bool isSubmitCallbackSucceed = false;
			std::condition_variable cv1;

			ThreadPool::SubmitCallback([&isSubmitCallbackSucceed, &cv1](CallbackInstance& instance)
			{
				Logger::WriteMessage("SubmitCallback");
				instance.MayRunLong();
				isSubmitCallbackSucceed = true;
				cv1.notify_all();
			});
			std::mutex mtx;
			std::unique_lock<std::mutex> lock(mtx);
			cv1.wait_for(lock, std::chrono::seconds(1), [&isSubmitCallbackSucceed]()
			{
				return isSubmitCallbackSucceed;
			});
			Assert::IsTrue(isSubmitCallbackSucceed);
		}
		TEST_METHOD(TestThreadPoolSimpleCallback)
		{
			using namespace Process::Thread;
			// 测试ThreadPoolSimpleCallback
			bool isSimpleCallbackSucceed = false;
			std::condition_variable cv2;
			ThreadPoolSimpleCallback sc([&isSimpleCallbackSucceed, &cv2](CallbackInstance& inst)
			{
				Logger::WriteMessage("ThreadPoolSimpleCallback");
				isSimpleCallbackSucceed = true;
				cv2.notify_all();
			});
			ThreadPool::Submit(sc);

			std::mutex mtx;
			std::unique_lock<std::mutex> lock(mtx);
			cv2.wait_for(lock, std::chrono::seconds(1), [&isSimpleCallbackSucceed]()
			{
				return isSimpleCallbackSucceed;
			});

			Assert::IsTrue(isSimpleCallbackSucceed);
		}
		TEST_METHOD(TestThreadPoolWork)
		{
			using namespace Process::Thread;
			// 测试ThreadPoolWork
			bool isWorkSucceed = false;
			ThreadPoolWork work([&isWorkSucceed](CallbackInstance& instance, ThreadPoolWork& self)
			{
				Logger::WriteMessage("ThreadPoolWork");

				isWorkSucceed = true;
			});
			ThreadPool::Submit(work);
			// 测试等待
			work.WaitForCallbacks();

			Assert::IsTrue(isWorkSucceed);
		}
		TEST_METHOD(TestThreadPoolWait)
		{
			using namespace Process::Thread;

			// 测试ThreadPoolWait
			// TODO: 之后这类同步的东西也要做一个封装
			auto e = CreateEvent(NULL, true, false, NULL);
			bool isWaitSucceed = false;
			std::condition_variable cv3;
			if (e == NULL)
			{
				Assert::Fail(L"create event fail");
			}
			ThreadPoolWait wait(e, NULL, [&isWaitSucceed, &cv3](CallbackInstance&, ThreadPoolWait&, WaitResult)
			{
				Logger::WriteMessage("ThreadPoolWait");
				isWaitSucceed = true;
				cv3.notify_all();
			});
			ThreadPool::Register(wait);


			// 触发
			SetEvent(e);
			CloseHandle(e);

			wait.WaitForCallbacks();

			std::mutex mtx;
			std::unique_lock<std::mutex> lock(mtx);
			cv3.wait_for(lock, std::chrono::seconds(1), [&isWaitSucceed]()
			{
				return isWaitSucceed;
			});

			Assert::IsTrue(isWaitSucceed);

		}
		TEST_METHOD(TestThreadPoolTimer)
		{
			using namespace Process::Thread;
			char outputStr[] = "ThreadPoolTimer";

			ULARGE_INTEGER dueTime;
			dueTime.QuadPart = (ULONGLONG)-1;// (1 * 10 * 1000 * 1000);

			FILETIME time;
			time.dwHighDateTime = dueTime.HighPart;
			time.dwLowDateTime = dueTime.LowPart;
			auto it = std::begin(outputStr);
			std::condition_variable cv;
			DWORD period = 100;
			ThreadPoolTimer timer(&time, period, 0, [&it, end = std::end(outputStr), &cv](CallbackInstance&, ThreadPoolTimer& self)
			{
				auto& chr = *(it + 1);
				auto bak = chr;
				chr = 0;
				Logger::WriteMessage(it);
				chr = bak;
				if (++it == end)
				{
					self.WaitForCallbacks(true);
					cv.notify_all();
				}
			});

			ThreadPool::Register(timer);
			std::mutex mtx;
			std::unique_lock<std::mutex> lock(mtx);
			cv.wait_for(lock, std::chrono::milliseconds(period*(sizeof(outputStr) + 10)), [&it, end = std::end(outputStr)]()
			{
				return it == end;
			});

			Assert::IsTrue(it == std::end(outputStr));
		}
	};
	_STD pair<bool, CONTEXT> UnitTest1::OldContext;
	bool UnitTest1::IsContextTestSucceed = true;
}