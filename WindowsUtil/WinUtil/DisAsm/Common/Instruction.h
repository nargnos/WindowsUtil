#pragma once
#include "Common.h"

// 表示一条指令，用来临时存储供状态机用的变量
class Instruction :public _STD enable_shared_from_this<Instruction>
{
protected:
	bool isSuccess;
	unsigned char* beginPtr;
	unsigned char* currentPtr;
	shared_ptr<IStateFactory>& factory;
public:

	explicit Instruction(shared_ptr<IStateFactory> factory)
		:factory(factory)
	{
	}
	virtual ~Instruction()
	{
	}
	template<typename TCast>
	shared_ptr<TCast> Cast()
	{
		return dynamic_pointer_cast<TCast>(shared_from_this());
	}
	// ptr为读取起始位置
	virtual void Init(void* ptr)
	{
		assert(ptr != NULL);
		currentPtr = beginPtr = reinterpret_cast<unsigned char*>(ptr);
		isSuccess = false;
		factory->Reset();
	}
	// 以当前读取位置重置存储环境
	virtual void Reset()
	{
		Init(CurrentBytePtr());
	}

	// 成功返回指令长度
	virtual int GetLength()
	{
		if (IsSuccess())
		{
			return currentPtr - beginPtr;
		}
		return 0;
	}

	template<typename TStateFactory = IStateFactory>
	shared_ptr<TStateFactory> GetFactory()
	{
		return dynamic_pointer_cast<TStateFactory>(factory);
	}
	template<>
	shared_ptr<IStateFactory> GetFactory()
	{
		return factory;
	}
	virtual unsigned char* CurrentBytePtr()
	{
		return currentPtr;
	}
	virtual void NextByte()
	{
		currentPtr++;
	}
	// 是否解析成功
	virtual bool IsSuccess()
	{
		return isSuccess;
	}
};

