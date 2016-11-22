#pragma once

#include <Windows.h>
namespace PeDecoder
{

	__interface IDosHeader
	{
		bool IsValid() const;
		PIMAGE_DOS_HEADER RawPtr() const;
	};
}