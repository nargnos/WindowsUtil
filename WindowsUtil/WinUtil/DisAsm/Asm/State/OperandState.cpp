#include "OperandState.h"
namespace Disassembler
{
	int AsmState<AsmStateFactory::State_Operand>::Next(AsmStateFactory::ParamType * param)
	{
		auto wapper = param->GetOpcodeDataWapper();
		auto storage = param->GetStorage();
		auto operandGrpStorage = storage->GetOperandGroupStorage();

		auto grpCount = operandGrpStorage->GetOperandCount();

		// 此时的读取位置在指令Hex后，RM或操作数Hex前
		// 读RM、sib或读操作数都会步进该类型的长度，
		// 如果是操作数，需要记录数据起始地址、类型长度和类型（方便后面输出时用，类型是指整型单精度双精度浮点啥的）
		// 如果是寄存器，会记录reg枚举值（可变长的会选定到正确字长的寄存器）

		for (auto i = 0; i < grpCount; i++)
		{
			// 此时OperandInfo存储的是操作数类型下标
			auto& tmpOperand = wapper->GetOperands(operandGrpStorage->GetOperandInfo(i));
			assert(operandGrpStorage->GetOperandInfoType(i) == OVT_RegOrOperandGroupID);
			ReadOperand(param, i, tmpOperand);
			assert(operandGrpStorage->GetOperandInfoType(i) != OVT_RegOrOperandGroupID);
		}

		storage->SetSuccess();
		return AsmStateFactory::State_PreEnd;
	}
	void AsmState<AsmStateFactory::State_Operand>::ReadOperand(
		AsmStateFactory::ParamType * param,
		int index,
		const RegOrOperandGroup & pair)
	{
		// 只有H才可能为reg
		if (pair.H.IsReg)
		{
			// 因为段寄存器定义跟reg混一起，所以要分一下
			if (param->GetOpcodeDataWapper()->IsSeg(pair.H.Val))
			{
				// L为NULL不用理
				assert(pair.L.Val == NULL);
				SEG_Handler(param, index, (OperandType)pair.H.Val);
			}
			else
			{
				// 单reg的组合的L部分要么为NULL，要么为CHANGE_REG，所以直接用作指示是否可以根据大小可变的标识
				REG_Handler(param, index, (OperandType)pair.H.Val, pair.L.Val);
			}
		}
		else
		{
			assert(pair.H.Val >= NULL && pair.H.Val <= SPC_Ux_Mw);
			assert(pair.L.Val >= NULL && pair.L.Val <= SPC_Ux_Mw);
			// 先确定操作数类型再使用寻址方式
			Self::Handlers[pair.L.Operand](param, index);
			Self::Handlers[pair.H.Operand](param, index);
		}
	}
	void AsmState<AsmStateFactory::State_Operand>::SetOperandInfo(
		AsmStateFactory::ParamType* param,
		int index,
		const unsigned char* convertTable,
		OperandValueType type = OVT_Integer)
	{
		auto storage = param->GetStorage();
		auto oprandStorage = storage->GetOperandGroupStorage();
		auto opSizeAttr = oprandStorage->GetOperandSizeAttribute() - 1;
		oprandStorage->SetOperandInfo(index, convertTable[opSizeAttr]);
		oprandStorage->SetOperandInfoType(index, type);
	}
	void AsmState<AsmStateFactory::State_Operand>::SetOperandInfo(
		AsmStateFactory::ParamType* param,
		int index,
		unsigned char val,
		OperandValueType type = OVT_Integer)
	{
		auto storage = param->GetStorage();
		auto oprandStorage = storage->GetOperandGroupStorage();
		oprandStorage->SetOperandInfo(index, val);
		oprandStorage->SetOperandInfoType(index, type);

	}
	unsigned char AsmState<AsmStateFactory::State_Operand>::defaultSizeConvert[] =
	{ BIT_SIZE(WORD), BIT_SIZE(DWORD), BIT_SIZE(DWORD64) };

	// FIX: 注意！并没有找到在不同的大小属性中选择何种长度的描述，现在还需要看文档来修复这里的长度选择
	void AsmState<AsmStateFactory::State_Operand>::NULL_Handler(AsmStateFactory::ParamType * param, int index)
	{
		auto storage = param->GetStorage();
		storage->GetOperandGroupStorage()->SetOperandInfoType(index, OVT_NotSet);
	}
	unsigned char AsmState<AsmStateFactory::State_Operand>::l_a_SizeConvert[] =
	{ BIT_SIZE(WORD) * 2, BIT_SIZE(DWORD) * 2, BIT_SIZE(DWORD) * 2 };

	void AsmState<AsmStateFactory::State_Operand>::L_a_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// FIX: 并未找到操作数大小属性对应选择大小的描述
		assert(MaxConvertTableSize == sizeof(l_a_SizeConvert));
		SetOperandInfo(param, index, l_a_SizeConvert);
	}
	void AsmState<AsmStateFactory::State_Operand>::L_b_Handler(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, BIT_SIZE(unsigned char));
	}
	void AsmState<AsmStateFactory::State_Operand>::L_c_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// 目前表中没有操作数使用
		assert(false);
	}
	void AsmState<AsmStateFactory::State_Operand>::L_d_Handler(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, BIT_SIZE(DWORD));
	}
	void AsmState<AsmStateFactory::State_Operand>::L_dq_Handler(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, BIT_SIZE(DWORD64) * 2);
	}
	void AsmState<AsmStateFactory::State_Operand>::L_p_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// TODO: 32位，48位，或80位的指针，取决于操作数大小属性。
		// SetOperandInfo(param, index,?,OVT_Pointer);

	}
	void AsmState<AsmStateFactory::State_Operand>::L_pd_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// TODO: 128位或256位紧缩双精度浮点数。
		// SetOperandInfo(param, index,?,OVT_Double);
	}
	void AsmState<AsmStateFactory::State_Operand>::L_pi_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// TODO: QWORD MMX寄存器（如mm0）
	}
	void AsmState<AsmStateFactory::State_Operand>::L_ps_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// TODO: 128位或256位紧缩单精度浮点数。
		// SetOperandInfo(param, index,?,OVT_Float);

	}
	void AsmState<AsmStateFactory::State_Operand>::L_q_Handler(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, BIT_SIZE(DWORD64));
	}
	void AsmState<AsmStateFactory::State_Operand>::L_qq_Handler(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, BIT_SIZE(DWORD64) * 4);
	}
	void AsmState<AsmStateFactory::State_Operand>::L_s_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// TODO: 6字节或10字节的伪描述符
	}
	void AsmState<AsmStateFactory::State_Operand>::L_sd_Handler(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, 128, OVT_DoubleScalar);
	}
	void AsmState<AsmStateFactory::State_Operand>::L_ss_Handler(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, 128, OVT_FloatScalar);
	}
	void AsmState<AsmStateFactory::State_Operand>::L_si_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// 没有使用
		assert(false);
	}
	void AsmState<AsmStateFactory::State_Operand>::L_v_Handler(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, defaultSizeConvert);
	}
	void AsmState<AsmStateFactory::State_Operand>::L_w_Handler(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, BIT_SIZE(WORD));
	}
	void AsmState<AsmStateFactory::State_Operand>::L_x_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// TODO: 基于dq或qq的操作数大小属性
	}

	unsigned char AsmState<AsmStateFactory::State_Operand>::l_y_SizeConvert[] =
	{ BIT_SIZE(DWORD), BIT_SIZE(DWORD), BIT_SIZE(DWORD64) };

	void AsmState<AsmStateFactory::State_Operand>::L_y_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// FIX: BIT16时的大小相关描述未找到，
		SetOperandInfo(param, index, l_y_SizeConvert);
	}

	unsigned char AsmState<AsmStateFactory::State_Operand>::l_z_SizeConvert[] =
	{ BIT_SIZE(WORD), BIT_SIZE(DWORD), BIT_SIZE(DWORD) };
	void AsmState<AsmStateFactory::State_Operand>::L_z_Handler(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, l_z_SizeConvert);
	}

	// TODO: 以下函数要做的是记录当前指针位置，并偏移解析后的长度。RM和Sib需要记录其地址
	// 最终得到的是一个记录 操作数类型、长度、值（Reg，数字的只记地址和长度）、内存位置（用到立即数的指令）、RM/Sib开始位置 的表
	// 得到这个表就可以组织字符串输出了（RM域的处理打算用传函数指针方式、或者传ID后面再找函数）
	// 最后需要优化 只需要解析指令长度不需要输出的情况
	void AsmState<AsmStateFactory::State_Operand>::H_1_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// FIX: 文档并未描述
	}
	void AsmState<AsmStateFactory::State_Operand>::H_A_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// [0xXXXX....]
	}
	void AsmState<AsmStateFactory::State_Operand>::H_B_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// vex pfx vvvv
	}
	void AsmState<AsmStateFactory::State_Operand>::H_C_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M reg ctr
	}
	void AsmState<AsmStateFactory::State_Operand>::H_D_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M reg dbg
	}
	void AsmState<AsmStateFactory::State_Operand>::H_E_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M [reg+xxxx]
	}
	void AsmState<AsmStateFactory::State_Operand>::H_F_Handler(AsmStateFactory::ParamType * param, int index)
	{
		//eflags/rflags
	}
	void AsmState<AsmStateFactory::State_Operand>::H_G_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M reg
	}
	void AsmState<AsmStateFactory::State_Operand>::H_H_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// vex vvvv xmm|ymm
		// 传统SSE忽略掉这个操作数
	}
	void AsmState<AsmStateFactory::State_Operand>::H_I_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// imm
	}
	void AsmState<AsmStateFactory::State_Operand>::H_J_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// offset imm
	}
	void AsmState<AsmStateFactory::State_Operand>::H_L_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// 8位立即数的高4位用作表示128位的XMM寄存器或256位的YMM寄存器，取决于操作数类型（在32位模式下忽略MSB）
	}
	void AsmState<AsmStateFactory::State_Operand>::H_M_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M mem
	}
	void AsmState<AsmStateFactory::State_Operand>::H_N_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M rm 4mmx
	}
	void AsmState<AsmStateFactory::State_Operand>::H_O_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// 该指令没有ModR/M字节。操作数的偏移被编码为字或双字(取决于地址大小属性)。
		// 没有基址寄存器、变址寄存器或比例因数可以应用。
	}
	void AsmState<AsmStateFactory::State_Operand>::H_P_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M reg 4mmx
	}
	void AsmState<AsmStateFactory::State_Operand>::H_Q_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M mmx mem
	}
	void AsmState<AsmStateFactory::State_Operand>::H_R_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M
	}
	void AsmState<AsmStateFactory::State_Operand>::H_S_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M seg
	}
	void AsmState<AsmStateFactory::State_Operand>::H_U_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M rm xmm|ymm
	}
	void AsmState<AsmStateFactory::State_Operand>::H_V_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M reg xmm|ymm
	}
	void AsmState<AsmStateFactory::State_Operand>::H_W_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M xmm|ymm
	}
	void AsmState<AsmStateFactory::State_Operand>::H_X_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// DS:rSI
	}
	void AsmState<AsmStateFactory::State_Operand>::H_Y_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// ES:rDI
	}

	void AsmState<AsmStateFactory::State_Operand>::SPC_XL_RXL_Handler(AsmStateFactory::ParamType * param, int index, const OperandType* selectTable)
	{
		// 数组长度必须 == 2
		auto storage = param->GetStorage();
		auto pfx = storage->GetPrefixStorage();
		if (pfx->HasRex() && pfx->GetRex()->B)
		{
			// rxl
			REG_Handler(param, index, selectTable[0], false);
		}
		else
		{
			// xl
			REG_Handler(param, index, selectTable[1], false);
		}
	}
	void AsmState<AsmStateFactory::State_Operand>::SPC_AL_R8L_Handler(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_R8L ,REG_AL };
		SPC_XL_RXL_Handler(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::SPC_CL_R9L_Handler(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_R9L ,REG_CL };
		SPC_XL_RXL_Handler(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::SPC_DL_R10L_Handler(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_R10L ,REG_DL };
		SPC_XL_RXL_Handler(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::SPC_BL_R11L_Handler(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_R11L ,REG_BL };
		SPC_XL_RXL_Handler(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::SPC_AH_R12L_Handler(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_R12L ,REG_AH };
		SPC_XL_RXL_Handler(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::SPC_CH_R13L_Handler(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_R13L ,REG_CH };
		SPC_XL_RXL_Handler(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::SPC_DH_R14L_Handler(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_R14L ,REG_DH };
		SPC_XL_RXL_Handler(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::SPC_BH_R15L_Handler(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_R15L ,REG_BH };
		SPC_XL_RXL_Handler(param, index, table);
	}


	void AsmState<AsmStateFactory::State_Operand>::SPC_AL_rAX_Handler(AsmStateFactory::ParamType * param, int index)
	{
		// FIX: 操作数大小属性表里没有8位的，需要先找到描述
	}
	void AsmState<AsmStateFactory::State_Operand>::SPC_rXX_rX_Handler(AsmStateFactory::ParamType * param, int index, const OperandType* selectTable)
	{
		// 数组长度必须 == 4
		auto storage = param->GetStorage();
		auto pfx = storage->GetPrefixStorage();
		auto operand = storage->GetOperandGroupStorage();
		switch (operand->GetOperandSizeAttribute())
		{
		case Bit16:
			// xx
			REG_Handler(param, index, selectTable[0], false);
			break;
		case Bit32:
			// exx
			REG_Handler(param, index, selectTable[1], false);
			break;
		case Bit64:
			if (pfx->HasRex() && pfx->GetRex()->B)
			{
				// rx
				REG_Handler(param, index, selectTable[2], false);
			}
			else
			{
				// rxx
				REG_Handler(param, index, selectTable[3], false);
			}
			break;
		default:
			assert(false);
			break;
		}
	}
	void AsmState<AsmStateFactory::State_Operand>::SPC_rAX_r8_Handler(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_AX ,REG_EAX,REG_R8,REG_RAX };
		SPC_rXX_rX_Handler(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::SPC_rCX_r9_Handler(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_CX ,REG_ECX,REG_R9,REG_RCX };
		SPC_rXX_rX_Handler(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::SPC_rDX_r10_Handler(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_DX ,REG_EDX,REG_R10,REG_RDX };
		SPC_rXX_rX_Handler(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::SPC_rBX_r11_Handler(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_BX ,REG_EBX,REG_R11,REG_RBX };
		SPC_rXX_rX_Handler(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::SPC_rSP_r12_Handler(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_SP ,REG_ESP,REG_R12,REG_RSP };
		SPC_rXX_rX_Handler(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::SPC_rBP_r13_Handler(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_BP ,REG_EBP,REG_R13,REG_RBP };
		SPC_rXX_rX_Handler(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::SPC_rSI_r14_Handler(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_SI ,REG_ESI,REG_R14,REG_RSI };
		SPC_rXX_rX_Handler(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::SPC_rDI_r15_Handler(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_DI ,REG_EDI,REG_R15,REG_RDI };
		SPC_rXX_rX_Handler(param, index, table);
	}


	void AsmState<AsmStateFactory::State_Operand>::SPC_RAX_EAX_R8_R8D_Handler(AsmStateFactory::ParamType * param, int index)
	{
		auto storage = param->GetStorage();
		auto pfx = storage->GetPrefixStorage();
		auto operand = storage->GetOperandGroupStorage();
		if (pfx->HasRex() && pfx->GetRex()->B)
		{
			// rex.b
			switch (operand->GetOperandSizeAttribute())
			{
			case Bit16:
				// ?
				break;
			case Bit32:
				// r8d
				break;
			case Bit64:
				// r8
				break;
			default:
				break;
			}
		}
		else
		{
			switch (operand->GetOperandSizeAttribute())
			{
			case Bit16:
				// ?
				break;
			case Bit32:
				// eax
				break;
			case Bit64:
				// rax
				break;
			default:
				break;
			}
		}

	}
	void AsmState<AsmStateFactory::State_Operand>::SPC_RCX_ECX_R9_R9D_Handler(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::SPC_RDX_EDX_R10_R10D_Handler(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::SPC_RBX_EBX_R11_R11D_Handler(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::SPC_RSP_ESP_R12_R12D_Handler(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::SPC_RBP_EBP_R13_R13D_Handler(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::SPC_RSI_ESI_R14_R14D_Handler(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::SPC_RDI_EDI_R15_R15D_Handler(AsmStateFactory::ParamType * param, int index)
	{}

	// 下面这些组合好像都是SSE用的
	void AsmState<AsmStateFactory::State_Operand>::SPC_Ib_Iz_Handler(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::SPC_Mw_Rv_Handler(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::SPC_Rd_Mb_Handler(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::SPC_Rd_Mw_Handler(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::SPC_Rv_Mw_Handler(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::SPC_Ry_Mb_Handler(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::SPC_Ry_Mw_Handler(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::SPC_Udq_Md_Handler(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::SPC_Ux_Md_Handler(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::SPC_Ux_Mq_Handler(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::SPC_Ux_Mw_Handler(AsmStateFactory::ParamType * param, int index)
	{}

	void AsmState<AsmStateFactory::State_Operand>::SEG_Handler(AsmStateFactory::ParamType * param, int index, OperandType seg)
	{
		auto storage = param->GetStorage();
		auto opgrp = storage->GetOperandGroupStorage();
		opgrp->SetOperandInfo(index, seg);
		opgrp->SetOperandInfoType(index, OVT_SEG);
	}
	void AsmState<AsmStateFactory::State_Operand>::REG_Handler(AsmStateFactory::ParamType * param, int index, OperandType reg, bool isChange)
	{
		RegOrOperand tmpReg;
		tmpReg.Val = reg;
		assert(tmpReg.IsReg);
		auto storage = param->GetStorage();
		auto opgrp = storage->GetOperandGroupStorage();
		auto opSize = opgrp->GetOperandSizeAttribute();
		// 如果reg.len小于属性，忽略
		// 大于属性，按照属性来
		// 不知道有没有8位的，8位需要再处理

		if (isChange)
		{
			if (tmpReg.Reg.LenType > opSize)
			{
				assert(opSize != BitNotSet);
				tmpReg.Reg.LenType = opSize;
			}
		}

		opgrp->SetOperandInfo(index, tmpReg.Val);
		opgrp->SetOperandInfoType(index, OVT_REG);

	}
	// NOTICE: 顺序必须跟枚举值一致
	const AsmState<AsmStateFactory::State_Operand>::Handler  AsmState<AsmStateFactory::State_Operand>::Handlers[] =
	{
		NULL_Handler,
		L_a_Handler,
		L_b_Handler,
		L_c_Handler,
		L_d_Handler,
		L_dq_Handler,
		L_p_Handler,
		L_pd_Handler,
		L_pi_Handler,
		L_ps_Handler,
		L_q_Handler,
		L_qq_Handler,
		L_s_Handler,
		L_sd_Handler,
		L_ss_Handler,
		L_si_Handler,
		L_v_Handler,
		L_w_Handler,
		L_x_Handler,
		L_y_Handler,
		L_z_Handler,
		H_1_Handler,
		H_A_Handler,
		H_B_Handler,
		H_C_Handler,
		H_D_Handler,
		H_E_Handler,
		H_F_Handler,
		H_G_Handler,
		H_H_Handler,
		H_I_Handler,
		H_J_Handler,
		H_L_Handler,
		H_M_Handler,
		H_N_Handler,
		H_O_Handler,
		H_P_Handler,
		H_Q_Handler,
		H_R_Handler,
		H_S_Handler,
		H_U_Handler,
		H_V_Handler,
		H_W_Handler,
		H_X_Handler,
		H_Y_Handler,
		SPC_AL_R8L_Handler,
		SPC_CL_R9L_Handler,
		SPC_DL_R10L_Handler,
		SPC_BL_R11L_Handler,
		SPC_AH_R12L_Handler,
		SPC_CH_R13L_Handler,
		SPC_DH_R14L_Handler,
		SPC_BH_R15L_Handler,
		SPC_AL_rAX_Handler,
		SPC_rAX_r8_Handler,
		SPC_rCX_r9_Handler,
		SPC_rDX_r10_Handler,
		SPC_rBX_r11_Handler,
		SPC_rSP_r12_Handler,
		SPC_rBP_r13_Handler,
		SPC_rSI_r14_Handler,
		SPC_rDI_r15_Handler,
		SPC_RAX_EAX_R8_R8D_Handler,
		SPC_RCX_ECX_R9_R9D_Handler,
		SPC_RDX_EDX_R10_R10D_Handler,
		SPC_RBX_EBX_R11_R11D_Handler,
		SPC_RSP_ESP_R12_R12D_Handler,
		SPC_RBP_EBP_R13_R13D_Handler,
		SPC_RSI_ESI_R14_R14D_Handler,
		SPC_RDI_EDI_R15_R15D_Handler,
		SPC_Ib_Iz_Handler,
		SPC_Mw_Rv_Handler,
		SPC_Rd_Mb_Handler,
		SPC_Rd_Mw_Handler,
		SPC_Rv_Mw_Handler,
		SPC_Ry_Mb_Handler,
		SPC_Ry_Mw_Handler,
		SPC_Udq_Md_Handler,
		SPC_Ux_Md_Handler,
		SPC_Ux_Mq_Handler,
		SPC_Ux_Mw_Handler,
	};
}  // namespace Disassembler