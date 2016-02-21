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
				Handle_SEG(param, index, (OperandType)pair.H.Val);
			}
			else
			{
				// 单reg的组合的L部分要么为NULL，要么为CHANGE_REG，所以直接用作指示是否可以根据大小可变的标识
				Handle_REG(param, index, (OperandType)pair.H.Val, pair.L.Val);
			}
		}
		else
		{
			assert(pair.H.Val >= NULL && pair.H.Val <= SPC_Ux_Mw);
			assert(pair.L.Val >= NULL && pair.L.Val <= SPC_Ux_Mw);
			// 先确定操作数类型再使用寻址方式
			Self::HandleFunctions[pair.L.Operand](param, index);
			Self::HandleFunctions[pair.H.Operand](param, index);
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
	void AsmState<AsmStateFactory::State_Operand>::Handle_NULL(AsmStateFactory::ParamType * param, int index)
	{
		auto storage = param->GetStorage();
		storage->GetOperandGroupStorage()->SetOperandInfoType(index, OVT_NotSet);
	}
	unsigned char AsmState<AsmStateFactory::State_Operand>::l_a_SizeConvert[] =
	{ BIT_SIZE(WORD) * 2, BIT_SIZE(DWORD) * 2, BIT_SIZE(DWORD) * 2 };

	void AsmState<AsmStateFactory::State_Operand>::Handle_L_a(AsmStateFactory::ParamType * param, int index)
	{
		// FIX: 并未找到操作数大小属性对应选择大小的描述
		assert(MaxConvertTableSize == sizeof(l_a_SizeConvert));
		SetOperandInfo(param, index, l_a_SizeConvert);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_b(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, BIT_SIZE(unsigned char));
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_c(AsmStateFactory::ParamType * param, int index)
	{
		// 目前表中没有操作数使用
		assert(false);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_d(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, BIT_SIZE(DWORD));
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_dq(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, BIT_SIZE(DWORD64) * 2);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_p(AsmStateFactory::ParamType * param, int index)
	{
		// TODO: 32位，48位，或80位的指针，取决于操作数大小属性。
		// SetOperandInfo(param, index,?,OVT_Pointer);

	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_pd(AsmStateFactory::ParamType * param, int index)
	{
		// TODO: 128位或256位紧缩双精度浮点数。
		// SetOperandInfo(param, index,?,OVT_Double);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_pi(AsmStateFactory::ParamType * param, int index)
	{
		// TODO: QWORD MMX寄存器（如mm0）
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_ps(AsmStateFactory::ParamType * param, int index)
	{
		// TODO: 128位或256位紧缩单精度浮点数。
		// SetOperandInfo(param, index,?,OVT_Float);

	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_q(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, BIT_SIZE(DWORD64));
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_qq(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, BIT_SIZE(DWORD64) * 4);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_s(AsmStateFactory::ParamType * param, int index)
	{
		// TODO: 6字节或10字节的伪描述符
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_sd(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, 128, OVT_DoubleScalar);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_ss(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, 128, OVT_FloatScalar);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_si(AsmStateFactory::ParamType * param, int index)
	{
		// 没有使用
		assert(false);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_v(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, defaultSizeConvert);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_w(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, BIT_SIZE(WORD));
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_x(AsmStateFactory::ParamType * param, int index)
	{
		// TODO: 基于dq或qq的操作数大小属性
	}

	unsigned char AsmState<AsmStateFactory::State_Operand>::l_y_SizeConvert[] =
	{ BIT_SIZE(DWORD), BIT_SIZE(DWORD), BIT_SIZE(DWORD64) };

	void AsmState<AsmStateFactory::State_Operand>::Handle_L_y(AsmStateFactory::ParamType * param, int index)
	{
		// FIX: BIT16时的大小相关描述未找到，
		SetOperandInfo(param, index, l_y_SizeConvert);
	}

	unsigned char AsmState<AsmStateFactory::State_Operand>::l_z_SizeConvert[] =
	{ BIT_SIZE(WORD), BIT_SIZE(DWORD), BIT_SIZE(DWORD) };
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_z(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, l_z_SizeConvert);
	}

	// TODO: 以下函数要做的是记录当前指针位置，并偏移解析后的长度。RM和Sib需要记录其地址
	// 最终得到的是一个记录 操作数类型、长度、值（Reg，数字的只记地址和长度）、内存位置（用到立即数的指令）、RM/Sib开始位置 的表
	// 得到这个表就可以组织字符串输出了（RM域的处理打算用传函数指针方式、或者传ID后面再找函数）
	// 最后需要优化 只需要解析指令长度不需要输出的情况
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_1(AsmStateFactory::ParamType * param, int index)
	{
		// FIX: 文档并未描述
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_A(AsmStateFactory::ParamType * param, int index)
	{
		// [0xXXXX....]
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_B(AsmStateFactory::ParamType * param, int index)
	{
		// vex pfx vvvv
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_C(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M reg ctr
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_D(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M reg dbg
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_E(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M [reg+xxxx]
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_F(AsmStateFactory::ParamType * param, int index)
	{
		//eflags/rflags
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_G(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M reg
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_H(AsmStateFactory::ParamType * param, int index)
	{
		// vex vvvv xmm|ymm
		// 传统SSE忽略掉这个操作数
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_I(AsmStateFactory::ParamType * param, int index)
	{
		// imm
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_J(AsmStateFactory::ParamType * param, int index)
	{
		// offset imm
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_L(AsmStateFactory::ParamType * param, int index)
	{
		// 8位立即数的高4位用作表示128位的XMM寄存器或256位的YMM寄存器，取决于操作数类型（在32位模式下忽略MSB）
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_M(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M mem
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_N(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M rm 4mmx
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_O(AsmStateFactory::ParamType * param, int index)
	{
		// 该指令没有ModR/M字节。操作数的偏移被编码为字或双字(取决于地址大小属性)。
		// 没有基址寄存器、变址寄存器或比例因数可以应用。
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_P(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M reg 4mmx
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_Q(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M mmx mem
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_R(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_S(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M seg
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_U(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M rm xmm|ymm
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_V(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M reg xmm|ymm
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_W(AsmStateFactory::ParamType * param, int index)
	{
		// ModR/M xmm|ymm
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_X(AsmStateFactory::ParamType * param, int index)
	{
		// DS:rSI
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_Y(AsmStateFactory::ParamType * param, int index)
	{
		// ES:rDI
	}

	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_XL_RXL(AsmStateFactory::ParamType * param, int index, const OperandType* selectTable)
	{
		// 数组长度必须 == 2
		auto storage = param->GetStorage();
		auto pfx = storage->GetPrefixStorage();
		if (pfx->HasRex() && pfx->GetRex()->B)
		{
			// rxl
			Handle_REG(param, index, selectTable[0], false);
		}
		else
		{
			// xl
			Handle_REG(param, index, selectTable[1], false);
		}
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_AL_R8L(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_R8L ,REG_AL };
		Handle_SPC_XL_RXL(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_CL_R9L(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_R9L ,REG_CL };
		Handle_SPC_XL_RXL(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_DL_R10L(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_R10L ,REG_DL };
		Handle_SPC_XL_RXL(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_BL_R11L(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_R11L ,REG_BL };
		Handle_SPC_XL_RXL(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_AH_R12L(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_R12L ,REG_AH };
		Handle_SPC_XL_RXL(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_CH_R13L(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_R13L ,REG_CH };
		Handle_SPC_XL_RXL(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_DH_R14L(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_R14L ,REG_DH };
		Handle_SPC_XL_RXL(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_BH_R15L(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_R15L ,REG_BH };
		Handle_SPC_XL_RXL(param, index, table);
	}


	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_AL_rAX(AsmStateFactory::ParamType * param, int index)
	{
		// FIX: 操作数大小属性表里没有8位的，需要先找到描述
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_rXX_rX(AsmStateFactory::ParamType * param, int index, const OperandType* selectTable)
	{
		// 数组长度必须 == 4
		auto storage = param->GetStorage();
		auto pfx = storage->GetPrefixStorage();
		auto operand = storage->GetOperandGroupStorage();
		switch (operand->GetOperandSizeAttribute())
		{
		case Bit16:
			// xx
			Handle_REG(param, index, selectTable[0], false);
			break;
		case Bit32:
			// exx
			Handle_REG(param, index, selectTable[1], false);
			break;
		case Bit64:
			if (pfx->HasRex() && pfx->GetRex()->B)
			{
				// rx
				Handle_REG(param, index, selectTable[2], false);
			}
			else
			{
				// rxx
				Handle_REG(param, index, selectTable[3], false);
			}
			break;
		default:
			assert(false);
			break;
		}
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_rAX_r8(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_AX ,REG_EAX,REG_R8,REG_RAX };
		Handle_SPC_rXX_rX(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_rCX_r9(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_CX ,REG_ECX,REG_R9,REG_RCX };
		Handle_SPC_rXX_rX(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_rDX_r10(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_DX ,REG_EDX,REG_R10,REG_RDX };
		Handle_SPC_rXX_rX(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_rBX_r11(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_BX ,REG_EBX,REG_R11,REG_RBX };
		Handle_SPC_rXX_rX(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_rSP_r12(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_SP ,REG_ESP,REG_R12,REG_RSP };
		Handle_SPC_rXX_rX(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_rBP_r13(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_BP ,REG_EBP,REG_R13,REG_RBP };
		Handle_SPC_rXX_rX(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_rSI_r14(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_SI ,REG_ESI,REG_R14,REG_RSI };
		Handle_SPC_rXX_rX(param, index, table);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_rDI_r15(AsmStateFactory::ParamType * param, int index)
	{
		OperandType table[] = { REG_DI ,REG_EDI,REG_R15,REG_RDI };
		Handle_SPC_rXX_rX(param, index, table);
	}


	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_RAX_EAX_R8_R8D(AsmStateFactory::ParamType * param, int index)
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
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_RCX_ECX_R9_R9D(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_RDX_EDX_R10_R10D(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_RBX_EBX_R11_R11D(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_RSP_ESP_R12_R12D(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_RBP_EBP_R13_R13D(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_RSI_ESI_R14_R14D(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_RDI_EDI_R15_R15D(AsmStateFactory::ParamType * param, int index)
	{}

	// 下面这些组合好像都是SSE用的
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Ib_Iz(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Mw_Rv(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Rd_Mb(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Rd_Mw(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Rv_Mw(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Ry_Mb(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Ry_Mw(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Udq_Md(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Ux_Md(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Ux_Mq(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Ux_Mw(AsmStateFactory::ParamType * param, int index)
	{}

	void AsmState<AsmStateFactory::State_Operand>::Handle_SEG(AsmStateFactory::ParamType * param, int index, OperandType seg)
	{
		auto storage = param->GetStorage();
		auto opgrp = storage->GetOperandGroupStorage();
		opgrp->SetOperandInfo(index, seg);
		opgrp->SetOperandInfoType(index, OVT_SEG);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_REG(AsmStateFactory::ParamType * param, int index, OperandType reg, bool isChange)
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
	const AsmState<AsmStateFactory::State_Operand>::HandleFunction  AsmState<AsmStateFactory::State_Operand>::HandleFunctions[] =
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
}  // namespace Disassembler