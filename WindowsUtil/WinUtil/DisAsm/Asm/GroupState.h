#pragma once
#include "..\Common\Common.h"
class GroupState :
	public State
{
public:

	GroupState()
	{
	}

	~GroupState()
	{
	}
	virtual  const State*  Next(const shared_ptr<Instruction>& inst) const override;
};

