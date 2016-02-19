#pragma once
#include "..\..\Common\Interface\IState.h"

namespace Disassembler
{
	template<int stateID>
	class AsmState;
	// 特例中需要定义static int Next(AsmStateFactory::ParamType* param)

}  // namespace Disassembler