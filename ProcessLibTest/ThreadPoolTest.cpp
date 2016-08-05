#include "stdafx.h"
#include "CppUnitTest.h"

#include <algorithm>
#include <numeric>
#include <Process\ThreadPool.h>
#include <Process\ThreadPoolSimpleCallback.h>
#include <Process\ThreadPoolWork.h>
#include <Process\ThreadPoolWait.h>
#include <Process\ThreadPoolTimer.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProcessLibTest
{
	TEST_CLASS(ThreadPoolTest)
	{
	public:
		TEST_METHOD(TestThreadPool)
		{
			using namespace Process::Thread;
			using namespace std;
			// 拆分任务分别计算

			std::condition_variable cv;
			typedef _STD vector<int> Vector;
			Vector vec(654321);
			_STD atomic<bool> inited = false;

			ThreadPool::SubmitCallback([&](CallbackInstance&)
			{
				_STD iota(begin(vec), end(vec), 1);
				inited.store(true, memory_order_release);
				cv.notify_all();
			});


			vector<future<long long>> futures;
			size_t vecLen = vec.size();
			size_t dataPerThread = vec.size() / thread::hardware_concurrency();
			// 每个线程分16次处理完，每次处理数据对64取整
			size_t step = (dataPerThread / 16) & (-64);
			auto begin = vec.begin();
			auto end = vec.end();

			std::mutex mtx;
			std::unique_lock<std::mutex> lock(mtx);
			cv.wait(lock, [&inited]()
			{
				return inited.load(memory_order_acquire);
			});
			while (begin < end)
			{
				auto dst = _STD distance(begin, end);
				auto tmpstep = dst > step ? step : dst;
				auto tmpend = begin + tmpstep;
				_STD packaged_task<long long(CallbackInstance&)> task([begin_ = begin, end_ = tmpend](CallbackInstance& instance) mutable
				{
					return accumulate<Vector::iterator, long long>(begin_, end_, 0);
				});
				begin = tmpend;
				futures.emplace_back(task.get_future());
				auto sumitResult = ThreadPool::SubmitCallback(move(task));
				Assert::IsTrue(sumitResult);
			}
			auto result = accumulate<vector<future<long long>>::iterator, long long>(futures.begin(), futures.end(), 0, [](long long ret, future<long long>& val)
			{
				return ret + val.get();
			});

			Assert::IsTrue(futures.size() == 1 + (vec.size() - 1) / step);

			long long trueResult = (*vec.begin() + *vec.rbegin()) * (double)vec.size() / 2;

			Assert::IsTrue(trueResult == result);

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
			if (e == NULL)
			{
				Assert::Fail(L"create event fail");
				return;
			}
			bool isWaitSucceed = false;
			std::condition_variable cv3;

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
}