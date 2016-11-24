#pragma once
#include <cassert>
#include <Windows.h>

#include <WinBase.h>
#include <WinTrust.h>

#include <algorithm>
#include <memory>
#include <vector>
#include <delayimp.h>

using std::unique_ptr;
using std::make_unique;
using std::vector;

#define ALIGN_UP(value, alignment) (((UINT)value + (UINT)alignment - 1)& ~((UINT)alignment - 1))