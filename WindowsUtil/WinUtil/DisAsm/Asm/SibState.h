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
	virtual  const State*  Next(const shared_ptr<Instruction>& inst) const override;
};

