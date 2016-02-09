#pragma once
#include "..\Common\Common.h"
class RmState :
	public State
{
private:
	static bool HasRM(OperandType ot);
public:

	RmState()
	{
	}

	~RmState()
	{
	}
	virtual  const State* Next(const shared_ptr<Instruction>& inst) const override;
	
	static bool HasRM(AsmOpcodeWapper& wapper, int operandCount, unsigned char* operandGrpAddr)
	{
		for (auto i = 0; i < operandCount; i++)
		{
			auto& tmpOperand = wapper.GetOperands(operandGrpAddr[i]);
			if (!tmpOperand.H.IsReg && HasRM((OperandType)tmpOperand.H.Operand))
			{
				return true;
			}
		}
		return false;
	}
};

