#pragma once
#include <Windows.h>
#include "IOptionalHeader.h"
#include "IFileHeader.h"
#include "NtHeaderType.h"

namespace PeDecoder
{
	__interface INtHeader :
		public IFileHeader,
		public IOptionalHeader
	{
		NtHeaderType GetHeaderType() const;
		bool IsValid() const;
		unsigned char* RawPtr() const;
	};
}  // namespace PeDecoder