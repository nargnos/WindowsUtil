#pragma once
#include "..\LazyLoad\LazyLoadSystemApi.h"
#include "Opcode\GetInstructionLen.h"
namespace Process
{
	namespace Hook
	{

		using LazyLoad::_VirtualProtect;
		using Process::Hook::GetInstructionLen;
		
		// 注意：不可在Hook函数里执行原API，否则会无限循环，需要执行则使用返回的地址
		// 如果不再调用原函数也不再UnHook，就delete[]掉返回地址
		
		// backupLen>5
		// api :原函数地址
		// hook :hook函数地址,其定义需要跟原函数一致
		// backupLen :原函数需要备份的指令长度,需要正确分割且>=5(使用E9XXXXXXXX jmp)
		// return :返回备份后的Api地址（原函数内容,这个地址unhook需要用）,错误时返回NULL
		PVOID _HookApi32(PVOID api, PVOID hook, int backupLen);
		
		// 自动确定备份字长的版本
		// 可以重复使用，只要中间的hook函数有一个不运行原函数，则整个链会断开
		PVOID HookApi32(PVOID api, PVOID hook);

		// 多次hook重定位jmp数值用的，无视就好
		void _RelocJmp(PVOID des, PVOID oldAddr, int offset);

		// TODO: UnHook
	}
}