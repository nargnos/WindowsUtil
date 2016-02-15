#include "OperandState.h"
#include "StateFactory.h"

// TODO: 从文档63页CHAPTER 3 BASIC EXECUTION ENVIRONMENT 开始看
// TODO: 好像关于SSE的还挺乱的，先看一段时间文档再说
// TODO: 缺了文档3A，下载了再说吧

// 解析并输出操作数信息
const State* OperandState::Next(const shared_ptr<Instruction>& inst) const
{
	auto asmInst = inst->Cast<AsmInstruction>();
	auto operandGrp = asmInst->operandGrpStorage.GetOperandGrp();
	auto grpCount = asmInst->operandGrpStorage.GetOperandCount();
	// 此时的读取位置在指令Hex后，RM或操作数Hex前
	// 读RM、sib或读操作数都会步进该类型的长度，
	// 如果是操作数，需要记录数据起始地址、类型长度和类型（方便后面输出时用，类型是指整型单精度双精度浮点啥的）
	// 如果是寄存器，会记录reg枚举值（可变长的会选定到正确字长的寄存器）
	// TODO: 需要确定好存储什么内容，Dflag怎么用等

	for (auto i = 0; i < grpCount; i++)
	{
		auto& tmpOperand = asmInst->GetOpcodeDataWapper()->GetOperands(operandGrp[i]);
		ReadOperand(asmInst, i, tmpOperand);
	}
	
	asmInst->SetSuccess();
	return inst->GetFactory()->GetState(StateFactory::State_End);
}

void OperandState::ReadOperand(AsmInstruction* asmInst, int index, const RegOrOperandGroup& pair) const
{
	// 只有H才可能为reg
	if (pair.H.IsReg)
	{
		// 因为段寄存器定义跟reg混一起，所以要分一下
		if (asmInst->GetOpcodeDataWapper()->IsSeg(pair.H.Val))
		{
			// L为NULL不用理
			assert(pair.L.Val == NULL);
			Handle_SEG(asmInst, index, pair.H);
		}
		else
		{
			// 单reg的组合的L部分要么为NULL，要么为CHANGE_REG，所以直接用作指示是否可以根据大小可变的标识
			Handle_REG(asmInst, index, pair.H, pair.L.Val);
		}
	}
	else
	{
		assert(pair.H.Val >= NULL && pair.H.Val <= SPC_Ux_Mw);
		assert(pair.L.Val >= NULL && pair.L.Val <= SPC_Ux_Mw);
		// 先确定操作数类型再使用寻址方式
		OperandState::HandleFunctions[pair.L.Operand](asmInst, index);
		OperandState::HandleFunctions[pair.H.Operand](asmInst, index);
	}
}
void OperandState::Handle_NULL(AsmInstruction* asmInst, int index)
{
	// H和L都有可能选到这个
}
void OperandState::Handle_L_a(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_b(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_c(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_d(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_dq(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_p(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_pd(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_pi(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_ps(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_q(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_qq(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_s(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_sd(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_ss(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_si(AsmInstruction* asmInst, int index)
{
	// 没有使用
}
void OperandState::Handle_L_v(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_w(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_x(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_y(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_z(AsmInstruction* asmInst, int index)
{

}


void OperandState::Handle_H_1(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_A(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_B(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_C(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_D(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_E(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_F(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_G(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_H(AsmInstruction* asmInst, int index)
{
	// 忽略掉这个操作数
}
void OperandState::Handle_H_I(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_J(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_L(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_M(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_N(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_O(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_P(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_Q(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_R(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_S(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_U(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_V(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_W(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_X(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_Y(AsmInstruction* asmInst, int index)
{

}

// 特殊组合需要选定一个然后跳转到前面的函数
void OperandState::Handle_SPC_AL_R8L(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_CL_R9L(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_DL_R10L(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_BL_R11L(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_AH_R12L(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_CH_R13L(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_DH_R14L(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_BH_R15L(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_AL_rAX(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_rAX_r8(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_rCX_r9(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_rDX_r10(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_rBX_r11(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_rSP_r12(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_rBP_r13(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_rSI_r14(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_rDI_r15(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_RAX_EAX_R8_R8D(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_RCX_ECX_R9_R9D(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_RDX_EDX_R10_R10D(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_RBX_EBX_R11_R11D(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_RSP_ESP_R12_R12D(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_RBP_EBP_R13_R13D(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_RSI_ESI_R14_R14D(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_RDI_EDI_R15_R15D(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Ib_Iz(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Mw_Rv(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Rd_Mb(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Rd_Mw(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Rv_Mw(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Ry_Mb(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Ry_Mw(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Udq_Md(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Ux_Md(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Ux_Mq(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Ux_Mw(AsmInstruction* asmInst, int index)
{

}

void OperandState::Handle_SEG(AsmInstruction* asmInst, int index, const RegOrOperand& seg)
{
	// asmInst->opcodeDataWapper.GetSegName((OperandType)seg.Val);
}

void OperandState::Handle_REG(AsmInstruction* asmInst, int index, const RegOrOperand& reg, bool isChange)
{
	auto ot = (OperandType)reg.Val;
	auto tmpReg = reinterpret_cast<RegOrOperand*>(&ot);
	assert(tmpReg->IsReg);
	// GetRegisterName(tmpReg->Reg.Hex, (RegisterLength)tmpReg->Reg.LenType);
	// 选择短的就把tmpReg->Reg.LenType减掉就行了

}

// NOTICE: 顺序必须跟枚举值一致
const OperandState::HandleFunction OperandState::HandleFunctions[] =
{
	Handle_NULL,
	Handle_L_a,
	Handle_L_b,
	Handle_L_c,
	Handle_L_d,
	Handle_L_dq,
	Handle_L_p,
	Handle_L_pd,
	Handle_L_pi,
	Handle_L_ps,
	Handle_L_q,
	Handle_L_qq,
	Handle_L_s,
	Handle_L_sd,
	Handle_L_ss,
	Handle_L_si,
	Handle_L_v,
	Handle_L_w,
	Handle_L_x,
	Handle_L_y,
	Handle_L_z,
	Handle_H_1,
	Handle_H_A,
	Handle_H_B,
	Handle_H_C,
	Handle_H_D,
	Handle_H_E,
	Handle_H_F,
	Handle_H_G,
	Handle_H_H,
	Handle_H_I,
	Handle_H_J,
	Handle_H_L,
	Handle_H_M,
	Handle_H_N,
	Handle_H_O,
	Handle_H_P,
	Handle_H_Q,
	Handle_H_R,
	Handle_H_S,
	Handle_H_U,
	Handle_H_V,
	Handle_H_W,
	Handle_H_X,
	Handle_H_Y,
	Handle_SPC_AL_R8L,
	Handle_SPC_CL_R9L,
	Handle_SPC_DL_R10L,
	Handle_SPC_BL_R11L,
	Handle_SPC_AH_R12L,
	Handle_SPC_CH_R13L,
	Handle_SPC_DH_R14L,
	Handle_SPC_BH_R15L,
	Handle_SPC_AL_rAX,
	Handle_SPC_rAX_r8,
	Handle_SPC_rCX_r9,
	Handle_SPC_rDX_r10,
	Handle_SPC_rBX_r11,
	Handle_SPC_rSP_r12,
	Handle_SPC_rBP_r13,
	Handle_SPC_rSI_r14,
	Handle_SPC_rDI_r15,
	Handle_SPC_RAX_EAX_R8_R8D,
	Handle_SPC_RCX_ECX_R9_R9D,
	Handle_SPC_RDX_EDX_R10_R10D,
	Handle_SPC_RBX_EBX_R11_R11D,
	Handle_SPC_RSP_ESP_R12_R12D,
	Handle_SPC_RBP_EBP_R13_R13D,
	Handle_SPC_RSI_ESI_R14_R14D,
	Handle_SPC_RDI_EDI_R15_R15D,
	Handle_SPC_Ib_Iz,
	Handle_SPC_Mw_Rv,
	Handle_SPC_Rd_Mb,
	Handle_SPC_Rd_Mw,
	Handle_SPC_Rv_Mw,
	Handle_SPC_Ry_Mb,
	Handle_SPC_Ry_Mw,
	Handle_SPC_Udq_Md,
	Handle_SPC_Ux_Md,
	Handle_SPC_Ux_Mq,
	Handle_SPC_Ux_Mw,
};
