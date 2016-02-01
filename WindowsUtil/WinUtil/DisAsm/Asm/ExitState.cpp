#include "ExitState.h"
#include "StateFactory.h"
const unique_ptr<IState>&  ExitState::Next(shared_ptr<Instruction>& inst)
{
	return unique_ptr<IState>();
}

 bool ExitState::HasNext()
{
	return false;
}
