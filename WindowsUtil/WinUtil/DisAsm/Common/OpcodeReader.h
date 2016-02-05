#pragma once
#include "Common.h"
class OpcodeReader
{
public:

	OpcodeReader()
	{
	}
	// 返回读取长度, 读取信息保存在inst参数里
	int Read(const shared_ptr<Instruction>& inst) const
	{
		auto current = inst->GetFactory()->GetBeginStateInstance();
		while (current != NULL && current->HasNext())
		{
			current = current->Next(inst);
			assert(current);
		}
		return inst->GetLength();
	}
	~OpcodeReader()
	{
	}
};

