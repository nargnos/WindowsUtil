#include "StateFactory.h"

const unique_ptr<IState>& StateFactory::GetBeginStateInstance()
{
	return GetState(State_Init);
}
