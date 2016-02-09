#pragma once
#include "AsmCommon.h"
#include "Opcode\OpcodeDef.h"
#include "InitState.h"
#include "SibState.h"
#include "RMState.h"
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

private:
	shared_ptr<State> states[_Enum_States_End];
	States currentState;
	States lastState;
protected:
	
	const State* GetState(OpcodeType opType)
	{
		switch (opType)
		{
		case OT_Inst:
		case OT_Inst_Change:
			assert(currentState == StateFactory::State_Byte);
			return GetState(StateFactory::State_Instruction);
		case OT_Grp:
			assert(currentState == StateFactory::State_Byte);
			return GetState(StateFactory::State_Group);
		case OT_Table_0F:
		case OT_Table_0F38:
		case OT_Table_0F3A:
			assert(currentState == StateFactory::State_Byte);
			return GetState(StateFactory::State_Byte);
		case OT_Esc:
			assert(currentState == StateFactory::State_Byte);
			return GetState(StateFactory::State_Escape);
		case OT_Prefix:
			assert(currentState == StateFactory::State_Byte);
			return GetState(StateFactory::State_Prefix);
		default:
			break;
		}

		return GetState(StateFactory::State_End);
	}

	virtual const State* GetState(unsigned char index) override
	{
		assert(index >= _Enum_States_Start && index < _Enum_States_End);
		auto& tmpState = states[index];
		lastState = currentState;
		currentState = static_cast<States>(index);
		if (!tmpState)
		{
			switch (currentState)
			{
			case StateFactory::State_Init:
				tmpState = make_shared<InitState>();
				break;
			/*case StateFactory::State_Sib:
				tmpState = make_shared<SibState>();
				break;
			case StateFactory::State_Rm:
				tmpState = make_shared<RmState>();
				break;*/
			case StateFactory::State_Escape:
				tmpState = make_shared<EscapeState>();
				break;
			case StateFactory::State_Group:
				tmpState = make_shared<GroupState>();
				break;
			case StateFactory::State_Instruction:
				tmpState = make_shared<InstructionState>();
				break;
			case StateFactory::State_Prefix:
				tmpState = make_shared<PrefixState>();
				break;
			case StateFactory::State_Byte:
				tmpState = make_shared<ByteState>();
				break;
			case StateFactory::State_End:
				tmpState = make_shared<EndState>();
				break;
			case StateFactory::State_Exit:
				tmpState = make_shared<ExitState>();
				break;
			case StateFactory::State_Operand:
				tmpState = make_shared<OperandState>();
				break;
			default:
				break;
			}
		}

		return tmpState.get();
	}


};

