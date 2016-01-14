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
	virtual shared_ptr<IState> Next(shared_ptr<IInstruction>& inst) override;
};

