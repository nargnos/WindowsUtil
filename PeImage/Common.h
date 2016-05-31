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

#include <boost\iterator_adaptors.hpp>
using boost::iterator_facade;
using boost::random_access_traversal_tag;
using boost::iterator_core_access;
using boost::forward_traversal_tag;
using boost::bidirectional_traversal_tag;

#define ALIGN_UP(value, alignment) (((UINT)value + (UINT)alignment - 1)& ~((UINT)alignment - 1))