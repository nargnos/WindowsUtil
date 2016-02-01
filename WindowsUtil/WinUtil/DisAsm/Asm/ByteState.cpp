#include "ByteState.h"
#include "StateFactory.h"
const unique_ptr<IState>&  ByteState::Next(shared_ptr<Instruction>& inst)
{
	auto asmInst = inst->Cast<AsmInstruction>();
	// 返回下个状态
	auto asmFac = asmInst->GetFactory<StateFactory>();
	// 需要根据上个指令的类型确定应该读取哪个表（多字节指令）
	auto lastInstType = asmInst->GetTmpInstType();
	auto currentInstType = asmInst->ReadInst(lastInstType);
	return asmFac->GetState(currentInstType);
}
