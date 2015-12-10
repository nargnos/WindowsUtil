#include "DosHeader.h"

PE::DosHeader::DosHeader(PeDecoder & pe) :PeStructBase(pe)
{
	dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(peDecoder.GetBase());
}

PE::DosHeader::~DosHeader() {}

bool PE::DosHeader::VerifyDosSignature()
{
	return dosHeader->e_magic == IMAGE_DOS_SIGNATURE;
}

PIMAGE_DOS_HEADER PE::DosHeader::GetValue()
{
	return dosHeader;
}
