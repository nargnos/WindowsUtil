#include "ParameterState.h"
#include "StateFactory.h"

const unique_ptr<IState>&  ParameterState::Next(shared_ptr<Instruction>& inst)
{
	return unique_ptr<IState>();
}
