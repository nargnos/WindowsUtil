#pragma once
#include "..\Common\Common.h"
#include "AsmInstruction.h"
class OperandState :
	public State
{
public:

	OperandState()
	{
	}

	~OperandState()
	{
	}
	virtual  const State*  Next(const shared_ptr<Instruction>& inst) const override;
	void ReadOperand(AsmInstruction* asmInst, int index, const RegOrOperandGroup& pair) const;
	// OperandType
private:
	typedef void (*HandleFunction)(AsmInstruction*, int);
	static void Handle_NULL(AsmInstruction* asmInst, int index);
	
	static void Handle_L_a(AsmInstruction* asmInst, int index);
	static void Handle_L_b(AsmInstruction* asmInst, int index);
	static void Handle_L_c(AsmInstruction* asmInst, int index);
	static void Handle_L_d(AsmInstruction* asmInst, int index);
	static void Handle_L_dq(AsmInstruction* asmInst, int index);
	static void Handle_L_p(AsmInstruction* asmInst, int index);
	static void Handle_L_pd(AsmInstruction* asmInst, int index);
	static void Handle_L_pi(AsmInstruction* asmInst, int index);
	static void Handle_L_ps(AsmInstruction* asmInst, int index);
	static void Handle_L_q(AsmInstruction* asmInst, int index);
	static void Handle_L_qq(AsmInstruction* asmInst, int index);
	static void Handle_L_s(AsmInstruction* asmInst, int index);
	static void Handle_L_sd(AsmInstruction* asmInst, int index);
	static void Handle_L_ss(AsmInstruction* asmInst, int index);
	static void Handle_L_si(AsmInstruction* asmInst, int index);
	static void Handle_L_v(AsmInstruction* asmInst, int index);
	static void Handle_L_w(AsmInstruction* asmInst, int index);
	static void Handle_L_x(AsmInstruction* asmInst, int index);
	static void Handle_L_y(AsmInstruction* asmInst, int index);
	static void Handle_L_z(AsmInstruction* asmInst, int index);
	static void Handle_H_1(AsmInstruction* asmInst, int index);
	static void Handle_H_A(AsmInstruction* asmInst, int index);
	static void Handle_H_B(AsmInstruction* asmInst, int index);
	static void Handle_H_C(AsmInstruction* asmInst, int index);
	static void Handle_H_D(AsmInstruction* asmInst, int index);
	static void Handle_H_E(AsmInstruction* asmInst, int index);
	static void Handle_H_F(AsmInstruction* asmInst, int index);
	static void Handle_H_G(AsmInstruction* asmInst, int index);
	static void Handle_H_H(AsmInstruction* asmInst, int index);
	static void Handle_H_I(AsmInstruction* asmInst, int index);
	static void Handle_H_J(AsmInstruction* asmInst, int index);
	static void Handle_H_L(AsmInstruction* asmInst, int index);
	static void Handle_H_M(AsmInstruction* asmInst, int index);
	static void Handle_H_N(AsmInstruction* asmInst, int index);
	static void Handle_H_O(AsmInstruction* asmInst, int index);
	static void Handle_H_P(AsmInstruction* asmInst, int index);
	static void Handle_H_Q(AsmInstruction* asmInst, int index);
	static void Handle_H_R(AsmInstruction* asmInst, int index);
	static void Handle_H_S(AsmInstruction* asmInst, int index);
	static void Handle_H_U(AsmInstruction* asmInst, int index);
	static void Handle_H_V(AsmInstruction* asmInst, int index);
	static void Handle_H_W(AsmInstruction* asmInst, int index);
	static void Handle_H_X(AsmInstruction* asmInst, int index);
	static void Handle_H_Y(AsmInstruction* asmInst, int index);

	static void Handle_SPC_AL_R8L(AsmInstruction* asmInst, int index);
	static void Handle_SPC_CL_R9L(AsmInstruction* asmInst, int index);
	static void Handle_SPC_DL_R10L(AsmInstruction* asmInst, int index);
	static void Handle_SPC_BL_R11L(AsmInstruction* asmInst, int index);
	static void Handle_SPC_AH_R12L(AsmInstruction* asmInst, int index);
	static void Handle_SPC_CH_R13L(AsmInstruction* asmInst, int index);
	static void Handle_SPC_DH_R14L(AsmInstruction* asmInst, int index);
	static void Handle_SPC_BH_R15L(AsmInstruction* asmInst, int index);
	static void Handle_SPC_AL_rAX(AsmInstruction* asmInst, int index);
	static void Handle_SPC_rAX_r8(AsmInstruction* asmInst, int index);
	static void Handle_SPC_rCX_r9(AsmInstruction* asmInst, int index);
	static void Handle_SPC_rDX_r10(AsmInstruction* asmInst, int index);
	static void Handle_SPC_rBX_r11(AsmInstruction* asmInst, int index);
	static void Handle_SPC_rSP_r12(AsmInstruction* asmInst, int index);
	static void Handle_SPC_rBP_r13(AsmInstruction* asmInst, int index);
	static void Handle_SPC_rSI_r14(AsmInstruction* asmInst, int index);
	static void Handle_SPC_rDI_r15(AsmInstruction* asmInst, int index);
	static void Handle_SPC_RAX_EAX_R8_R8D(AsmInstruction* asmInst, int index);
	static void Handle_SPC_RCX_ECX_R9_R9D(AsmInstruction* asmInst, int index);
	static void Handle_SPC_RDX_EDX_R10_R10D(AsmInstruction* asmInst, int index);
	static void Handle_SPC_RBX_EBX_R11_R11D(AsmInstruction* asmInst, int index);
	static void Handle_SPC_RSP_ESP_R12_R12D(AsmInstruction* asmInst, int index);
	static void Handle_SPC_RBP_EBP_R13_R13D(AsmInstruction* asmInst, int index);
	static void Handle_SPC_RSI_ESI_R14_R14D(AsmInstruction* asmInst, int index);
	static void Handle_SPC_RDI_EDI_R15_R15D(AsmInstruction* asmInst, int index);
	static void Handle_SPC_Ib_Iz(AsmInstruction* asmInst, int index);
	static void Handle_SPC_Mw_Rv(AsmInstruction* asmInst, int index);
	static void Handle_SPC_Rd_Mb(AsmInstruction* asmInst, int index);
	static void Handle_SPC_Rd_Mw(AsmInstruction* asmInst, int index);
	static void Handle_SPC_Rv_Mw(AsmInstruction* asmInst, int index);
	static void Handle_SPC_Ry_Mb(AsmInstruction* asmInst, int index);
	static void Handle_SPC_Ry_Mw(AsmInstruction* asmInst, int index);
	static void Handle_SPC_Udq_Md(AsmInstruction* asmInst, int index);
	static void Handle_SPC_Ux_Md(AsmInstruction* asmInst, int index);
	static void Handle_SPC_Ux_Mq(AsmInstruction* asmInst, int index);
	static void Handle_SPC_Ux_Mw(AsmInstruction* asmInst, int index);

	// change标识合并到reg
	static void Handle_SEG(AsmInstruction* asmInst, int index, const RegOrOperand& seg);
	static void Handle_REG(AsmInstruction* asmInst, int index, const RegOrOperand& reg, bool isChange);
	static const HandleFunction HandleFunctions[];
};

