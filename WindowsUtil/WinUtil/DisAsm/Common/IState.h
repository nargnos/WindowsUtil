#pragma once
#include "Common.h"
class IInstruction;
class IState
{
public:
	// 执行并返回下一个状态
	virtual shared_ptr<IState> Next(shared_ptr<IInstruction>& inst) = 0;
	// 指示是否已经结束
	virtual bool HasNext() = 0;
	virtual ~IState()
	{
	}
};
class State:public IState
{
public:

	State()
	{
	}
	virtual bool HasNext()  override
	{ 
		return true; 
	};
};
