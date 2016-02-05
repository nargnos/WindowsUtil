#include "..\Common\Common.h"
#include "StateFactory.h"
// 解析SIB表
// 会跳到Operand、End
const State* SibState::Next(const shared_ptr<Instruction>& inst) const 
{
	// TODO: 依赖RM
	return NULL; 
}
