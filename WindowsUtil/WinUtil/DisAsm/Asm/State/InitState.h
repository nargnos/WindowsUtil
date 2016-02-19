#pragma once
#include "AsmState.h"
#include "AsmStateFactory.h"
#include "..\AsmInstruction.h"
#include "..\AsmDisassembler.h"
#include "..\AsmStorage.h"
namespace Disassembler
{
	template<>
	class AsmState<AsmStateFactory::State_Init>:public IState
	{
	public:
		static int Next(AsmStateFactory::ParamType* param);
	};
	 
}  // namespace Disassembler
