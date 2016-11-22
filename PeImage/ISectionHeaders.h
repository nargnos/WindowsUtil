#pragma once
#include <Windows.h>
#include "Section.h"
namespace PeDecoder
{
	__interface ISectionHeaders
	{
		Detail::Section* RawPtr() const;
		WORD GetSize() const;
		DWORD GetSectionAlignment() const;

		Detail::Section* RvaToSectionHeader(DWORD rva) const;
		Detail::Section* OffsetToSectionHeader(DWORD fileOffset) const;

		// 为了兼容c++算法，首字母不大写了
		Detail::Section* begin() const;
		// 结尾的下一元素地址
		Detail::Section* end() const;
	};
}  // namespace PeDecoder