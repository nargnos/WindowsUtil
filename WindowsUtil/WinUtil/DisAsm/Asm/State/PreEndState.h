#pragma once
#include "AsmState.h"
#include "AsmStateFactory.h"
// 用来做一些收尾工作

namespace Disassembler
{
	template<>
	class AsmState<AsmStateFactory::State_PreEnd>:public IState
	{
	public:
		static int Next(AsmStateFactory::ParamType* param)
		{
			return AsmStateFactory::State_End;
		}
	};
}  // namespace Disassembler
