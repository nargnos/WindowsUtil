#include "AsmGenerator.h"

namespace Asm
{
#pragma  pack(push)
#pragma pack(1)
#ifndef _WIN64
#endif
#pragma  pack(pop)

	AsmGenerator::AsmGenerator(PVOID buff, DWORD size)
	{
		assert(buff != NULL);
		binBuff = (PUINT8)buff;
		endBuff = binBuff + size;
		writeCur = oldCur= binBuff;
		isGenerated = false;
		isGenerated = Process::LazyLoad::_VirtualProtect(buff, size, PAGE_EXECUTE_READWRITE, NULL);
	}


	AsmGenerator::~AsmGenerator()
	{
		if (!isGenerated)
		{
			delete[] binBuff;
		}
	}
	template<typename T>
	T AsmGenerator::GetCode()
	{
		return (T)binBuff;
	}
	DWORD AsmGenerator::CodeSize()
	{
		return (DWORD)(writeCur-binBuff);
	}
	template<typename T>
	void AsmGenerator::Write(T val)
	{
		if (!isGenerated)
		{
			return;
		}
		assert(sizeof(T) + writeCur <= endBuff);
		oldCur = writeCur;
		*(T*)writeCur = val;
		writeCur += sizeof(T);
	}
	bool AsmGenerator::SetWriteCur(PVOID addr)
	{
		bool result = true;
		if (addr<binBuff)
		{
			addr = binBuff;
			result = false;
		}
		if (addr>endBuff)
		{
			addr = endBuff;
			result = false;
		}
		writeCur = (PUINT8)addr;
		return result;
	}
	bool AsmGenerator::MoveWriteCur(DWORD addr)
	{
		auto newAddr = writeCur + addr;
		return SetWriteCur(newAddr);
	}
	void AsmGenerator::SaveCur(OUT PVOID* save)
	{
		if (save)
		{
			*save = writeCur;
		}
	}

	const PUINT8 AsmGenerator::CurrCur()
	{
		return writeCur;
	}
	const PUINT8 AsmGenerator::PrevCur()
	{
		return oldCur;
	}
	/*AsmGenerator& __stdcall  AsmGenerator::Jmp_Short_Address(INT8 pos, OUT PVOID* currentCodeAddr)
	{
		SaveCur(currentCodeAddr);
		Write<UINT8>(0xeb);
		Write(pos);
		return *this;
	}
	AsmGenerator& __stdcall AsmGenerator::Jmp_Address(DWORD address, OUT PVOID* currentCodeAddr)
	{
		auto currentAddr = writeCur;
		SaveCur(currentCodeAddr);
		Write<UINT8>(0xe9);
		Write(address - ((DWORD)currentAddr+5));
		
		return *this;
	}

	AsmGenerator& __stdcall AsmGenerator::Push_Value(DWORD value, OUT PVOID* currentCodeAddr)
	{
		SaveCur(currentCodeAddr);
		Write<UINT8>(0x68);
		Write(value);
		return *this;
	}
	AsmGenerator& __stdcall AsmGenerator::Retn(SHORT value, OUT PVOID* currentCodeAddr)
	{
		SaveCur(currentCodeAddr);
		if (value<0)
		{
			Write<UINT8>(0xc3);
		}
		else
		{
			Write<UINT8>(0xc2);
			Write(value);
		}
		return *this;
	}
	AsmGenerator& __stdcall AsmGenerator::OneByteCmd(UINT8 cmdCode, OUT PVOID* currentCodeAddr)
	{
		SaveCur(currentCodeAddr);
		Write(cmdCode);
		return *this;
	}
	AsmGenerator& __stdcall AsmGenerator::Pushad(OUT PVOID* currentCodeAddr)
	{
		return OneByteCmd(0x60, currentCodeAddr);
	}

	AsmGenerator& __stdcall AsmGenerator::Cld(OUT PVOID* currentCodeAddr)
	{
		return OneByteCmd(0xfc, currentCodeAddr);
	}
	AsmGenerator& __stdcall AsmGenerator::Nop(OUT PVOID* currentCodeAddr)
	{
		return OneByteCmd(0x90, currentCodeAddr);
	}*/

	template<typename T>
	AsmGenerator& __stdcall AsmGenerator::Emit(T val, OUT PVOID* currentCodeAddr)
	{
		SaveCur(currentCodeAddr);
		Write(val);
		return *this;
	}

	template<typename T>
	AsmGenerator& __stdcall  AsmGenerator::operator<<(T val)
	{
		Write(val);
		return *this;
	}
}