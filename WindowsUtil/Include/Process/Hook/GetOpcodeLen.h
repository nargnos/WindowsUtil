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
		
		
		class GetOpcodeLen
		{
			enum NextStat
			{
				Stat_End,
				Stat_ReadHex,
				Stat_ReadRM,
				Stat_ReadSib
			};
		public:
			GetOpcodeLen(bool is32);
			~GetOpcodeLen();
			void Reset();
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
			bool has66; // 有操作数大小切换前缀
			bool has67; // 有地址大小切换前缀
			bool hasF2;
			bool hasF3;

			bool isGroupExist[4];
			// 读取步骤
			// 读hex，找1表长度，如果有rm再读rm
			// 如果跳表就跳
			// 读取分3种，读1字节时的识别
			// 读RM，读SIB，
			GetOpcodeLen::NextStat _ReadHex(BYTE hex);
			GetOpcodeLen::NextStat _ReadRM(BYTE hex);
			GetOpcodeLen::NextStat _ReadSib(BYTE hex);

			GetOpcodeLen::NextStat _SwitchTable(OpcodeTables table);
			GetOpcodeLen::NextStat _AnalyGroup(BYTE grpIndex);
			GetOpcodeLen::NextStat _AnalyPrefix(OpcodePrefixGroup prefixGroup,BYTE hex);

			GetOpcodeLen::NextStat _AnalyCmd(OpcodeCmd& cmd);
			
			GetOpcodeLen::NextStat _AnalyGroup_E(OpcodeGroup_E& grpe);
			GetOpcodeLen::NextStat _AnalyEsc(BYTE hex);
			
		};
		
	}
}