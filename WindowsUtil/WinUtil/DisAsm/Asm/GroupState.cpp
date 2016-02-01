#include "..\Common\Common.h"
#include "StateFactory.h"
const unique_ptr<IState>&  GroupState::Next(shared_ptr<Instruction>& inst) { return unique_ptr<IState>(); }
