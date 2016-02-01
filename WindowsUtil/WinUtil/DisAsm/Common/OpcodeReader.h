#pragma once
#include "Common.h"
class OpcodeReader
{
public:

	OpcodeReader()
	{
	}
	// 返回读取长度, 读取信息保存在inst参数里
	int Read(shared_ptr<Instruction>& inst)
	{
		auto current = inst->GetFactory()->GetBeginStateInstance().get();
		while (current!=NULL && current->HasNext())
		{
			auto& tmpState = current->Next(inst);
			assert(tmpState);
			current = tmpState.get();
		}
		return inst->GetLength();
	}
	~OpcodeReader()
	{
	}
};

