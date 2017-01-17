#include "HookApi.h"
#include <cmath>
#include <cassert>
#include <PeImage\PeDecoder.h>
#include <Process\EnvironmentBlock.h>
#include <Process\WriteProcessMemory.h>
#include <Process\VirtualProtect.h>
namespace Hook
{
	// jmp xxx
#define E9_JMP_LEN 5
	// jmp [xxx], 需要加上对应地址的长度
#define FF25_JMP_LEN 6

	// 最小备份长度
#ifdef _WIN64
	const int BACKUPLEN = FF25_JMP_LEN + sizeof(DWORD64);
#else
	const int BACKUPLEN = FF25_JMP_LEN + sizeof(DWORD);
#endif




	void _EmitE9Jmp(PVOID pos, PVOID des)
	{
		assert(pos != nullptr);
		assert(des != nullptr);

		PBYTE& apiAddr = (PBYTE&)pos;
		apiAddr[0] = 0xe9;
		*(PDWORD)(&apiAddr[1]) = (PBYTE)des - (PBYTE)pos - E9_JMP_LEN;
	}

	void _EmitFF25Jmp(PVOID pos, PVOID des)
	{
		assert(pos != nullptr);
		assert(des != nullptr);

		PBYTE& apiAddr = (PBYTE&)pos;
		apiAddr[0] = 0xff;
		apiAddr[1] = 0x25;
		apiAddr += 2;

		// 32写绝对地址,64写相对地址, 指向这条指令的结束位置
#ifdef _WIN64
		*(PDWORD)apiAddr = (DWORD)0;
#else
		*(PDWORD)apiAddr = (DWORD)(apiAddr + sizeof(DWORD));
#endif
		apiAddr += sizeof(DWORD);
		// 写入目标地址
		*reinterpret_cast<HANDLE_PTR*>(apiAddr) = reinterpret_cast<HANDLE_PTR>(des);

	}

	bool IsFF25Jmp(PVOID addr)
	{
		assert(addr != nullptr);
		return ((PBYTE)addr)[0] == 0xff && ((PBYTE)addr)[1] == 0x25;
	}

	bool IsE9Jmp(PVOID addr)
	{
		assert(addr != nullptr);
		return ((PBYTE)addr)[0] == 0xe9;
	}

	// offset为指令开始位置
	// 为jmp的目标立即数添加指针Δ
	bool _RelocJmp(PBYTE des, PVOID oldAddr, int offset)
	{
		auto jmpPos = des + offset;
		if (IsFF25Jmp(jmpPos))
		{
			// 只支持本hook
#ifndef _WIN64
			if (*(PDWORD)&jmpPos[2] != 0)
			{
				// 修改绝对偏移,32位才有
				jmpPos += 2;
				*(PDWORD)jmpPos = (DWORD)(jmpPos + sizeof(DWORD));
			}
#endif
			return true;
		}
		return false;
		// TODO: 还有其它跳转情况,如果存在使用不同方式hook的时候需要注意
	}


	//	int GetCodeBackupLen(PVOID api, int minLen)
	//	{
	//#ifdef _WIN64
	//		GetInstructionLen gil(false);
	//#else
	//		GetInstructionLen gil(true);
	//#endif
	//		int len = 0;  // 实际指令备份长度
	//		int loopTimes = 0;
	//		// 获取函数头备份长度
	//		while (len < minLen)
	//		{
	//			if (loopTimes++ > minLen)
	//			{
	//				return 0;
	//			}
	//			len += gil.GetLen((PBYTE)api + len);
	//		}
	//		return len;
	//	}

	//	PVOID HookApi(PVOID api, PVOID hook)
	//	{
	//#ifdef _WIN64
	//		GetInstructionLen gil(false);
	//#else
	//		GetInstructionLen gil(true);
	//#endif
	//		int len = 0;
	//		int tmpLen = 0;  // 假定每一个指令都是1BYTE时累计的长度
	//		if (IsFF25Jmp(api))
	//		{
	//			len = BACKUPLEN;
	//		}
	//		else
	//		{
	//			// 获取函数头备份长度
	//			while (len < BACKUPLEN)
	//			{
	//				len += gil.GetLen((PBYTE)api + len);
	//				if (tmpLen++ >= BACKUPLEN)
	//				{
	//					// 读取失败，可能取指令长度部分有BUG或其它原因
	//					return nullptr;
	//				}
	//			}
	//		}
	//		auto result = _HookApi(api, hook, len);
	//
	//
	//		// 重定位函数头跳转,以实现重复hook(别的hook程序可能不行)
	//		if (result)
	//		{
	//			tmpLen = 0;
	//			while (tmpLen < len)
	//			{
	//				// 修复跳转
	//				if (_RelocJmp((PBYTE)result, api, tmpLen))
	//				{
	//					break;
	//				}
	//				tmpLen += gil.GetLen((PBYTE)result + tmpLen);
	//			}
	//		}
	//		return result;
	//	}


	bool IsLongDistance(PVOID addr1, PVOID addr2)
	{
		assert(addr1 != nullptr);
		assert(addr2 != nullptr);
		LONGLONG distance = (PBYTE)addr1 - (PBYTE)addr2;
		return abs(distance) >= 0x7fff0000;
	}


	bool Backup(PVOID api, PVOID hook, PBYTE buffer, int backupLen, int bufferLen)
	{
		using namespace Process;
		assert(bufferLen >= backupLen + BACKUPLEN);
		// 备份原函数
		memcpy(buffer, api, backupLen);
		DWORD oldProtect = 0;

		// 设置备份地址访问性
		if (!Overwrite::VirtualProtect(buffer, bufferLen, PAGE_EXECUTE_READWRITE, &oldProtect))
		{
			return false;
		}
		
		// 设置备份代码跳转(跳回,需要考虑距离
		auto jmpBackAddr = (PBYTE)api + backupLen;
		auto jmpCode = buffer + backupLen;
		if (IsLongDistance(jmpCode, jmpBackAddr))
		{
			_EmitFF25Jmp(jmpCode, jmpBackAddr);
		}
		else
		{
			_EmitE9Jmp(jmpCode, jmpBackAddr);
		}

		return true;
	}


	/*
	result -> | api(backupLen) | jmp api+backuplen -> 连起来就是原始代码
	api -> |jmp hook|  -> 如果需要调用原始代码就不能用这个地址
	*/
	bool _HookApi(PVOID api, PVOID hook, int backupLen, PVOID * oldFunc, int minBackupLen, void(*emitFunc)(PVOID,PVOID))
	{
		using namespace Process;
		assert(api != nullptr);
		assert(hook != nullptr);

		if (oldFunc != nullptr)
		{
			assert(backupLen >= minBackupLen);

			*oldFunc = nullptr;
			auto backupBufferLen = backupLen + BACKUPLEN;
			auto backup = new BYTE[backupBufferLen];

			// 备份原函数
			if (!Backup(api, hook, backup, backupLen, backupBufferLen))
			{
				delete[] backup;
				return false;
			}

			// 备份完毕
			*oldFunc = backup;
		}
		else
		{
			backupLen = minBackupLen;
		}

		DWORD oldProtect = 0;
		// 设置api函数访问性
		if (!Overwrite::VirtualProtect(api, backupLen, PAGE_EXECUTE_READWRITE, &oldProtect))
		{
			if (oldFunc != nullptr)
			{
				delete[] *oldFunc;
				*oldFunc = nullptr;
			}
			return false;
		}
		// set hook
		emitFunc(api, hook);

		// 恢复访问性
		if (!Overwrite::VirtualProtect(api, backupLen, oldProtect, &oldProtect))
		{
			// 设置失败，恢复函数
			if (oldFunc != nullptr)
			{
				memcpy(api, *oldFunc, backupLen);
				delete[] *oldFunc;
				*oldFunc = nullptr;
			}
			return false;
		}
		return true;
	}
	
	
	bool HookApi_FF25(PVOID api, PVOID hook, int backupLen, PVOID * oldFunc)
	{
		return _HookApi(api, hook, backupLen, oldFunc, BACKUPLEN, _EmitFF25Jmp);
	}
	// 使用e9 jmp的版本,当距离过远不适用
	bool HookApi_E9(PVOID api, PVOID hook, int backupLen, PVOID * oldFunc)
	{
		assert(!IsLongDistance(api, hook));
		return _HookApi(api, hook, backupLen, oldFunc, E9_JMP_LEN, _EmitE9Jmp);
	}
	//bool HookApi(PVOID api, PVOID hook, int backupLen, PVOID * oldFunc)
	//{
	//	if (IsE9Jmp(api) || IsFF25Jmp(api))
	//	{
	//		return false;
	//	}
	//	if (IsLongDistance(api, hook))
	//	{
	//		return HookApi_FF25(api, hook, backupLen, oldFunc);
	//	}
	//	else
	//	{
	//		return HookApi_E9(api, hook, backupLen, oldFunc);
	//	}
	//}
}  // namespace Hook