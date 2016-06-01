#pragma once
#include <memory>
using _STD shared_ptr;
using _STD unique_ptr;
#define interface struct
#define PURE = 0
namespace Disassembler
{
	interface Interface
	{
		virtual ~Interface() = default;
	};
}  // namespace Disassembler
