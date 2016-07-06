#pragma once
#include "Common.h"
#include "CallbackInstance.h"
namespace Process
{
	namespace Thread
	{

		class ThreadPool
		{
		public:
			template<typename T>
			static bool Submit(T& obj)
			{
				assert(obj.GetFunc());
				return obj.Submit(GetEnviron());
			}
			static bool Submit(_STD function<void(CallbackInstance&)>&& obj)
			{
				return SubmitCallback(_STD move(obj));
			}

			template<typename T>
			static bool Register(T& obj)
			{
				assert(obj.GetFunc());
				return obj.Register(GetEnviron());
			}
			static bool SubmitCallback(_STD function<void(CallbackInstance&)>&& func);

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