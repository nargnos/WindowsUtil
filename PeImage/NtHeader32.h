#pragma once
#include "NtHeader.h"
namespace PeDecoder
{

	class NtHeader32 :
		public NtHeader
	{
	public:
		explicit NtHeader32(const PIMAGE_DOS_HEADER dosHeader);
		PIMAGE_NT_HEADERS32 RawPtr() const;
		PIMAGE_OPTIONAL_HEADER32 GetOptionalHeader() const;
		virtual void ReadDetails(const INtHeaderVisitor & visitor) const override;
	};

}  // namespace PeDecoder
