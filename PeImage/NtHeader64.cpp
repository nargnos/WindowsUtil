#include "stdafx.h"
#include "NtHeader64.h"
#include "DataDirectoryEntries.h"
namespace PeDecoder
{
	NtHeader64::NtHeader64(const PIMAGE_DOS_HEADER dosHeader) :NtHeader(dosHeader) {}
	PIMAGE_NT_HEADERS64 NtHeader64::RawPtr() const
	{
		return static_cast<PIMAGE_NT_HEADERS64>(ptr_);
	}
	PIMAGE_OPTIONAL_HEADER64 NtHeader64::GetOptionalHeader() const
	{
		return &RawPtr()->OptionalHeader;
	}
	void NtHeader64::ReadDetails(const INtHeaderVisitor & visitor) const
	{
		visitor.Visit(*this);
	}

}  // namespace PeDecoder
