#pragma once
#include <assert.h>
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
extern const char* Registers[16][6] =
{
	{ "AL",		"AX",		"EAX",		"RAX",		"MM0",		"XMM0" },
	{ "CL",		"CX",		"ECX",		"RCX",		"MM1",		"XMM1" },
	{ "DL",		"DX",		"EDX",		"RDX",		"MM2",		"XMM2" },
	{ "BL",		"BX",		"EBX",		"RBX",		"MM3",		"XMM3" },
	{ "AH",		"SP",		"ESP",		"RSP",		"MM4",		"XMM4" },
	{ "CH",		"BP",		"EBP",		"RBP",		"MM5",		"XMM5" },
	{ "DH",		"SI",		"ESI",		"RSI",		"MM6",		"XMM6" },
	{ "BH",		"DI",		"EDI",		"RDI",		"MM7",		"XMM7" },
	{ "R8L",	"R8W",		"R8D",		"R8",		0,			"XMM8" },
	{ "R9L",	"R9W",		"R9D",		"R9",		0,			"XMM9" },
	{ "R10L",	"R10W",		"R10D",		"R10",		"CS",		"XMM10" },
	{ "R11L",	"R11W",		"R11D",		"R11",		"DS",		"XMM11" },
	{ "R12L",	"R12W",		"R12D",		"R12",		"ES",		"XMM12" },
	{ "R13L",	"R13W",		"R13D",		"R13",		"FS",		"XMM13" },
	{ "R14L",	"R14W",		"R14D",		"R14",		"GS",		"XMM14" },
	{ "R15L",	"R15W",		"R15D",		"R15",		"SS",		"XMM15" }
};
const char* GetRegisterName(unsigned char hex, RegisterLength type)
{
	assert(hex < 16 && (unsigned char)type < 6);
	assert(hex < 8 ? true : (type != Len_64_MM));
	return Registers[hex][type];
};

#define _REG(hex,type) (unsigned char)((1<<7)|(((type)&0x7)<<4)|((hex)&0x0f))
#define _OP(info) (unsigned char)((info)&0x7f)

// 寄存器定义，对应值可以在字符串表里找到

enum OperandTypes:unsigned char
{
	// NULL = 0,
	CHANGE_REG = 1, // 表示寄存器参数会随着长度限定改变
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
	//AddressingMethods
	H_1,// 不知道是什么
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
	// Segs
	// 使用长度赋值不代表是这个长度，共用名字表好查而已
	SEG_CS= _REG(10, Len_64_MM),
	SEG_DS= _REG(11, Len_64_MM),
	SEG_ES= _REG(12, Len_64_MM),
	SEG_FS= _REG(13, Len_64_MM),
	SEG_GS= _REG(14, Len_64_MM),
	SEG_SS= _REG(15, Len_64_MM),
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

const char* GetSegName(OperandTypes seg)
{
	assert(seg >= SEG_CS&& seg <= SEG_SS);
	auto op = reinterpret_cast<RegOrOperand*>(&seg);
	return Registers[op->Reg.Hex][op->Reg.LenType];
}



enum PrefixGroups :unsigned char
{
	G1,
	G2,
	G3,
	G4,
	GRex
};
enum Prefixes :unsigned char
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
enum OpcodeGroups :unsigned char
{
	G1_80x83,
	G1A_8F,
	G2_C0C1_D0D1_D2D3,
	G3_F6F7,
	G4_FE,
	G5_FF,
	G6_0F00,
	G7_0F01,
	G8_0FBA,
	G9_0FC7,
	G10_0FB9,
	G11_C6,
	G11_C7,
	G12_0F71,
	G13_0F72,
	G14_0F73,
	G15_0FAE,
	G16_0F18,
	G17_VEX_0F38_F3
};


// 指令存在条件
enum Conditions :unsigned char
{
	C_None,
	C_Mod_210_000,
	C_Mod_210_001,
	C_Mod_210_010,
	C_Mod_210_011,
	C_Mod_210_100,
	C_Mod_210_101,
	C_Mod_210_110,
	C_Mod_210_111,
	C_Mod_76_mem,
	C_Mod_76_11B,
	C_Mod_76_mem_11B,
	C_66,
	C_F2,
	C_F3,
	C_66_F2,
	C_x32,
	C_x64
};
enum Superscripts :unsigned char
{
	S_None,
	S_1A, // ModRM3-5为扩展操作码
	S_1B, // 使用0F0BH(UD2指令)或者0FB9H故意产生一个指令异常(#UD)
	S_1C, // 使用ModRM区分不同指令

 // 条件
	S_i64, // 在64位非法或未编码，40-4f在64为中做REX前缀，使用FE/FF/Grp4 5代替inc/dec
	S_o64, // 仅64位可用

	S_d64, // 在64位中操作数默认64位，不能编码32位数据
	S_f64, // 64位时操作数强制64位，操作数尺寸前缀无效

	S_v, // vex
	S_v1,
};

// 指向条件判断的结构
typedef struct
{
	unsigned char Count; // 个数
	unsigned short Index; // 起始下标
}CountIndexPair,*PCountIndexPair;

// 指向参数数组结构,取消掉多名称
typedef struct
{
	unsigned char Count; // 参数个数
	unsigned char Index; // 对应参数个数表中的ID
}NameCountIndexPair, *PNameCountIndexPair;

// 条件表结构
typedef struct
{
	unsigned char Condition; // 条件
	unsigned short Index; // NameCountIndexPair的下标
}ConditionNode, *PConditionNode;

// 参数数组元素结构在顶上


// 1b\2b\3b 表中元素结构
typedef struct Opcode
{
	unsigned char OpcodeType;
	// 附加存储信息，
	// 前缀存前缀组，
	// 指令存操作数个数
	// Esc
	// 组
	// 下一个表
	// 其它不存
	unsigned char Ex;
	unsigned short Index;
};




// 操作数表已做好
// 参数长度和参数关系表取消，合并到关系表里
// 需要做的表

// 1B、2B、3B Opcode
// 条件表表头 CountIndexPair
// 条件 - 指令关系 关系表  ConditionNode
// 指令表头 NameCountIndexPair
// 参数表1234 RegOrOperandGroup
// 名字表 char*


//root->condition[condition,param len]->param