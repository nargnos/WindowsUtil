#include "stdafx.h"
#include "SectionHeaders.h"
#include "PeImage.h"
#include "NtHeader.h"

namespace PeDecoder
{
	SectionHeaders::SectionHeaders(TDataPtr ptr, TSizePtr sizePtr, PDWORD sectionAlignmentPtr) :
		DataPtr(ptr),
		DataSize(sizePtr),
		sectionAlignmentPtr_(sectionAlignmentPtr)
	{
	}
	SectionHeaders::SectionHeaders(const PeImage & pe) :
		SectionHeaders(nullptr, nullptr, nullptr)
	{
		if (pe.IsPe())
		{
			auto& ntHeader = pe.GetNtHeader();
			switch (NtHeader::GetHeaderType(ntHeader->GetPtr32()))
			{
			case NtHeaderType::NtHeader32:
			{
				auto tmpHeader = ntHeader->GetPtr32();
				SetPtr(IMAGE_FIRST_SECTION(tmpHeader));
				SetSizePtr(&tmpHeader->FileHeader.NumberOfSections);
				sectionAlignmentPtr_ = &tmpHeader->OptionalHeader.SectionAlignment;
			}
			break;
			case NtHeaderType::NtHeader64:
			{
				auto tmpHeader = ntHeader->GetPtr64();
				SetPtr(IMAGE_FIRST_SECTION(tmpHeader));
				SetSizePtr(&tmpHeader->FileHeader.NumberOfSections);
				sectionAlignmentPtr_ = &tmpHeader->OptionalHeader.SectionAlignment;
			}
			break;
			default:
				assert(false);
				__assume(false);
				break;
			}
		}
	}
	PDWORD SectionHeaders::GetSectionAlignment() const
	{
		assert(sectionAlignmentPtr_);
		return sectionAlignmentPtr_;
	}
	SectionHeaders::TDataPtr SectionHeaders::RvaToSectionHeader(DWORD rva) const
	{
		auto beginPtr = begin();
		auto endPtr = end();

		auto result = _STD find_if(beginPtr, endPtr, [this, rva, align = *GetSectionAlignment()](const iterator::value_type& val)
		{
			return val.RvaInRange(rva, align);
		});
		return result == endPtr ? nullptr : &*result;
	}
	SectionHeaders::TDataPtr SectionHeaders::OffsetToSectionHeader(DWORD fileOffset) const
	{
		auto beginPtr = begin();
		auto endPtr = end();

		auto result = _STD find_if(beginPtr, endPtr, [this, fileOffset, align = *GetSectionAlignment()](const iterator::value_type& val)
		{
			return val.OffsetInRange(fileOffset,align);
		});
		return result == endPtr ? nullptr : &*result;
	}

	SectionHeaders::iterator SectionHeaders::begin() const
	{
		return{ GetPtr(),GetSize() };
	}

	SectionHeaders::iterator SectionHeaders::end() const
	{
		return{ GetPtr() + GetSize(),GetSize() };
	}
}  // namespace PeDecoder
