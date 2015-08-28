#include "Registers.h"
namespace Asm
{
	const PCSTR Registers[16][6] =
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
		{ "R10L",	"R10W",		"R10D",		"R10",		0,			"XMM10" },
		{ "R11L",	"R11W",		"R11D",		"R11",		0,			"XMM11" },
		{ "R12L",	"R12W",		"R12D",		"R12",		0,			"XMM12" },
		{ "R13L",	"R13W",		"R13D",		"R13",		0,			"XMM13" },
		{ "R14L",	"R14W",		"R14D",		"R14",		0,			"XMM14" },
		{ "R15L",	"R15W",		"R15D",		"R15",		0,			"XMM15" }
	};

	PCSTR GetRegisterName(BYTE hex, RegisterLength type)
	{
		assert(hex < 16 && (BYTE)type < 6);
		assert(hex < 8 ? true : (type != Len_64_MM));
		return Registers[hex][type];
	}
}