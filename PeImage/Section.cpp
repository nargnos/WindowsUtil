#include "stdafx.h"
#include "Section.h"

std::array<BYTE, PeDecoder::Detail::Section::Size>& PeDecoder::Detail::Section::GetNameArray() const
{
	return *reinterpret_cast<_STD array<BYTE, Size>*>(const_cast<BYTE*>(Name));
}

PeDecoder::Detail::SectionCharacteristics PeDecoder::Detail::Section::GetCharacteristics() const
{
	return static_cast<SectionCharacteristics>(Characteristics);
}

bool PeDecoder::Detail::Section::RvaInRange(DWORD rva, DWORD sectionAlignment) const
{
	return (rva >= VirtualAddress) &&
		(rva < VirtualAddress + ALIGN_UP(Misc.VirtualSize, sectionAlignment));
}

bool PeDecoder::Detail::Section::OffsetInRange(DWORD fileOffset, DWORD sectionAlignment) const
{
	return (fileOffset >= PointerToRawData) && (fileOffset < PointerToRawData + SizeOfRawData);
}
