#include "..\Common\Common.h"
#include "StateFactory.h"
const unique_ptr<IState>&  InitState::Next(shared_ptr<Instruction>& inst)
{
	// TODO: Init
	return inst->GetFactory<StateFactory>()->GetState(StateFactory::State_Byte);
}

