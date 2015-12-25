#include "stdafx.h"
using namespace System;
System::String ^ GetValueSizeStr(int size)
{
	return Enum::GetName(WinSize::typeid, size);
}
