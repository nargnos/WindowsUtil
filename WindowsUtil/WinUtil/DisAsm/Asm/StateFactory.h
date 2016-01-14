#pragma once
#include "..\Common\Common.h"
#include "InitState.h"
#include "SibState.h"
#include "RMState.h"
#include "EscapeState.h"
#include "GroupState.h"
#include "ParameterState.h"
#include "PrefixState.h"
#include "Byte1State.h"
#include "Byte2State.h"
#include "Byte3State.h"
#include "EndState.h"
class StateFactory :
	public IStateFactory
{
	enum States:unsigned char
	{
		_Enum_States_Start,
		State_Init = _Enum_States_Start,
		State_Sib,
		State_Rm,
		State_Escape,
		State_Group,
		State_Parameter,
		State_Prefix,
		State_Byte1,
		State_Byte2,
		State_Byte3,
		State_End,
		_Enum_States_End
	};
	friend class InitState;
	friend class SibState;
	friend class RmState;
	friend class EscapeState;
	friend class GroupState;
	friend class ParameterState;
	friend class PrefixState;
	friend class Byte1State;
	friend class Byte2State;
	friend class Byte3State;
	friend class EndState;
	shared_ptr<IState> states[_Enum_States_End];
protected:
	virtual shared_ptr<IState> GetState(unsigned char index) override
	{
		assert(index >= _Enum_States_Start && index <_Enum_States_End);
		auto& tmpState = states[index];
		if (!tmpState)
		{
			switch (static_cast<States>(index))
			{
			case StateFactory::State_Init:
				tmpState = make_shared<InitState>();
				break;
			case StateFactory::State_Sib:
				tmpState = make_shared<SibState>();
				break;
			case StateFactory::State_Rm:
				tmpState = make_shared<RmState>();
				break;
			case StateFactory::State_Escape:
				tmpState = make_shared<EscapeState>();
				break;
			case StateFactory::State_Group:
				tmpState = make_shared<GroupState>();
				break;
			case StateFactory::State_Parameter:
				tmpState = make_shared<ParameterState>();
				break;
			case StateFactory::State_Prefix:
				tmpState = make_shared<PrefixState>();
				break;
			case StateFactory::State_Byte1:
				tmpState = make_shared<Byte1State>();
				break;
			case StateFactory::State_Byte2:
				tmpState = make_shared<Byte2State>();
				break;
			case StateFactory::State_Byte3:
				tmpState = make_shared<Byte3State>();
				break;
			case StateFactory::State_End:
				tmpState = make_shared<EndState>();
				break;
			default:
				break;
			}
		}
		return tmpState;
	}
public:

	StateFactory()
	{
	}

	~StateFactory()
	{
	}

	// Í¨¹ý IStateFactory ¼Ì³Ð
	virtual shared_ptr<IState> GetBeginStateInstance() override;
};

