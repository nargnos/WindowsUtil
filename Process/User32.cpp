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
				const LoadUser32 & Instance()
				{
					static LoadUser32 instance;
					return instance;
				}
			}  // namespace Detail



		}  // namespace User32

	}  // namespace LazyLoad
}  // namespace Process

