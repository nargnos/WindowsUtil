#include "..\Common\Common.h"
#include "StateFactory.h"
// »áÌøµ½µÄ×´Ì¬£ºByte
const State*  InitState::Next(const shared_ptr<Instruction>& inst) const
{
	// TODO: Init
	return inst->GetFactory<StateFactory>()->GetState(StateFactory::State_Byte);
}

