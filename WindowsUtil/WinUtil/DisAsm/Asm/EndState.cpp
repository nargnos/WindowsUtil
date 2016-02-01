#include "EndState.h"
#include "StateFactory.h"
const unique_ptr<IState>& EndState::Next(shared_ptr<Instruction>& inst)
{
	return inst->GetFactory<StateFactory>()->GetState(StateFactory::State_Exit);
}
