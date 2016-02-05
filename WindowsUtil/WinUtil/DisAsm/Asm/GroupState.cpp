#include "..\Common\Common.h"
#include "StateFactory.h"
const State*  GroupState::Next(const shared_ptr<Instruction>& inst) const
{
	// TODO: 表没录入, 可能需要子状态
	return NULL; 
}
