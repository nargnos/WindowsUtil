#pragma once
#include "SectionIterator.h"
namespace PeDecoder
{
	namespace Detail
	{
		struct Section;
	}
	class NtHeader;
	class SectionHeaders
	{
	public:
		typedef Detail::Section* DataPtr;
		typedef DataPtr iterator;

		SectionHeaders(DataPtr ptr, PWORD sizePtr, PDWORD sectionAlignmentPtr);
		explicit SectionHeaders(const NtHeader& nt);

		WORD size() const;

		DataPtr RawPtr() const;
		WORD GetSize() const;
		DWORD GetSectionAlignment() const;

		DataPtr RvaToSectionHeader(DWORD rva) const;
		DataPtr OffsetToSectionHeader(DWORD fileOffset) const;

		// 为了兼容c++算法，首字母不大写了
		iterator begin() const;
		// 结尾的下一元素地址
		iterator end() const;

	protected:
		void Set(DataPtr ptr, PWORD sizePtr, PDWORD sectionAlignmentPtr);
		PWORD sizePtr_;
		PDWORD alignmentPtr_;
		DataPtr ptr_;
	};

}  // namespace PeDecoder
