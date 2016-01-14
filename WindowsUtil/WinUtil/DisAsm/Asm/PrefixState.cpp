#include "..\Common\Common.h"
#include "StateFactory.h"
shared_ptr<IState> PrefixState::Next(shared_ptr<IInstruction>& inst) { return shared_ptr<IState>(); }
