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
	virtual  const unique_ptr<IState>&  Next(shared_ptr<Instruction>& inst) override;
};

