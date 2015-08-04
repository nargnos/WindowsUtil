#pragma once
#include <windows.h>
#include <WinBase.h>
#include <queue>
#include "opcodes.h"
namespace Asm
{
	class DisAsm
	{
	public:
		DisAsm();
		~DisAsm();

	private:
		bool PushPrefix(BYTE prefix); // 失败时表示遇到冲突
		std::queue<BYTE> prefixs;
		struct _PrefixRecord
		{
			_PrefixRecord();
			void Reset();
			BYTE Record(BYTE prefix); // 不冲突返回0，失败返回组号1-4
			bool Exist[4];
		}prefixRecord;
	};
}