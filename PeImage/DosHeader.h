#pragma once
#include <Windows.h>
namespace PeDecoder
{
	class DosHeader
	{
	public:
		explicit DosHeader(PIMAGE_DOS_HEADER ptr);
		static bool IsValid(const PIMAGE_DOS_HEADER ptr);

		bool IsValid() const;
		const PIMAGE_DOS_HEADER RawPtr() const;
	protected:
		PIMAGE_DOS_HEADER ptr_;
	};
}  // namespace PeDecoder
