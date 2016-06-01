#include "OpcodeDef.h"
#include <assert.h>
// 用指针更费空间, 节省空间把段寄存器标识隐藏在表里，并把跟ah、bh、dh、bh重合的寄存器放在空的地方
// 这里的顺序是按RM表来的，不要换
const char Registers[16][6][6] =
{
	{ "al\0cs",		"ax",		"eax",		"rax",		"mm0",		"xmm0" },
	{ "cl\0ds",		"cx",		"ecx",		"rcx",		"mm1",		"xmm1" },
	{ "dl\0es",		"dx",		"edx",		"rdx",		"mm2",		"xmm2" },
	{ "bl\0fs",		"bx",		"ebx",		"rbx",		"mm3",		"xmm3" },
	{ "ah\0gs",		"sp",		"esp",		"rsp",		"mm4",		"xmm4" },
	{ "ch\0ss",		"bp",		"ebp",		"rbp",		"mm5",		"xmm5" },
	{ "dh",			"si",		"esi",		"rsi",		"mm6",		"xmm6" },
	{ "bh",			"di",		"edi",		"rdi",		"mm7",		"xmm7" },
	{ "r8l",		"r8w",		"r8d",		"r8",		"spl",		"xmm8" },
	{ "r9l",		"r9w",		"r9d",		"r9",		"bpl",		"xmm9" },
	{ "r10l",		"r10w",		"r10d",		"r10",		"sil",		"xmm10" },
	{ "r11l",		"r11w",		"r11d",		"r11",		"dil",		"xmm11" },
	{ "r12l",		"r12w",		"r12d",		"r12",		"error",	"xmm12" },
	{ "r13l",		"r13w",		"r13d",		"r13",		"error",	"xmm13" },
	{ "r14l",		"r14w",		"r14d",		"r14",		"error",	"xmm14" },
	{ "r15l",		"r15w",		"r15d",		"r15",		"error",	"xmm15" },
};
const SizeAttribute EffectiveMode64[2][2][2][2] =
{
	{
		{ { Bit32,Bit64 },{ Bit32,Bit32 } },
		{ { Bit16,Bit64 },{ Bit16,Bit32 } },
	},
	{
		{ { Bit64,Bit64 },{ Bit64,Bit32 } },
		{ { Bit64,Bit64 },{ Bit64,Bit32 } },
	}
};
const SizeAttribute EffectiveMode32[2][2][2] =
{
	{ { Bit32,Bit32 },{ Bit32,Bit16 } },
	{ { Bit16,Bit32 },{ Bit16,Bit16 } },
};
// TODO: 缺cr、dr