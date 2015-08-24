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
		
		enum NextStat
			{
				Stat_End,
				Stat_ReadHex,
				Stat_ReadRM,
				Stat_ReadSib,
			/*	Stat_SwitchTable,
				Stat_ReadGroup,
				Stat_ReadPrefix,*/
				//Stat_ReadNone,

			};
		class GetOpcodeLen
		{
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
			PUINT8 startPos;
			PUINT8 currentPos;
			int count; // 指令长度计数
			bool IsOpcodeExDefine(OpcodeEx& cmd);
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
			NextStat _ReadHex(BYTE hex);
			NextStat _ReadRM(BYTE hex);
			NextStat _ReadSib(BYTE hex);

			NextStat _SwitchTable(OpcodeTables table);
			NextStat _AnalyGroup(BYTE grpIndex);
			NextStat _AnalyPrefix(OpcodePrefixGroup prefixGroup,BYTE hex);
			//NextStat _ReadNone();
			NextStat _AnalyCmd(OpcodeCmd& cmd);
			
			NextStat _AnalyGroup_E(OpcodeGroup_E& grpe);
			NextStat _AnalyEsc(BYTE hex);
			
		};
		
	}
}