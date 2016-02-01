#pragma once
#include "..\OverwriteWinApi\OverwriteWinApi.h"
#include "Opcode\GetInstructionLen.h"
namespace Process
{
	namespace Hook
	{

		// 注意：不可在Hook函数里执行Hook后的API地址，否则会无限循环，需要执行则使用返回的地址
		// 为了支持64位,使用ff25的jmp,地址写在这条指令后面,如果使用e9的jmp在64位时将不能跳回(距离太远了)
		// 后hook有更高优先权
		// 多次hook后会形成一个函数链表,中间有一个函数不下发,后面的函数都不会执行
		// 如果不再调用原函数也不再UnHook，就delete[]掉返回地址，否则会泄露

		// api :原函数地址
		// hook :hook函数地址,其定义需要跟原函数一致
		// backupLen :原函数需要备份的指令长度,需要正确分割且>=10(64位为14,使用ff25 jmp[xxx],绝对地址跟在这条指令后)
		// return :返回备份后的Api地址（原函数内容,这个地址unhook需要用）,错误时返回NULL
		PVOID _HookApi(PVOID api, PVOID hook, int backupLen);
		
		// 自动确定备份字长的版本
		// 可以重复使用，只要中间的hook函数有一个不运行原函数，则整个链会断开
		PVOID HookApi(PVOID api, PVOID hook);

		// 只hook一次的版本,不支持多次hook,不支持跟其它混用
		PVOID HookApiOnce(PVOID api, PVOID hook);

		template<typename T>
		T HookApiEx(T api, T hook)
		{
			return (T)HookApi(api, hook);
		}


		// TODO: UnHook
	}
}