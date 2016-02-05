#pragma once
#include "Common.h"

// 表示一条指令，用来临时存储供状态机用的变量
class Instruction
{
protected:
	bool isSuccess;
	const unsigned char* beginPtr;
	const unsigned char* currentPtr;
	shared_ptr<IStateFactory> factory;
	void SetSuccess()
	{
		isSuccess = true;
	}
public:

	explicit Instruction(const shared_ptr<IStateFactory>& factory)
	{
		assert(factory != nullptr);
		this->factory = factory;
		isSuccess = false;
	}
	virtual ~Instruction() = default;
	template<typename TCast>
	TCast* Cast()
	{
		return dynamic_cast<TCast*>(this);
	}
	// ptr为读取起始位置
	virtual void Init(const void* ptr)
	{
		assert(ptr != NULL);
		currentPtr = beginPtr = reinterpret_cast<const unsigned char*>(ptr);
		isSuccess = false;
		assert(factory!=nullptr);
		factory->Reset();
	}
	// 以当前读取位置重置存储环境
	virtual void Reset()
	{
		Init(CurrentBytePtr());
	}

	// 成功返回指令长度
	virtual int GetLength() const
	{
		if (IsSuccess())
		{
			return currentPtr - beginPtr;
		}
		return 0;
	}

	template<typename TStateFactory = IStateFactory>
	shared_ptr<TStateFactory> GetFactory() const
	{
		return dynamic_pointer_cast<TStateFactory>(factory);
	}
	template<>
	shared_ptr<IStateFactory> GetFactory() const
	{
		return factory;
	}
	virtual const unsigned char* CurrentBytePtr() const
	{
		return currentPtr;
	}
	virtual void NextByte()
	{
		currentPtr++;
	}
	// 是否解析成功
	virtual bool IsSuccess() const
	{
		return isSuccess;
	}
};

