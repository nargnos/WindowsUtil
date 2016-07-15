#pragma once
#include "Common.h"
#include "CallbackInstance.h"
#include "ThreadPoolApi.h"
namespace Process
{
	namespace Thread
	{
		namespace Detail
		{

			// function会复制一份函数，如果lambda中catch了只能move的对象，会导致编译不过
			template<typename TFunc>
			void NTAPI _Callback(PTP_CALLBACK_INSTANCE instance, PVOID param)
			{
				assert(param != nullptr);
				auto data = static_cast<_STD tuple<_STD decay_t<TFunc>>*>(param);
				_STD decay_t<TFunc> func(_STD move(_STD get<0>(*data)));
				delete data;

				CallbackInstance inst(instance);
				func(inst);
			}

		}  // namespace Detail

		// FIX: 用到的API都是新的，需要弄一个旧的版本
		// 不过这个没有什么意义，直接用ppl就好了
		class ThreadPool
		{
		public:
			template<typename T>
			static bool Submit(T& obj)
			{
				assert(obj.GetFunc());
				return obj.Submit(GetEnviron());
			}
			// 这里传入的函数参数必须为 CallbackInstance&
			template<typename TFunc>
			static bool SubmitCallback(TFunc&& func)
			{
				auto funcPtr = new _STD tuple<_STD decay_t<TFunc>>(_STD forward<TFunc>(func));
				assert(funcPtr);
				auto result = Detail::WinApi::TrySubmitThreadpoolCallback(Detail::_Callback<TFunc>, funcPtr, GetEnviron()) != FALSE;
				if (!result)
				{
					delete funcPtr;
				}
				return result;
			}


			template<typename T>
			static bool Register(T& obj)
			{
				assert(obj.GetFunc());
				return obj.Register(GetEnviron());
			}


			static void SetEnviron(PTP_CALLBACK_ENVIRON env);
			static PTP_CALLBACK_ENVIRON GetEnviron();
		protected:
			ThreadPool() = delete;
			~ThreadPool() = delete;
			static void NTAPI Callback(PTP_CALLBACK_INSTANCE instance, PVOID param);
			static PTP_CALLBACK_ENVIRON environ_;


		};

	}  // namespace Thread
}  // namespace Process