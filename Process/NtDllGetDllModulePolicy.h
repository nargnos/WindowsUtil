#pragma once
namespace Process
{
	namespace LazyLoad
	{
		namespace Detail
		{
			// 只能找已经载入的dll
			struct NtDllGetDllModulePolicy
			{
				static HMODULE GetDllModule(LPCWSTR dllName);
			};
		}  // namespace Detail
	}  // namespace LazyLoad
}  // namespace Process
