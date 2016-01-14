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
	virtual shared_ptr<IState> Next(shared_ptr<IInstruction>& inst) override;
};

