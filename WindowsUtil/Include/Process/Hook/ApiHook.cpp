#include "ApiHook.h"

namespace Process
{
	namespace Hook
	{

	
		PApiHookStruct HookApi(PVOID desFunc, PVOID hookFunc)
		{
			assert(desFunc&&hookFunc);
			auto result = new ApiHookStruct;
			auto fff = Process::LazyLoad::_VirtualProtect(result, sizeof(_ApiHookStruct), PAGE_EXECUTE_READWRITE, NULL);
			result->Init(desFunc, hookFunc);
			((void(__stdcall*)())&result->Hook)();
			return result;
			// 暂停这个, 这样做在多线程环境下会出问题!! 还是要用通用方法,这样要写disasm, 暂时放一放
			// api -> jmp B
			// address
			// 
			// A 保存覆盖的前几个字节,
			// Hook() ret
			// B 恢复前几个字节,保存栈顶C,pop push A                                                 //XXX pop当前ret地址(现在在栈顶)(C->调用api的返回地址),push C,
			// jmp hook函数 可选return 原函数() 
			// 
			// 执行A,ret到C

		}
	}
}