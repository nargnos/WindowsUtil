#pragma once
// 在这里处理指令
// 处理输出名称，根据指令信息决定跳转到读取操作数还是读取RM
// 会跳转到结束或RM状态

#include "..\Common\Common.h"
#include "Opcode\OpcodeDef.h"
class InstructionState :
	public State
{
public:

	InstructionState()
	{
	}

	~InstructionState()
	{
	}
	virtual  const State*  Next(const shared_ptr<Instruction>& inst)  const override;
	
};

