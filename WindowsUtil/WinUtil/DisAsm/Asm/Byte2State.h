#pragma once
#include "..\Common\Common.h"
class Byte2State :
	public State
{
public:

	Byte2State()
	{
	}

	~Byte2State()
	{
	}
	virtual shared_ptr<IState> Next(shared_ptr<IInstruction>& inst) override { return shared_ptr<IState>(); }
};

