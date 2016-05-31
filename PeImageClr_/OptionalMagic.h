#pragma once
#include <Windows.h>
#include <WinBase.h>
#include "EnumHexConverter.h"
namespace PeImageClr
{
	using namespace System::ComponentModel;

	[TypeConverter(EnumHexConverter::typeid)]
	public enum class OptionalMagic :WORD
	{
		[BrowsableAttribute(false)]
	UNKNOWN = 0,
		NT_HDR32 = IMAGE_NT_OPTIONAL_HDR32_MAGIC,
		NT_HDR64 = IMAGE_NT_OPTIONAL_HDR64_MAGIC,
		ROM_HDR = IMAGE_ROM_OPTIONAL_HDR_MAGIC
	};
}  // namespace PeImageClr
