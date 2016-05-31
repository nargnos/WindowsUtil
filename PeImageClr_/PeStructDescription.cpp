#include "stdafx.h"
#include "PeStructDescription.h"

namespace PeImageClr
{
	void PeStructDescription::SetDescription(IntPtr ptr, IntPtr basePtr, int size)
	{
		addr = ptr;
		base = basePtr;
		structSize = size;
	}
	PeStructDescription::PeStructDescription() :StructOffset(IntPtr::Zero, IntPtr::Zero)
	{
		structSize = 0;
	}
	String ^ PeStructDescription::GetDescription()
	{
		if (addr == IntPtr::Zero)
		{
			return String::Empty;
		}
		auto offset = Offset.ToString("X" + 2 * IntPtr::Size);
		if (structSize == 0)
		{
			return String::Format("[{0}]", offset);
		}
		return String::Format("[{0} ({1} Bytes)]", offset, structSize);
	}
}  // namespace PeImageClr
