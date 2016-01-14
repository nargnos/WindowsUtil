#pragma once
#include "..\Common\Common.h"


class Byte1State :
	public State
{
public:
	
	Byte1State()
	{
	}

	~Byte1State()
	{
	}
	virtual shared_ptr<IState> Next(shared_ptr<IInstruction>& inst) override { return shared_ptr<IState>(); }
};

