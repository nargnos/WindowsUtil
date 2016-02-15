#pragma once
#include "Common.h"

// 表示一条指令，用来临时存储供状态机用的变量
class Instruction
{
	Instruction(const Instruction&) = delete;
protected:
	bool isSuccess;
	const unsigned char* beginPtr;
	const unsigned char* currentPtr;
	unsigned int range;  // 读取的限制范围，设置为0表示无限
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
	virtual void Init(const void* ptr, unsigned int range)
	{
		assert(ptr != NULL);
		beginPtr = reinterpret_cast<const unsigned char*>(ptr);
		currentPtr = 0;
		isSuccess = false;
		assert(factory != nullptr);
		factory->Reset();
		this->range = range;
	}
	void Init(const void* ptr)
	{
		Init(ptr, 0);
	}
	// 以当前读取位置重置存储环境
	virtual void Reset()
	{
		Init(CurrentBytePtr());
	}
	// 返回已读长度
	int ReadCount() const
	{
		return currentPtr == NULL ? 0 : currentPtr - beginPtr;
	}

	// 成功返回指令长度
	virtual int GetInstructionLength() const
	{
		return IsSuccess() ? ReadCount() : 0;
	}

	template<typename TStateFactory = IStateFactory>
	TStateFactory* GetFactory() const
	{
		return dynamic_cast<TStateFactory*>(factory.get());
	}
	template<>
	IStateFactory* GetFactory() const
	{
		return factory.get();
	}

	virtual const unsigned char* CurrentBytePtr() const
	{
		return currentPtr;
	}
	// 第一次步进设置初始位置开始读取
	virtual bool NextByte()
	{
		if (currentPtr == 0)
		{
			currentPtr = beginPtr;
			return true;
		}

		++currentPtr;
		return (range == 0) | (ReadCount() < range);
	}
	// 是否解析成功
	virtual bool IsSuccess() const
	{
		return isSuccess;
	}
};

