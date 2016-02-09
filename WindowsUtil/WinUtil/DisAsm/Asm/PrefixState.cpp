#include "..\Common\Common.h"
#include "StateFactory.h"
const State*  PrefixState::Next(const shared_ptr<Instruction>& inst) const
{
	return NULL;
}
