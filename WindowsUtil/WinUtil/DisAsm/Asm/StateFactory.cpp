#include "StateFactory.h"

shared_ptr<IState> StateFactory::GetBeginStateInstance()
{
	return GetState(State_Init);
}
