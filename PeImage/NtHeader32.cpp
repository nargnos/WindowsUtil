#include "stdafx.h"
#include "NtHeader32.h"
#include "DataDirectoryEntries.h"
namespace PeDecoder
{
	NtHeader32::NtHeader32(const PIMAGE_DOS_HEADER dosHeader) :NtHeader(dosHeader)
	{}
	PIMAGE_NT_HEADERS32 NtHeader32::RawPtr() const
	{
		return GetHeader32();
	}
	PIMAGE_OPTIONAL_HEADER32 NtHeader32::GetOptionalHeader() const
	{
		return &GetHeader32()->OptionalHeader;
	}
	void NtHeader32::ReadDetails(const INtHeaderVisitor & visitor) const
	{
		visitor.Visit(*this);
	}
	
}  // namespace PeDecoder
