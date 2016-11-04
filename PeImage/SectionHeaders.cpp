#include "stdafx.h"
#include "SectionHeaders.h"
#include "NtHeader.h"
#include "NtHeader32.h"
#include "NtHeader64.h"
#include "INtHeaderVisitor.h"
namespace PeDecoder
{


	SectionHeaders::SectionHeaders(DataPtr ptr, PWORD sizePtr, PDWORD sectionAlignmentPtr) :
		ptr_(ptr),
		sizePtr_(sizePtr),
		alignmentPtr_(sectionAlignmentPtr)
	{
	}
	SectionHeaders::SectionHeaders(const NtHeader & nt) :
		SectionHeaders(nullptr, nullptr, nullptr)
	{
		assert(nt.IsValid());
		auto visitor = MakeNtHeaderVisitor(
			[this](const NtHeader32 & nt)
		{
			auto ptr = nt.RawPtr();
			Set(static_cast<Detail::Section*>(IMAGE_FIRST_SECTION(ptr)),
				&ptr->FileHeader.NumberOfSections,
				&ptr->OptionalHeader.SectionAlignment);
		},
			[this](const NtHeader64 & nt)
		{
			auto ptr = nt.RawPtr();
			Set(static_cast<Detail::Section*>(IMAGE_FIRST_SECTION(ptr)),
				&ptr->FileHeader.NumberOfSections,
				&ptr->OptionalHeader.SectionAlignment);
		});
		nt.ReadDetails(visitor);
	}
	DWORD SectionHeaders::GetSectionAlignment() const
	{
		assert(alignmentPtr_);
		return *alignmentPtr_;
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
	void SectionHeaders::Set(DataPtr ptr, PWORD sizePtr, PDWORD sectionAlignmentPtr)
	{
		sizePtr_ = sizePtr;
		ptr_ = ptr;
		alignmentPtr_ = sectionAlignmentPtr;
	}
	SectionHeaders::DataPtr SectionHeaders::RawPtr() const
	{
		return ptr_;
	}
	WORD SectionHeaders::GetSize() const
	{
		assert(sizePtr_);
		return *sizePtr_;
	}
	WORD SectionHeaders::size() const
	{
		return GetSize();
	}
}  // namespace PeDecoder
