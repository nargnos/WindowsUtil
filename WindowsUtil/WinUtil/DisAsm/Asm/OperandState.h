#pragma once
#include "..\Common\Common.h"
class OperandState :
	public State
{
public:

	OperandState()
	{
	}

	~OperandState()
	{
	}
	virtual  const State*  Next(const shared_ptr<Instruction>& inst) const override;
};

