#pragma once
namespace PeImageClr
{
	using namespace System;
	public enum class WinSize
	{
		Byte = 1,
		Word = 2,
		Dword = 4,
		Qword = 8
	};

	inline extern System::String^ GetValueSizeStr(int size)
	{
		return Enum::GetName(WinSize::typeid, size);
	}
}  // namespace PeImageClr
