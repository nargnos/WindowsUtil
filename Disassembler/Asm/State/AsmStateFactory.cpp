#include "AsmStateFactory.h"
#include "AsmState.h"
#include "InitState.h"
#include "ByteState.h"
#include "PreEndState.h"
#include "EscapeState.h"
#include "GroupState.h"
#include "InstructionState.h"
#include "ByteState.h"
#include "OperandState.h"
#include "PrefixState.h"
namespace Disassembler
{

	AsmStateFactory::NextStateFunction AsmStateFactory::stateFunctions[]=
	{
		AsmState<State_Init>::Next,
		AsmState<State_Operand>::Next,
		AsmState<State_Escape>::Next,
		AsmState<State_Group>::Next,
		AsmState<State_Instruction>::Next,
		AsmState<State_Prefix>::Next,
		AsmState<State_Byte>::Next,
		AsmState<State_PreEnd>::Next,
	};
	// FIX: 此处需要传入变量循环调用，找有什么方法可以把那个数组去掉而又不用switch
	// 状态Next直接返回函数的话NextStateFunction无法声明
	AsmStateFactory::NextStateFunction AsmStateFactory::GetStateFunction(unsigned char stateId)
	{
		assert(stateId < (sizeof(stateFunctions) / sizeof(NextStateFunction)));
		return stateFunctions[stateId];
	}

}  // namespace Disassembler

