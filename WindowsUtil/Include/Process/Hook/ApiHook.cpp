#include "ApiHook.h"

namespace Process
{
	namespace Hook
	{
		bool HookApi(LPCWSTR dllName, LPCSTR procName, LPCVOID hookFunc)
		{
			auto funcAddr = Process::LazyLoad::_GetProcAddressEx(dllName, procName);
			if (!funcAddr)
			{
				return false;
			}
			// A 保存覆盖的前几个字节,Hook
			// api -> jmp B
			// B 恢复前几个字节,pop当前ret地址(现在在栈顶)(C->调用api的返回地址),push A,push C
			// 
		}
	}
}