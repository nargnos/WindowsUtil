#pragma once
#include "InterfaceDefine.h"
#include <sstream>
namespace Disassembler
{
	interface IInstruction :public Interface
	{
		virtual void ToString(_STD ostringstream&) const PURE;
	};
	
}  // namespace Disassembler
