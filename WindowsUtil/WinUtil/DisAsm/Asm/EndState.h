#pragma once
#include "AsmCommon.h"
// 用来做一些收尾工作
class EndState :
	public State
{
public:

	EndState()
	{
	}

	~EndState()
	{
	}
	virtual  const unique_ptr<IState>&  Next(shared_ptr<Instruction>& inst) override;
};

