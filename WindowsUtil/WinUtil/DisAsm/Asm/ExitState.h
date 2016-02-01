#pragma once
#include "AsmCommon.h"
// 退出整个循环
class ExitState :
	public State
{
public:

	ExitState()
	{
	}

	~ExitState()
	{
	}
	virtual  const unique_ptr<IState>&  Next(shared_ptr<Instruction>& inst) override;
	virtual bool HasNext()  override;;
};

