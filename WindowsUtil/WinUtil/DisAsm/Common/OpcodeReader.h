#pragma once
#include "..\Common\Common.h"
class OpcodeReader
{
public:

	OpcodeReader()
	{
	}
	// 返回读取长度, 读取信息保存在inst参数里
	int Read(shared_ptr<IInstruction>& inst)
	{
		auto& current = inst->GetFactory()->GetBeginStateInstance();
		while ((current = current->Next(inst))->HasNext());
		return inst->GetLength();		
	}
	~OpcodeReader()
	{
	}
};

