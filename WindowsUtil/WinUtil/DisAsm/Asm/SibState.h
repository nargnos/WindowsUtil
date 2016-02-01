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
	virtual  const unique_ptr<IState>&  Next(shared_ptr<Instruction>& inst) override;
};

