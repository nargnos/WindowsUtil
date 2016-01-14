#pragma once
#include "..\Common\Common.h"
class EndState :
	public State
{
public:

	EndState()
	{
	}

	~EndState()
	{
	}
	virtual shared_ptr<IState> Next(shared_ptr<IInstruction>& inst) override { return shared_ptr<IState>(); }
};

