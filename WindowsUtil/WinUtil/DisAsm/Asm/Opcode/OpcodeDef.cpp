#include "OpcodeDef.h"
#include <assert.h>
const char* Registers[16][6] =
{
	{ "al",		"ax",		"eax",		"rax",		"mm0",		"xmm0" },
	{ "cl",		"cx",		"ecx",		"rcx",		"mm1",		"xmm1" },
	{ "dl",		"dx",		"edx",		"rdx",		"mm2",		"xmm2" },
	{ "bl",		"bx",		"ebx",		"rbx",		"mm3",		"xmm3" },
	{ "ah",		"sp",		"esp",		"rsp",		"mm4",		"xmm4" },
	{ "ch",		"bp",		"ebp",		"rbp",		"mm5",		"xmm5" },
	{ "dh",		"si",		"esi",		"rsi",		"mm6",		"xmm6" },
	{ "bh",		"di",		"edi",		"rdi",		"mm7",		"xmm7" },
	{ "r8l",	"r8w",		"r8d",		"r8",		0,			"xmm8" },
	{ "r9l",	"r9w",		"r9d",		"r9",		0,			"xmm9" },
	{ "r10l",	"r10w",		"r10d",		"r10",		"cs",		"xmm10" },
	{ "r11l",	"r11w",		"r11d",		"r11",		"ds",		"xmm11" },
	{ "r12l",	"r12w",		"r12d",		"r12",		"es",		"xmm12" },
	{ "r13l",	"r13w",		"r13d",		"r13",		"fs",		"xmm13" },
	{ "r14l",	"r14w",		"r14d",		"r14",		"gs",		"xmm14" },
	{ "r15l",	"r15w",		"r15d",		"r15",		"ss",		"xmm15" }
};