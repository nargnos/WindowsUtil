#pragma once
#include <Windows.h>
#include "DataPtr.h"
namespace PeDecoder
{
	class DosHeader:
		public Detail::DataPtr<PIMAGE_DOS_HEADER>
	{
	public:
		using DataPtr::DataPtr;
		static bool Valid(const PIMAGE_DOS_HEADER ptr);

		bool Valid() const;
	};
}  // namespace PeDecoder
