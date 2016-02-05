#pragma once
#include "Common.h"
class Instruction;
class State
{
public:
	// 执行并返回下一个状态
	virtual const State* Next(const shared_ptr<Instruction>& inst) const = 0;
	// 指示是否已经结束(通过覆盖修改返回值，指示结束状态
	virtual bool HasNext() const
	{
		return true;
	};
	virtual ~State()
	{
	}
};

