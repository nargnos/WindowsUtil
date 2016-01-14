#pragma once
#include "..\Common\Common.h"

class IInstruction
{
public:
	virtual void Init(void* ptr) = 0;
	// 是否解析成功
	virtual bool IsSuccess() = 0;
	virtual int GetLength()=0;
	virtual shared_ptr<IStateFactory> GetFactory() = 0;
	virtual ~IInstruction()
	{
	}
};
class Instruction:public IInstruction
{
protected:
	unsigned char* beginPtr;
	unsigned char* currentPtr;
	shared_ptr<IStateFactory>& factory;
public:

	Instruction(shared_ptr<IStateFactory>& factory):factory(factory)
	{
	}
	virtual void Init(void* ptr) override
	{
		assert(ptr != NULL);
		currentPtr = beginPtr = reinterpret_cast<unsigned char*>(ptr);
	}
	virtual int GetLength() override
	{
		if (IsSuccess())
		{
			return currentPtr - beginPtr;
		}
		return 0;
	}
	virtual shared_ptr<IStateFactory> GetFactory() override
	{
		return factory;
	}
};

