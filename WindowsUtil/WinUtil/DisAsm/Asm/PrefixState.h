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
	virtual  const unique_ptr<IState>&  Next(shared_ptr<Instruction>& inst) override;
};

