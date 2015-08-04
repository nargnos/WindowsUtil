#include "Opcodes.h"
namespace Asm
{
	UINT8 GetAsmCmdLen(PVOID code)
	{
		return 0;
	}
	BYTE PrefixByteToGroup(BYTE prefix)
	{
		
		switch (prefix)
		{
		case (BYTE)0xf0:
		case (BYTE)0xf2:
		case (BYTE)0xf3:
			return 1;
		case (BYTE)0x2e:
		case (BYTE)0x36:
		case (BYTE)0x3e:
		case (BYTE)0x26:
		case (BYTE)0x64:
		case (BYTE)0x65:
			return 2;
		case (BYTE)0x66:
			return 3;
		case (BYTE)0x67:
			return 4;
		default:
			return 0; // ·Çprefix
		}
	}
}