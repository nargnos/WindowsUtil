#pragma once
#include "..\Common\Common.h"
// 需要避免生成太多无用对象
class IStateFactory
{
public:

	IStateFactory()
	{
	}
	// 取得入口
	virtual shared_ptr<IState> GetBeginStateInstance() = 0;
	// 取任意状态
	virtual shared_ptr<IState> GetState(unsigned char) = 0;
	virtual ~IStateFactory()
	{
	}
};
