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
	virtual shared_ptr<IState> Next(shared_ptr<IInstruction>& inst) override;
};

