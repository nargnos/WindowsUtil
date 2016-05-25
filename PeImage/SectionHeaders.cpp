#include "stdafx.h"
#include "SectionHeaders.h"

namespace PeDecoder
{
	SectionHeaders::SectionHeaders(TDataPtr ptr, TSizePtr sizePtr, PDWORD sectionAlignmentPtr) :
		DataPtr(ptr),
		DataSize(sizePtr),
		sectionAlignmentPtr_(sectionAlignmentPtr)
	{
		assert(ptr);
		assert(sizePtr);
		assert(sectionAlignmentPtr);
	}
	PDWORD SectionHeaders::GetSectionAlignment()
	{
		return sectionAlignmentPtr_;
	}
	SectionHeaders::TDataPtr SectionHeaders::RvaToSectionHeader(DWORD rva)
	{
		auto beginPtr = begin();
		auto endPtr = end();

		auto result = _STD find_if(beginPtr, endPtr, [this, rva](TDataType& val)
		{
			return (rva >= val.VirtualAddress) &&
				(rva < val.VirtualAddress + ALIGN_UP(val.Misc.VirtualSize, *GetSectionAlignment()));
		});
		return result == endPtr ? nullptr : result;
	}
	SectionHeaders::TDataPtr SectionHeaders::OffsetToSectionHeader(DWORD fileOffset)
	{
		auto beginPtr = begin();
		auto endPtr = end();

		auto result = _STD find_if(beginPtr, endPtr, [this, fileOffset](TDataType& val)
		{
			return (fileOffset >= val.PointerToRawData) && (fileOffset < val.PointerToRawData + val.SizeOfRawData);
		});
		return result == endPtr ? nullptr : result;
	}

	SectionHeaders::iterator SectionHeaders::begin() const
	{
		return GetPtr();
	}

	SectionHeaders::iterator SectionHeaders::end() const
	{
		return GetPtr() + GetSize();
	}
}  // namespace PeDecoder
