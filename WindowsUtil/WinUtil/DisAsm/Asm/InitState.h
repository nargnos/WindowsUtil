#pragma once
#include "AsmCommon.h"
class InitState :
	public State
{
public:

	InitState()
	{
	}

	~InitState()
	{
	}

	// Í¨¹ý State ¼Ì³Ð
	virtual  const unique_ptr<IState>&  Next(shared_ptr<Instruction>& inst) override;
	
};

