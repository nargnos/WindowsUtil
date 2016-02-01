#pragma once
#include "..\Common\Common.h"
class EscapeState :
	public State
{
public:

	EscapeState()
	{
	}

	~EscapeState()
	{
	}
	virtual  const unique_ptr<IState>&  Next(shared_ptr<Instruction>& inst) override;
};

