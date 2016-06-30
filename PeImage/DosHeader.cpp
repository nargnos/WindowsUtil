#include "stdafx.h"
#include "DosHeader.h"
#include "DosStub.h"
#include "PeImage.h"
namespace PeDecoder
{
	DosHeader::DosHeader(TDataPtr ptr) :
		DataPtr(ptr)
	{
		assert(ptr);
	}
	bool DosHeader::IsValid() const
	{
		return GetPtr()->e_magic == IMAGE_DOS_SIGNATURE;
	}
	const unique_ptr<DosStub>& DosHeader::GetDosStub()
	{
		assert(IsValid());
		if (!dosStub_)
		{
			// dosHeader和ntHeader之间的范围
			auto ntPtr = reinterpret_cast<unsigned char*>(PeImage::GetNtHeaderPtr(GetPtr()));  // NtHeader位置
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
