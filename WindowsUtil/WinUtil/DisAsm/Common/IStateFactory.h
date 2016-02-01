#pragma once
#include "Common.h"
// 需要避免生成太多无用对象
class IStateFactory
{
	IStateFactory(const IStateFactory&) = delete;
	IStateFactory& operator = (const IStateFactory&) = delete;
protected:
	// 取任意状态
	virtual  const unique_ptr<IState>& GetState(unsigned char) = 0;
public:

	IStateFactory()
	{
	}
	// 取得入口
	virtual const unique_ptr<IState>& GetBeginStateInstance() = 0;
	// 重置
	virtual void Reset() = 0;
	virtual ~IStateFactory()
	{
	}
};
