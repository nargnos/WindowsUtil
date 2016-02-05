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
	virtual  const State*  Next(const shared_ptr<Instruction>& inst) const override;
};

