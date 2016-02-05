#pragma once
#include <Windows.h>
#pragma region 操作数存储结构
typedef struct
{
	union
	{
		union
		{
			struct
			{
				unsigned char Operand : 7;
				unsigned char : 1;
			};
			struct
			{
				unsigned char Hex : 4;
				unsigned char LenType : 3;
				unsigned char : 1;
			}Reg;
			unsigned char IsReg : 1;
		};
		unsigned char Val;
	};
}RegOrOperand, *PRegOrOperand;
typedef struct
{
	RegOrOperand H;
	RegOrOperand L;
}RegOrOperandGroup, *PRegOrOperandGroup;
#pragma endregion

enum RegisterLength
{
	Len_8,
	Len_16,
	Len_32,
	Len_64,
	Len_64_MM,
	Len_128_XMM
};

// 跟段标识共用一个表节约一下空间
extern const char* Registers[16][6];

#define _REG(hex, type) (unsigned char)((1<<7)|(((type)&0x7)<<4)|((hex)&0x0f))

// 寄存器定义，对应值可以在字符串表里找到

enum OperandType :unsigned char
{
	// NULL = 0,
	CHANGE_REG = 1,  // 表示寄存器参数会随着长度限定改变
	// OperandTypes
	L_a,
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
	// AddressingMethods
	H_1,  // 不知道是什么
	H_A,
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
	// 特殊

	SPC_AL_R8L,
	SPC_CL_R9L,
	SPC_DL_R10L,
	SPC_BL_R11L,
	SPC_AH_R12L,
	SPC_CH_R13L,
	SPC_DH_R14L,
	SPC_BH_R15L,
	SPC_AL_rAX,
	SPC_rAX_r8,
	SPC_rCX_r9,
	SPC_rDX_r10,
	SPC_rBX_r11,
	SPC_rSP_r12,
	SPC_rBP_r13,
	SPC_rSI_r14,
	SPC_rDI_r15,


	SPC_RAX_EAX_R8_R8D,
	SPC_RCX_ECX_R9_R9D,
	SPC_RDX_EDX_R10_R10D,
	SPC_RBX_EBX_R11_R11D,
	SPC_RSP_ESP_R12_R12D,
	SPC_RBP_EBP_R13_R13D,
	SPC_RSI_ESI_R14_R14D,
	SPC_RDI_EDI_R15_R15D,

	SPC_Ib_Iz,
	SPC_Mw_Rv,
	SPC_Rd_Mb,
	SPC_Rd_Mw,
	SPC_Rv_Mw,
	SPC_Ry_Mb,
	SPC_Ry_Mw,
	SPC_Udq_Md,
	SPC_Ux_Md,
	SPC_Ux_Mq,
	SPC_Ux_Mw,
	// Segs
	// 使用长度赋值不代表是这个长度，共用名字表好查而已
	SEG_CS = _REG(10, Len_64_MM),
	SEG_DS = _REG(11, Len_64_MM),
	SEG_ES = _REG(12, Len_64_MM),
	SEG_FS = _REG(13, Len_64_MM),
	SEG_GS = _REG(14, Len_64_MM),
	SEG_SS = _REG(15, Len_64_MM),
	// reg
	REG_AL = _REG(0, Len_8),
	REG_AX = _REG(0, Len_16),
	REG_EAX = _REG(0, Len_32),
	REG_RAX = _REG(0, Len_64),
	REG_MM0 = _REG(0, Len_64_MM),
	REG_XMM0 = _REG(0, Len_128_XMM),
	REG_CL = _REG(1, Len_8),
	REG_CX = _REG(1, Len_16),
	REG_ECX = _REG(1, Len_32),
	REG_RCX = _REG(1, Len_64),
	REG_MM1 = _REG(1, Len_64_MM),
	REG_XMM1 = _REG(1, Len_128_XMM),
	REG_DL = _REG(2, Len_8),
	REG_DX = _REG(2, Len_16),
	REG_EDX = _REG(2, Len_32),
	REG_RDX = _REG(2, Len_64),
	REG_MM2 = _REG(2, Len_64_MM),
	REG_XMM2 = _REG(2, Len_128_XMM),
	REG_BL = _REG(3, Len_8),
	REG_BX = _REG(3, Len_16),
	REG_EBX = _REG(3, Len_32),
	REG_RBX = _REG(3, Len_64),
	REG_MM3 = _REG(3, Len_64_MM),
	REG_XMM3 = _REG(3, Len_128_XMM),
	REG_AH = _REG(4, Len_8),
	REG_SP = _REG(4, Len_16),
	REG_ESP = _REG(4, Len_32),
	REG_RSP = _REG(4, Len_64),
	REG_MM4 = _REG(4, Len_64_MM),
	REG_XMM4 = _REG(4, Len_128_XMM),
	REG_CH = _REG(5, Len_8),
	REG_BP = _REG(5, Len_16),
	REG_EBP = _REG(5, Len_32),
	REG_RBP = _REG(5, Len_64),
	REG_MM5 = _REG(5, Len_64_MM),
	REG_XMM5 = _REG(5, Len_128_XMM),
	REG_DH = _REG(6, Len_8),
	REG_SI = _REG(6, Len_16),
	REG_ESI = _REG(6, Len_32),
	REG_RSI = _REG(6, Len_64),
	REG_MM6 = _REG(6, Len_64_MM),
	REG_XMM6 = _REG(6, Len_128_XMM),
	REG_BH = _REG(7, Len_8),
	REG_DI = _REG(7, Len_16),
	REG_EDI = _REG(7, Len_32),
	REG_RDI = _REG(7, Len_64),
	REG_MM7 = _REG(7, Len_64_MM),
	REG_XMM7 = _REG(7, Len_128_XMM),

	REG_R8L = _REG(8, Len_8),
	REG_R8W = _REG(8, Len_16),
	REG_R8D = _REG(8, Len_32),
	REG_R8 = _REG(8, Len_64),
	REG_XMM8 = _REG(8, Len_128_XMM),
	REG_R9L = _REG(9, Len_8),
	REG_R9W = _REG(9, Len_16),
	REG_R9D = _REG(9, Len_32),
	REG_R9 = _REG(9, Len_64),
	REG_XMM9 = _REG(9, Len_128_XMM),
	REG_R10L = _REG(10, Len_8),
	REG_R10W = _REG(10, Len_16),
	REG_R10D = _REG(10, Len_32),
	REG_R10 = _REG(10, Len_64),
	REG_XMM10 = _REG(10, Len_128_XMM),
	REG_R11L = _REG(11, Len_8),
	REG_R11W = _REG(11, Len_16),
	REG_R11D = _REG(11, Len_32),
	REG_R11 = _REG(11, Len_64),
	REG_XMM11 = _REG(11, Len_128_XMM),
	REG_R12L = _REG(12, Len_8),
	REG_R12W = _REG(12, Len_16),
	REG_R12D = _REG(12, Len_32),
	REG_R12 = _REG(12, Len_64),
	REG_XMM12 = _REG(12, Len_128_XMM),
	REG_R13L = _REG(13, Len_8),
	REG_R13W = _REG(13, Len_16),
	REG_R13D = _REG(13, Len_32),
	REG_R13 = _REG(13, Len_64),
	REG_XMM13 = _REG(13, Len_128_XMM),
	REG_R14L = _REG(14, Len_8),
	REG_R14W = _REG(14, Len_16),
	REG_R14D = _REG(14, Len_32),
	REG_R14 = _REG(14, Len_64),
	REG_XMM14 = _REG(14, Len_128_XMM),
	REG_R15L = _REG(15, Len_8),
	REG_R15W = _REG(15, Len_16),
	REG_R15D = _REG(15, Len_32),
	REG_R15 = _REG(15, Len_64),
	REG_XMM15 = _REG(15, Len_128_XMM),
};

enum OpcodeType :unsigned char
{
	OT_None,
	OT_Inst,  //  普通指令
	OT_Inst_Change,  //  根据长度修改指令名的指令
	OT_Prefix,

	OT_Grp,
	OT_Table_0F,
	OT_Table_0F38,
	OT_Table_0F3A,
	OT_Esc
};

enum PrefixGroup :unsigned char
{
	PfxGrp_1 = 1,
	PfxGrp_2,
	PfxGrp_3,
	PfxGrp_4,
	PfxGrp_Rex,
	PfxGrp_Vex
};
enum Prefix :unsigned char
{
	Rex = 0x40,
	Rex_B = 0x41,
	Rex_X = 0x42,
	Rex_XB = 0x43,
	Rex_R = 0x44,
	Rex_RB = 0x45,
	Rex_RX = 0x46,
	Rex_RXB = 0x47,
	Rex_W = 0x48,
	Rex_WB = 0x49,
	Rex_WX = 0x4a,
	Rex_WXB = 0x4b,
	Rex_WR = 0x4c,
	Rex_WRB = 0x4d,
	Rex_WRX = 0x4e,
	Rex_WRXB = 0x4f,
	Vex_2Byte = 0xC4,
	Vex_1Byte = 0xC5,
	G4_address_size = 0x67,
	G1_lock = 0xf0,
	G3_operand_size = 0x66,
	G1_repne_xacquire = 0xf2,
	G1_reprepe_xrelease = 0xf3,
	G2_seg_cs = 0x2e,
	G2_seg_ds = 0x3e,
	G2_seg_es = 0x26,
	G2_seg_fs = 0x64,
	G2_seg_gs = 0x65,
	G2_seg_ss = 0x36,
};
enum OpcodeGroup :unsigned char
{
	Grp_1 = 1,  // _80x83
	Grp_1A,  // _8F
	Grp_2,  // _C0C1_D0D1_D2D3,
	Grp_3,  // _F6F7,
	Grp_4,  // _FE,
	Grp_5,  // _FF,
	Grp_6,  // _0F00,
	Grp_7,  // _0F01,
	Grp_8,  // _0FBA,
	Grp_9,  // _0FC7,
	Grp_10,  // _0FB9,
	Grp_11_C6,
	Grp_11_C7,
	Grp_12,  // _0F71,
	Grp_13,  // _0F72,
	Grp_14,  // _0F73,
	Grp_15,  // _0FAE,
	Grp_16,  // _0F18,
	Grp_17,  // _VEX_0F38_F3
};


// 指令存在条件
enum PrefixCondition :unsigned char
{
	// C_None,
	C_66 = 1,
	C_F2 = 1 << 1,
	C_F3 = 1 << 2,
	/*C_x32,
	C_x64*/
};

enum Mod210Condition :unsigned char
{
	C_Mod_210_000 = 1,
	C_Mod_210_001,
	C_Mod_210_010,
	C_Mod_210_011,
	C_Mod_210_100,
	C_Mod_210_101,
	C_Mod_210_110,
	C_Mod_210_111,
};
enum Mod76Condition :unsigned char
{
	C_Mod_76_mem = 1,
	C_Mod_76_11B,
	C_Mod_76_mem_11B
};

enum Superscript :unsigned char
{
	// S_None,
	// S_1A ,  // ModRM3-5为扩展操作码,组特有上标
	S_1B = 1,  // 使用0F0BH(UD2指令)或者0FB9H故意产生一个指令异常(#UD)
	S_1C,  // 使用ModRM区分不同指令

	// 条件
	S_i64,  // 在64位非法或未编码，40-4f在64为中做REX前缀，使用FE/FF/Grp4 5代替inc/dec
	S_o64,  // 仅64位可用

	S_d64,  // 在64位中操作数默认64位，不能编码32位数据
	S_f64,  // 64位时操作数强制64位，操作数尺寸前缀无效

	S_v,  // vex
	S_v1,
	// S_1A_i64,
	// S_1A_1C
};

// 名字后缀
enum NameExt :unsigned char
{
	// Ext_None = 0,
	Ext_B = 1,
	Ext_W = Ext_B << 1,
	Ext_D = Ext_W << 1,
	Ext_Q = Ext_D << 1
};

#pragma pack(push, 1)
// 1b\2b 表中元素结构,Count为0表示指令不存在
struct OpcodeData
{
	unsigned short Hex_InstIndex : 12;
	unsigned short Count : 4;
};
// 3b 表中元素结构
struct ZipOpcodeData
{
	unsigned short Hex_InstIndex : 12;
	unsigned short Count : 4;
	unsigned char Index;  // OpcodeData下标
};

// hex和inst的关系表元素
struct Hex_Inst
{
	unsigned short Type : 6;
	unsigned short InstIndex : 10;

};

// 注意这里InstData和InstChangeData的参数顺序和类型大小必须相同，
// 在不需要使用指令名的场合可以把它们当作同一类型
struct InstData
{
	unsigned char Pfxcdt : 4;  // 前缀条件PrefixCondition
	unsigned char Ss : 4;  // Superscript
	unsigned char ParamID;
	unsigned short ParamCount : 3;
	unsigned short NameCount : 3;
	unsigned short NameID : 10;
	// unsigned char Ext:4; // Inst_Change 类型特有NameExt
};
struct InstChangeData
{
	unsigned char Pfxcdt : 4;  // 前缀条件PrefixCondition
	unsigned char Ss : 4;  // Superscript
	unsigned char ParamID;
	unsigned short ParamCount : 3;
	unsigned short NameCount : 3;
	unsigned short NameID : 10;
	unsigned char Ext : 4;   // Inst_Change 类型特有NameExt
};
struct PrefixInstData
{
	unsigned short Ss : 4;  // Superscript
	unsigned short PfxGrp : 3;
	unsigned short NameID : 9;  // prefix 名字靠前所以9位足够
};

struct GrpInstData
{
	unsigned char Ss : 4;  // Superscript
	unsigned char : 4;
	unsigned char ParamID;
	unsigned char ParamCount : 3;
	unsigned char GrpID : 5;
};
typedef struct
{
	BYTE Rm : 3;
	BYTE Reg : 3;
	BYTE Mod : 2;
}OpcodeModRM, *POpcodeModRM;
#pragma pack(pop)
