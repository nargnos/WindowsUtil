#pragma once
#include <windows.h>
#include <WinBase.h>
#include <queue>
#include "OpcodeTables.h"
namespace Asm
{
	class PrefixQueue
	{
	public:
		PrefixQueue();
		~PrefixQueue();
		void Reset(); 

		// 返回0表示成功添加，大于0值表示冲突发生，出队数量
		int Push(OpcodePrefix prefix);
		std::queue<OpcodePrefix> ConflictQueues; // 冲突的前缀丢这，下次push清
		BYTE Pop();
	private:
		
		std::queue<OpcodePrefix> prefixQueues;
		

		bool Exist[4];

	};
}