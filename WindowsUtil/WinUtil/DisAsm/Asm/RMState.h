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
	virtual  const unique_ptr<IState>& Next(shared_ptr<Instruction>& inst) override;
};

