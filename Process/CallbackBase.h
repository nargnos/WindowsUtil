#pragma once
#include "Common.h"
namespace Process
{
	namespace Thread
	{
		namespace Detail
		{
			class _Submitted
			{
			public:
				_Submitted();
				virtual ~_Submitted() = default;				
			protected:
				bool IsSubmitted() const;
				void Submitted();
			private:
				bool isSubmitted_;
			};

			template<typename TFunc>
			class CallbackBase :
				public _Submitted
			{
			public:
				typedef TFunc Func;
				CallbackBase() = default;
				CallbackBase(Func&& func) :
					func_(_STD move(func))
				{
				}
				~CallbackBase() = default;


				CallbackBase(CallbackBase&& val)
				{
					if (&val == this)
					{
						return;
					}
					assert(!IsSubmitted());
					MoveAssign(_STD move(val));
				}

				const CallbackBase& operator=(CallbackBase&& val)
				{
					if (&val != this)
					{
						assert(!IsSubmitted());
						MoveAssign(_STD move(val));
					}
					return *this;
				}


				CallbackBase(const CallbackBase& val)
				{
					if (&val == this)
					{
						return;
					}
					assert(!IsSubmitted());
					Assign(val);
				}
				const CallbackBase& operator=(const CallbackBase& val)
				{
					if (&val != this)
					{
						assert(!IsSubmitted());
						Assign(val);
					}
					return *this;
				}
			protected:
				Func& GetFunc()
				{
					return func_;
				}
			private:
				void Assign(const CallbackBase& val)
				{
					// 已提交就无法赋值
					assert(!val.IsSubmitted());
					this->func_ = val.func_;
				}
				void MoveAssign(CallbackBase&& val)
				{
					// work_为空表示未提交，已提交就无法移动
					assert(!val.IsSubmitted());
					this->func_ = _STD move(val.func_);
				}

				Func func_;
			};
		}  // namespace Detail
	}  // namespace Thread
}  // namespace Process