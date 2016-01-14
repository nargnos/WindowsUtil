#include "..\Common\Common.h"
#include "StateFactory.h"
shared_ptr<IState> InitState::Next(shared_ptr<IInstruction>& inst)
{
	// TODO: Init
	return inst->GetFactory()->GetState(StateFactory::State_Byte1);
}

