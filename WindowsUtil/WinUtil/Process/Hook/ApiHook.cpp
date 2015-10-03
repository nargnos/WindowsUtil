#include "ApiHook.h"

namespace Process
{
	namespace Hook
	{
#define E9_JMP_LEN 5
#define CALC_E9_JMP(codeAddr,desAddr) ((DWORD)((DWORD)(desAddr)-E9_JMP_LEN-(DWORD)(codeAddr)))

		using Process::Overwrite::_VirtualProtect;
		using Process::Hook::GetInstructionLen;

		PVOID _HookApi32(PVOID api, PVOID hook, int backupLen)
		{

			assert(backupLen >= E9_JMP_LEN);
			PBYTE result = new BYTE[backupLen + E9_JMP_LEN];
			// 备份原函数
			memcpy(result, api, backupLen);

			DWORD oldProtect;
			// 设置备份地址访问性
			if (!_VirtualProtect(result, backupLen + E9_JMP_LEN, PAGE_EXECUTE_READWRITE, &oldProtect))
			{
				return NULL;
			}

			// 设置api函数访问性
			if (!_VirtualProtect(api, backupLen, PAGE_EXECUTE_READWRITE, &oldProtect))
			{
				return NULL;
			}
			// 设置跳转->Hook
			((PBYTE)api)[0] = 0xe9;
			*(PDWORD)&((PBYTE)api)[1] = CALC_E9_JMP(api, hook);

			// 恢复访问性
			if (!_VirtualProtect(api, backupLen, oldProtect, &oldProtect))
			{
				// 设置失败，恢复函数
				memcpy(api, result, backupLen);
				delete[] result;
				return NULL;
			}

			// 设置备份代码跳转(跳回
			result[backupLen] = 0xe9;
			PBYTE tmpAddr = result + backupLen + 1;
			*(PDWORD)tmpAddr = CALC_E9_JMP(result + backupLen, ((PBYTE)api) + backupLen);
			return result;
		}

		PVOID HookApi32(PVOID api, PVOID hook)
		{
			GetInstructionLen gil(true);
			int len = 0;
			int tmpLen = 0; // 假定每一个指令都是1BYTE时累计的长度
			// 获取函数头备份长度
			while (len < E9_JMP_LEN)
			{
				len += gil.GetLen((PBYTE)api + len);
				if (tmpLen++ >= E9_JMP_LEN)
				{
					// 读取失败，可能取指令长度部分有BUG或其它原因
					return NULL;
				}
			}
			auto result = _HookApi32(api, hook, len);
			// 重定位函数头跳转,以实现重复hook
			if (result)
			{
				tmpLen = 0;
				while (tmpLen < len)
				{
					// 修复跳转					
					_RelocJmp(result, api, tmpLen);
					tmpLen += gil.GetLen((PBYTE)result + tmpLen);
				}
			}
			return result;
		}

		// offset为指令开始位置
		void _RelocJmp(PVOID des, PVOID oldAddr, int offset)
		{
			// E9			
			if (((PBYTE)des)[offset]==0xe9)
			{
				*(PDWORD)&((PBYTE)des)[offset + 1] += (DWORD)oldAddr- (DWORD)des;
			}
			// TODO: 还有其它跳转情况,如果存在使用不同方式hook的时候需要注意
		}
		
	}
}