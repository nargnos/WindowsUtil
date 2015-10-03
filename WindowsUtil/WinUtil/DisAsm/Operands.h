#pragma once
// 存储指令的操作数信息
// 单个操作数信息有一个总表，指令根据操作数个数分成几个表，每个表对应操作数的位置设置为信息总表的下标
#include <Windows.h>
#include <WinBase.h>
#include "instructionNames.h"
#include "registers.h"
#include "operandStruct.h"
namespace Asm
{
enum OperandId
{
	OP_Null,

	OP_Seg_cs,
	OP_Seg_ds,
	OP_Seg_es,
	OP_Seg_fs,
	OP_Seg_gs,
	OP_Seg_ss,

	OP_EAX_Rex, // 后面用作64位的rex前缀
	OP_ECX_Rex_B,
	OP_EDX_Rex_X,
	OP_EBX_Rex_XB,
	OP_ESP_Rex_R,
	OP_EBP_Rex_RB,
	OP_ESI_Rex_RX,
	OP_EDI_Rex_RXB,

	OP_EAX_Rex_W,
	OP_ECX_Rex_WB,
	OP_EDX_Rex_WX,
	OP_EBX_Rex_WXB,
	OP_ESP_Rex_WR,
	OP_EBP_Rex_WRB,
	OP_ESI_Rex_WRX,
	OP_EDI_Rex_WRXB,

	OP_RAX_R8,
	OP_RCX_R9,
	OP_RDX_R10,
	OP_RBX_R11,
	OP_RSP_R12,
	OP_RBP_R13,
	OP_RSI_R14,
	OP_RDI_R15,

	OP_RAX_EAX,
	OP_RCX_ECX,
	OP_RDX_EDX,
	OP_RBX_EBX,
	OP_RSP_ESP,
	OP_RBP_EBP,
	OP_RSI_ESI,
	OP_RDI_EDI,

	OP_R8_R8D,
	OP_R9_R9D,
	OP_R10_R10D,
	OP_R11_R11D,
	OP_R12_R12D,
	OP_R13_R13D,
	OP_R14_R14D,
	OP_R15_R15D,

	OP_AL_R8L,
	OP_CL_R9L,
	OP_DL_R10L,
	OP_BL_R11L,
	OP_AH_R12L,
	OP_CH_R13L,
	OP_DH_R14L,
	OP_BH_R15L,


	OP_Jb,
	OP_Jz,
	OP_Eb,
	OP_Ib,
	OP_Iw,
	OP_Iz,

	OP_Ap,
	OP_Fv,
	OP_Ev,
	OP_Iv,
	OP_Pq,
	OP_Gb,
	OP_Gv,
	OP_Lb,

	OP_Ob,
	OP_Qd,
	OP_Qq,
	OP_Vx,
	OP_Gy,
	OP_Ew,
	OP_Ov,
	OP_Mq,
	OP_Yb,
	OP_Xb,
	OP_Xz,
	OP_Qpi,
	OP_Ppi,
	OP_Vps,
	OP_Wps,
	OP_Vpd,
	OP_Wpd,
	OP_Wx,
	OP_Vq,
	OP_Vqq,
	OP_Hqq,
	OP_Wqq,
	OP_Hx,
	OP_Hps,
	OP_Hpd,
	OP_Vss,
	OP_Vsd,
	OP_Wsd,
	OP_Wss,
	OP_Vdq,
	OP_Wdq,
	OP_Mdq,
	OP_Hdq,
	OP_Hss,
	OP_Hsd,
	OP_Hq,
	OP_Uq,
	OP_Ey,
	OP_Gd,
	OP_Mx,
	OP_Yv,
	OP_Rd,
	OP_Cd,
	OP_Dd,
	OP_Pd,
	OP_Wd,
	OP_Wq,
	OP_My,
	OP_Mp,
	OP_Mps,
	OP_Mpd,
	OP_Gw,
	OP_Mw,
	OP_Nq,
	OP_Ma,
	OP_Xv,
	OP_Gz,
	OP_Yz,
	OP_Sw,
	OP_Ups,
	OP_Upd,
	OP_Vy,
	OP_Ux,
	OP_Udq,
	OP_By,
	OP_Ed,
	OP_Lx,
	OP_M,

	OP_AL,
	OP_RAX,
	OP_EAX,
	OP_DX,
	OP_CL,
	OP_RDX,

	OP_Rd_Mb,
	OP_Rd_Mw,
	OP_Ry_Mw,
	OP_Ry_Mb,
	OP_Ux_Md,
	OP_Ux_Mq,
	OP_Ux_Mw,
	OP_Udq_Md,

	OP_1

};
// 操作数信息组合，为了减少存储量
extern const RegOrOperandGroup Operands[];


// 前缀所属组号由1开始
extern const ZeroOperand Opcode_Prefixs[];
extern const ZeroOperand Opcode_0[];
extern const OneOperand Opcode_0_Grp[];
// nameid superscript operand namerange size extoperand
extern const  OneOperand Opcode_1[];

// grp 都带有1A上标,所以上标省掉
extern const  OneOperand Opcode_1_Grp[];

extern const  TwoOperands Opcode_2[];

extern const  TwoOperands Opcode_2_Grp[];

extern const  ThreeOperands Opcode_3[];

extern const  FourOperands Opcode_4[];
}