#include "StateFactory.h"

const State* StateFactory::GetBeginStateInstance()
{
	return GetState(State_Init);
}
