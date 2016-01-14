#pragma once
#include "..\Common\Common.h"
class Byte3State :
	public State
{
public:

	Byte3State()
	{
	}

	~Byte3State()
	{
	}
	virtual shared_ptr<IState> Next(shared_ptr<IInstruction>& inst) override{ return shared_ptr<IState>(); }
};

