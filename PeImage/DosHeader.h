#pragma once
#include "IDosHeader.h"
namespace PeDecoder
{
	class DosHeader :
		public IDosHeader
	{
	public:
		static bool IsValid(const PIMAGE_DOS_HEADER ptr);
		static _STD unique_ptr<IDosHeader> Create(const PIMAGE_DOS_HEADER rawptr);
		virtual bool IsValid() const override;
		virtual PIMAGE_DOS_HEADER RawPtr() const override;
		virtual ~DosHeader();
	protected:
		DosHeader(const DosHeader&) = delete;
		DosHeader& operator=(const DosHeader&) = delete;
		explicit DosHeader(PIMAGE_DOS_HEADER ptr);
		PIMAGE_DOS_HEADER ptr_;
	};
}  // namespace PeDecoder
