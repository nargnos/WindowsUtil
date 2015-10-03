#pragma once
// 用到的表的结构定义
#include <Windows.h>
#include <WinBase.h>

namespace Asm
{
	enum SizeOptions
	{
		Size_None = 0,
		Size_B = 1,
		Size_D = Size_B << 1,
		Size_W = Size_D << 1,
		Size_Q = Size_W << 1
	};
	// hex表示的内容
	enum OpTypes
	{
		OT_None,
		OT_Command,
		OT_Prefix,
		OT_Group,
		OT_Table,
		OT_Array, // 多指令表
		OT_ESC // 协处理器指令
	};
	enum Superscripts
	{
		S_None,
		S_1A, // ModRM3-5为扩展操作码
		S_1B, // 使用0F0BH(UD2指令)或者0FB9H故意产生一个指令异常(#UD)
		S_1C, // 使用ModRM区分不同指令
		S_i64, // 在64位非法或未编码，40-4f在64为中做REX前缀，使用FE/FF/Grp4 5代替inc/dec
		S_o64, // 仅64位可用
		S_d64, // 在64位中操作数默认64位，不能编码32位数据
		S_f64, // 64位时操作数强制64位，操作数尺寸前缀无效
		S_v,
		S_v1,
		S_i64_o64 // 多上标,这个是在64位用作REX前缀的指令上带的上标
	};

	// 选择该指令的条件
	enum Conditions
	{
		C_None,
		C_66,
		C_F2,
		C_F3,
		C_66_And_F2,
		C_000,
		C_001,
		C_010,
		C_011,
		C_100,
		C_101,
		C_110,
		C_111
	};	
	// 下面的是操作数信息填入的东西
	enum OperandTypes
	{
		L_a = 1,
		L_b,
		L_c,
		L_d,
		L_dq,
		L_p,
		L_pd,
		L_pi,
		L_ps,
		L_q,
		L_qq,
		L_s,
		L_sd,
		L_ss,
		L_si,
		L_v,
		L_w,
		L_x,
		L_y,
		L_z,
		OperandTypes_end
	};
	enum AddressingMethods
	{

		H_A = OperandTypes_end,
		H_B,
		H_C,
		H_D,
		H_E,
		H_F,
		H_G,
		H_H,
		H_I,
		H_J,
		H_L,
		H_M,
		H_N,
		H_O,
		H_P,
		H_Q,
		H_R,
		H_S,
		H_U,
		H_V,
		H_W,
		H_X,
		H_Y,
		AddressingMethods_end

	};

	enum MethodAndTypes
	{
		HL_Ux = AddressingMethods_end,
		HL_Mb,
		HL_Md,
		HL_Mw,
		HL_Mq,
		HL_Rd,
		HL_Ry,
		HL_Udq,
		MethodAndTypes_end,
	};
	enum Segs
	{
		Seg_cs = MethodAndTypes_end,
		Seg_ds,
		Seg_es,
		Seg_fs,
		Seg_gs,
		Seg_ss,
		Segs_end
	};
	enum Rexes
	{
		Rex = Segs_end,
		Rex_B,
		Rex_X,
		Rex_XB,
		Rex_R,
		Rex_RB,
		Rex_RX,
		Rex_RXB,
		Rex_W,
		Rex_WB,
		Rex_WX,
		Rex_WXB,
		Rex_WR,
		Rex_WRB,
		Rex_WRX,
		Rex_WRXB,
		Rexes_end
	};
	enum Grp
	{
		Grp_1 = Rexes_end // 组用的一个标识(1)
	};
#pragma  pack(push)
#pragma pack(1)
	typedef struct _ModRM
	{
		BYTE Rm : 3;
		BYTE Reg : 3;
		BYTE Mod : 2;
	}ModRM, *PModRM;
	typedef struct _OpcodeCommand// 指令
	{

		USHORT Index : 10; // 数组下标
		USHORT OpCount : 3; // 操作数个数
		USHORT: 3;
	}OpcodeCommand, *POpcode_Command;
	typedef struct _OpcodePrefix// 前缀
	{
		USHORT Index : 10; // 前缀数组索引
		USHORT PrefixGroup : 3; // 前缀所属的前缀组
		USHORT: 3;
	}OpcodePrefix, *POpcodePrefix;
	typedef struct _OpcodeGroup// 组
	{
		USHORT Index : 5; // 组数组下标
		USHORT GroupNum : 5; // 组号，标识跳转到哪个组的表
		USHORT OpCount : 3; // 操作数个数
	USHORT: 3;
	}OpcodeGroup, *POpcodeGroup;
	typedef struct _OpcodeTable// 跳转到多字节表
	{
		USHORT Index : 10; // 表序号
		USHORT: 6;
	}OpcodeTable, *POpcodeTable;
	typedef struct _OpcodeArray// 多指令数组
	{
		USHORT Index : 10; // 数组索引
		USHORT Size : 3; // 项数
	USHORT: 3;
	}OpcodeArray, *POpcodeArray;
	typedef struct _Opcode
	{

		union
		{
			/*
			OT_Command,
			OT_Prefix,
			OT_Group,
			OT_Table,
			OT_Array
			*/
			USHORT Val;
			// TODO: 协处理器指令没结构
			OpcodeCommand Command;
			OpcodePrefix Prefix;
			OpcodeGroup Group;
			OpcodeTable Table;
			OpcodeArray Array;
			struct
			{
				USHORT:13;
				USHORT OpType : 3;
			};
			
			
			
		};


	}Opcode, *POpcode;

#define HEX_CMD(opCount,index) {(USHORT)(((OT_Command&0x7)<<13)|((opCount&0x7)<<10)|(index&0x3ff))}
#define HEX_PREFIX(prefixGroup,index) {(USHORT)(((OT_Prefix&0x7)<<13)|((prefixGroup&0x7)<<10)|(index&0x3ff))}
#define HEX_GROUP(group,opCount,index) {(USHORT)(((OT_Group&0x7)<<13)|((opCount&0x7)<<10)|((group&0x1f)<<7)|(index&0x1f))}
#define HEX_TABLE(tableNum) {(USHORT)((OT_Table<<13)|(tableNum&0x3ff))}
#define HEX_ARRAY(size,index) {(USHORT)((OT_Array<<13)|((size&0x7)<<10)|(index&0x3ff))}

#pragma region 存储结构
	typedef struct _RegOrOperand
	{
		union
		{
			union
			{
				struct
				{
					BYTE Operand : 7;
				BYTE: 1;
				};
				struct
				{
					BYTE Hex : 4;
					BYTE LenType : 3;
				BYTE: 1;
				}Reg;
				BYTE IsReg : 1;
			};
			BYTE Val;
		};
	}RegOrOperand, *PRegOrOperand;
	typedef struct _RegOrOperandGroup
	{
		RegOrOperand H;
		RegOrOperand L;
	}RegOrOperandGroup, *PRegOrOperandGroup;
#define _REG(hex,type) ((BYTE)((1<<7)|((type&0x70)<<4)|(hex&0x0f)))
#define _OP(info) ((BYTE)(info&0x7f))

	// 寄存器定义，对应值可以在字符串表里找到
#define _REG_AL _REG(0,Len_8)
#define _REG_AX _REG(0,Len_16)
#define _REG_EAX _REG(0,Len_32)
#define _REG_RAX _REG(0,Len_64)
#define _REG_MM0 _REG(0,Len_64_MM)
#define _REG_XMM0 _REG(0,Len_128_XMM)
#define _REG_CL _REG(1,Len_8)
#define _REG_CX _REG(1,Len_16)
#define _REG_ECX _REG(1,Len_32)
#define _REG_RCX _REG(1,Len_64)
#define _REG_MM1 _REG(1,Len_64_MM)
#define _REG_XMM1 _REG(1,Len_128_XMM)
#define _REG_DL _REG(2,Len_8)
#define _REG_DX _REG(2,Len_16)
#define _REG_EDX _REG(2,Len_32)
#define _REG_RDX _REG(2,Len_64)
#define _REG_MM2 _REG(2,Len_64_MM)
#define _REG_XMM2 _REG(2,Len_128_XMM)
#define _REG_BL _REG(3,Len_8)
#define _REG_BX _REG(3,Len_16)
#define _REG_EBX _REG(3,Len_32)
#define _REG_RBX _REG(3,Len_64)
#define _REG_MM3 _REG(3,Len_64_MM)
#define _REG_XMM3 _REG(3,Len_128_XMM)
#define _REG_AH _REG(4,Len_8)
#define _REG_SP _REG(4,Len_16)
#define _REG_ESP _REG(4,Len_32)
#define _REG_RSP _REG(4,Len_64)
#define _REG_MM4 _REG(4,Len_64_MM)
#define _REG_XMM4 _REG(4,Len_128_XMM)
#define _REG_CH _REG(5,Len_8)
#define _REG_BP _REG(5,Len_16)
#define _REG_EBP _REG(5,Len_32)
#define _REG_RBP _REG(5,Len_64)
#define _REG_MM5 _REG(5,Len_64_MM)
#define _REG_XMM5 _REG(5,Len_128_XMM)
#define _REG_DH _REG(6,Len_8)
#define _REG_SI _REG(6,Len_16)
#define _REG_ESI _REG(6,Len_32)
#define _REG_RSI _REG(6,Len_64)
#define _REG_MM6 _REG(6,Len_64_MM)
#define _REG_XMM6 _REG(6,Len_128_XMM)
#define _REG_BH _REG(7,Len_8)
#define _REG_DI _REG(7,Len_16)
#define _REG_EDI _REG(7,Len_32)
#define _REG_RDI _REG(7,Len_64)
#define _REG_MM7 _REG(7,Len_64_MM)
#define _REG_XMM7 _REG(7,Len_128_XMM)

#define _REG_R8L _REG(8,Len_8) // 8
#define _REG_R8W _REG(8,Len_16) // 16
#define _REG_R8D _REG(8,Len_32) // 32
#define _REG_R8 _REG(8,Len_64) // 64
#define _REG_XMM8 _REG(8,Len_128_XMM)
#define _REG_R9L _REG(9,Len_8) // 8
#define _REG_R9W _REG(9,Len_16) // 16
#define _REG_R9D _REG(9,Len_32) // 32
#define _REG_R9 _REG(9,Len_64)
#define _REG_XMM9 _REG(9,Len_128_XMM)
#define _REG_R10L _REG(10,Len_8) // 8
#define _REG_R10W _REG(10,Len_16) // 16
#define _REG_R10D _REG(10,Len_32) // 32
#define _REG_R10 _REG(10,Len_64)
#define _REG_XMM10 _REG(10,Len_128_XMM)
#define _REG_R11L _REG(11,Len_8) // 8
#define _REG_R11W _REG(11,Len_16) // 16
#define _REG_R11D _REG(11,Len_32) // 32
#define _REG_R11 _REG(11,Len_64)
#define _REG_XMM11 _REG(11,Len_128_XMM)
#define _REG_R12L _REG(12,Len_8) // 8
#define _REG_R12W _REG(12,Len_16) // 16
#define _REG_R12D _REG(12,Len_32) // 32
#define _REG_R12 _REG(12,Len_64)
#define _REG_XMM12 _REG(12,Len_128_XMM)
#define _REG_R13L _REG(13,Len_8) // 8
#define _REG_R13W _REG(13,Len_16) // 16
#define _REG_R13D _REG(13,Len_32) // 32
#define _REG_R13 _REG(13,Len_64)
#define _REG_XMM13 _REG(13,Len_128_XMM)
#define _REG_R14L _REG(14,Len_8) // 8
#define _REG_R14W _REG(14,Len_16) // 16
#define _REG_R14D _REG(14,Len_32) // 32
#define _REG_R14 _REG(14,Len_64)
#define _REG_XMM14 _REG(14,Len_128_XMM)
#define _REG_R15L _REG(15,Len_8) // 8
#define _REG_R15W _REG(15,Len_16) // 16
#define _REG_R15D _REG(15,Len_32) // 32
#define _REG_R15 _REG(15,Len_64)
#define _REG_XMM15 _REG(15,Len_128_XMM)

#pragma endregion

	typedef struct _ZeroOperand
	{
		USHORT NameID : 10;
		USHORT NameRange : 3; // 表示范围内的名字都属于该指令
		BYTE Superscript : 4;
		BYTE SizeOption : 4; // bwdq，在名字后面附加

	}ZeroOperand, *PZeroOperand;
	typedef struct _OneOperand
	{
		USHORT NameID : 10;

		USHORT Superscript : 4; // 上标

		BYTE OperandIndex;
		//RegOrOperandGroup Operand;

		CHAR NameRange : 3;
		CHAR SizeOption : 4;
		//RegOrOperandGroup Operand_Ext;
		BYTE OperandIndex_Ext;

	}OneOperand, *POneOperand;
	typedef struct _TwoOperands
	{
		USHORT NameID : 10;
		BYTE OperandIndex1;
		BYTE OperandIndex2;
		BYTE Condition : 4; // 条件
		BYTE Superscript : 4;
		BYTE SizeOption : 4;
		BYTE NameRange : 3;

	}TwoOperands, *PTwoOperands;
	typedef struct _ThreeOperands
	{

		USHORT NameID : 10;
		USHORT Condition : 4;

		BYTE OperandIndex1;
		BYTE OperandIndex2;
		BYTE OperandIndex3;
		BYTE Superscript : 4;
		BYTE SizeOption : 4;

	}ThreeOperands, *PThreeOperands;
	typedef struct _FourOperands
	{
		USHORT NameID : 10;
		USHORT Condition : 4;
		BYTE OperandIndex1;
		BYTE OperandIndex2;
		BYTE OperandIndex3;
		BYTE OperandIndex4;
		BYTE Superscript : 4;
		BYTE SizeOption : 4; // bwdq
	}FourOperands, *PFourOperands;

#pragma  pack(pop)
}