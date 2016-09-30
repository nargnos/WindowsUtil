#include "stdafx.h"
#include "DosHeader.h"
namespace PeDecoder
{
	bool DosHeader::Valid(const TDataPtr ptr)
	{
		assert(ptr);
		return ptr->e_magic == IMAGE_DOS_SIGNATURE;
	}
	void * DosHeader::GetNtHeaderPtr(const PIMAGE_DOS_HEADER dosHeader)
	{
		return reinterpret_cast<unsigned char*>(dosHeader) + dosHeader->e_lfanew;
	}
	const unique_ptr<DosStub>& DosHeader::GetDosStub()
	{
		assert(Valid(GetPtr()));
		if (!dosStub_)
		{
			// dosHeader和ntHeader之间的范围
			auto ntPtr = reinterpret_cast<unsigned char*>(GetNtHeaderPtr(GetPtr()));  // NtHeader位置
			auto ptr = reinterpret_cast<unsigned char*>(GetPtr() + 1); // dosStub应该在的位置
			auto size = ntPtr - ptr; // 实际大小，NtHeader跟DosHeader重叠时（被人为修改）没有DosStub
			if (size > 0)
			{
				dosStub_ = make_unique<DosStub>(ptr, size);
			}
		}
		return dosStub_;
	}
}  // namespace PeDecoder
