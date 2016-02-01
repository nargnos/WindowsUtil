#include "..\Common\Common.h"
#include "StateFactory.h"
const unique_ptr<IState>& SibState::Next(shared_ptr<Instruction>& inst) { return unique_ptr<IState>(); }
