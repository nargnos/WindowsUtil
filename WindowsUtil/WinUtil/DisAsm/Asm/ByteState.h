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
	virtual const State* Next(const shared_ptr<Instruction>& inst) const override;
};

