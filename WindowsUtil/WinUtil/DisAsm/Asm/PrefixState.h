#pragma once
#include "..\Common\Common.h"
class PrefixState :
	public State
{
public:

	PrefixState()
	{
	}

	~PrefixState()
	{
	}
	virtual const State* Next(const shared_ptr<Instruction>& inst) const override;
};

