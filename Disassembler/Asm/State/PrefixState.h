#pragma once

#include "AsmState.h"
#include "AsmStateFactory.h"
namespace Disassembler
{
	template<>
	class AsmState<AsmStateFactory::State_Prefix> :public IState
	{
	public:
		static int Next(AsmStateFactory::ParamType* param);
	};
	
}  // namespace Disassembler

