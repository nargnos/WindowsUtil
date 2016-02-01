#pragma once
#include "AsmCommon.h"

class ByteState :
	public State
{
	
public:

	ByteState()
	{
	}

	~ByteState()
	{
	}
	virtual const unique_ptr<IState>& Next(shared_ptr<Instruction>& inst) override;
};

