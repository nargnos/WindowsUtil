#pragma once
#include "..\Common\Common.h"
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
	virtual shared_ptr<IState> Next(shared_ptr<IInstruction>& inst) override;
	
};

