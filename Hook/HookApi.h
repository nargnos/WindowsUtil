#pragma once
#include "Common.h"
namespace Hook
{
#pragma region 旧声明和注释，暂时保留完成这部分后再整理删除

	//// UNDONE: 这里先保存旧代码，之后补全
	//// 以前写的的反汇编引擎有问题（删掉了），等新的引擎编好了再更新这里的代码

	//// 注意：不可在Hook函数里执行Hook后的API地址，否则会无限循环，需要执行则使用返回的地址
	//// 为了支持64位,使用ff25的jmp,地址写在这条指令后面,如果使用e9的jmp在64位时将不能跳回(距离太远了)
	//// 后hook有更高优先权
	//// 多次hook后会形成一个函数链表,中间有一个函数不下发,后面的函数都不会执行
	//// 如果不再调用原函数也不再UnHook，就delete[]掉返回地址，否则会出现内存泄露

	//// api :原函数地址
	//// hook :hook函数地址,其定义需要跟原函数一致
	//// backupLen :原函数需要备份的指令长度,需要正确分割且>=10(64位为14,使用ff25 jmp[xxx],绝对地址跟在这条指令后)
	//// return :返回备份后的Api地址（原函数内容,这个地址unhook需要用）,错误时返回NULL
	//PVOID _HookApi(PVOID api, PVOID hook, int backupLen);
	//// 自动确定备份字长的版本
	//// 可以重复使用，只要中间的hook函数有一个不运行原函数，则整个链会断开
	//PVOID HookApi(PVOID api, PVOID hook);

	//// 只hook一次的版本,不支持多次hook,不支持跟其它混用
	//PVOID HookApiOnce(PVOID api, PVOID hook);

	//template<typename T>
	//T HookApiEx(T api, T hook)
	//{
	//	return (T)HookApi(api, hook);
	//}
#pragma endregion


	// 使用 jmp[addr]跳转, 汇编存储格式为
	//		ff 25 [end]
	// end: addr

	// UNDONE: 之后会补充自动判断备份长度，只能hook一次，hook多次的有空再修复
	// 
	// @api: 被hook的函数地址
	// @hook: hook函数地址，需要声明跟原函数一致，可以取到参数
	// @backupLen: 备份api开头指令长度，需要传入api开头正确的汇编指令备份长度，不能截断。
	//			   计算正确的备份长度需要反汇编引擎，*未写完*。可以用反汇编工具得到正确长度
	//			   长度最小值32位是10，64位是14，需要根据实际api开头汇编指令长度调整
	//			   设置最小备份长度目的是调用原始函数时能得到正确结果，如果不需要调用原始函数，可以忽略
	// @oldFunc: 返回原始函数备份位置,如果需要调用原始函数就调用这个地址，调用时需要传入参数；如果不需要调用原函数就传nullptr
	//			 注意：此返回可用来unhook，得到返回后如果不需要调用原函数时需要delete[]掉它回收内存
	// @return: 返回是否成功
	bool HookApi_FF25(_In_ _Notnull_ PVOID api,
		_In_ _Notnull_  PVOID hook,
		int backupLen,
		_Outptr_opt_ PVOID* oldFunc);

	// 使用e9 jmp的版本,当hook地址和api地址距离过远不适用（64位情况会出现）,优势是修改的代码没那么多= =
	// @backuplen: api函数地址和hook函数地址距离不能过远，最小备份长度是5
	bool HookApi_E9(_In_ _Notnull_ PVOID api,
		_In_ _Notnull_  PVOID hook,
		int backupLen,
		_Outptr_opt_ PVOID* oldFunc);

	// 用来判断api和hook函数之间的距离，太远就用ff25（远近都可用）
	bool IsLongDistance(PVOID addr1, PVOID addr2);
}  // namespace Hook