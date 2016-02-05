#include "..\Common\Common.h"
#include "StateFactory.h"
// 这里决定操作数格式和类型
// 会跳转到End、Operand、Sib
const State* RmState::Next(const shared_ptr<Instruction>& inst) const 
{ 
	auto asmInst = inst->Cast<AsmInstruction>();
	
	// TODO: 这里依赖Prefix解析，解析还要先弄一个可以方便转字符串的表
	return NULL;
}
