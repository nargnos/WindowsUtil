#include "ByteState.h"
#include "StateFactory.h"
// 读Hex的状态，根据HexInst类型跳转，可能会多次进入
// Grp和Esc指令记录格式不同，所以由各自的状态分别读取
// 会跳到的状态：Instruction、Group、Byte、Escape、Prefix、End
const State*  ByteState::Next(const shared_ptr<Instruction>& inst) const
{
	auto asmInst = inst->Cast<AsmInstruction>();
	// 返回下个状态
	auto asmFac = asmInst->GetFactory<StateFactory>();
	// 需要根据上个指令的类型确定应该读取哪个表（多字节指令）
	auto lastInstType = asmInst->GetTmpInstType();
	auto currentInstType = asmInst->ReadInst(lastInstType);
	return asmFac->GetState(currentInstType);
}
