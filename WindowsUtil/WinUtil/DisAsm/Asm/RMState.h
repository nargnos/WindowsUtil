#pragma once
#include "..\Common\Common.h"
class RmState :
	public State
{
public:

	RmState()
	{
	}

	~RmState()
	{
	}
	virtual  const State* Next(const shared_ptr<Instruction>& inst) const override;
};

