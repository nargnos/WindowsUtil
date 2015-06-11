#pragma once
#include <Windows.h>
#include <WinBase.h>
class PeDecoder
{
public:

	PeDecoder(PCHAR fileBuffer):
		base(fileBuffer),
		isMapped(false)
	{
	}
	PeDecoder(HMODULE module): 
		base((PCHAR)module),
		isMapped(true)
	{
	}

	PIMAGE_DOS_HEADER DosHeader()
	{
		return reinterpret_cast<PIMAGE_DOS_HEADER>(base);
	}
	bool Is32Image()
	{
	
	}
	PIMAGE_NT_HEADERS32 NtHeader32()
	{
	
	}

	~PeDecoder()
	{
	}
private:
	PCHAR base;
	bool isMapped;

};

