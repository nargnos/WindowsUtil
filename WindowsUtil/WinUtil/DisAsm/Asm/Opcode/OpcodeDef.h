#pragma once
#include <Windows.h>
// 把文档中的一些介绍文字作为注释
// 这样可以减少查文档次数，所以这里会有很多英文的非必要注释，懒得翻译了
#pragma region 操作数存储结构
#pragma pack(push, 1)
typedef struct
{
	union
	{
		union
		{
			struct
			{
				unsigned char Operand : 7;
				unsigned char IsReg : 1;
			};
			struct
			{
				unsigned char Hex : 4;
				unsigned char LenType : 3;
				unsigned char : 1;
			}Reg;
		};
		unsigned char Val;
	};
}RegOrOperand, *PRegOrOperand;
typedef struct
{
	RegOrOperand H;
	RegOrOperand L;
}RegOrOperandGroup, *PRegOrOperandGroup;
struct RexPrefix
{
	unsigned char : 4;  // 0100
	unsigned char W : 1;  // 0 = Operand size determined by CS.D / 1 = 64 Bit Operand Size
	unsigned char R : 1;  // Extension of the ModR/M reg field
	unsigned char X : 1;  // Extension of the SIB index field
	unsigned char B : 1;  // Extension of the ModR/M r/m field, SIB base field, or Opcode reg field

};
// 文档位置 V3-C3-3.4.5  P.2049
// 其实不用这个结构，文档搬过来写成结构便于查看
// struct SegmentDescriptors
// {
// 	unsigned int Base31_24: 8;
// 	// G (granularity) flag
// 	unsigned int G : 1;
// 	
// 	// 在16位的一些机器这个Flag始终为0，现在只编32位和64位的，忽略这种情况
// 	// D/B (default operation size/default stack pointer size and/or upper bound) flag
// 	// This flag should always be set to 1 for 32 - bit code and data segments and to 0 for 16 - bit code and data segments.
// 	// If the flag is set,32 - bit addresses and 32 - bit or 8 - bit operands are assumed;
// 	// if it is clear, 16 - bit addresses and 16 - bit or 8 - bit operands are assumed.
// 	// The instruction prefix 66H can be used to select an operand size other than the default, and the
// 	// prefix 67H can be used select an address size other than the default.
// 	unsigned int D : 1;
// 	// L (64-bit code segment) flag
// 	// In IA - 32e mode, bit 21 of the second doubleword of the segment descriptor indicates whether a
// 	// code segment contains native 64 - bit code.A value of 1 indicates instructions in this code segment
// 	// are executed in 64 - bit mode.A value of 0 indicates the instructions in this code segment are
// 	// executed in compatibility mode.If L - bit is set, then D - bit must be cleared.When not in IA - 32e mode
// 	// or for non - code segments, bit 21 is reserved and should always be set to 0.
// 	unsigned int L : 1;
// 	// Available and reserved bits
// 	unsigned int AVL : 1;
// 	// Segment limit field
// 	unsigned int SegLimit : 4;
// 	// P (segment-present) flag
// 	unsigned int P : 1;
// 	// DPL (descriptor privilege level) field
// 	unsigned int DPL : 2;
// 	// S (descriptor type) flag
// 	unsigned int S : 1;
// 	// Type field
// 	unsigned int Type : 4;
// 	unsigned int Base23_16:8;
// };
#pragma pack(pop)
#pragma endregion

enum RegisterLength :unsigned char
{
	Len_8,
	Len_16,
	Len_32,
	Len_64,
	Len_64_MM,
	Len_128_XMM
};

#define _REG(hex, type) (unsigned char)((1<<7)|(((type)&0x7)<<4)|((hex)&0x0f))
// 表示解析后得到的参数类型，这些描述不具备大小熟悉，相关的大小或值由其它变量存储
enum OperandValueType :unsigned char
{
	OVT_RegOrOperandGroupID,  // 表示数据未解析，这时候存储的数据用作OperandType组合的ID
	OVT_NotSet,
	OVT_Integer,
	OVT_Float,
	OVT_FloatScalar,
	OVT_Double,
	OVT_DoubleScalar,
	OVT_Pointer,
	OVT_Offset,
	OVT_PseudoDescriptor,
	OVT_REG,
	OVT_SEG,
	OVT_MMX
};
// 寄存器定义，对应值可以在字符串表里找到
// 把文档翻译了一下做参考，可能不准
enum OperandType :unsigned char
{
	OT_NULL = 0,

	// OperandTypes 操作数类型

	// 两个WORD或两个DWORD内存操作数，取决于操作数大小属性（只用在BOUND指令中）
	L_a,  // 只有Ma组合

	// BYTE，不管操作数大小属性
	L_b,

	// BYTE或WORD，取决于操作数大小属性
	L_c,  // 没有使用

	// DWORD，无视大小属性
	L_d,  // 只组合了有RM的寻址方式

	// 2*QWORD，无视属性
	L_dq,

	// 32位，48位，或80位的指针，取决于操作数大小属性。
	L_p,

	// 128位或256位紧缩双精度浮点数。
	L_pd,

	// QWORD MMX寄存器（如mm0）
	L_pi,  // 只组合了有RM的寻址方式

	// 128位或256位紧缩单精度浮点数。
	L_ps,

	// QWORD，不管属性
	L_q,

	// 4*QWORD（256位），无视属性
	L_qq,

	// 6字节或10字节的伪描述符
	L_s,

	// 128位双精度浮点数的标量元素
	L_sd,

	// 128位单精度浮点数的标量元素
	L_ss,

	// DWORD整数寄存器（如eax）
	L_si,  // 没有使用，为什么？

	// WORD、DWORD、QWORD（64位），取决属性
	L_v,

	// WORD，无视属性
	L_w,

	// 基于dq或qq的操作数大小属性
	L_x,

	// DWORD或QWORD (in 64-bit mode)，取决于属性
	L_y,

	// 16位大小时为WORD，32位或64位大小时为DWORD
	L_z,

	// AddressingMethods 寻址方式
	H_1,  // 不知道是什么

	// 直接寻址：该指令没有ModR/M字节；操作数的地址被编码在指令中。
	// 没有基址寄存器、变址寄存器，也没有比例因数可以应用。
	H_A,  // 只组合了p

	// 用VEX前缀的VEX.vvvv字段表示一个通用寄存器
	H_B,  // 只组合了y

	// 用ModR/M字节的reg域表示控制寄存器
	H_C,  // 只组合了d

	// 用ModR/M字节的reg域表示调试寄存器
	H_D,  // 只组合了d

	// 一个ModR/M字节跟在Opcode之后并指定操作数。这个操作数可以是通用寄存器或内存地址。
	// 如果它是内存地址，该地址用段寄存器和以下任何值：基址寄存器、变址寄存器、比例因数和位移相加来计算
	H_E,

	// EFLAGS/RFLAGS 寄存器
	H_F,  // 只组合了v

	// 用ModR/M字节的reg域表示通用寄存器
	H_G,

	// 用VEX前缀的VEX.vvvv字段选择一个128位的XMM寄存器或256位的YMM寄存器，取决于操作数类型。
	// 对于旧版SSE编码这个操作并不存在
	H_H,

	// 立即数
	H_I,

	// 该指令包含一个相对指令指针寄存器的偏移
	H_J,

	// 8位立即数的高4位用作表示128位的XMM寄存器或256位的YMM寄存器，取决于操作数类型（在32位模式下忽略MSB）
	H_L,  // 只组合了x

	// ModR/M字节可能只引用内存(例如, BOUND, LES, LDS, LSS, LFS, LGS,CMPXCHG8B)
	H_M,

	// ModR/M字节的R/M域表示一个紧缩4字MMX寄存器
	H_N,  // 只组合了q

	// 该指令没有ModR/M字节。操作数的偏移被编码为字或双字(取决于地址大小属性)。
	// 没有基址寄存器、变址寄存器或比例因数可以应用。
	H_O,

	// ModR/M字节的reg域表示一个紧缩4字MMX寄存器
	H_P,

	// 一个ModR/M字节跟在Opcode之后并指定操作数。这个操作数可以是MMX寄存器或内存地址。
	// 如果是内存地址，该地址用段寄存器和以下任何值：基址寄存器、变址寄存器、比例因数和位移相加来计算
	H_Q,

	// ModR/M字节可能只引用通用寄存器
	H_R,

	// ModR/M字节的reg域表示一个段寄存器
	H_S,  // 只组合了w

	// ModR/M字节的R/M域表示128位的XMM寄存器或256位的YMM寄存器，取决于操作数类型
	H_U,

	// ModR/M字节的reg域表示128位的XMM寄存器或256位的YMM寄存器，取决于操作数类型
	H_V,

	// 一个ModR/M字节跟在Opcode之后并指定操作数。操作数可能为一个128位的XMM寄存器或256位的YMM寄存器（取决于操作数类型）或内存地址。
	// 如果是内存地址，该地址用段寄存器和以下任何值：基址寄存器、变址寄存器、比例因数和位移相加来计算
	H_W,

	// 内存寻址为DS:rSI寄存器对
	H_X,
	// 内存寻址为ES:rDI寄存器对
	H_Y,

	// 特殊，寄存器与操作数大小属性相关
	// 比如eAX在16（AX）或32位（EAX）出现，rAX可能为AX（16）、EAX（32）、RAX（64）
	// 当REX.B被用于改变opcode的reg域时，使用 /xxx 表示其可能性

	// al:8 /rex.b r8l:8
	SPC_AL_R8L,
	SPC_CL_R9L,
	SPC_DL_R10L,
	SPC_BL_R11L,
	SPC_AH_R12L,
	SPC_CH_R13L,
	SPC_DH_R14L,
	SPC_BH_R15L,
	// al:8 ax:16 eax:32 rax:64
	SPC_AL_rAX,
	// ax:16 eax:32 rax:64 /rex.b r8:64
	SPC_rAX_r8,
	SPC_rCX_r9,
	SPC_rDX_r10,
	SPC_rBX_r11,
	SPC_rSP_r12,
	SPC_rBP_r13,
	SPC_rSI_r14,
	SPC_rDI_r15,
	// rax:64 eax:32 /rex.b r8:64 r8d:32
	SPC_RAX_EAX_R8_R8D,
	SPC_RCX_ECX_R9_R9D,
	SPC_RDX_EDX_R10_R10D,
	SPC_RBX_EBX_R11_R11D,
	SPC_RSP_ESP_R12_R12D,
	SPC_RBP_EBP_R13_R13D,
	SPC_RSI_ESI_R14_R14D,
	SPC_RDI_EDI_R15_R15D,
	// ib /rex.b iz ?
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

	// 表示寄存器参数(字符串)会随着长度限定改变
	// 这个是配合后面REG用的标识
	CHANGE_REG,

	// SPL,BPL,SIL,DIL（Len_8长度，需要REX前缀，会替换掉ah、ch、dh、bh）
	// 使用长度赋值不代表是这个长度,放在那里节省空间
	// 注意大小的转换需要考虑到这里
	REG_SPL = _REG(8, Len_64_MM),
	REG_BPL = _REG(9, Len_64_MM),
	REG_SIL = _REG(10, Len_64_MM),
	REG_DIL = _REG(11, Len_64_MM),
	// 待定
	REG_X12 = _REG(12, Len_64_MM),
	REG_X13 = _REG(13, Len_64_MM),
	REG_X14 = _REG(14, Len_64_MM),
	REG_X15 = _REG(15, Len_64_MM),

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
	// 到223
	REG_END = REG_XMM15,
	// Segs
	// 从SEG_XX按顺序递增,需要做一些处理才能取到字符串
	SEG_XX = 250,
	SEG_CS = SEG_XX,
	SEG_DS = SEG_XX + 1,
	SEG_ES = SEG_XX + 2,
	SEG_FS = SEG_XX + 3,
	SEG_GS = SEG_XX + 4,
	SEG_SS = SEG_XX + 5,
};

enum OpcodeType :unsigned char
{
	OT_None,
	OT_Inst,  // 普通指令
	OT_Inst_Change,  // 根据长度修改指令名的指令
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
	// Instructions that include a VEX prefix are organized relative to the 2-byte and 3-byte opcode maps, 
	// based on the VEX.mmmmm field encoding of implied 0F, 0F38H, 0F3AH, respectively. 
	// Each entry in the opcode map of a VEX-encoded instruction is based on the value of the opcode byte, 
	// similar to non-VEX-encoded instructions.
	// A VEX prefix includes several bit fields that encode implied 66H, F2H, F3H prefix functionality(VEX.pp) 
	// and operand size / opcode information(VEX.L).See chapter 4 for details.
	// Opcode tables A2 - A6 include both instructions with a VEX prefix and instructions without a VEX prefix.
	// Many entries are only made once, but represent both the VEX and non - VEX forms of the instruction.
	// If the VEX prefix is present all the operands are valid and the mnemonic is usually prefixed with a “v”.
	// If the VEX prefix is not present the VEX.vvvv operand is not available and the prefix “v” is dropped from the mnemonic.
	// A few instructions exist only in VEX form and these are marked with a superscript “v”.
	// Operand size of VEX prefix instructions can be determined by the operand type code. 
	// 128 - bit vectors are indicated by 'dq', 256 - bit vectors are indicated by 'qq', 
	// and instructions with operands supporting either 128 or 256 - bit,
	// determined by VEX.L, are indicated by 'x'.
	// For example, the entry "VMOVUPD Vx,Wx" indicates both VEX.L = 0 and VEX.L = 1 are supported.
	PfxGrp_Vex,
	PfxGrp_End
};
enum Prefix :unsigned char
{
	// Some combinations of REX prefix fields are invalid. In such cases, the prefix is ignored. Some addi-
	// tional information follows:
	// Setting REX.W can be used to determine the operand size but does not solely determine operand width. Like
	// the 66H size prefix, 64-bit operand size override has no effect on byte-specific operations.
	// For non-byte operations: if a 66H prefix is used with prefix (REX.W = 1), 66H is ignored.
	// If a 66H override is used with REX and REX.W = 0, the operand size is 16 bits.
	// REX.R modifies the ModR/M reg field when that field encodes a GPR, SSE, control or debug register. REX.R is
	// ignored when ModR/M specifies other registers or defines an extended opcode.
	// REX.X bit modifies the SIB index field.
	// REX.B either modifies the base in the ModR/M r/m field or SIB base field; or it modifies the opcode reg field
	// used for accessing GPRs.
	// 489页有一个表
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
	// 491页有相关内容
	Vex_2Byte = 0xC4,
	Vex_1Byte = 0xC5,

	// 81页有相关内容
	// The address - size override prefix(67H) allows programs to switch between 16 - and 32 - bit addressing.Either size
	// can be the default; the prefix selects the non - default size.Using this prefix and / or other undefined opcodes when
	// operands for the instruction do not reside in memory is reserved; such use may cause unpredictable behavior.

	// The address - size attribute selects the sizes of addresses used to address memory : 16 bits or 32 bits.When the 16 -
	// bit address - size attribute is in force, segment offsets and displacements are 16 bits.This restriction limits the size
	// of a segment to 64 KBytes.When the 32 - bit address - size attribute is in force, segment offsets and displacements
	// are 32 bits, allowing up to 4 GBytes to be addressed.
	G4_address_size = 0x67,
	// LOCK prefix is encoded using F0H.
	G1_lock = 0xf0,
	// The operand - size attribute selects the size of operands.When the 16 - bit operand - size attribute is in force, oper -
	// ands can generally be either 8 bits or 16 bits, and when the 32 - bit operand - size attribute is in force, operands can
	// generally be 8 bits or 32 bits.
	// The operand - size override prefix allows a program to switch between 16 - and 32 - bit operand sizes.Either size can
	// be the default; use of the prefix selects the non - default size.
	// Some SSE2 / SSE3 / SSSE3 / SSE4 instructions and instructions using a three - byte sequence of primary opcode bytes
	// may use 66H as a mandatory prefix to express distinct functionality.
	// Other use of the 66H prefix is reserved; such use may cause unpredictable behavior.
	G3_operand_size = 0x66,
	// REPNE / REPNZ prefix is encoded using F2H.Repeat - Not - Zero prefix applies only to string and
	// input / output instructions. (F2H is also used as a mandatory prefix for some instructions.)
	// Bound prefix is encoded using F2H if the following conditions are true:
	// CPUID.(EAX = 07H, ECX = 0) : EBX.MPX[bit 14] is set.
	// BNDCFGU.EN and / or IA32_BNDCFGS.EN is set.
	// When the F2 prefix precedes a near CALL, a near RET, a near JMP, or a near Jcc instruction(see Chapter
	// 16, “Intel® MPX, ” of the Intel® 64 and IA - 32 Architectures Software Developer’s Manual, Volume 1).

	// The operand - size attribute selects the size of operands.When the 16 - bit operand - size attribute is in force, oper -
	// ands can generally be either 8 bits or 16 bits, and when the 32 - bit operand - size attribute is in force, operands can
	// generally be 8 bits or 32 bits.
	G1_repne_xacquire = 0xf2,
	// REP or REPE / REPZ is encoded using F3H.The repeat prefix applies only to string and input / output
	// instructions.F3H is also used as a mandatory prefix for POPCNT, LZCNT and ADOX instructions.
	G1_reprepe_xrelease = 0xf3,
	// use with any branch instruction is reserved
	G2_seg_cs = 0x2e,  // Branch not taken (used only with Jcc instructions)
	G2_seg_ds = 0x3e,  // Branch taken (used only with Jcc instructions)
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
	C_None,
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
	S_1B = 1,  // 使用0F0B操作码（UD2指令）或0FB9H操作码时，刻意生成无效的操作码异常（#UD）。
	S_1C,  // 有些指令使用相同的两个字节码。如果该指令有变化，或者操作码表示不同的指令，该MODR/ M字节将用于区分该指令。

	// 条件
	S_i64,  // 在64位非法或未编码，40-4f在64位中做REX前缀，使用FE/FF/Grp4 5代替inc/dec
	S_o64,  // 仅64位可用

	S_d64,  // 在64位中操作数默认64位，不能编码32位数据
	S_f64,  // 64位时操作数强制64位，操作数尺寸前缀在64位下无效

	S_v,  // 只存在vex形式。没有传统的SSE指令形式。对于整数GPR指令它表示VEX前缀
	S_v1,  // 当不能从数据大小推断时，只存在VEX128和SSE形式（没有VEX256）
};

// 名字后缀
enum NameExt :unsigned char
{
	Ext_None = 0,
	Ext_B = 1,
	Ext_W = Ext_B << 1,
	Ext_D = Ext_W << 1,
	Ext_Q = Ext_D << 1
};

enum SizeAttribute :unsigned char
{
	BitNotSet = Len_8,
	Bit16 = Len_16,
	Bit32 = Len_32,
	Bit64 = Len_64
};
enum EffectiveSizeIndex :unsigned char
{
	EffectiveOperand,
	EffectiveAddress,
};

// If the flag is set,32 - bit addresses and 32 - bit or 8 - bit operands are assumed;
// if it is clear, 16 - bit addresses and 16 - bit or 8 - bit operands are assumed.

// D Flag in Code Segment Descriptor	0  0  0  0  1  1  1  1
// Operand - Size Prefix 66H			N  N  Y  Y  N  N  Y  Y
// Address - Size Prefix 67H			N  Y  N  Y  N  Y  N  Y
// Effective Operand Size				16 16 32 32 32 32 16 16
// Effective Address Size				16 32 16 32 32 16 32 16
// 下面忽略掉DFlag为0的情况
// [Operand Prefix Is Present]
// [Address Prefix Is Present]
// [Effective Operand Size/Effective Address Size]
extern const SizeAttribute EffectiveMode32[2][2][2];

// In the case of SSE / SSE2 / SSE3 / SSSE3 SIMD instructions : the 66H, F2H, and F3H prefixes are mandatory for
// opcode extensions.In such a case, there is no interaction between a valid REX.W prefix and a 66H opcode exten -
// sion prefix.

// L Flag in Code Segment Descriptor	1  1  1  1  1  1  1  1

// REX.W Prefix							0  0  0  0  1  1  1  1
// Operand - Size Prefix 66H			N  N  Y  Y  N  N  Y  Y
// Address - Size Prefix 67H			N  Y  N  Y  N  Y  N  Y
// Effective Operand Size				32 32 16 16 64 64 64 64
// Effective Address Size				64 32 64 32 64 32 64 32

// [REX.W Prefix]
// [Operand Prefix Is Present]
// [Address Prefix Is Present]
// [Effective Operand Size/Effective Address Size]
extern const SizeAttribute EffectiveMode64[2][2][2][2];

// 跟段标识共用一个表节约一下空间
extern const char Registers[16][6][6];

#pragma pack(push, 1)
// 1b\2b 表中元素结构,Count表示可选择的指令数，0表示指令不存在
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
