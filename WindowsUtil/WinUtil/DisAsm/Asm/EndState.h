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
	virtual  const State*  Next(const shared_ptr<Instruction>& inst) const override;
};

