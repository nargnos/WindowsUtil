#include "ApiHook.h"

namespace Process
{
	namespace Hook
	{

		using Process::Overwrite::_VirtualProtect;
		using Process::Hook::GetInstructionLen;

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
			PBYTE& apiAddr = (PBYTE&)pos;
			apiAddr[0] = 0xe9;
			*(PDWORD)(&apiAddr[1]) = (PBYTE)des - (PBYTE)pos - E9_JMP_LEN;
		}

		void _EmitFF25Jmp(PVOID pos, PVOID des)
		{
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
			*(HANDLE_PTR*)apiAddr = (HANDLE_PTR)des;

		}


		bool IsFF25Jmp(PVOID addr)
		{
			return ((PBYTE)addr)[0] == 0xff && ((PBYTE)addr)[1] == 0x25;
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


		int GetCodeBackupLen(PVOID api, int minLen)
		{
#ifdef _WIN64
			GetInstructionLen gil(false);
#else
			GetInstructionLen gil(true);
#endif
			int len = 0; // 实际指令备份长度
			int loopTimes = 0;
			// 获取函数头备份长度
			while (len < minLen)
			{
				if (loopTimes++>minLen)
				{
					return 0;
				}
				len += gil.GetLen((PBYTE)api + len);
			}
			return len;
		}

		PVOID _HookApi(PVOID api, PVOID hook, int backupLen)
		{
			assert(backupLen >= BACKUPLEN);
			PBYTE result = new BYTE[backupLen + BACKUPLEN];
			// 备份原函数
			memcpy(result, api, backupLen);

			DWORD oldProtect;
			// 设置备份地址访问性
			if (!_VirtualProtect(result, backupLen + BACKUPLEN, PAGE_EXECUTE_READWRITE, &oldProtect))
			{
				return NULL;
			}

			// 设置api函数访问性
			if (!_VirtualProtect(api, backupLen, PAGE_EXECUTE_READWRITE, &oldProtect))
			{
				return NULL;
			}
			// 设置跳转->Hook
			_EmitFF25Jmp(api, hook);

			// 设置备份代码跳转(跳回
			_EmitFF25Jmp(result + backupLen, ((PBYTE)api) + backupLen);

			// 恢复访问性
			if (!_VirtualProtect(api, backupLen, oldProtect, &oldProtect))
			{
				// 设置失败，恢复函数
				memcpy(api, result, backupLen);
				delete[] result;
				return NULL;
			}
			return result;
		}
		
		PVOID HookApi(PVOID api, PVOID hook)
		{
#ifdef _WIN64
			GetInstructionLen gil(false);
#else
			GetInstructionLen gil(true);
#endif
			int len = 0;
			int tmpLen = 0; // 假定每一个指令都是1BYTE时累计的长度
			if (IsFF25Jmp(api))
			{
				len = BACKUPLEN;
			}
			else
			{
				// 获取函数头备份长度
				while (len < BACKUPLEN)
				{
					len += gil.GetLen((PBYTE)api + len);
					if (tmpLen++ >= BACKUPLEN)
					{
						// 读取失败，可能取指令长度部分有BUG或其它原因
						return NULL;
					}
				}
			}
			auto result = _HookApi(api, hook, len);


			// 重定位函数头跳转,以实现重复hook(别的hook程序可能不行)
			if (result)
			{
				tmpLen = 0;
				while (tmpLen < len)
				{
					// 修复跳转					
					if (_RelocJmp((PBYTE)result, api, tmpLen))
					{
						break;
					}
					tmpLen += gil.GetLen((PBYTE)result + tmpLen);
				}
			}
			return result;
		}



		// 使用e9 jmp的版本,当距离过远不适用
		PVOID _HookApi_E9Jmp(PVOID api, PVOID hook, int backupLen)
		{
			PBYTE result = new BYTE[backupLen + BACKUPLEN]; // 使用当前字长的最大长度, 后面跳回需要用
			// 备份原函数
			memcpy(result, api, backupLen);

			DWORD oldProtect;
			// 设置备份地址访问性
			if (!_VirtualProtect(result, backupLen + BACKUPLEN, PAGE_EXECUTE_READWRITE, &oldProtect))
			{
				return NULL;
			}

			// 设置api函数访问性
			if (!_VirtualProtect(api, backupLen, PAGE_EXECUTE_READWRITE, &oldProtect))
			{
				return NULL;
			}
			// hook e9
			_EmitE9Jmp(api, hook);
			// 设置跳回,需要考虑距离
			LONGLONG distance = (PBYTE)result - (PBYTE)api;
			distance = distance > 0 ? distance : -distance;
			if (distance<0x7fff0000)
			{
				_EmitE9Jmp(result + backupLen, (PBYTE)api + backupLen);
			}
			else
			{
				_EmitFF25Jmp(result + backupLen, (PBYTE)api + backupLen);
			}
			


			// 恢复访问性
			if (!_VirtualProtect(api, backupLen, oldProtect, &oldProtect))
			{
				// 设置失败，恢复函数
				memcpy(api, result, backupLen);
				delete[] result;
				return NULL;
			}
			return result;
		}

		PVOID HookApiOnce(PVOID api, PVOID hook)
		{
			if (((PBYTE)api)[0]==0xe9 || IsFF25Jmp(api))
			{
				return NULL;
			}
			LONGLONG distance = (PBYTE)hook - (PBYTE)api;
			distance = distance > 0 ? distance : -distance;
			int codeLen = 0;
			if (distance<0x7fff0000)
			{
				// e9 jmp
				codeLen = GetCodeBackupLen(api, E9_JMP_LEN);
				return _HookApi_E9Jmp(api, hook, codeLen);
			}
			else
			{
				// ff25 jmp
				codeLen = GetCodeBackupLen(api, BACKUPLEN);
				return _HookApi(api, hook, codeLen);
			}
		}
	}
}