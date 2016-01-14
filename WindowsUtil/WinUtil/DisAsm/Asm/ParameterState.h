#pragma once
#include "..\Common\Common.h"
class ParameterState :
	public State
{
public:

	ParameterState()
	{
	}

	~ParameterState()
	{
	}
	virtual shared_ptr<IState> Next(shared_ptr<IInstruction>& inst) override;
};

