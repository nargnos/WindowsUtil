#pragma once
#include <Windows.h>
#include <WinBase.h>
#include <assert.h>
namespace Asm
{
	typedef struct _ModRM
	{
		BYTE Rm : 3;
		BYTE Reg : 3;
		BYTE Mod : 2;
	}ModRM, *PModRM;

	enum OperandTypes
	{
		L_a = 0,
		L_b = 1,
		L_c = 2,
		L_d = 3,
		L_dq = 4,
		L_p = 5,
		L_pd = 6,
		L_pi = 7,
		L_ps = 8,
		L_q = 9,
		L_qq = 10,
		L_s = 11,
		L_sd = 12,
		L_ss = 13,
		L_si = 14,
		L_v = 15,
		L_w = 16,
		L_x = 17,
		L_y = 18,
		L_z = 19
	};
	enum AddressingMethods
	{
		H_A = 0,
		H_B = 1,
		H_C = 2,
		H_D = 3,
		H_E = 4,
		H_F = 5,
		H_G = 6,
		H_H = 7,
		H_I = 8,
		H_J = 9,
		H_L = 10,
		H_M = 11,
		H_N = 12,
		H_O = 13,
		H_P = 14,
		H_Q = 15,
		H_R = 16,
		H_S = 17,
		H_U = 18,
		H_V = 19,
		H_W = 20,
		H_X = 21,
		H_Y = 22
	};
#pragma region 寄存器们
	enum RegisterLength
	{
		Len_8,
		Len_16,
		Len_32,
		Len_64,
		Len_64_MM,
		Len_128_XMM
	};
	extern const PCSTR Registers_0[] = 
	{
		"AL", // 8
		"AX", // 16
		"EAX",// 32
		"RAX",// 64
		"MM0",// 64
		"XMM0"// 128
	};
	extern const PCSTR Registers_1[] =
	{
		"CL",
		"CX",
		"ECX",
		"RCX",
		"MM1",
		"XMM1" 
	};
	extern const PCSTR Registers_2[] =
	{
		"DL",
		"DX",
		"EDX",
		"RDX",
		"MM2",
		"XMM2"
	};
	extern const PCSTR Registers_3[] =
	{
		"BL",
		"BX",
		"EBX",
		"RBX",
		"MM3",
		"XMM3" 
	};
	extern const PCSTR Registers_4[] =
	{
		"AH",
		"SP",
		"ESP",
		"RSP",
		"MM4",
		"XMM4" 
	};
	extern const PCSTR Registers_5[] =
	{ 
		"CH",
		"BP",
		"EBP",
		"RBP",
		"MM5",
		"XMM5" 
	};
	extern const PCSTR Registers_6[] =
	{
		"DH",
		"SI",
		"ESI",
		"RSI",
		"MM6",
		"XMM6" 
	};
	extern const PCSTR Registers_7[] =
	{
		"BH",
		"DI",
		"EDI",
		"RDI",
		"MM7",
		"XMM7" 
	};
	extern const PCSTR Registers_8[] = {
		"R8",
		"XMM8"
	};
	extern const PCSTR Registers_9[] = {
		"R9",
		"XMM9"
	};
	extern const PCSTR Registers_10[] = {
		"R10",
		"XMM10"
	};
	extern const PCSTR Registers_11[] = {
		"R11",
		"XMM11"
	};
	extern const PCSTR Registers_12[] = {
		"R12",
		"XMM12"
	};
	extern const PCSTR Registers_13[] = {
		"R13",
		"XMM13"
	};
	extern const PCSTR Registers_14[] = {
		"R14",
		"XMM14"
	};
	extern const PCSTR Registers_15[] = {
		"R15",
		"XMM15"
	};
	// 共64个
	extern const PCSTR* Registers[] =
	{
		Registers_0, // 6个元素
		Registers_1,
		Registers_2,
		Registers_3,
		Registers_4,
		Registers_5,
		Registers_6,
		Registers_7,
		Registers_8, // 从8开始只有2个，64 128
		Registers_9,
		Registers_10,
		Registers_11,
		Registers_12,
		Registers_13,
		Registers_14,
		Registers_15
	};
	// 取寄存器名
	// hex为寄存器16进制表示0-15，len为寄存器大小，类型0-5
	PCSTR GetRegisterName(BYTE hex, RegisterLength type)
	{
		assert(hex < 16 && (BYTE)type < 6);
		if (hex < 8) // 从8开始数组只有2项
		{
			return Registers[hex][type];
		}
		assert(type == Len_64 || type == Len_128_XMM);
		switch (type)
		{
		case Asm::Len_64:
			return  Registers[hex][0];
		case Asm::Len_128_XMM:
			return  Registers[hex][1];
		default:
			break;
		}
		return NULL; // 去除无谓判断，断言后不会到这里
	}
#pragma endregion
#pragma region 助记符们
	const PCSTR Instructions[] =
	{
		"aaa",
		"aad",
		"aam",
		"aas",
		"adc",
		"adcx",
		"add",
		"adox",
		"and",
		"andn",
		"arpl",
		"bextr",
		"blendvpd",
		"blendvps",
		"blsi",
		"blsmsk",
		"blsr",
		"bound",
		"bsf",
		"bsr",
		"bswap",
		"bt",
		"btc",
		"btr",
		"bts",
		"bzhi",
		"call",
		"cbw", // 2
		"cwde",
		"cdqe",
		"clac",
		"clc",
		"cld",
		"clflush",
		"cli",
		"clts",
		"cmc",
		"cmova",
		"cmovae",
		"cmovb",
		"cmovbe",
		"cmovc",
		"cmove",
		"cmovg",
		"cmovge",
		"cmovl",
		"cmovle",
		"cmovna",
		"cmovnae",
		"cmovnb",
		"cmovnbe",
		"cmovnc",
		"cmovne",
		"cmovng",
		"cmovnge",
		"cmovnl",
		"cmovnle",
		"cmovno",
		"cmovnp",
		"cmovns",
		"cmovnz",
		"cmovo",
		"cmovp",
		"cmovpe",
		"cmovpo",
		"cmovs",
		"cmovz",
		"cmp",
		"cmps", // b w d
		"cmpxch",
		"cmpxchg",
		"cpuid",
		"crc32",
		"cvtpd2pi",
		"cvtpi2pd",
		"cvtpi2ps",
		"cvtps2pi",
		"cvttpd2pi",
		"cvttps2pi",
		"cwd", // 2
		"cdq",
		"cqo",
		"daa",
		"das",
		"dec",
		"div",
		"emms",
		"enter",
		"esc",
		"fxrstor",
		"fxsave",
		"getsec",
		"hlt",
		"idiv",
		"imul",
		"in",
		"inc",
		"ins", // b w d
		"int",
		"int 3",
		"into",
		"invd",
		"invept",
		"invlpg",
		"invpcid",
		"invvpid",
		"iret", //d q
		"ja", // 1
		"jnbe",
		"jb", // 2
		"jnae",
		"jc",
		"jnz", // 1
		"jne",
		"jbe", // 1
		"jna",
		"jz", // 1
		"je",
		"jg", // 1
		"jnle",
		"jl", // 1
		"jnge",
		"jle", // 1
		"jng",
		"jmp",
		"jmpe",
		"jnb", //2
		"jae",
		"jnc",
		"jnl", // 1
		"jge",
		"jno",
		"jnp", // 1
		"jpo",
		"jns",
		"jo",
		"jp", // 1
		"jpe",
		"jrcxz",
		"js",
		"lahf",
		"lar",
		"ldmxcsr",
		"lds",
		"lea",
		"leave",
		"les",
		"lfence",
		"lfs",
		"lgdt",
		"lgs",
		"lidt",
		"lldt",
		"lmsw",
		"lods", // b w d q
		"loop",
		"loope", // 1
		"loopz",
		"loopne", // 1
		"loopnz",
		"lsl",
		"lss",
		"ltr",
		"maskmovq",
		"mfence",
		"monitor",
		"mov",
		"movbe",
		"movdq2q",
		"movnti",
		"movntq",
		"movq2dq",
		"movs", // b w d q
		"movsx",
		"movsxd",
		"movw",
		"movzx",
		"mul",
		"mulx",
		"mwait",
		"neg",
		"nop",
		"not",
		"or",
		"out",
		"outs", // b w d
		"pabsb",
		"pabsd",
		"pabsw",
		"packssdw",
		"packsswb",
		"packuswb",
		"paddb",
		"paddd",
		"paddq",
		"paddsb",
		"paddsw",
		"paddusb",
		"paddusw",
		"paddw",
		"palignr",
		"pand",
		"pandn",
		"pause",
		"pavgb",
		"pavgw",
		"pblendvb",
		"pcmpeqb",
		"pcmpeqd",
		"pcmpeqw",
		"pcmpgtb",
		"pcmpgtd",
		"pcmpgtw",
		"pdep",
		"pext",
		"pextrw",
		"phaddd",
		"phaddsw",
		"phaddw",
		"phsubd",
		"phsubsw",
		"phsubw",
		"pinsrw",
		"pmaddubsw",
		"pmaddwd",
		"pmaxsw",
		"pmaxub",
		"pminsw",
		"pminub",
		"pmovmskb",
		"pmulhrsw",
		"pmulhuw",
		"pmulhw",
		"pmullw",
		"pmuludq",
		"pop",
		"popa", // 1
		"popad",
		"popf", // d q(64)
		"popcnt",
		"por",
		"prefetch nta",
		"prefetch t0",
		"prefetch t1",
		"prefetch t2",
		"prefetchw",
		"prefix: address size", // 67h
		"prefix: lock", // f0h
		"prefix: operand size", // 66h
		"prefix: repne xacquire", // f2h
		"prefix: reprepe xrelease", // f3h
		"prefix: seg=cs", // 2eh
		"prefix: seg=ds", // 3eh
		"prefix: seg=es", // 26h
		"prefix: seg=fs", // 64h
		"prefix: seg=gs", // 65h
		"prefix: seg=ss", // 36h
		"psadbw",
		"pshufb",
		"pshufw",
		"psignb",
		"psignd",
		"psignw",
		"pslld",
		"psllq",
		"psllw",
		"psrad",
		"psraw",
		"psrld",
		"psrlq",
		"psrlw",
		"psubb",
		"psubd",
		"psubq",
		"psubsb",
		"psubsw",
		"psubusb",
		"psubusw",
		"psubw",
		"punpckhbw",
		"punpckhdq",
		"punpckhwd",
		"punpcklbw",
		"punpckldq",
		"punpcklwd",
		"push",
		"pusha", // 1
		"pushad",
		"pushf", // d q(64)
		"pxor",
		"rcl",
		"rcr",
		"rdfsbase",
		"rdgsbase",
		"rdmsr",
		"rdpmc",
		"rdrand",
		"rdseed",
		"rdtsc",
		"rdtscp",
		"ret",
		"rol",
		"ror",
		"rorx",
		"rsm",
		"sahf",
		"sar",
		"sarx",
		"sbb",
		"scas", // bwdq
		"seta", // 1
		"setnbe",
		"setae", // 2
		"setnb",
		"setnc",
		"setb", // 2
		"setc",
		"setnae",
		"setbe", // 1
		"setna",
		"sete", // 1
		"setz",
		"setg", // 1
		"setnle",
		"setge", // 1
		"setnl",
		"setl", // 1
		"setnge",
		"setle", // 1
		"setng",
		"setne", // 1
		"setnz",
		"setno",
		"setnp", // 1
		"setpo",
		"setns",
		"seto",
		"setp", // 1
		"setpe",
		"sets",
		"sfence",
		"sgdt",
		"shl",
		"sal",
		"shld",
		"shlx",
		"shr",
		"shrd",
		"shrx",
		"sidt",
		"sldt",
		"smsw",
		"stac",
		"stc",
		"std",
		"sti",
		"stmxcsr",
		"stos", // b w d q
		"str",
		"sub",
		"swapgs",
		"syscall",
		"sysenter",
		"sysexit",
		"sysret",
		"test",
		"tzcnt",
		"ud2",
		"vaddpd",
		"vaddps",
		"vaddsd",
		"vaddss",
		"vaddsubpd",
		"vaddsubps",
		"vaesdec",
		"vaesdeclast",
		"vaesenc",
		"vaesenclast",
		"vaesimc",
		"vaeskeygen",
		"vandnpd",
		"vandnps",
		"vandpd",
		"vandps",
		"vblendpd",
		"vblendps",
		"vblendvpd",
		"vblendvps",
		"vbroadcastf128",
		"vbroadcasti128",
		"vbroadcastsd",
		"vbroadcastss",
		"vcmppd",
		"vcmpps",
		"vcmpsd",
		"vcmpss",
		"vcomisd",
		"vcomiss",
		"vcvtdq2pd",
		"vcvtdq2ps",
		"vcvtpd2dq",
		"vcvtpd2ps",
		"vcvtph2ps",
		"vcvtps2dq",
		"vcvtps2pd",
		"vcvtps2ph",
		"vcvtsd2si",
		"vcvtsd2ss",
		"vcvtsi2sd",
		"vcvtsi2ss",
		"vcvtss2sd",
		"vcvtss2si",
		"vcvttpd2dq",
		"vcvttps2dq",
		"vcvttsd2si",
		"vcvttss2si",
		"vdivpd",
		"vdivps",
		"vdivsd",
		"vdivss",
		"vdppd",
		"vdpps",
		"verr",
		"verw",
		"vextractf128",
		"vextracti128",
		"vextractps",
		"vfmadd132pd",
		"vfmadd132ps",
		"vfmadd132sd",
		"vfmadd132ss",
		"vfmadd213pd",
		"vfmadd213ps",
		"vfmadd213sd",
		"vfmadd213ss",
		"vfmadd231pd",
		"vfmadd231ps",
		"vfmadd231sd",
		"vfmadd231ss",
		"vfmaddsub132pd",
		"vfmaddsub132ps",
		"vfmaddsub213pd",
		"vfmaddsub213ps",
		"vfmaddsub231pd",
		"vfmaddsub231ps",
		"vfmsub132pd",
		"vfmsub132ps",
		"vfmsub132sd",
		"vfmsub132ss",
		"vfmsub213pd",
		"vfmsub213ps",
		"vfmsub213sd",
		"vfmsub213ss",
		"vfmsub231pd",
		"vfmsub231ps",
		"vfmsub231sd",
		"vfmsub231ss",
		"vfmsubadd132pd",
		"vfmsubadd132ps",
		"vfmsubadd213pd",
		"vfmsubadd213ps",
		"vfmsubadd231pd",
		"vfmsubadd231ps",
		"vfnmadd132pd",
		"vfnmadd132ps",
		"vfnmadd132sd",
		"vfnmadd132ss",
		"vfnmadd213pd",
		"vfnmadd213ps",
		"vfnmadd213sd",
		"vfnmadd213ss",
		"vfnmadd231pd",
		"vfnmadd231ps",
		"vfnmadd231sd",
		"vfnmadd231ss",
		"vfnmsub132pd",
		"vfnmsub132ps",
		"vfnmsub132sd",
		"vfnmsub132ss",
		"vfnmsub213pd",
		"vfnmsub213ps",
		"vfnmsub213sd",
		"vfnmsub213ss",
		"vfnmsub231pd",
		"vfnmsub231ps",
		"vfnmsub231sd",
		"vfnmsub231ss",
		"vgatherdd",
		"vgatherdpd",
		"vgatherdps",
		"vgatherdq",
		"vgatherqd",
		"vgatherqpd",
		"vgatherqps",
		"vgatherqq",
		"vhaddpd",
		"vhaddps",
		"vhsubpd",
		"vhsubps",
		"vinsertf128",
		"vinserti128",
		"vinsertps",
		"vlddqu",
		"vmaskmovdqu",
		"vmaskmovpd",
		"vmaskmovps",
		"vmaxpd",
		"vmaxps",
		"vmaxsd",
		"vmaxss",
		"vmcall",
		"vmclear",
		"vmfunc",
		"vminpd",
		"vminps",
		"vminsd",
		"vminss",
		"vmlaunch",
		"vmovapd",
		"vmovaps",
		"vmovd",
		"vmovddup",
		"vmovdqa",
		"vmovdqu",
		"vmovhlps",
		"vmovhpd",
		"vmovhps",
		"vmovlhps",
		"vmovlpd",
		"vmovlps",
		"vmovmskpd",
		"vmovmskps",
		"vmovntdq",
		"vmovntdqa",
		"vmovntpd",
		"vmovntps",
		"vmovq",
		"vmovsd",
		"vmovsldup",
		"vmovss",
		"vmovupd",
		"vmovups",
		"vmpsadbw",
		"vmptrld",
		"vmptrst",
		"vmread",
		"vmresume",
		"vmulpd",
		"vmulps",
		"vmulsd",
		"vmulss",
		"vmwrite",
		"vmxoff",
		"vmxon",
		"vorpd",
		"vorps",
		"vpabsb",
		"vpabsd",
		"vpabsw",
		"vpackssdw",
		"vpacksswb",
		"vpackusdw",
		"vpackuswb",
		"vpaddb",
		"vpaddd",
		"vpaddq",
		"vpaddsb",
		"vpaddsw",
		"vpaddusb",
		"vpaddusw",
		"vpaddw",
		"vpalignr",
		"vpand",
		"vpandn",
		"vpavgb",
		"vpavgw",
		"vpblendd",
		"vpblendvb",
		"vpblendw",
		"vpbroadcastb",
		"vpbroadcastd",
		"vpbroadcastq",
		"vpbroadcastw",
		"vpclmulqdq",
		"vpcmpeqb",
		"vpcmpeqd",
		"vpcmpeqq",
		"vpcmpeqw",
		"vpcmpestri",
		"vpcmpestrm",
		"vpcmpgtb",
		"vpcmpgtd",
		"vpcmpgtq",
		"vpcmpgtw",
		"vpcmpistri",
		"vpcmpistrm",
		"vperm2f128",
		"vperm2i128",
		"vpermd",
		"vpermilpd",
		"vpermilps",
		"vpermpd",
		"vpermps",
		"vpermq",
		"vpextrb",
		"vpextrd",
		"vpextrq",
		"vpextrw",
		"vphaddd",
		"vphaddsw",
		"vphaddw",
		"vphminposuw",
		"vphsubd",
		"vphsubsw",
		"vphsubw",
		"vpinsrb",
		"vpinsrd",
		"vpinsrq",
		"vpinsrw",
		"vpmaddubsw",
		"vpmaddwd",
		"vpmaskmovd",
		"vpmaskmovq",
		"vpmaxsb",
		"vpmaxsd",
		"vpmaxsw",
		"vpmaxub",
		"vpmaxud",
		"vpmaxuw",
		"vpminsb",
		"vpminsd",
		"vpminsw",
		"vpminub",
		"vpminud",
		"vpminuw",
		"vpmovmskb",
		"vpmovsxbd",
		"vpmovsxbq",
		"vpmovsxbw",
		"vpmovsxdq",
		"vpmovsxwd",
		"vpmovsxwq",
		"vpmovzxbd",
		"vpmovzxbq",
		"vpmovzxbw",
		"vpmovzxdq",
		"vpmovzxwd",
		"vpmovzxwq",
		"vpmuldq",
		"vpmulhrsw",
		"vpmulhuw",
		"vpmulhw",
		"vpmulld",
		"vpmullw",
		"vpmuludq",
		"vpor",
		"vpsadbw",
		"vpshufb",
		"vpshufd",
		"vpshufhw",
		"vpshuflw",
		"vpsignb",
		"vpsignd",
		"vpsignw",
		"vpslld",
		"vpslldq",
		"vpsllq",
		"vpsllvd",
		"vpsllvq",
		"vpsllw",
		"vpsrad",
		"vpsravd",
		"vpsraw",
		"vpsrld",
		"vpsrldq",
		"vpsrlq",
		"vpsrlvd",
		"vpsrlvq",
		"vpsrlw",
		"vpsubb",
		"vpsubd",
		"vpsubq",
		"vpsubsb",
		"vpsubsw",
		"vpsubusb",
		"vpsubusw",
		"vpsubw",
		"vptest",
		"vpunpckhbw",
		"vpunpckhdq",
		"vpunpckhqdq",
		"vpunpckhwd",
		"vpunpcklbw",
		"vpunpckldq",
		"vpunpcklqdq",
		"vpunpcklwd",
		"vpxor",
		"vrcpps",
		"vrcpss",
		"vroundpd",
		"vroundps",
		"vroundsd",
		"vroundss",
		"vrsqrtps",
		"vrsqrtss",
		"vshufpd",
		"vshufps",
		"vsqrtpd",
		"vsqrtps",
		"vsqrtsd",
		"vsqrtss",
		"vsubpd",
		"vsubps",
		"vsubsd",
		"vsubss",
		"vtestpd",
		"vtestps",
		"vucomisd",
		"vucomiss",
		"vunpckhpd",
		"vunpckhps",
		"vunpcklpd",
		"vunpcklps",
		"vxorpd",
		"vxorps",
		"wait", // 1
		"fwait",
		"wbinvd",
		"wrfsbase",
		"wrgsbase",
		"wrmsr",
		"xabort",
		"xadd",
		"xbegin",
		"xchg",
		"xend",
		"xgetbv",
		"xlat", // b
		"xor",
		"xrstor",
		"xsave",
		"xsaveopt",
		"xsetbv",
		"xtest"
	};
	enum InstructionIndexs
	{
		Inst_aaa,
		Inst_aad,
		Inst_aam,
		Inst_aas,
		Inst_adc,
		Inst_adcx,
		Inst_add,
		Inst_adox,
		Inst_and,
		Inst_andn,
		Inst_arpl,
		Inst_bextr,
		Inst_blendvpd,
		Inst_blendvps,
		Inst_blsi,
		Inst_blsmsk,
		Inst_blsr,
		Inst_bound,
		Inst_bsf,
		Inst_bsr,
		Inst_bswap,
		Inst_bt,
		Inst_btc,
		Inst_btr,
		Inst_bts,
		Inst_bzhi,
		Inst_call,
		Inst_cbw, // 2
		Inst_cwde,
		Inst_cdqe,
		Inst_clac,
		Inst_clc,
		Inst_cld,
		Inst_clflush,
		Inst_cli,
		Inst_clts,
		Inst_cmc,
		Inst_cmova,
		Inst_cmovae,
		Inst_cmovb,
		Inst_cmovbe,
		Inst_cmovc,
		Inst_cmove,
		Inst_cmovg,
		Inst_cmovge,
		Inst_cmovl,
		Inst_cmovle,
		Inst_cmovna,
		Inst_cmovnae,
		Inst_cmovnb,
		Inst_cmovnbe,
		Inst_cmovnc,
		Inst_cmovne,
		Inst_cmovng,
		Inst_cmovnge,
		Inst_cmovnl,
		Inst_cmovnle,
		Inst_cmovno,
		Inst_cmovnp,
		Inst_cmovns,
		Inst_cmovnz,
		Inst_cmovo,
		Inst_cmovp,
		Inst_cmovpe,
		Inst_cmovpo,
		Inst_cmovs,
		Inst_cmovz,
		Inst_cmp,
		Inst_cmps, // b w d
		Inst_cmpxch,
		Inst_cmpxchg,
		Inst_cpuid,
		Inst_crc32,
		Inst_cvtpd2pi,
		Inst_cvtpi2pd,
		Inst_cvtpi2ps,
		Inst_cvtps2pi,
		Inst_cvttpd2pi,
		Inst_cvttps2pi,
		Inst_cwd, // 2
		Inst_cdq,
		Inst_cqo,
		Inst_daa,
		Inst_das,
		Inst_dec,
		Inst_div,
		Inst_emms,
		Inst_enter,
		Inst_esc,
		Inst_fxrstor,
		Inst_fxsave,
		Inst_getsec,
		Inst_hlt,
		Inst_idiv,
		Inst_imul,
		Inst_in,
		Inst_inc,
		Inst_ins, // b w d
		Inst_int,
		Inst_int_3,
		Inst_into,
		Inst_invd,
		Inst_invept,
		Inst_invlpg,
		Inst_invpcid,
		Inst_invvpid,
		Inst_iret, //d q
		Inst_ja, // 1
		Inst_jnbe,
		Inst_jb, // 2
		Inst_jnae,
		Inst_jc,
		Inst_jnz, // 1
		Inst_jne,
		Inst_jbe, // 1
		Inst_jna,
		Inst_jz, // 1
		Inst_je,
		Inst_jg, // 1
		Inst_jnle,
		Inst_jl, // 1
		Inst_jnge,
		Inst_jle, // 1
		Inst_jng,
		Inst_jmp,
		Inst_jmpe,
		Inst_jnb, //2
		Inst_jae,
		Inst_jnc,
		Inst_jnl, // 1
		Inst_jge,
		Inst_jno,
		Inst_jnp, // 1
		Inst_jpo,
		Inst_jns,
		Inst_jo,
		Inst_jp, // 1
		Inst_jpe,
		Inst_jrcxz,
		Inst_js,
		Inst_lahf,
		Inst_lar,
		Inst_ldmxcsr,
		Inst_lds,
		Inst_lea,
		Inst_leave,
		Inst_les,
		Inst_lfence,
		Inst_lfs,
		Inst_lgdt,
		Inst_lgs,
		Inst_lidt,
		Inst_lldt,
		Inst_lmsw,
		Inst_lods, // b w d q
		Inst_loop,
		Inst_loope, // 1
		Inst_loopz,
		Inst_loopne, // 1
		Inst_loopnz,
		Inst_lsl,
		Inst_lss,
		Inst_ltr,
		Inst_maskmovq,
		Inst_mfence,
		Inst_monitor,
		Inst_mov,
		Inst_movbe,
		Inst_movdq2q,
		Inst_movnti,
		Inst_movntq,
		Inst_movq2dq,
		Inst_movs, // b w d q
		Inst_movsx,
		Inst_movsxd,
		Inst_movw,
		Inst_movzx,
		Inst_mul,
		Inst_mulx,
		Inst_mwait,
		Inst_neg,
		Inst_nop,
		Inst_not,
		Inst_or,
		Inst_out,
		Inst_outs, // b w d
		Inst_pabsb,
		Inst_pabsd,
		Inst_pabsw,
		Inst_packssdw,
		Inst_packsswb,
		Inst_packuswb,
		Inst_paddb,
		Inst_paddd,
		Inst_paddq,
		Inst_paddsb,
		Inst_paddsw,
		Inst_paddusb,
		Inst_paddusw,
		Inst_paddw,
		Inst_palignr,
		Inst_pand,
		Inst_pandn,
		Inst_pause,
		Inst_pavgb,
		Inst_pavgw,
		Inst_pblendvb,
		Inst_pcmpeqb,
		Inst_pcmpeqd,
		Inst_pcmpeqw,
		Inst_pcmpgtb,
		Inst_pcmpgtd,
		Inst_pcmpgtw,
		Inst_pdep,
		Inst_pext,
		Inst_pextrw,
		Inst_phaddd,
		Inst_phaddsw,
		Inst_phaddw,
		Inst_phsubd,
		Inst_phsubsw,
		Inst_phsubw,
		Inst_pinsrw,
		Inst_pmaddubsw,
		Inst_pmaddwd,
		Inst_pmaxsw,
		Inst_pmaxub,
		Inst_pminsw,
		Inst_pminub,
		Inst_pmovmskb,
		Inst_pmulhrsw,
		Inst_pmulhuw,
		Inst_pmulhw,
		Inst_pmullw,
		Inst_pmuludq,
		Inst_pop,
		Inst_popa, // 1
		Inst_popad,
		Inst_popf, // d q(64)
		Inst_popcnt,
		Inst_por,
		Inst_prefetch_nta,
		Inst_prefetch_t0,
		Inst_prefetch_t1,
		Inst_prefetch_t2,
		Inst_prefetchw,
		Inst_prefix_address_size, // 67h
		Inst_prefix_lock, // f0h
		Inst_prefix_operand_size, // 66h
		Inst_prefix_repne_xacquire, // f2h
		Inst_prefix_reprepe_xrelease, // f3h
		Inst_prefix_seg_cs, // 2eh
		Inst_prefix_seg_ds, // 3eh
		Inst_prefix_seg_es, // 26h
		Inst_prefix_seg_fs, // 64h
		Inst_prefix_seg_gs, // 65h
		Inst_prefix_seg_ss, // 36h
		Inst_psadbw,
		Inst_pshufb,
		Inst_pshufw,
		Inst_psignb,
		Inst_psignd,
		Inst_psignw,
		Inst_pslld,
		Inst_psllq,
		Inst_psllw,
		Inst_psrad,
		Inst_psraw,
		Inst_psrld,
		Inst_psrlq,
		Inst_psrlw,
		Inst_psubb,
		Inst_psubd,
		Inst_psubq,
		Inst_psubsb,
		Inst_psubsw,
		Inst_psubusb,
		Inst_psubusw,
		Inst_psubw,
		Inst_punpckhbw,
		Inst_punpckhdq,
		Inst_punpckhwd,
		Inst_punpcklbw,
		Inst_punpckldq,
		Inst_punpcklwd,
		Inst_push,
		Inst_pusha, // 1
		Inst_pushad,
		Inst_pushf, // d q(64)
		Inst_pxor,
		Inst_rcl,
		Inst_rcr,
		Inst_rdfsbase,
		Inst_rdgsbase,
		Inst_rdmsr,
		Inst_rdpmc,
		Inst_rdrand,
		Inst_rdseed,
		Inst_rdtsc,
		Inst_rdtscp,
		Inst_ret,
		Inst_rol,
		Inst_ror,
		Inst_rorx,
		Inst_rsm,
		Inst_sahf,
		Inst_sar,
		Inst_sarx,
		Inst_sbb,
		Inst_scas, // bwdq
		Inst_seta, // 1
		Inst_setnbe,
		Inst_setae, // 2
		Inst_setnb,
		Inst_setnc,
		Inst_setb, // 2
		Inst_setc,
		Inst_setnae,
		Inst_setbe, // 1
		Inst_setna,
		Inst_sete, // 1
		Inst_setz,
		Inst_setg, // 1
		Inst_setnle,
		Inst_setge, // 1
		Inst_setnl,
		Inst_setl, // 1
		Inst_setnge,
		Inst_setle, // 1
		Inst_setng,
		Inst_setne, // 1
		Inst_setnz,
		Inst_setno,
		Inst_setnp, // 1
		Inst_setpo,
		Inst_setns,
		Inst_seto,
		Inst_setp, // 1
		Inst_setpe,
		Inst_sets,
		Inst_sfence,
		Inst_sgdt,
		Inst_shl,
		Inst_sal,
		Inst_shld,
		Inst_shlx,
		Inst_shr,
		Inst_shrd,
		Inst_shrx,
		Inst_sidt,
		Inst_sldt,
		Inst_smsw,
		Inst_stac,
		Inst_stc,
		Inst_std,
		Inst_sti,
		Inst_stmxcsr,
		Inst_stos, // b w d q
		Inst_str,
		Inst_sub,
		Inst_swapgs,
		Inst_syscall,
		Inst_sysenter,
		Inst_sysexit,
		Inst_sysret,
		Inst_test,
		Inst_tzcnt,
		Inst_ud2,
		Inst_vaddpd,
		Inst_vaddps,
		Inst_vaddsd,
		Inst_vaddss,
		Inst_vaddsubpd,
		Inst_vaddsubps,
		Inst_vaesdec,
		Inst_vaesdeclast,
		Inst_vaesenc,
		Inst_vaesenclast,
		Inst_vaesimc,
		Inst_vaeskeygen,
		Inst_vandnpd,
		Inst_vandnps,
		Inst_vandpd,
		Inst_vandps,
		Inst_vblendpd,
		Inst_vblendps,
		Inst_vblendvpd,
		Inst_vblendvps,
		Inst_vbroadcastf128,
		Inst_vbroadcasti128,
		Inst_vbroadcastsd,
		Inst_vbroadcastss,
		Inst_vcmppd,
		Inst_vcmpps,
		Inst_vcmpsd,
		Inst_vcmpss,
		Inst_vcomisd,
		Inst_vcomiss,
		Inst_vcvtdq2pd,
		Inst_vcvtdq2ps,
		Inst_vcvtpd2dq,
		Inst_vcvtpd2ps,
		Inst_vcvtph2ps,
		Inst_vcvtps2dq,
		Inst_vcvtps2pd,
		Inst_vcvtps2ph,
		Inst_vcvtsd2si,
		Inst_vcvtsd2ss,
		Inst_vcvtsi2sd,
		Inst_vcvtsi2ss,
		Inst_vcvtss2sd,
		Inst_vcvtss2si,
		Inst_vcvttpd2dq,
		Inst_vcvttps2dq,
		Inst_vcvttsd2si,
		Inst_vcvttss2si,
		Inst_vdivpd,
		Inst_vdivps,
		Inst_vdivsd,
		Inst_vdivss,
		Inst_vdppd,
		Inst_vdpps,
		Inst_verr,
		Inst_verw,
		Inst_vextractf128,
		Inst_vextracti128,
		Inst_vextractps,
		Inst_vfmadd132pd,
		Inst_vfmadd132ps,
		Inst_vfmadd132sd,
		Inst_vfmadd132ss,
		Inst_vfmadd213pd,
		Inst_vfmadd213ps,
		Inst_vfmadd213sd,
		Inst_vfmadd213ss,
		Inst_vfmadd231pd,
		Inst_vfmadd231ps,
		Inst_vfmadd231sd,
		Inst_vfmadd231ss,
		Inst_vfmaddsub132pd,
		Inst_vfmaddsub132ps,
		Inst_vfmaddsub213pd,
		Inst_vfmaddsub213ps,
		Inst_vfmaddsub231pd,
		Inst_vfmaddsub231ps,
		Inst_vfmsub132pd,
		Inst_vfmsub132ps,
		Inst_vfmsub132sd,
		Inst_vfmsub132ss,
		Inst_vfmsub213pd,
		Inst_vfmsub213ps,
		Inst_vfmsub213sd,
		Inst_vfmsub213ss,
		Inst_vfmsub231pd,
		Inst_vfmsub231ps,
		Inst_vfmsub231sd,
		Inst_vfmsub231ss,
		Inst_vfmsubadd132pd,
		Inst_vfmsubadd132ps,
		Inst_vfmsubadd213pd,
		Inst_vfmsubadd213ps,
		Inst_vfmsubadd231pd,
		Inst_vfmsubadd231ps,
		Inst_vfnmadd132pd,
		Inst_vfnmadd132ps,
		Inst_vfnmadd132sd,
		Inst_vfnmadd132ss,
		Inst_vfnmadd213pd,
		Inst_vfnmadd213ps,
		Inst_vfnmadd213sd,
		Inst_vfnmadd213ss,
		Inst_vfnmadd231pd,
		Inst_vfnmadd231ps,
		Inst_vfnmadd231sd,
		Inst_vfnmadd231ss,
		Inst_vfnmsub132pd,
		Inst_vfnmsub132ps,
		Inst_vfnmsub132sd,
		Inst_vfnmsub132ss,
		Inst_vfnmsub213pd,
		Inst_vfnmsub213ps,
		Inst_vfnmsub213sd,
		Inst_vfnmsub213ss,
		Inst_vfnmsub231pd,
		Inst_vfnmsub231ps,
		Inst_vfnmsub231sd,
		Inst_vfnmsub231ss,
		Inst_vgatherdd,
		Inst_vgatherdpd,
		Inst_vgatherdps,
		Inst_vgatherdq,
		Inst_vgatherqd,
		Inst_vgatherqpd,
		Inst_vgatherqps,
		Inst_vgatherqq,
		Inst_vhaddpd,
		Inst_vhaddps,
		Inst_vhsubpd,
		Inst_vhsubps,
		Inst_vinsertf128,
		Inst_vinserti128,
		Inst_vinsertps,
		Inst_vlddqu,
		Inst_vmaskmovdqu,
		Inst_vmaskmovpd,
		Inst_vmaskmovps,
		Inst_vmaxpd,
		Inst_vmaxps,
		Inst_vmaxsd,
		Inst_vmaxss,
		Inst_vmcall,
		Inst_vmclear,
		Inst_vmfunc,
		Inst_vminpd,
		Inst_vminps,
		Inst_vminsd,
		Inst_vminss,
		Inst_vmlaunch,
		Inst_vmovapd,
		Inst_vmovaps,
		Inst_vmovd,
		Inst_vmovddup,
		Inst_vmovdqa,
		Inst_vmovdqu,
		Inst_vmovhlps,
		Inst_vmovhpd,
		Inst_vmovhps,
		Inst_vmovlhps,
		Inst_vmovlpd,
		Inst_vmovlps,
		Inst_vmovmskpd,
		Inst_vmovmskps,
		Inst_vmovntdq,
		Inst_vmovntdqa,
		Inst_vmovntpd,
		Inst_vmovntps,
		Inst_vmovq,
		Inst_vmovsd,
		Inst_vmovsldup,
		Inst_vmovss,
		Inst_vmovupd,
		Inst_vmovups,
		Inst_vmpsadbw,
		Inst_vmptrld,
		Inst_vmptrst,
		Inst_vmread,
		Inst_vmresume,
		Inst_vmulpd,
		Inst_vmulps,
		Inst_vmulsd,
		Inst_vmulss,
		Inst_vmwrite,
		Inst_vmxoff,
		Inst_vmxon,
		Inst_vorpd,
		Inst_vorps,
		Inst_vpabsb,
		Inst_vpabsd,
		Inst_vpabsw,
		Inst_vpackssdw,
		Inst_vpacksswb,
		Inst_vpackusdw,
		Inst_vpackuswb,
		Inst_vpaddb,
		Inst_vpaddd,
		Inst_vpaddq,
		Inst_vpaddsb,
		Inst_vpaddsw,
		Inst_vpaddusb,
		Inst_vpaddusw,
		Inst_vpaddw,
		Inst_vpalignr,
		Inst_vpand,
		Inst_vpandn,
		Inst_vpavgb,
		Inst_vpavgw,
		Inst_vpblendd,
		Inst_vpblendvb,
		Inst_vpblendw,
		Inst_vpbroadcastb,
		Inst_vpbroadcastd,
		Inst_vpbroadcastq,
		Inst_vpbroadcastw,
		Inst_vpclmulqdq,
		Inst_vpcmpeqb,
		Inst_vpcmpeqd,
		Inst_vpcmpeqq,
		Inst_vpcmpeqw,
		Inst_vpcmpestri,
		Inst_vpcmpestrm,
		Inst_vpcmpgtb,
		Inst_vpcmpgtd,
		Inst_vpcmpgtq,
		Inst_vpcmpgtw,
		Inst_vpcmpistri,
		Inst_vpcmpistrm,
		Inst_vperm2f128,
		Inst_vperm2i128,
		Inst_vpermd,
		Inst_vpermilpd,
		Inst_vpermilps,
		Inst_vpermpd,
		Inst_vpermps,
		Inst_vpermq,
		Inst_vpextrb,
		Inst_vpextrd,
		Inst_vpextrq,
		Inst_vpextrw,
		Inst_vphaddd,
		Inst_vphaddsw,
		Inst_vphaddw,
		Inst_vphminposuw,
		Inst_vphsubd,
		Inst_vphsubsw,
		Inst_vphsubw,
		Inst_vpinsrb,
		Inst_vpinsrd,
		Inst_vpinsrq,
		Inst_vpinsrw,
		Inst_vpmaddubsw,
		Inst_vpmaddwd,
		Inst_vpmaskmovd,
		Inst_vpmaskmovq,
		Inst_vpmaxsb,
		Inst_vpmaxsd,
		Inst_vpmaxsw,
		Inst_vpmaxub,
		Inst_vpmaxud,
		Inst_vpmaxuw,
		Inst_vpminsb,
		Inst_vpminsd,
		Inst_vpminsw,
		Inst_vpminub,
		Inst_vpminud,
		Inst_vpminuw,
		Inst_vpmovmskb,
		Inst_vpmovsxbd,
		Inst_vpmovsxbq,
		Inst_vpmovsxbw,
		Inst_vpmovsxdq,
		Inst_vpmovsxwd,
		Inst_vpmovsxwq,
		Inst_vpmovzxbd,
		Inst_vpmovzxbq,
		Inst_vpmovzxbw,
		Inst_vpmovzxdq,
		Inst_vpmovzxwd,
		Inst_vpmovzxwq,
		Inst_vpmuldq,
		Inst_vpmulhrsw,
		Inst_vpmulhuw,
		Inst_vpmulhw,
		Inst_vpmulld,
		Inst_vpmullw,
		Inst_vpmuludq,
		Inst_vpor,
		Inst_vpsadbw,
		Inst_vpshufb,
		Inst_vpshufd,
		Inst_vpshufhw,
		Inst_vpshuflw,
		Inst_vpsignb,
		Inst_vpsignd,
		Inst_vpsignw,
		Inst_vpslld,
		Inst_vpslldq,
		Inst_vpsllq,
		Inst_vpsllvd,
		Inst_vpsllvq,
		Inst_vpsllw,
		Inst_vpsrad,
		Inst_vpsravd,
		Inst_vpsraw,
		Inst_vpsrld,
		Inst_vpsrldq,
		Inst_vpsrlq,
		Inst_vpsrlvd,
		Inst_vpsrlvq,
		Inst_vpsrlw,
		Inst_vpsubb,
		Inst_vpsubd,
		Inst_vpsubq,
		Inst_vpsubsb,
		Inst_vpsubsw,
		Inst_vpsubusb,
		Inst_vpsubusw,
		Inst_vpsubw,
		Inst_vptest,
		Inst_vpunpckhbw,
		Inst_vpunpckhdq,
		Inst_vpunpckhqdq,
		Inst_vpunpckhwd,
		Inst_vpunpcklbw,
		Inst_vpunpckldq,
		Inst_vpunpcklqdq,
		Inst_vpunpcklwd,
		Inst_vpxor,
		Inst_vrcpps,
		Inst_vrcpss,
		Inst_vroundpd,
		Inst_vroundps,
		Inst_vroundsd,
		Inst_vroundss,
		Inst_vrsqrtps,
		Inst_vrsqrtss,
		Inst_vshufpd,
		Inst_vshufps,
		Inst_vsqrtpd,
		Inst_vsqrtps,
		Inst_vsqrtsd,
		Inst_vsqrtss,
		Inst_vsubpd,
		Inst_vsubps,
		Inst_vsubsd,
		Inst_vsubss,
		Inst_vtestpd,
		Inst_vtestps,
		Inst_vucomisd,
		Inst_vucomiss,
		Inst_vunpckhpd,
		Inst_vunpckhps,
		Inst_vunpcklpd,
		Inst_vunpcklps,
		Inst_vxorpd,
		Inst_vxorps,
		Inst_wait, // 1
		Inst_fwait,
		Inst_wbinvd,
		Inst_wrfsbase,
		Inst_wrgsbase,
		Inst_wrmsr,
		Inst_xabort,
		Inst_xadd,
		Inst_xbegin,
		Inst_xchg,
		Inst_xend,
		Inst_xgetbv,
		Inst_xlat, // b
		Inst_xor,
		Inst_xrstor,
		Inst_xsave,
		Inst_xsaveopt,
		Inst_xsetbv,
		xtest
	};
#pragma endregion

	// NOTICE：算了，不存，改返回字符串数组（用已存在的字符指针）和指令长度
	// 前缀有一个有效起始位，无效的不起作用
	//typedef struct _Instruction
	//{
	//	// PVOID Start; // 指令起始地址，不需要
	//	BYTE Length;// 指令长度
	//	PVOID EndPrefix;// 前缀结束位置,也是opcode开始地址，无前缀时为指令开始地址
	//	BYTE Opcode1;
	//	BYTE Opcode2;
	//	BYTE Opcode3;


	//}Instruction,*PInstruction;

	BYTE PrefixByteToGroup(BYTE prefix);


	// 表中最小单位, 带命令名字和操作数信息
	typedef	struct _Opcode
	{
		_Opcode() 
		{
			// 未定义
			IsInit = 0;
		}
		// 组号
		_Opcode(USHORT group) 
		{
			// NOTICE:为了过编译暂时用的, 要改
			Type = 0;
		}
		// 表类型(操作数个数)，表行号，行号范围，
		_Opcode(USHORT type,USHORT index,  USHORT range =0)
		{
			IsInit = 1;
			Type = type;
			Index = index;
			Range = range;
		}
		USHORT IsInit : 1; // 0表示无数据, 未初始化
		USHORT Group : 5; // 0为无分组, 否则转到组, [1,18]	[21-23]表示多字节，使用下一个表处理，0为不跳转表, 否则跳转到第n类表[1-3]
		USHORT Range : 1;// 范围内表示同字节不同指令，要靠上标区分, 0为无，1表示下一指令在范围内，最多是1
		USHORT Type:3; // 表类型，以操作数个数区分
		USHORT Index:10; // 操作数描述表下标
		
	}Opcode, *POpcode;
#pragma region 寄存器表结构定义
	typedef struct _RegOrOperand
	{
		/*_RegOrOperand(BYTE regHex, BYTE lenType)
		{
			IsReg = 1;
			Reg.Hex = regHex;
			Reg.LenType = lenType;
		}*/
		_RegOrOperand(BYTE val)
		{
			Val = val;
		}
		_RegOrOperand()
		{
			IsReg = 0;
			OperandInfo = 0;
		}
		union
		{
			struct
			{
				union
				{
					struct
					{
						BYTE Hex : 4;
						BYTE LenType : 3;
					}Reg;
					BYTE OperandInfo : 7;
				};
				BYTE IsReg : 1;
			};
			BYTE Val;
		};
	}RegOrOperand, *PRegOrOperand;
#define MK_REG(hex,type) ((BYTE)((1<<7)|((type&0x70)<<4)|(hex&0x0f)))
#define MK_OP(info) ((BYTE)(info&0x7f))
#define MK_REG_AL MK_REG(0,Len_8)
#define MK_REG_AX MK_REG(0,Len_16)
#define MK_REG_EAX MK_REG(0,Len_32)
#define MK_REG_RAX MK_REG(0,Len_64)
#define MK_REG_MM0 MK_REG(0,Len_64_MM)
#define MK_REG_XMM0 MK_REG(0,Len_128_XMM)
#define MK_REG_CL MK_REG(1,Len_8)
#define MK_REG_CX MK_REG(1,Len_16)
#define MK_REG_ECX MK_REG(1,Len_32)
#define MK_REG_RCX MK_REG(1,Len_64)
#define MK_REG_MM1 MK_REG(1,Len_64_MM)
#define MK_REG_XMM1 MK_REG(1,Len_128_XMM)
#define MK_REG_DL MK_REG(2,Len_8)
#define MK_REG_DX MK_REG(2,Len_16)
#define MK_REG_EDX MK_REG(2,Len_32)
#define MK_REG_RDX MK_REG(2,Len_64)
#define MK_REG_MM2 MK_REG(2,Len_64_MM)
#define MK_REG_XMM2 MK_REG(2,Len_128_XMM)
#define MK_REG_BL MK_REG(3,Len_8)
#define MK_REG_BX MK_REG(3,Len_16)
#define MK_REG_EBX MK_REG(3,Len_32)
#define MK_REG_RBX MK_REG(3,Len_64)
#define MK_REG_MM3 MK_REG(3,Len_64_MM)
#define MK_REG_XMM3 MK_REG(3,Len_128_XMM)
#define MK_REG_AH MK_REG(4,Len_8)
#define MK_REG_SP MK_REG(4,Len_16)
#define MK_REG_ESP MK_REG(4,Len_32)
#define MK_REG_RSP MK_REG(4,Len_64)
#define MK_REG_MM4 MK_REG(4,Len_64_MM)
#define MK_REG_XMM4 MK_REG(4,Len_128_XMM)
#define MK_REG_CH MK_REG(5,Len_8)
#define MK_REG_BP MK_REG(5,Len_16)
#define MK_REG_EBP MK_REG(5,Len_32)
#define MK_REG_RBP MK_REG(5,Len_64)
#define MK_REG_MM5 MK_REG(5,Len_64_MM)
#define MK_REG_XMM5 MK_REG(5,Len_128_XMM)
#define MK_REG_DH MK_REG(6,Len_8)
#define MK_REG_SI MK_REG(6,Len_16)
#define MK_REG_ESI MK_REG(6,Len_32)
#define MK_REG_RSI MK_REG(6,Len_64)
#define MK_REG_MM6 MK_REG(6,Len_64_MM)
#define MK_REG_XMM6 MK_REG(6,Len_128_XMM)
#define MK_REG_BH MK_REG(7,Len_8)
#define MK_REG_DI MK_REG(7,Len_16)
#define MK_REG_EDI MK_REG(7,Len_32)
#define MK_REG_RDI MK_REG(7,Len_64)
#define MK_REG_MM7 MK_REG(7,Len_64_MM)
#define MK_REG_XMM7 MK_REG(7,Len_128_XMM)
#define MK_REG_R8 MK_REG(8,0)
#define MK_REG_XMM8 MK_REG(8,1)
#define MK_REG_R9 MK_REG(9,0)
#define MK_REG_XMM9 MK_REG(9,1)
#define MK_REG_R10 MK_REG(10,0)
#define MK_REG_XMM10 MK_REG(10,1)
#define MK_REG_R11 MK_REG(11,0)
#define MK_REG_XMM11 MK_REG(11,1)
#define MK_REG_R12 MK_REG(12,0)
#define MK_REG_XMM12 MK_REG(12,1)
#define MK_REG_R13 MK_REG(13,0)
#define MK_REG_XMM13 MK_REG(13,1)
#define MK_REG_R14 MK_REG(14,0)
#define MK_REG_XMM14 MK_REG(14,1)
#define MK_REG_R15 MK_REG(15,0)
#define MK_REG_XMM15 MK_REG(15,1)

#pragma endregion

	typedef struct _NoneOperand
	{
		CHAR HasName : 1;// grp用的，暂时
		CHAR Superscript : 4; // 上标，用来区分同字节不同指令
		USHORT NameID : 10;
		CHAR NameRange : 3;
		CHAR SizeOption : 4; // bwdq标识，指令名字后缀可选字符
	}NoneOperand,*PNoneOperand;
	typedef struct _OneOperand
	{
		_OneOperand()
		{}
		USHORT HasName : 1;// grp用的，暂时
		USHORT Superscript:4; // 上标，用来区分同字节不同指令
		USHORT SizeOption : 4; // bwdq标识，add文本中的bwdq表示名字后面可加，具体能加什么还需要设置
		USHORT NameRange : 3; // 索引范围内名字都是同一个指令
		USHORT NameID : 10; // 名字索引
		
		USHORT One:5; // 第一操作数大写信息
		USHORT One2 : 5; // 小写信息

		USHORT Two:5;
		USHORT Two2 : 5;
	}OneOperand, *POneOperand;
	typedef struct _TwoOperands
	{
		// 如果有一操作数为寄存器，低位在64位的时候使用，64位低位下标从1开始，0为不使用
		_TwoOperands(USHORT nameID,CHAR oh,CHAR ol,CHAR to,CHAR tl, USHORT nameRange = 0)
		{
			
			HasName = 1;
			NameID = nameID;
			NameRange = nameRange;
			OneH = oh;
		}
		// NOTICE: 这个寄存器个数有问题，还有一些没写进去
		CHAR HasName : 1;// grp用的，暂时
		CHAR Superscript : 4; // 上标，用来区分同字节不同指令
		USHORT NameID:10;
		CHAR NameRange : 3;
		CHAR SizeOption : 4; // bwdq标识，指令名字后缀可选字符
		RegOrOperand OneH; // 第一操作数大写信息，可能会包含寄存器信息
		RegOrOperand OneL; // 如果这一位也为寄存器则表示或的关系
		RegOrOperand TwoH;
		RegOrOperand TwoL;
		// DONEXT:操作数的描述部分需要看怎么才能跟寄存器的合在一起 
	}TwoOperands,*PTwoOperands;

	//typedef struct _Info
	//{
	//	_Info(PCSTR operand)
	//	{
	//		Operand = operand;
	//		//Group = -1;
	//	}
	//	//INT8 Group;
	//	PCSTR Operand;
	//}Info, *PInfo;
	




	// 名字id，每个操作数的信息
	const TwoOperands Opcode_2[] =
	{
		// 0 add
		{ Inst_add,		MK_OP(H_E),		MK_OP(L_b),			MK_OP(H_G),			MK_OP(L_b) },
		{ Inst_add,		MK_OP(H_E),		MK_OP(L_v),			MK_OP(H_G),			MK_OP(L_v) },
		{ Inst_add,		MK_OP(H_G),		MK_OP(L_b),			MK_OP(H_E),			MK_OP(L_b) },
		{ Inst_add,		MK_OP(H_G),		MK_OP(L_v),			MK_OP(H_E),			MK_OP(L_v) },
		{ Inst_add,		MK_REG_AL,		NULL,				MK_OP(H_L),			MK_OP(L_b) },
		{ Inst_add,		MK_REG_RAX,		NULL,				MK_OP(H_I),			MK_OP(L_z) },
		// 6 adc
		{ Inst_adc,		MK_OP(H_E),		MK_OP(L_b),			MK_OP(H_G),			MK_OP(L_b) },
		{ Inst_adc,		MK_OP(H_E),		MK_OP(L_v),			MK_OP(H_G),			MK_OP(L_v) },
		{ Inst_adc,		MK_OP(H_G),		MK_OP(L_b),			MK_OP(H_E),			MK_OP(L_b) },
		{ Inst_adc,		MK_OP(H_G),		MK_OP(L_v),			MK_OP(H_E),			MK_OP(L_v) },
		{ Inst_adc,		MK_REG_AL,		NULL,				MK_OP(H_L),			MK_OP(L_b) },
		{ Inst_adc,		MK_REG_RAX,		NULL,				MK_OP(H_I),			MK_OP(L_z) },
		// 12 and
		{ Inst_and,		MK_OP(H_E),		MK_OP(L_b),			MK_OP(H_G),			MK_OP(L_b) },
		{ Inst_and,		MK_OP(H_E),		MK_OP(L_v),			MK_OP(H_G),			MK_OP(L_v) },
		{ Inst_and,		MK_OP(H_G),		MK_OP(L_b),			MK_OP(H_E),			MK_OP(L_b) },
		{ Inst_and,		MK_OP(H_G),		MK_OP(L_v),			MK_OP(H_E),			MK_OP(L_v) },
		{ Inst_and,		MK_REG_AL,		NULL,				MK_OP(H_L),			MK_OP(L_b) },
		{ Inst_and,		MK_REG_RAX,		NULL,				MK_OP(H_I),			MK_OP(L_z) },
		// 18 xor
		{ Inst_xor,		MK_OP(H_E),		MK_OP(L_b),			MK_OP(H_G),			MK_OP(L_b) },
		{ Inst_xor,		MK_OP(H_E),		MK_OP(L_v),			MK_OP(H_G),			MK_OP(L_v) },
		{ Inst_xor,		MK_OP(H_G),		MK_OP(L_b),			MK_OP(H_E),			MK_OP(L_b) },
		{ Inst_xor,		MK_OP(H_G),		MK_OP(L_v),			MK_OP(H_E),			MK_OP(L_v) },
		{ Inst_xor,		MK_REG_AL,		NULL,				MK_OP(H_L),			MK_OP(L_b) },
		{ Inst_xor,		MK_REG_RAX,		NULL,				MK_OP(H_I),			MK_OP(L_z) },
		// 19 bound
		{ Inst_bound,	MK_OP(H_G),		MK_OP(L_v),			MK_OP(H_M),			MK_OP(L_a) },
		// 20 arpl
		{ Inst_arpl,	MK_OP(H_E),		MK_OP(L_w),			MK_OP(H_G),			MK_OP(L_w) },
		// 21 movsxd
		{ Inst_movsxd,	MK_OP(H_G),		MK_OP(L_v),			MK_OP(H_E),			MK_OP(L_v) },
		// 22 test
		{ Inst_test,	MK_OP(H_E),		MK_OP(L_b),			MK_OP(H_G),			MK_OP(L_b) },
		{ Inst_test,	MK_OP(H_E),		MK_OP(L_v),			MK_OP(H_G),			MK_OP(L_v) },
		// 24 xchg
		{ Inst_xchg,	MK_OP(H_E),		MK_OP(L_b),			MK_OP(H_G),			MK_OP(L_b) },
		{ Inst_xchg,	MK_OP(H_E),		MK_OP(L_v),			MK_OP(H_G),			MK_OP(L_v) },
		// 26 mov
		{ Inst_mov,		MK_REG_AL,		NULL,				MK_OP(H_O),			MK_OP(L_b) },
		{ Inst_mov,		MK_REG_RAX,		NULL,				MK_OP(H_O),			MK_OP(L_v) },
		{ Inst_mov,		MK_OP(H_O),		MK_OP(L_b),			MK_REG_AL,			NULL },
		{ Inst_mov,		MK_OP(H_O),		MK_OP(L_v),			MK_REG_RAX,			NULL },
		// 30 movs(b w d q)
		{ Inst_movs,	MK_OP(H_Y),		MK_OP(L_b),			MK_OP(H_X),			MK_OP(L_b), },
		{ Inst_movs,	MK_OP(H_Y),		MK_OP(L_v),			MK_OP(H_X),			MK_OP(L_v), },
		// 31 cmps(b w d q)
		{ Inst_cmps,	MK_OP(H_Y),		MK_OP(L_b),			MK_OP(H_X),			MK_OP(L_b), },
		{ Inst_cmps,	MK_OP(H_Y),		MK_OP(L_v),			MK_OP(H_X),			MK_OP(L_v), },
		// 32 mov
		{ Inst_mov,		MK_REG_RAX,		NULL,				MK_OP(H_I),			MK_OP(L_b) },
	};

	// 表类型(操作数个数)，行号，行号范围，
	const Opcode OneByteOpcodeMap[0x100] =
	{
		// 00-0f
		{ 2,0 }, { 2,1 }, { 2,2 }, { 2,3 }, { 2,4 }, { 2,5 },/* add */{ 0 },/* push es */{ 0 },/* pop es */
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },/* or */{ 0 }, /* push cs */{ 0 },/* 2B */

		// 10-1f

		{ 2,6 },{ 2,7 },{ 2,8 },{ 2,9 },{ 2,10 },{ 2,11 },/* adc */{ 0 },/* push ss */{ 0 },/* pop ss */
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },/* sbb */{ 0 },/* push ds */{ 0 },/* pop ds */

		// 20-2f

		{ 2,12 },{ 2,13 },{ 2,14 },{ 2,15 },{ 2,16 },{ 2,17 },/* and */{ 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },/* sub */{ 0 },/* seg=ds (prefix) */{ 0 },/* das */

		// 30-3f

		{ 2,18 },{ 2,19 },{ 2,20 },{ 2,21 },{ 2,22 },{ 2,23 },/* xor */{ 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },/* cmp */{ 0 },/* seg=ds (prefix) */{ 0 },/* aas */

		// 40-4f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, /* inc */
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },/* dec */

		// 50-5f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, /* push */
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },/* pop */

		// 60-6f

		{ 0 },/* pusha */{ 0 },/* popa */{ 2,19 },/* bound */{ 2,20,1 },/* arpl / movsxd */{ 0 },/* seg=fs (prefix)*/{ 0 },/* seg=gs (prefix) */{ 0 },/* operand size (prefix) */{ 0 },/* address size (prefix) */
		{ 0 }, /* push */{ 0 },/* imul */{ 0 },/* push */{ 0 },/* imul */{ 0 }, { 0 },/* ins */{ 0 }, { 0 },/* outs */

		// 70-7f

		{ 0 },/* jo */{ 0 },/* jno */{ 0 },/* jb */{ 0 },/* jnb */{ 0 }, /* jz */{ 0 },/* jnz */{ 0 }, /* jbe */{ 0 }, /* ja */
		{ 0 }, /* js */{ 0 },/* jns */{ 0 },/* jp */{ 0 },/* jnp */{ 0 },/* jl */{ 0 },/* jnl */{ 0 },/* jng */{ 0 },/* jg */

		// 80-8f

		{ 0 }, { 0 }, { 0 }, { 0 },/* grp 1 */{ 2,22 }, { 2,23 }, /* test */{ 0 }, { 0 },/* xchg */
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 },/* mov */{ 0 },/* lea */{ 0 }, /* mov */{ 0 },/* grp1 */

		// 90-9f

		{ 0 },/* nop */{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },/* xchg */
		{ 0 }, /* cbw */{ 0 },/* cwd */{ 0 },/* call */{ 0 },/* wait */{ 0 },/* pushf/d/q */{ 0 },/* popf/d/q */{ 0 },/* sahf */{ 0 },/* lahf */

		// a0-af

		{ 0 }, { 0 }, { 0 }, { 0 }, /* mov */{ 0 },/* movs/b */{ 0 },/* movs/w/d/q */{ 0 },/* cmps/b */{ 0 },/* cmps/w/d */
		{ 0 }, { 0 }, /* test */{ 0 }, /* stos/b */{ 0 },/* stos/w/d/q */{ 0 },/* lods/b */{ 0 },/* lods/w/d/q */{ 0 },/* scas/b */{ 0 },/* scas/w/d/q */

		// b0-bf

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },/* mov */
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },/* mov */

		// c0-cf

		{ 0 }, { 0 },/* grp2 */{ 0 }, { 0 },/* ret */{ 0 },/* les */{ 0 },/* lds */{ 0 }, { 0 },/* grp 11 */
		{ 0 }, /* enter */{ 0 },/* leave */{ 0 }, { 0 },/* ret */{ 0 },/* int 3 */{ 0 },/* int */{ 0 },/* into */{ 0 },/* iret/d/q */

		// d0-df

		{ 0 }, { 0 }, { 0 }, { 0 },/* grp2 */{ 0 },/* aam */{ 0 },/* aad */{ 0 },/* salc */{ 0 },/* xlat */
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },/* esc */

		// e0-ef

		{ 0 },/* loopne */{ 0 },/* loope */{ 0 }, /* loop */{ 0 },/* jrcxz */{ 0 }, { 0 },/* in */{ 0 }, { 0 },/* out */
		{ 0 }, /* call */{ 0 }, { 0 }, { 0 },/* jmp */{ 0 }, { 0 },/* in */{ 0 }, { 0 },/* out */

		// f0-ff

		{ 0 }, /* lock(prefix) */{ 0 }, /* int1 */{ 0 },/* repne */{ 0 }, /* rep */{ 0 }, /* hlt */{ 0 },/* cmc */{ 0 }, { 0 },/* grp3 */
		{ 0 },/* clc */{ 0 },/* stc */{ 0 }, /* cli */{ 0 },/* sti */{ 0 },/* cld */{ 0 },/* std */{ 0 },/* grp4 */{ 0 },/* grp5 */

	};


	const Opcode TwoByteOpcodeMap[0x100] =
	{
		// 00-0f

		{ 0 },/* grp6 */{ 0 },/* grp7 */{ 0 }, /* lar */{ 0 },/* lsl */ { 0 },/* ??? */ { 0 },/* syscall */ { 0 },/* clts */ { 0 },/* sysret */
		{ 0 },/* invd */{ 0 },/* wbinvd */{ 0 },/* ??? */{ 0 }, /* ud2 */{ 0 }, /* ??? */{ 0 },/* prefetchw */ { 0 }, { 0 },/* ??? */

		// 10-1f

		{ 0 }, { 0 },/* vmovups */{ 0 }, { 0 },/* vmovlps */{ 0 }, /* vunpcklps */{ 0 }, /* vunpckhps */{ 0 }, { 0 },/* vmovhps */
		{ 0 },/* grp16 */ { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },/* ??? */ { 0 },/* nop */

		// 20-2f

		{ 0 }, { 0 }, { 0 }, { 0 },/* mov */ { 0 }, { 0 }, { 0 }, { 0 },/* ??? */
		{ 0 }, { 0 }, /* vmovaps */{ 0 }, /* cvtpi2ps */{ 0 },/* vmovntps */{ 0 },/* cvttps2pi */{ 0 }, /* cvtps2pi */{ 0 },/* vucomiss */ { 0 },/* vcomiss */

		// 30-3f

		{ 0 },/* wrmsr */{ 0 },/* rdtsc */{ 0 },/* rdmsr */{ 0 }, /* rdpmc */{ 0 },/* sysenter */ { 0 },/* sysexit */ { 0 },/* ??? */ { 0 },/* getsec */
		{ 0 },/* 3B */{ 0 },/* ??? */{ 0 }, /* 3B */{ 0 }, { 0 }, { 0 }, { 0 }, { 0 },/* ??? */

		// 40-4f

		{ 0 },{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },/* cmov */
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },/* cmov */

		// 50-5f

		{ 0 },/* vmovmskps */{ 0 },/* vsqrtps */{ 0 }, /* vrsqrtps */{ 0 },/* vrcpps */{ 0 },/* vandps */{ 0 },/* vandnps */{ 0 }, /* vorps */{ 0 },/* vxorps */
		{ 0 }, /* vaddps */{ 0 },/* vmulps */{ 0 },/* vcvtps2pd */{ 0 },/* vcvtdq2ps */{ 0 },/* vsubps */{ 0 },/* vminps */{ 0 }, /* vdivps */{ 0 },/* vmaxps */

		// 60-6f

		{ 0 },/* punpcklbw */{ 0 },/* punpcklwd */{ 0 },/* punpckldq */{ 0 }, /* packsswb */{ 0 }, /* pcmpgtb */{ 0 }, /* pcmpgtw */{ 0 }, /* pcmpgtd */{ 0 },/* packuswb */
		{ 0 },/* punpckhbw */ { 0 },/* punpckhwd */ { 0 },/* punpckhdq */ { 0 },/* packssdw */ { 0 }, { 0 },/* ??? */ { 0 },/* movd/q */ { 0 },/* movq */

		// 70-7f

		{ 0 }, /* pshufw */{ 0 },/* grp12 */{ 0 }, /* grp13 */{ 0 },/* grp14 */ { 0 },/* pcmpeqb */ { 0 },/* pcmpeqw */ { 0 },/* pcmpeqd */ { 0 },/* emms */
		{ 0 }, /* vmread */{ 0 },/* vmwrite */{ 0 }, { 0 }, { 0 }, { 0 }, /* ??? */{ 0 }, /* movd/q */{ 0 },/* movq */

		// 80-8f

		{ 0 },/* jo */{ 0 },/* jno */{ 0 },/* jb */{ 0 },/* jnb */{ 0 },/* jz */{ 0 }, /* jnz */{ 0 },/* jbe */ { 0 },/* ja */
		{ 0 }, /* js */{ 0 },/* jns */{ 0 },/* jp */{ 0 },/* jnp */{ 0 },/* jl */{ 0 }, /* jnl */{ 0 },/* jng */ { 0 },/* jg */

		// 90-9f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },/* set */
		{ 0 },/* sets */ { 0 },/* setns */ { 0 },/* setp */ { 0 },/* setnp */ { 0 },/* setl */ { 0 },/* setnl */ { 0 },/* setng */ { 0 },/* setg */

		// a0-af

		{ 0 },/* push fs */{ 0 },/* pop fs */{ 0 },/* cpuid */{ 0 }, /* bt */{ 0 }, { 0 }, /* shld */{ 0 }, { 0 },/* ??? */
		{ 0 },/* push gs */ { 0 },/* pop gs */ { 0 },/* rsm */ { 0 },/* bts */ { 0 }, { 0 },/* shrd */ { 0 },/* grp15 */ { 0 },/* imul */

		// b0-bf

		{ 0 }, { 0 }, /* cmpxchg */{ 0 }, /* lss */{ 0 }, /* btr */{ 0 }, /* lfs */{ 0 }, /* lgs */{ 0 }, { 0 },/* movzx */
		{ 0 },/* jmpe */ { 0 },/* grp10 */ { 0 },/* grp8 */ { 0 }, /* btc */ { 0 },/* bsf */ { 0 },/* bsr */ { 0 }, { 0 },/* movsx */

		// c0-cf

		{ 0 }, { 0 },/* xadd */{ 0 },/* vcmpps */{ 0 }, /* movntl */{ 0 }, /* pinsnw */{ 0 },/* pextrw */ { 0 },/* vshufps */ { 0 },/* grp9 */
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },/* bswap */

		// d0-df

		{ 0 }, /* ??? */{ 0 },/* psrlw */{ 0 }, /* psrld */{ 0 },/* psrlq */ { 0 },/* paddq */ { 0 },/* pmullw */ { 0 },/* ??? */ { 0 },/* pmovmskb */
		{ 0 }, /* psubusb */{ 0 },/* psubusw */{ 0 },/* pminub */{ 0 },/* pand */{ 0 },/* paddusb */{ 0 },/* paddusw */{ 0 }, /* pmaxub */{ 0 },/* pandn */

		// e0-ef

		{ 0 },/* pavgb */{ 0 },/* psraw */{ 0 },/* psrad */{ 0 },/* pavgw */{ 0 }, /* pmulhuw */{ 0 }, /* pmulhw */{ 0 }, /* ??? */{ 0 },/* movntq */
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// f0-ff

		{ 0 },/* ??? */{ 0 },/* psllw */{ 0 },/* pslld */{ 0 }, /* psllq */{ 0 },/* pmuludq */ { 0 },/* pmaddwd */ { 0 },/* psadbw */ { 0 },/* maskmovq */
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

	};
	const Opcode TwoByteOpcodeMap_66[0x100] =
	{
		// 00-0f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 10-1f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 20-2f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 30-3f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 40-4f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 50-5f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 60-6f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 70-7f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 80-8f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 90-9f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// a0-af

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// b0-bf

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// c0-cf

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// d0-df

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// e0-ef

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// f0-ff

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

	};
	const Opcode TwoByteOpcodeMap_F3[0x100] =
	{
		// 00-0f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 10-1f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 20-2f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 30-3f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 40-4f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 50-5f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 60-6f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 70-7f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 80-8f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 90-9f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// a0-af

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// b0-bf

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// c0-cf

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// d0-df

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// e0-ef

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// f0-ff

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

	};
	const Opcode TwoByteOpcodeMap_F2[0x100] =
	{
		// 00-0f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 10-1f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 20-2f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 30-3f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 40-4f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 50-5f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 60-6f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 70-7f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 80-8f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// 90-9f

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// a0-af

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// b0-bf

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// c0-cf

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// d0-df

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// e0-ef

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

		// f0-ff

		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
		{ 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },

	};
	UINT8 GetAsmCmdLen(PVOID code); // 返回指令长度, 识别不出返回0

	

	
}