#pragma once
#include "IDosHeader.h"
namespace PeDecoder
{
	class DosHeader :
		public IDosHeader
	{
	public:
		explicit DosHeader(PIMAGE_DOS_HEADER ptr);
		static bool IsValid(const PIMAGE_DOS_HEADER ptr);

		virtual bool IsValid() const override;
		virtual PIMAGE_DOS_HEADER RawPtr() const override;
	protected:
		PIMAGE_DOS_HEADER ptr_;
	};
}  // namespace PeDecoder
