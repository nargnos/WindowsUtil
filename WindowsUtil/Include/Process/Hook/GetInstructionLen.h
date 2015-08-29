#pragma once
#include <Windows.h>
#include <WinBase.h>
#include "SimpleOpcodeMap.h"
#include <queue>
#include <assert.h>
namespace Process
{
	namespace Hook
	{
		class GetInstructionLen
		{
			enum NextStat
			{
				Stat_End,
				Stat_ReadHex,
				Stat_ReadRM,
				Stat_ReadSib
			};
		public:
			GetInstructionLen(bool is32);
			~GetInstructionLen();
			int GetLen(PUINT8 hex);
		private:
			std::queue<OpcodePrefixGroup> prefix;
			bool is32;
			NextStat stat;
			OpcodeTables table;
			PUINT8 currentPos;
			int count; // 指令长度计数
			bool IsOpcodeExDefine(OpcodeEx& cmd);
			bool IsPrefixVerify(OpcodePrefixCondition && opc);
			void AddImmCount(OpcodeLenType len);
			void Reset();
			bool has66; // 有操作数大小切换前缀
			bool has67; // 有地址大小切换前缀
			bool hasF2;
			bool hasF3;
			bool isModBit00;
			bool isGroupExist[4];
			void NotDefine();
			
			GetInstructionLen::NextStat _ReadHex(BYTE hex);
			GetInstructionLen::NextStat _ReadRM(BYTE hex);
			GetInstructionLen::NextStat _ReadSib(BYTE hex);

			GetInstructionLen::NextStat _SwitchTable(OpcodeTables table);
			GetInstructionLen::NextStat _AnalyGroup(BYTE grpIndex);
			GetInstructionLen::NextStat _AnalyPrefix(OpcodePrefixGroup prefixGroup,BYTE hex);

			GetInstructionLen::NextStat _AnalyCmd(OpcodeCmd& cmd);
			
			GetInstructionLen::NextStat _AnalyGroup_E(OpcodeGroup_E& grpe);
			GetInstructionLen::NextStat _AnalyEsc(BYTE hex);
			
		};
		
	}
}