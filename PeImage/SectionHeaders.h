#pragma once
#include "DataPtr.h"
#include "DataSize.h"
#include "SectionIterator.h"
#include "IPeImage.h"
namespace PeDecoder
{

	class SectionHeaders :
		public Detail::DataPtr<PIMAGE_SECTION_HEADER>,
		public Detail::DataSize<PWORD>
	{
	public:
		typedef Detail::SectionIterator iterator;
		SectionHeaders(TDataPtr ptr, TSizePtr sizePtr, PDWORD sectionAlignmentPtr);
		explicit SectionHeaders(const IPeImage& pe);
		PDWORD GetSectionAlignment() const;

		TDataPtr RvaToSectionHeader(DWORD rva) const;
		TDataPtr OffsetToSectionHeader(DWORD fileOffset) const;

		// 为了兼容c++算法，首字母不大写了
		iterator begin() const;
		// 结尾的下一元素地址
		iterator end() const;

	protected:
		// 必须保存来源，以提供修改
		PDWORD sectionAlignmentPtr_;
	};

}  // namespace PeDecoder
