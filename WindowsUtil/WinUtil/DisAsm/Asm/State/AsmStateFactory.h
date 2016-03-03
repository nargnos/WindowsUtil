#pragma once
#include "..\AsmDisassembler_Trait.h"
#include "..\..\Common\StateFactory.h"
namespace Disassembler
{
	
	class AsmStateFactory:public StateFactory<AsmDisassembler>
	{
	public:
		enum StateIDs :unsigned char
		{
			_Enum_States_Start,
			State_Init = _Enum_States_Start,
			State_Operand,
			State_Escape,
			State_Group,
			State_Instruction,
			State_Prefix,
			State_Byte,
			State_PreEnd,
			State_End,
			_Enum_States_End
		};
		static NextStateFunction GetStateFunction(unsigned char stateId);

		static constexpr unsigned char BeginStateID = State_Init;
		static constexpr unsigned char EndStateID = State_End;

	private:
		static NextStateFunction stateFunctions[];
	};
}  // namespace Disassembler
