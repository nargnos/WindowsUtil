#pragma once
#include "..\Common\Common.h"
class SibState :
	public State
{
public:

	SibState()
	{
	}

	~SibState()
	{
	}
	virtual shared_ptr<IState> Next(shared_ptr<IInstruction>& inst) override;
};

