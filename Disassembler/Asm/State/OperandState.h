#pragma once

#include "AsmState.h"
#include "AsmStateFactory.h"
#include "..\Opcode\OpcodeDef.h"
#include "..\Opcode\AsmOpcodeDataWrapper.h"
#include "..\AsmStorage.h"
namespace Disassembler
{
	template<>
	class AsmState<AsmStateFactory::State_Operand> :public IState
	{
	public:
		typedef AsmState<AsmStateFactory::State_Operand> Self;
		static int Next(AsmStateFactory::ParamType* param);
	private:
		static void ReadOperand(AsmStateFactory::ParamType* param, int index, const RegOrOperandGroup& pair);
		static const int MaxConvertTableSize = 3;
#define BIT_SIZE(type) (sizeof(type)*8)

		// 在下面的一些用到操作数大小属性的函数中，使用查表转换最后设置的大小
		// Bit16为下标0，所以得到值时需要-1
		// 转换表长度必须为3，否则程序错误
		static void SetOperandInfo(AsmStateFactory::ParamType* param, int index, const unsigned char* convertTable, OperandValueType type);
		// 直接设置大小，不需要转换
		static void SetOperandInfo(AsmStateFactory::ParamType* param, int index, unsigned char val, OperandValueType type);
		static unsigned char defaultSizeConvert[];
		// 下面的函数设置完大小后记得设置解析后的参数类型
		typedef void(*Handler)(AsmStateFactory::ParamType*, int);
		static void NULL_Handler(AsmStateFactory::ParamType* param, int index);
		static unsigned char l_a_SizeConvert[];
		static void L_a_Handler(AsmStateFactory::ParamType* param, int index);
		static void L_b_Handler(AsmStateFactory::ParamType* param, int index);
		static void L_c_Handler(AsmStateFactory::ParamType* param, int index);
		static void L_d_Handler(AsmStateFactory::ParamType* param, int index);
		static void L_dq_Handler(AsmStateFactory::ParamType* param, int index);
		static void L_p_Handler(AsmStateFactory::ParamType* param, int index);
		static void L_pd_Handler(AsmStateFactory::ParamType* param, int index);
		static void L_pi_Handler(AsmStateFactory::ParamType* param, int index);
		static void L_ps_Handler(AsmStateFactory::ParamType* param, int index);
		static void L_q_Handler(AsmStateFactory::ParamType* param, int index);
		static void L_qq_Handler(AsmStateFactory::ParamType* param, int index);
		static void L_s_Handler(AsmStateFactory::ParamType* param, int index);
		static void L_sd_Handler(AsmStateFactory::ParamType* param, int index);
		static void L_ss_Handler(AsmStateFactory::ParamType* param, int index);
		static void L_si_Handler(AsmStateFactory::ParamType* param, int index);
		static void L_v_Handler(AsmStateFactory::ParamType* param, int index);
		static void L_w_Handler(AsmStateFactory::ParamType* param, int index);
		static void L_x_Handler(AsmStateFactory::ParamType* param, int index);
		static unsigned char l_y_SizeConvert[];
		static void L_y_Handler(AsmStateFactory::ParamType* param, int index);
		static unsigned char l_z_SizeConvert[];
		static void L_z_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_1_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_A_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_B_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_C_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_D_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_E_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_F_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_G_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_H_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_I_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_J_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_L_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_M_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_N_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_O_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_P_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_Q_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_R_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_S_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_U_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_V_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_W_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_X_Handler(AsmStateFactory::ParamType* param, int index);
		static void H_Y_Handler(AsmStateFactory::ParamType* param, int index);

		static void SPC_XL_RXL_Handler(AsmStateFactory::ParamType * param, int index, const OperandType* selectTable);

		static void SPC_AL_R8L_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_CL_R9L_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_DL_R10L_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_BL_R11L_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_AH_R12L_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_CH_R13L_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_DH_R14L_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_BH_R15L_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_AL_rAX_Handler(AsmStateFactory::ParamType* param, int index);

		static void SPC_rXX_rX_Handler(AsmStateFactory::ParamType * param, int index, const OperandType* selectTable);

		static void SPC_rAX_r8_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_rCX_r9_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_rDX_r10_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_rBX_r11_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_rSP_r12_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_rBP_r13_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_rSI_r14_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_rDI_r15_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_RAX_EAX_R8_R8D_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_RCX_ECX_R9_R9D_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_RDX_EDX_R10_R10D_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_RBX_EBX_R11_R11D_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_RSP_ESP_R12_R12D_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_RBP_EBP_R13_R13D_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_RSI_ESI_R14_R14D_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_RDI_EDI_R15_R15D_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_Ib_Iz_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_Mw_Rv_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_Rd_Mb_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_Rd_Mw_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_Rv_Mw_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_Ry_Mb_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_Ry_Mw_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_Udq_Md_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_Ux_Md_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_Ux_Mq_Handler(AsmStateFactory::ParamType* param, int index);
		static void SPC_Ux_Mw_Handler(AsmStateFactory::ParamType* param, int index);

		// change标识合并到reg
		static void SEG_Handler(AsmStateFactory::ParamType* param, int index, OperandType seg);
		static void REG_Handler(AsmStateFactory::ParamType* param, int index, OperandType reg, bool isChange);
		static const Handler Handlers[];
	};



}  // namespace Disassembler

