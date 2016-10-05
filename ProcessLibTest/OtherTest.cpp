#include "stdafx.h"
#include "CppUnitTest.h"

#include <random>
#include <Process\ThreadEx.h>
#include <Process\Fiber.h>
#include <Process\Coroutine.h>
#include <Process\Pipe.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProcessLibTest
{
	class DtorTestObj
	{
	public:
		DtorTestObj()
		{
			Logger::WriteMessage("---ctor");
		}

		~DtorTestObj()
		{
			Logger::WriteMessage("---dtor");

		}

	private:
	};
	TEST_CLASS(OtherTest)
	{
	public:
		OtherTest()
		{
			Process::Fiber::ConvertThreadToFiber(NULL);
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
					std::this_thread::sleep_for(std::chrono::milliseconds(50));
				}
			});


			std::this_thread::sleep_for(std::chrono::milliseconds(20));
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
			if (pf == nullptr)
			{
				pf = Process::Fiber::GetCurrentFiber();
			}
			PNT_TIB fiberCtx;

			{
				// 测试普通传参
				auto test1 = MakeFiber([pf, &fiberCtx](const char* val)
				{
					DtorTestObj obj;
					// 取上下文（试验）
					auto data = GetFiberData();
					// 实验看一下切换时会改什么 -> 这里存的都是指针，这个结构什么都没改
					// TODO: 找出用什么存储Xip
					fiberCtx = GetCurrentFiberContext();
					assert(data == fiberCtx->FiberData);

					Logger::WriteMessage("Begin Test");
					SwitchToFiber(pf);

					Logger::WriteMessage(val);
					return pf;
				}, "Succeed");
				if (!test1)
				{
					Assert::Fail();
				}

				test1.Switch();

				// 测试移动构造
				auto move1(_STD move(test1));

				move1.Switch();
			}


			// 测试引用传参
			bool test = false;
			auto test2 = MakeFiber([pf](bool& val)
			{
				Logger::WriteMessage("value = false");
				SwitchToFiber(pf);
				val = true;
				Logger::WriteMessage("value = true");
				return pf;
			}, _STD ref(test));

			if (!test2)
			{
				Assert::Fail();
			}

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
			unique_ptr<int> val9 = make_unique<int>(123);
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
				auto x = move(arg9);
				return pf;
			}, val0, val1, _STD ref(val2), _STD ref(val3), val4, val5, val6, 12345, 67890, _STD move(val9));


			if (!test3)
			{
				Assert::Fail();
			}

			test3.Switch();
			Assert::IsTrue((bool)val9);
			test3.Switch();
			Assert::IsFalse((bool)val9);


			// 无参测试
			auto test4 = MakeFiber([pf]()
			{
				DtorTestObj obj;
				Logger::WriteMessage("无参测试");
				return pf;
			});
			if (!test4)
			{
				Assert::Fail();
			}

			test4.Switch();

			Logger::WriteMessage("End");
		}
		TEST_METHOD(TestUnpackTuple)
		{
			using Tuple::Invoke;
			using namespace std;

			bool val = false;

			Invoke([](bool val1, const bool& val2, const bool& val3)
			{
				Assert::IsTrue(!val1 && !val2);
			}, make_tuple(false, false, ref(val)));

			Invoke([](bool& val1, auto val2, auto val3)
			{
				Assert::IsTrue(!val1 && !val2 && !val3);
			}, make_tuple(ref(val), ref(val), val));

			Invoke([](bool&& val1, auto&& val2)
			{
				Assert::IsTrue(!val1 && !val2);
			}, forward_as_tuple(false, move(val)));

			Invoke([&](auto val1, auto val2, auto val3)
			{
				Assert::IsTrue(!val1 && !val2 && !val3);
			}, forward_as_tuple(false, ref(val), move(val)));


			shared_ptr<bool> sptr = make_shared<bool>(true);
			unique_ptr<bool> uptr = make_unique<bool>(true);
			Invoke([](auto& val1, auto& val2)
			{
				Assert::IsTrue(*val1.get());
				Assert::IsTrue(*val2.get());

			}, forward_as_tuple(ref(sptr), ref(uptr)));

			Invoke([](auto&& val1, auto&& val2)
			{
				auto val1Move = move(val1);
				Assert::IsTrue(*val1Move);
				auto val2Move = move(val2);
				Assert::IsTrue(*val2Move);

			}, forward_as_tuple(move(sptr), move(uptr)));
			Assert::IsFalse((bool)sptr);
			Assert::IsFalse((bool)uptr);

			auto result = Invoke([](auto val)
			{
				return val;
			}, tuple<bool>(false));
			Assert::IsTrue(!result);
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


			// 测试返回指针
			auto c = MakeCoroutine<int*>([&vec](auto yield, _STD vector<int>& v)
			{
				Assert::IsTrue(&vec == &v);
				for (auto val : v)
				{
					yield(&val);
				}
			}, _STD ref(vec));

			int i = 0;

			for (auto val : c)
			{
				Assert::IsTrue(*val == vec[i++]);
			}

			// 测试不return
			auto c2 = MakeCoroutine<int>([](auto yield)
			{
				DtorTestObj obj;
			});

			Assert::IsTrue(c2.begin() == c2.end());

			// 测试迭代器适配和返回值
			auto fi = MakeCoroutine<int>([](auto yield, auto num)
			{
				DtorTestObj obj;
				int preLast = 1;
				yield(preLast);
				int last = 1;
				yield(last);
				int result;
				for (size_t i = 2; i < num; i++)
				{
					result = preLast + last;
					yield(result);
					preLast = last;
					last = result;
				}
			}, (size_t)10);


			_STD ostringstream out;
			_STD ostream_iterator<int> outIt(out, " ");

			_STD copy(_STD begin(fi), _STD end(fi), outIt);
			Logger::WriteMessage(out.str().c_str());


			// 测试重置参数
			fi.RetsetParams(20);
			out.swap(_STD ostringstream());
			// 用另一种输出方式，测试返回引用
			// 向协程输入内容
			auto output = MakeCoroutine<int&>([&out](auto yield)
			{
				int input = 0;
				do
				{
					yield(input);
					out << input << " ";
				} while (true);
			});

			_STD copy(_STD begin(fi), _STD end(fi), _STD begin(output));
			Logger::WriteMessage(out.str().c_str());

			// 直接生成adapter测试
			char* outputStr[]{ "Coroutine","测试","成功" };
			// 可以合并到下面的语句里去，但是太乱，分开来写
			auto lambda = [](auto yield, char** begin, char** end)
			{
				_STD for_each(begin, end, [&yield](char* str)
				{
					yield(_STD string(str));
				});
			};

			for (auto& str : MakeCoroutine<_STD string>(lambda, _STD begin(outputStr), _STD end(outputStr)))
			{
				Logger::WriteMessage(str.c_str());
			}

			// 传递临时变量引用
			int num = 0;
			auto refTest = MakeCoroutine<_STD reference_wrapper<volatile int>>([](auto yield, int& v)
			{
				volatile int result = 123;
				yield(_STD ref(result));
				Assert::IsTrue(result == 456);
				v = 123456;
			}, _STD ref(num));
			auto bgn = refTest.begin();
			auto val = *bgn;
			Assert::IsTrue(val == 123);
			val.get() = 456;
			++bgn;
			Assert::IsTrue(num == 123456);


			// 嵌套测试
			// 重设一下参数
			fi.RetsetParams(30);
			auto qtest = MakeCoroutine<_STD string>([&fi, &out, &outIt](auto yield)
			{
				out.swap(_STD ostringstream());
				_STD copy(_STD begin(fi), _STD end(fi), outIt);
				yield(out.str());
			});

			Logger::WriteMessage((*qtest.begin()).c_str());


			// 多类型测试
			// bool
			auto type1 = MakeCoroutine<bool>([](auto yield)
			{
				yield(true);
				auto ret = true;
				yield(ret);
			});
			for (auto val : type1)
			{
				Assert::IsTrue(val);
			}

			auto type1Ref = MakeCoroutine<bool&>([](auto yield)
			{
				// yield(true);
				auto ret = true;
				yield(ret);
				Assert::IsTrue(!ret);
				ret = !ret;
				yield(ret);
			});
			for (auto& val : type1Ref)
			{
				Assert::IsTrue(val);
				val = !val;
			}
			auto type1Ptr = MakeCoroutine<bool*>([](auto yield)
			{
				// yield(true);
				auto ret = true;
				yield(&ret);
				Assert::IsTrue(!ret);
				ret = !ret;
				yield(&ret);
			});
			for (auto val : type1Ptr)
			{
				if (val == nullptr)
				{
					Assert::Fail();
					break;
				}
				Assert::IsTrue(*val);
				*val = !*val;
			}

			// long long
			auto type2 = MakeCoroutine<long long>([](auto yield)
			{
				yield(123456);
				auto ret = 123456;
				yield(ret);
			});

			for (const auto& val : type2)
			{
				Assert::IsTrue(val == 123456);
			}
			for (auto val : type2)
			{
				Assert::IsTrue(val == 123456);
			}

			auto type2Ref = MakeCoroutine<long long&>([](auto yield)
			{
				long long ret = 123456;
				yield(ret);
				Assert::IsTrue(ret == 654321);
				ret = 123456;
				yield(ret);
			});
			for (auto& val : type2Ref)
			{
				Assert::IsTrue(val == 123456);
				val = 654321;
			}

			auto type2cRef = MakeCoroutine<const long long&>([](auto yield)
			{
				long long ret = 123456;
				yield(ret);
				yield(123456);
			});
			for (const auto& val : type2cRef)
			{

				Assert::IsTrue(val == 123456);
			}

			// string
			auto type3 = MakeCoroutine<_STD string>([](auto yield)
			{
				yield(_STD string("Hello World"));
				_STD string str = "Hello World";
				yield(str);
			});
			for (auto& val : type3)
			{
				Assert::AreEqual(val.c_str(), "Hello World");
			}

			auto type3Ref = MakeCoroutine<_STD string&>([](auto yield)
			{
				_STD string str = "Hello World";
				yield(str);
				str.reserve();
				yield(str);

			});
			for (auto& val : type3Ref)
			{
				Assert::AreEqual(val.c_str(), "Hello World");
				val.reserve();
			}
			// 未处理&&，当作&来用
			auto type3Move = MakeCoroutine<_STD string&&>([](auto yield)
			{
				_STD string str = "Hello World";
				yield(str);
				str.reserve();
				yield(str);

			});

			for (auto& val : type3Move)
			{
				Assert::AreEqual(val.c_str(), "Hello World");
				val.reserve();
			}

			for (auto val : MakeCoroutine<int>([](auto yield)
			{}))
			{
				Assert::Fail();
			}

			Logger::WriteMessage("Exit");
		}


		TEST_METHOD(TestPipe)
		{
			using namespace Process::InterProcess;

			auto pipeName = L"\\\\.\\pipe\\echo";
			NamePipeServer<false> server(pipeName);

			Assert::IsTrue(server.IsOpen());

			_STD thread t([&]()
			{
				bool isStop = false;
				while (!isStop)
				{
					char buffer[128]{ 0 };
					if (server.WaitForConnection())
					{
						while (!isStop)
						{
							auto reads = server.Read(buffer, sizeof(buffer));
							if (!reads.Result)
							{
								break;
							}
							if (strcmp(buffer, "Exit") == 0)
							{
								isStop = true;
								break;
							}
							auto writes = server.Write(buffer, reads.NumberOfBytesTransferred);
							if (!writes.Result)
							{
								break;
							}
							Assert::IsTrue(writes.NumberOfBytesTransferred == reads.NumberOfBytesTransferred);
						}
					}
				}
			});



			std::string random("1234567890");
			auto randomLen = random.length();
			_STD random_shuffle(_STD begin(random), _STD end(random));

			NamePipeClient<true> client(pipeName);

			WaitNamedPipe(pipeName, NMPWAIT_WAIT_FOREVER);
			if (!client.Connect())
			{
				Assert::Fail();
				return;
			}

			char buffer[100]{ 0 };
			auto writes = client.Write(random.c_str(), random.length() + 1);
			Assert::IsTrue(writes.Result);

			auto result = writes.AsyncResult.get();
			if (result.IoResult != S_OK)
			{
				Assert::Fail();
				return;
			}
			auto reads = client.Read(buffer, result.NumberOfBytesTransferred);
			Assert::IsTrue(reads.Result);

			result = reads.AsyncResult.get();
			if (result.IoResult != S_OK)
			{
				Assert::Fail();
				return;
			}

			Assert::AreEqual(buffer, random.c_str());
			std::string exit("Exit");
			auto ret = client.Write(exit.c_str(), exit.length() + 1);
			ret.AsyncResult.get();
			server.Dispose();
			t.join();
		}
	};
	_STD pair<bool, CONTEXT> OtherTest::OldContext;
	bool OtherTest::IsContextTestSucceed = true;
}