#pragma once
namespace Process
{
	namespace LazyLoad
	{
		namespace Detail
		{
			// 使用重写的loadlibrary
			// 如果需要使用加密的dll名称，需要修改传参类型和解密policy的GetStr返回类型
			struct DefaultGetDllModulePolicy
			{
				static HMODULE GetDllModule(LPCWSTR dllName);
			};
		}  // namespace Detail
	}  // namespace LazyLoad
}  // namespace Process
