#include "stdafx.h"
#include "User32.h"
namespace Process
{
	namespace LazyLoad
	{
		namespace User32
		{
			namespace Detail
			{
				LoadUser32::LoadUser32() :
					LoadDllBase(L"user32.dll"),
					MessageBoxA(*this, "MessageBoxA")
				{
				}
				LoadUser32 & Instance()
				{
					static auto instance_ = _STD unique_ptr<LoadUser32>(new LoadUser32());
					return *instance_;
				}
			}  // namespace Detail



		}  // namespace User32

	}  // namespace LazyLoad
}  // namespace Process

