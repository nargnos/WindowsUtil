#pragma once
#include "../Common/Common.h"
namespace PE
{
	template<typename _PeDecoder>
	class DosHeader :public IGetValue<PIMAGE_DOS_HEADER>, public PeStruct<_PeDecoder>
	{
		PIMAGE_DOS_HEADER  dosHeader;
	public:
		friend _PeDecoder;
		DosHeader(_PeDecoder& pe) :PeStructBase(pe)
		{
			dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(peDecoder.GetBase());
		}
		~DosHeader() {}
		inline bool VerifyDosSignature()
		{
			return dosHeader->e_magic == IMAGE_DOS_SIGNATURE;
		}
		inline virtual PIMAGE_DOS_HEADER GetValue() override
		{
			return dosHeader;
		}
		
	};

}