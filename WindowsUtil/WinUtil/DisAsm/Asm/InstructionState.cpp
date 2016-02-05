#include "InstructionState.h"
#include "StateFactory.h"
// 如果需要读RM会跳转到Rm状态再跳到读操作数
// 会跳到的状态：End、Rm、Operand
const State*  InstructionState::Next(const shared_ptr<Instruction>& inst) const
{
	auto asmInst = inst->Cast<AsmInstruction>();
	auto type = asmInst->GetTmpInstType();
	// TODO: 输出名字
	
	// 这里跟InstChangeData共用结构，这两个结构成员变量类型大小顺序必须相同
	// InstChangeData的最后一个成员变量是用来添加名字后缀用的，这里不需要
	auto instData = asmInst->GetTmpData<InstData>();
	if (instData->ParamCount == 0)
	{
		asmInst->SetSuccess();
		return asmInst->GetFactory<StateFactory>()->GetState(StateFactory::State_End);
	}
	auto operandGrp = asmInst->wapper->GetOperandGroup(instData->ParamCount, instData->ParamID);
	for (auto i = 0; i < instData->ParamCount; i++)
	{
		auto& tmpOperand = asmInst->wapper->GetOperands(operandGrp[i]);
		if (!tmpOperand.H.IsReg && HasRM((OperandType)tmpOperand.H.Operand))
		{
			return asmInst->GetFactory<StateFactory>()->GetState(StateFactory::State_Rm);
		}
	}
	return asmInst->GetFactory<StateFactory>()->GetState(StateFactory::State_Operand);
}

bool InstructionState::HasRM(OperandType ot) const
{
	switch (ot)
	{
	case H_C:
	case H_D:
	case H_E:
	case H_G:
	case H_M:
	case H_N:
	case H_P:
	case H_Q:
	case H_R:
	case H_S:
	case H_U:
	case H_V:
	case H_W:
	case SPC_Mw_Rv:
	case SPC_Rd_Mb:
	case SPC_Rd_Mw:
	case SPC_Rv_Mw:
	case SPC_Ry_Mb:
	case SPC_Ry_Mw:
	case SPC_Udq_Md:
	case SPC_Ux_Md:
	case SPC_Ux_Mq:
	case SPC_Ux_Mw:
		return true;
	default:
		break;
	}
	return false;
}
