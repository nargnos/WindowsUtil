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
	virtual  const unique_ptr<IState>&  Next(shared_ptr<Instruction>& inst) override;
};

