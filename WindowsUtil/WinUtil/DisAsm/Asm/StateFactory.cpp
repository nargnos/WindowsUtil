#include "StateFactory.h"

const State* StateFactory::GetBeginStateInstance()
{
	return GetState(State_Init);
}
const State* StateFactory::GetState(OpcodeType opType)
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

const State* StateFactory::GetState(unsigned char index)
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