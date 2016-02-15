#pragma once
#include "AsmCommon.h"
#include "Opcode\OpcodeDef.h"
#include "InitState.h"
//#include "SibState.h"
//#include "RMState.h"
#include "EscapeState.h"
#include "GroupState.h"
#include "InstructionState.h"
#include "PrefixState.h"
#include "ByteState.h"
#include "EndState.h"
#include "ExitState.h"
#include "OperandState.h"
class StateFactory :
	public IStateFactory
{
public:
	friend class InitState;
	//friend class SibState;
	//friend class RmState;
	friend class EscapeState;
	friend class GroupState;
	friend class InstructionState;
	friend class PrefixState;
	friend class ByteState;
	friend class EndState;
	friend class ExitState;
	friend class OperandState;
	enum States :unsigned char
	{
		_Enum_States_Start,
		State_Init = _Enum_States_Start,
		//State_Sib,
		//State_Rm,
		State_Operand,
		State_Escape,
		State_Group,
		State_Instruction,
		State_Prefix,
		State_Byte,
		State_End,
		State_Exit,
		_Enum_States_End
	};
	StateFactory()
	{
		Reset();
	}
	virtual void Reset() override
	{
		currentState = lastState = _Enum_States_Start;
	}
	~StateFactory()
	{
	}
	inline States GetCurrentState() const
	{
		return currentState;
	}
	inline States GetLastState() const
	{
		return lastState;
	}

	virtual const State* GetBeginStateInstance() override;
	const State* GetState(OpcodeType opType);

	virtual const State* GetState(unsigned char index) override;
private:
	shared_ptr<State> states[_Enum_States_End];
	States currentState;
	States lastState;

};

