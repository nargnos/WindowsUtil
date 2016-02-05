#pragma once
#include <assert.h>
#include <memory>
using _STD shared_ptr;
using _STD unique_ptr;
using _STD make_shared;
using _STD make_unique;
using _STD static_pointer_cast;
using _STD dynamic_pointer_cast;
#include "State.h"
#include "IStateFactory.h"
#include "Instruction.h"
#include "OpcodeReader.h"
