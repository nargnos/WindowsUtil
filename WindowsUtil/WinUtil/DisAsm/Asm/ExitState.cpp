#include "ExitState.h"
#include "StateFactory.h"
const State*  ExitState::Next(const shared_ptr<Instruction>& inst) const
{
	return NULL;
}

 bool ExitState::HasNext() const
{
	return false;
}
