#pragma once
#include "AsmCommon.h"
#include "Opcode\OpcodeDef.h"
#include "InitState.h"
#include "SibState.h"
#include "RMState.h"
#include "EscapeState.h"
#include "GroupState.h"
#include "ParameterState.h"
#include "PrefixState.h"
#include "ByteState.h"
#include "EndState.h"
#include "ExitState.h"

class StateFactory :
	public IStateFactory
{
public:
	friend class InitState;
	friend class SibState;
	friend class RmState;
	friend class EscapeState;
	friend class GroupState;
	friend class ParameterState;
	friend class PrefixState;
	friend class ByteState;
	friend class EndState;
	friend class ExitState;
	enum States :unsigned char
	{
		_Enum_States_Start,
		State_Init = _Enum_States_Start,
		State_Sib,
		State_Rm,
		State_Escape,
		State_Group,
		State_Parameter,
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
	inline  States GetCurrentState()
	{
		return currentState;
	}
	inline  States GetLastState()
	{
		return lastState;
	}

	virtual  const unique_ptr<IState>& GetBeginStateInstance() override;

private:
	
	unique_ptr<IState> states[_Enum_States_End];
protected:
	States currentState;
	States lastState;
	const unique_ptr<IState>& GetState(OpcodeType opType)
	{
		
		switch (opType)
		{
		case OT_Inst:
		case OT_Inst_Change:
			assert(currentState == StateFactory::State_Byte);
			return GetState(StateFactory::State_Parameter);
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
			break;
		default:
			break;
		}

		return GetState(StateFactory::State_End);
	}

	virtual const unique_ptr<IState>& GetState(unsigned char index) override
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
				tmpState = make_unique<InitState>();
				break;
			case StateFactory::State_Sib:
				tmpState = make_unique<SibState>();
				break;
			case StateFactory::State_Rm:
				tmpState = make_unique<RmState>();
				break;
			case StateFactory::State_Escape:
				tmpState = make_unique<EscapeState>();
				break;
			case StateFactory::State_Group:
				tmpState = make_unique<GroupState>();
				break;
			case StateFactory::State_Parameter:
				tmpState = make_unique<ParameterState>();
				break;
			case StateFactory::State_Prefix:
				tmpState = make_unique<PrefixState>();
				break;
			case StateFactory::State_Byte:
				tmpState = make_unique<ByteState>();
				break;
			case StateFactory::State_End:
				tmpState = make_unique<EndState>();
				break;
			case StateFactory::State_Exit:
				tmpState = make_unique<ExitState>();
				break; 
			default:
				break;
			}
		}

		return tmpState;
	}


};

