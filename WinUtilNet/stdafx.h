#pragma once

#include <PE\PeImage.h>
#define NAMESPACE WinUtilWapper
namespace NAMESPACE {

	using namespace System;
	using namespace System::Diagnostics;
	using namespace System::Runtime::InteropServices;
	using namespace System::ComponentModel;
}
public enum class WinSize
{
	Byte = 1,
	Word = 2,
	Dword = 4,
	Qword = 8
};

extern System::String^ GetValueSizeStr(int size);
#include "UITypeEditor.h"
#include "UnmanagedWrite.h"
#include "Converters.h"
#include "UnmanagedWapper.h"
#include "UnmanagedArray.h"
#include "UnmanagedValue.h"
#include "PeStructWapper.h"

