#include "EndState.h"
#include "StateFactory.h"
const State* EndState::Next(const shared_ptr<Instruction>& inst) const
{
	return inst->GetFactory()->GetState(StateFactory::State_Exit);
}
