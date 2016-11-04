#pragma once
#include "NtHeader.h"
namespace PeDecoder
{
	class NtHeader64 :
		public NtHeader
	{
	public:
		explicit NtHeader64(const PIMAGE_DOS_HEADER dosHeader);
		PIMAGE_NT_HEADERS64 RawPtr() const;
		PIMAGE_OPTIONAL_HEADER64 GetOptionalHeader() const;
		virtual void ReadDetails(const INtHeaderVisitor & visitor) const override;
	};
}  // namespace PeDecoder
