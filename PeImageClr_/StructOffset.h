#pragma once
#include "WinSize.h"
#include "ValueConverter.h"
namespace PeImageClr
{
	using namespace System;
	using namespace System::ComponentModel;
	public ref class  StructOffset
	{
	protected:
		IntPtr base;
		IntPtr addr;
	public:
		StructOffset(IntPtr addr, IntPtr base);
		// 相对于文件开头的偏移量
		[TypeConverter(ValueConverter::typeid)]
		property IntPtr Offset
		{
			IntPtr get()
			{
				switch (IntPtr::Size)
				{
				case sizeof(DWORD32) :
					return IntPtr(addr.ToInt32() - base.ToInt32());
				case sizeof(DWORD64) :
					return IntPtr(addr.ToInt64() - base.ToInt64());
				default:
					throw gcnew System::InvalidCastException();
				}

			}
		}

	};
}  // namespace PeImageClr
