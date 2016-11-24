#include "stdafx.h"
#include "SectionHeaders.h"
#include "PeImage.h"
#include "NtHeader.h"
namespace PeDecoder
{
	SectionHeaders::SectionHeaders(const PeImage & pe)
	{
		auto& nt = *pe.GetNtHeader();
		assert(nt.IsValid());
		size_ = nt.GetNumberOfSections();
		alignment_ = nt.GetSectionAlignment();
		ptr_ = static_cast<Detail::Section*>(nt.GetSectionHeaderPtr());
	}
	DWORD SectionHeaders::GetSectionAlignment() const
	{
		return alignment_;
	}
	SectionHeaders::DataPtr SectionHeaders::RvaToSectionHeader(DWORD rva) const
	{
		auto beginPtr = begin();
		auto endPtr = end();

		auto result = _STD find_if(beginPtr, endPtr, [this, rva, align = GetSectionAlignment()](const Detail::Section& val)
		{
			return val.RvaInRange(rva, align);
		});
		return result == endPtr ? nullptr : &*result;
	}
	SectionHeaders::DataPtr SectionHeaders::OffsetToSectionHeader(DWORD fileOffset) const
	{
		auto beginPtr = begin();
		auto endPtr = end();

		auto result = _STD find_if(beginPtr, endPtr, [this, fileOffset, align = GetSectionAlignment()](const Detail::Section& val)
		{
			return val.OffsetInRange(fileOffset, align);
		});
		return result == endPtr ? nullptr : &*result;
	}

	SectionHeaders::iterator SectionHeaders::begin() const
	{
		return{ RawPtr() };
	}

	SectionHeaders::iterator SectionHeaders::end() const
	{
		return{ RawPtr() + GetSize() };
	}
	SectionHeaders::~SectionHeaders()
	{
		ptr_ = nullptr;
	}
	SectionHeaders::DataPtr SectionHeaders::RawPtr() const
	{
		assert(ptr_);
		return ptr_;
	}
	WORD SectionHeaders::GetSize() const
	{
		return size_;
	}
}  // namespace PeDecoder
