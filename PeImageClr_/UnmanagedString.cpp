#include "stdafx.h"
#include "UnmanagedString.h"

namespace PeImageClr
{
	UnmanagedString::UnmanagedString(IntPtr addr, IntPtr base, int strLen) :StructOffset(addr, base), strLen(strLen)
	{
	}
	String ^ UnmanagedString::GetDescription()
	{
		return String;

	}
	array<String^>^ UnmanagedString::GetSortList()
	{
		return UnmanagedValueSort::GetSortList();
	}
}  // namespace PeImageClr
