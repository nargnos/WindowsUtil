#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include <algorithm>
#include <random>
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
#include <Process\Coroutine.h>
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

			auto pf = Process::Fiber::ConvertThreadToFiber(NULL);

			// 测试普通传参
			auto test1 = MakeFiber([pf](const char* val)
			{
				Logger::WriteMessage("Begin Test");
				SwitchToFiber(pf);
				Logger::WriteMessage(val);
				SwitchToFiber(pf);
			}, "Succeed");
			auto ptr = test1.NativeHandle();
			test1.Switch();
			// 测试移动构造
			auto move1(_STD move(test1));

			move1.Switch();

			// 测试引用传参
			bool test = false;
			auto test2 = MakeFiber([pf](bool& val)
			{
				Logger::WriteMessage("value = false");
				SwitchToFiber(pf);
				val = true;
				Logger::WriteMessage("value = true");
				SwitchToFiber(pf);
			}, _STD ref(test));

			test2.Switch();
			Assert::IsTrue(!test);
			// 测试移动构造
			auto move2(_STD move(test2));
			move2.Switch();
			Assert::IsTrue(test);

			// 测试传多参(顺便测的是解包tuple是否正确)
			int intVal = 123;
			short shortVal = 456;

			const void* val0 = &intVal;
			void* val1 = &shortVal;
			const int& val2 = intVal;
			short& val3 = shortVal;
			char val4 = 'X';
			shared_ptr<string> val5 = make_shared<string>("Str");
			tuple<int> val6 = make_tuple(789);
			unique_ptr<int> val9;
			auto test3 = MakeFiber([pf](
				const void* arg0,
				void* arg1,
				const int& arg2,
				short& arg3,
				char arg4,
				shared_ptr<string> arg5,
				tuple<int> arg6,
				const int& arg7,
				int&& arg8,
				unique_ptr<int>&& arg9
				)
			{
				SwitchToFiber(pf);
			}, val0, val1, _STD ref(val2), _STD ref(val3), val4, val5, val6, 12345, 67890, _STD move(val9));
			test3.Switch();


			// 无参测试
			auto test4 = MakeFiber([pf]()
			{
				Logger::WriteMessage("无参测试");
				SwitchToFiber(pf);
			});
			test4.Switch();
			Logger::WriteMessage("End");
		}
		TEST_METHOD(TestThreadPool)
		{
			using namespace Process::Thread;
			// 直接提交函数

			bool isSubmitCallbackSucceed = false;
			std::condition_variable cv1;

			ThreadPool::Submit([&isSubmitCallbackSucceed, &cv1](CallbackInstance& instance)
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

		TEST_METHOD(TestCoroutine)
		{
			using namespace Process::Fiber;
			// 生成测试数据
			_STD random_device seed;
			_STD default_random_engine ng(seed());

			_STD vector<int> vec;
			auto inst = _STD back_inserter(vec);
			_STD generate_n(inst, 10, ng);
			// 结束生成


			// 普通测试
			auto c = MakeCoroutine<int>([&vec](_STD vector<int>& v)
			{
				Assert::IsTrue(&vec == &v);
				for (auto val : v)
				{
					YieldReturn(val);
				}
			}, _STD ref(vec));

			int i = 0;

			for (auto val : c)
			{
				Assert::IsTrue(val == vec[i++]);
			}

			// 测试不return
			auto c2 = MakeCoroutine<int>([]()
			{});

			Assert::IsTrue(c2.begin() == c2.end());

			// 测试迭代器适配
			auto fi = MakeCoroutine<int>([](int num)
			{
				int preLast = 1;
				YieldReturn(preLast);
				int last = 1;
				YieldReturn(last);
				int result;
				for (size_t i = 2; i < num; i++)
				{
					result = preLast + last;
					YieldReturn(result);
					preLast = last;
					last = result;
				}
			}, 10);


			_STD ostringstream out;
			_STD ostream_iterator<int> outIt(out, " ");

			_STD copy(_STD begin(fi), _STD end(fi), outIt);
			Logger::WriteMessage(out.str().c_str());

			// 第二次使用，输出应该为同样内容
			out.swap(_STD ostringstream());
			_STD copy(_STD begin(fi), _STD end(fi), outIt);
			Logger::WriteMessage(out.str().c_str());

			// 测试重置参数
			fi.RetsetParams(20);
			out.swap(_STD ostringstream());
			// 用另一种输出方式
			for (auto val : fi)
			{
				out << val << " ";
			}
			Logger::WriteMessage(out.str().c_str());

			// 直接生成adapter测试
			char* outputStr[]{ "Coroutine","测试","成功" };
			// 可以合并到下面的语句里去，但是太乱，分开来写
			auto lambda = [](char** begin, char** end)
			{
				_STD for_each(begin, end, [](char* str)
				{
					YieldReturn(_STD string(str));
				});
			};

			for (auto& str : MakeCoroutine<_STD string>(lambda, _STD begin(outputStr), _STD end(outputStr)))
			{
				Logger::WriteMessage(str.c_str());
			}

			// 传递临时变量引用
			int num = 0;
			auto refTest = MakeCoroutine<_STD reference_wrapper<volatile int>>([](int& v)
			{
				volatile int result = 123;
				YieldReturn(_STD ref(result));
				Assert::IsTrue(result == 456);
				v = 123456;
			}, _STD ref(num));
			auto bgn = refTest.begin();
			auto val = *bgn;
			Assert::IsTrue(val == 123);
			val.get() = 456;
			++bgn;
			Assert::IsTrue(num == 123456);

			

			Logger::WriteMessage("Exit");
		}
	};
	_STD pair<bool, CONTEXT> UnitTest1::OldContext;
	bool UnitTest1::IsContextTestSucceed = true;
}