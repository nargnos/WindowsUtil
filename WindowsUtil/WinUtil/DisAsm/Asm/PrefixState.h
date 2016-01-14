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
	virtual shared_ptr<IState> Next(shared_ptr<IInstruction>& inst) override;
};

